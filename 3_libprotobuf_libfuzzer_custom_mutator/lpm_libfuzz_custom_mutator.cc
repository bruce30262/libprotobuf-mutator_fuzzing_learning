#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "test.pb.h"

#include <bits/stdc++.h>

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

extern "C" int FuzzTEST(const uint8_t* data, size_t size); // our customized fuzzing function
bool hasRegister = false;

DEFINE_PROTO_FUZZER(const TEST &test_proto) {
    /* Register post processor with our custom mutator method */
    if(!hasRegister) {
        protobuf_mutator::libfuzzer::RegisterPostProcessor(
                TEST::descriptor(),
                [](google::protobuf::Message* message, unsigned int seed) {
                    TEST *t = static_cast<TEST *>(message);
                    /* test.b will only be "FUCK" or "SHIT" */
                    if (seed % 2) {
                        t->set_b("FUCK");
                    }
                    else {
                        t->set_b("SHIT");
                    }
                }
            );
        hasRegister = true; 
        return;
    }

    auto s = ProtoToData(test_proto);
    FuzzTEST((const uint8_t*)s.data(), s.size());
}
