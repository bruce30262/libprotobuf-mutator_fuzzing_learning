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

/**
 * Initialize this custom mutator
 *
 * @param[in] afl a pointer to the internal state object. Can be ignored for
 * now.
 * @param[in] seed A seed for this mutator - the same seed should always mutate
 * in the same way.
 * @return Pointer to the data object this custom mutator instance should use.
 *         There may be multiple instances of this mutator in one afl-fuzz run!
 *         Return NULL on error.
 */
extern "C" void *afl_custom_init(void *afl, unsigned int seed) {
    srand(seed);
    return afl;
}

/**
 * Perform custom mutations on a given input
 *
 * @param[in] data pointer returned in afl_custom_init for this fuzz case
 * @param[in] buf Pointer to input data to be mutated
 * @param[in] buf_size Size of input data
 * @param[out] out_buf the buffer we will work on. we can reuse *buf. NULL on
 * error.
 * @param[in] add_buf Buffer containing the additional test case
 * @param[in] add_buf_size Size of the additional test case
 * @param[in] max_size Maximum size of the mutated output. The mutation must not
 *     produce data larger than max_size.
 * @return Size of the mutated output.
 */
extern "C" size_t afl_custom_fuzz(void *data, // afl state
                       uint8_t *buf, size_t buf_size, // input data to be mutated
                       uint8_t **out_buf, // output buffer
                       uint8_t *add_buf, size_t add_buf_size,  // add_buf can be NULL
                       size_t max_size) {

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
    // Copy the raw data to output buffer
    size_t mutated_size = s.size() <= max_size ? s.size() : max_size; // check if raw data's size is larger than max_size
    uint8_t *mutated_out = new uint8_t[mutated_size+1];
    memcpy(mutated_out, s.c_str(), mutated_size);
    *out_buf = mutated_out;

    return mutated_size;
}

/**
 * Deinitialize everything
 *
 * @param data The data ptr from afl_custom_init
 */
extern "C" void afl_custom_deinit(void *data) {
    // Honestly I don't know what I'm gonna do with this...
    return;
}

