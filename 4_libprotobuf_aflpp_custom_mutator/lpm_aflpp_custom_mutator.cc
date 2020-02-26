#include "lpm_aflpp_custom_mutator.h"

using std::cin;
using std::cout;
using std::endl;

std::string ProtoToData(const TEST &test_proto) {
    std::stringstream all;
    const auto &aa = test_proto.a();
    const auto &bb = test_proto.b();
    all.write((const char*)&aa, sizeof(aa));
    if(bb.size() != 0) {
        all.write(bb.c_str(), bb.size());
    }

    std::string res = all.str();
    if (bb.size() != 0 && res.size() != 0) {
        // set PROTO_FUZZER_DUMP_PATH env to dump the serialized protobuf
        if (const char *dump_path = getenv("PROTO_FUZZER_DUMP_PATH")) {
            std::ofstream of(dump_path);
            of.write(res.data(), res.size());
        }
    }
    return res;
}

extern "C" size_t afl_custom_mutator(uint8_t *data, size_t size, uint8_t *mutated_out, size_t max_size, unsigned int seed) {
    static MyMutator mutator;
    using protobuf_mutator::ParseTextMessage;
    TEST input;

    // For libprotobuf, it's best for input data to be a TEST message text (e.g. a: 100\nb: "fff")

    srand(seed);
    int id = rand() % 305;
    input.set_a(id);
    std::string tmp = "";
    std::string new_string = mutator.MutateString(tmp, 1000); // use the default protobuf mutator
    input.set_b(new_string);
    const TEST *p = &input;
    std::string s = ProtoToData(*p); // convert TEST to raw data
    memcpy(mutated_out, s.c_str(), s.size()); // copy data to output buffer

    return s.size();
}
