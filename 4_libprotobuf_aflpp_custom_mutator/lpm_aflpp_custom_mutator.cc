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

/*
 * This method is called when AFL++ starts up and is used to seed RNG. ( optional )
 */
extern "C" void afl_custom_init(unsigned int seed) {
    srand(seed);
}

/**
 * Perform custom mutations on a given input
 *
 * (Optional for now. Required in the future)
 *
 * @param[in] buf Input data to be mutated
 * @param[in] buf_size Size of input data
 * @param[in] add_buf Buffer containing the additional test case
 * @param[in] add_buf_size Size of the additional test case
 * @param[out] mutated_out Buffer to store the mutated input
 * @param[in] max_size Maximum size of the mutated output. The mutation must not
 *     produce data larger than max_size.
 * @return Size of the mutated output.
 */
extern "C" size_t afl_custom_fuzz(uint8_t *buf, size_t buf_size, uint8_t *add_buf,size_t add_buf_size, uint8_t *mutated_out, size_t max_size) {
    // This function can be named either "afl_custom_fuzz" or "afl_custom_mutator"
    // A simple test shows that "buf" will be the content of the current test case
    // "add_buf" will be the next test case ( from AFL++'s input queue )

    // Here we implement our own custom mutator
    static MyMutator mutator;
    TEST input;
    // mutate input.a ( integer )
    int id = rand() % 305;
    input.set_a(id);
    // mutate input.b ( string )
    std::string tmp = "";
    std::string new_string = mutator.MutateString(tmp, 1000); // use the default protobuf mutator
    input.set_b(new_string);
    // convert input from TEST to raw data, and copy to mutated_out
    const TEST *p = &input;
    std::string s = ProtoToData(*p); // convert TEST to raw data
    size_t copy_size = s.size() <= max_size ? s.size() : max_size; // check if raw data's size is larger than max_size
    memcpy(mutated_out, s.c_str(), copy_size); // copy the mutated data

    return copy_size;
}
