#!/usr/bin/env sh

LD_LIBRARY_PATH=/usr/local/lib/ \ # for libprotobuf-mutator-libfuzzer.so.0 and libprotobuf-mutator.so.0
AFL_CUSTOM_MUTATOR_ONLY=1 \
AFL_CUSTOM_MUTATOR_LIBRARY=$HOME/libprotobuf-mutator_fuzzing_learning/4_libprotobuf_aflpp_custom_mutator/lpm_aflpp_custom_mutator.so \
AFL_SKIP_CPUFREQ=1 \
$HOME/AFLplusplus/afl-fuzz -i ./in -o ./out ./vuln

