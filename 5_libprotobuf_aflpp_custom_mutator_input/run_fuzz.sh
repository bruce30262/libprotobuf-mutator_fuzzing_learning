#!/usr/bin/env sh

AFL_DISABLE_TRIM=1 \
AFL_CUSTOM_MUTATOR_ONLY=1 \
AFL_CUSTOM_MUTATOR_LIBRARY=$HOME/libprotobuf-mutator_fuzzing_learning/5_libprotobuf_aflpp_custom_mutator_input/lpm_aflpp_custom_mutator_input.so \
AFL_SKIP_CPUFREQ=1 \
$HOME/AFLplusplus/afl-fuzz -i ./in -o ./out ./vuln

