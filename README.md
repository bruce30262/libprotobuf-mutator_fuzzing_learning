# libprotobuf-mutator_fuzzing_learning
Learn how to combine libprotobuf-mutator with libfuzzer &amp; AFL++  

## Environment Settings 
* Ubuntu Linux 18.04 64 bit  
* Clang 9.0.0  

### Install Clang/LLVM & libfuzzer  
* Follow the step in [this article](https://linuxhint.com/install-llvm-ubuntu/) and add the toolchain's apt repository in Ubuntu.  
* `sudo apt-get install clang-9 libfuzzer-9-dev`  

### Install libprotobuf-mutator  
Follow the step in [libprotobuf-mutator's readme](https://github.com/google/libprotobuf-mutator/blob/master/README.md)  

#### Install dependencies
```shell
sudo apt-get update
sudo apt-get install protobuf-compiler libprotobuf-dev binutils cmake \
  ninja-build liblzma-dev libz-dev pkg-config autoconf libtool
```

#### Compile and test everything:

```shell
cd libprotobuf-mutator
mkdir build
cd build
cmake .. -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON
ninja check # test
ninja # build
sudo ninja install # install
```
> **Notice**  
> Use the following cmake command to build `libprotobuf-mutator-libfuzzer.so.0` and `libprotobuf-mutator.so.0` shared library

```shell
 cmake .. -GNinja -DCMAKE_C_COMPILER=clang-9 -DCMAKE_CXX_COMPILER=clang++-9 -DCMAKE_BUILD_TYPE=Debug -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON -DBUILD_SHARED_LIBS=ON
```

## Learning  
* [Simple protobuf example](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/1_simple_protobuf)  
* [libprotobuf + libfuzzer](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/2_libprotobuf_libfuzzer)  
* [libprotobuf + libfuzzer ( custom mutator )](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/3_libprotobuf_libfuzzer_custom_mutator)  
* [How to combine libprotobuf-mutator and AFL++](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/4_libprotobuf_aflpp_custom_mutator)

## Reference  
* [libprotobuf-mutator](https://github.com/google/libprotobuf-mutator)  
* [Deconstructing LibProtobuf/Mutator Fuzzing](https://bshastry.github.io/2019/01/18/Deconstructing-LPM.html)  
* [Custom Proto Mutation](https://bshastry.github.io/2019/12/27/Custom-Proto-Mutation.html)  
* [AFL++ custom mutator](https://github.com/vanhauser-thc/AFLplusplus/blob/master/docs/custom_mutator.md)

