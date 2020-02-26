#include "libprotobuf-mutator/src/text_format.h"
#include "libprotobuf-mutator/src/mutator.h"
#include "test.pb.h"

#include <bits/stdc++.h>

extern "C" size_t afl_custom_mutator(uint8_t *data, size_t size, uint8_t *mutated_out, size_t max_size, unsigned int seed);

class MyMutator : public protobuf_mutator::Mutator {
    public:
        friend size_t afl_custom_mutator(uint8_t *data, size_t size, uint8_t *mutated_out, size_t max_size, unsigned int seed);
};
