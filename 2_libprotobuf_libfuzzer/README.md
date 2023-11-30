# Combine libprotobuf-mutator with libfuzzer

* `lpm_libfuzz.cc`: Convert protobuf to raw data and feed it to the target function
* `harness.cc`: Our target function  

## Makefile
* Modify `PROTOBUF_DIR` to your own protobuf installation path  
* Modify `LPM_DIR` to the root direcotry of libprotobuf-mutator  
* Use `-DLLVMFuzzerTestOneInput=XXX` to set the target fuzzing function name

## Test the program  
* **!! Make sure you compile the protobuf in `1_simple_protobuf` first ( goto `1_simple_protobuf` and `make proto`) !!**.
* `make` && `./lpm_libfuzz`
* It should generate a crash sample immediately  
    * The sample contains the crash data in protobuf format  
    * Set the `PROTO_FUZZER_DUMP_PATH` env to generate the crash sample in raw format

