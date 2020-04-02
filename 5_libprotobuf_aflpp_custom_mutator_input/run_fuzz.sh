#!/usr/bin/env sh

LD_LIBRARY_PATH=/usr/local/lib/ \ # for libprotobuf-mutator-libfuzzer.so.0 and libprotobuf-mutator.so.0
AFL_DISABLE_TRIM=1 \
AFL_CUSTOM_MUTATOR_ONLY=1 \
AFL_CUSTOM_MUTATOR_LIBRARY=$HOME/libprotobuf-mutator_fuzzing_learning/5_libprotobuf_aflpp_custom_mutator_input/lpm_aflpp_custom_mutator_input.so \
AFL_SKIP_CPUFREQ=1 \
$HOME/AFLplusplus/afl-fuzz -i ./in -o ./out ./vuln

