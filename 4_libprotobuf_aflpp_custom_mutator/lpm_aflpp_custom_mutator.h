#include "libprotobuf-mutator/src/mutator.h"
#include "test.pb.h"

#include <bits/stdc++.h>

extern "C" size_t afl_custom_fuzz(void *data, uint8_t *buf, size_t buf_size, uint8_t **out_buf, uint8_t *add_buf, size_t add_buf_size, size_t max_size); 

class MyMutator : public protobuf_mutator::Mutator {
    public:
        friend size_t afl_custom_fuzz(void *data, uint8_t *buf, size_t buf_size, uint8_t **out_buf, uint8_t *add_buf, size_t add_buf_size, size_t max_size); 
};
