# Combine libprotobuf-mutator with libfuzzer ( custom mutator )

* `lpm_libfuzz_custom_mutator.cc`: Convert protobuf to raw data and feed it to the target function  
    - Also register post processor with our custom mutator method
* `harness.cc`: Our target function  

## Makefile

* Modify `PROTOBUF_DIR` to your own protobuf installation path  
* Modify `LPM_DIR` to the root direcotry of libprotobuf-mutator  
* Use `-DLLVMFuzzerTestOneInput=XXX` to set the target fuzzing function name

## Test the program  

* `make` && `./lpm_libfuzz_custom_mutator`
* It should generate a crash sample immediately  
    * The sample contains the crash data in protobuf format  
    * Set the `PROTO_FUZZER_DUMP_PATH` env to generate the crash sample in raw format  
    * `test.b` should always be "FUCK" in the crash sample

