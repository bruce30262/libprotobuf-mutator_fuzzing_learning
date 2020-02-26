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

DEFINE_PROTO_FUZZER(const TEST &test_proto) {
    auto s = ProtoToData(test_proto); // convert protobuf to raw data
    FuzzTEST((const uint8_t*)s.data(), s.size()); // fuzz the function
}
