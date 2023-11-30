#include "libprotobuf-mutator/src/mutator.h"
#include "test.pb.h"

#include <bits/stdc++.h>

class MyMutator : public protobuf_mutator::Mutator {
};

/**
custom_mutator state structure
Reference: https://github.com/airbus-seclab/AFLplusplus-blogpost/blob/b0cfc7016bd60cf998969d79a78eabd8471c78eb/src/mutator/custom_mutator.cpp#L29
*/
typedef struct custom_mutator {
    MyMutator *mutator;
    unsigned int seed;
    uint8_t *mutated_out_buf;
    size_t mutated_out_buf_size;
} custom_mutator_t;

uint8_t dummy[10] = {}; // dummy buffer 
