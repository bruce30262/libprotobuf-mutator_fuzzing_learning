
> Notice:  
> AFL++'s custom mutator might be frequently updated. Make sure to check out its [document](https://github.com/vanhauser-thc/AFLplusplus/blob/master/docs/custom_mutators.md) for the latest changes.  
> I'll try my best to follow the latest APIs of its custom mutator.

# Handling input from AFL++ in our custom mutator

## Intro

In the example of [4_libprotobuf_aflpp_custom_mutator](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/4_libprotobuf_aflpp_custom_mutator), you might notice that the custom mutator **doesn't handle the input data at all** -- all it does is randomly generate a new `TEST` protobuf message. This might be inconvenient if we want to fuzz the program with some input samples.  

Here in this example, it'll show you how to process the input data from AFL++, convert it to a `TEST` protobuf and mutate the protobuf with libprotobuf-mutator. It also provide an example of a custom `PostProcessor`, which allow user to process the protobuf message after the mutation.

## Source code
* `lpm_aflpp_custom_mutator_input.cc`: Shared library for AFL++  
    - Parse the input data and convert it to `TEST` protobuf message.
    - Mutate the protobuf with libprotobuf-mutator.
    - Register a `PostProcessor` so we can process the result of the mutation.
        + The mutator in libprotobuf-mutator is kind of simple, we'll have to use a PostProcessor to optimize its mutation, or else it's pretty hard to trigger the crash in our `vuln` program.
    - Convert the protobuf to raw data and return the result to AFL++.
* `lpm_aflpp_custom_mutator.h`: Declare our custom mutator.
* `test_proto_serializer.cc`: A program used for generating the serialized `TEST` protobuf.  
    - In order to convert the input data to `TEST`, the input data **should be serialized first**.
* `vuln.c`: Vulnerable C program.  

## Makefile
* Modify `PROTOBUF_DIR` to your own protobuf installation path.  
* Modify `LPM_DIR` to the root directory of libprotobuf-mutator.  
* Modify `AFLCC` to the path of an AFL++'s compiler.  

## Test the program  

Unlike the one in [4_libprotobuf_aflpp_custom_mutator](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/blob/master/4_libprotobuf_aflpp_custom_mutator/Makefile#L15), the example uses the static library of `libprotobuf-mutator-libfuzzer` and `libprotobuf-mutator`. Make sure these two library is compiled with `-fPIC` flag. You can use the following `cmake` command to enable the option:  

```sh
cmake .. -GNinja -DCMAKE_C_COMPILER=clang-11 \
-DCMAKE_CXX_COMPILER=clang++-11 \
-DCMAKE_BUILD_TYPE=Debug \
-DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON \
-DCMAKE_C_FLAGS="-fPIC" -DCMAKE_CXX_FLAGS="-fPIC"
```

> Reference: [afl-libprotobuf-mutator](https://github.com/thebabush/afl-libprotobuf-mutator/blob/master/build.sh)

* `make`
    - This will create `lpm_aflpp_custom_mutator_input.so`, the shared library for AFL++ ( for custom mutator's usage ).  
* `make vuln` to create the vulnerable binary.  
* `make test_proto_serializer` to create the serializer.  
    - Use this program to generate the input sample in `./in`.  
* `run_fuzz.sh`  
    - Modify the path of `afl-fuzz` before you run the script.  
    - `AFL_DISABLE_TRIM=1` is required, since we don't want AFL++ trim our data before running into our custom mutator.  
    - `AFL_CUSTOM_MUTATOR_ONLY=1` is optional. However this is recommended since we want to observe the mutation performance ( = how well it generate a sample that crashes the program ) of our custom mutator.

* It should generate the crash samples immediately  
    * Check `out/crashes/id:000xxxxx.........`.  
    * The first byte of the crash sample should be `0xe8` or `0x02`.  
    * You can take out the `PostProcessor` to see how "slow" it will generate a crash sample without it.
