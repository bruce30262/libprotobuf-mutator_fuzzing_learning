> **2020/04/03 update**:  
> It is recommended that reader learn how to combine libprotobuf-mutator and AFL++ with [5_libprotobuf_aflpp_custom_mutator_input](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/5_libprotobuf_aflpp_custom_mutator_input). It provides more details and informations about how to handle input in the custom mutator.

# Combine libprotobuf-mutator with AFL++
* `lpm_aflpp_custom_mutator.cc`: Shared library for AFL++  
    - Custom mutate `TEST` protobuf.  
        + In fact it just randomly generate a brand new `TEST` protobuf message.  
    - Convert the protobuf to raw data and return the result to AFL++.
* `lpm_aflpp_custom_mutator.h`: Declare `afl_custom_fuzz` as a friend function so it can use protobuf's mutators.  
* `vuln.c`: Vulnerable C program.  

## Makefile
* Modify `PROTOBUF_DIR` to your own protobuf installation path.  
* Modify `LPM_DIR` to the root direcotry of libprotobuf-mutator.  
* Modify `AFLCC` to the path of an AFL++'s compiler.  

## Test the program  
This example uses the shared library of `libprotobuf-mutator`. Make sure you have `libprotobuf-mutator.so` compiled. You can refer to the [README](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/blob/master/README.md) in this repo to learn how to compile the shared library.

* `make`
    - This will create `lpm_aflpp_custom_mutator.so`, the shared library for AFL++ ( for custom mutator's usage ).  
* `make vuln` to create the vulnerable binary.  
* `run_fuzz.sh`  
    - Modify the path of `afl-fuzz` before you run the script.  
    - Make sure `LD_LIBRARY_PATH` is set to the path that contains the `libprotobuf-mutator.so` library.  
    - `AFL_CUSTOM_MUTATOR_ONLY=1` is optional. However this is recommended since we want to observe the mutation performance ( = how well it generate a sample that crashes the program ) of our custom mutator.  
* It should generate the crash samples immediately  
    - Check `out/crashes/id:000xxxxx.........`.  
    - The first byte of the crash sample should be `0xe8` or `0x02`.
