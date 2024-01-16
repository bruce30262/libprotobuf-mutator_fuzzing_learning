# libprotobuf-mutator_fuzzing_learning
Learn how to combine libprotobuf-mutator with libfuzzer &amp; AFL++  

## Environment Settings 
* Ubuntu Linux 22.04 64 bit  
* Clang 14.0.0
* libprotobuf-mutator 3.21.7 [(af3bb1)](https://github.com/google/libprotobuf-mutator/tree/af3bb18749db3559dc4968dd85319d05168d4b5e)
    - As of 2023/12/01, this repo won't work with the latest libprotobuf-mutator. It is recommended to switch to commit `af3bb1` before compile & installing the libraries ( [reference](https://github.com/google/libprotobuf-mutator/issues/223) ).
* AFL++ 4.09a [(61e27c)](https://github.com/AFLplusplus/AFLplusplus/tree/61e27c6b54f7641a168b6acc6ecffb1754c10918)    

### Install Clang/LLVM & libfuzzer  
* Follow the step in [this article](https://linuxhint.com/install-llvm-ubuntu/) and add the toolchain's apt repository in Ubuntu.  
* `sudo apt-get install clang-14 libfuzzer-14-dev`  

### Install libprotobuf-mutator  
Follow the step in [libprotobuf-mutator's readme](https://github.com/google/libprotobuf-mutator/blob/master/README.md)  

#### Install dependencies
```shell
sudo apt-get update
sudo apt-get install protobuf-compiler libprotobuf-dev binutils cmake \
  ninja-build liblzma-dev libz-dev pkg-config autoconf libtool
```

#### Build the required libraries

```shell
cd libprotobuf-mutator
mkdir build
cd build
( A cmake command, check the below section )
ninja # build the libraries
sudo ninja install # install the libraries
```
About `cmake` command :  
* Use the following cmake command to build `libprotobuf-mutator-libfuzzer.so.0` and `libprotobuf-mutator.so.0` shared library :

```shell
 cmake .. -GNinja -DCMAKE_C_COMPILER=clang-14 \ 
 -DCMAKE_CXX_COMPILER=clang++-14 \ 
 -DCMAKE_BUILD_TYPE=Debug \ 
 -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON \ 
 -DBUILD_SHARED_LIBS=ON
```

* To build static libraries, use the following `cmake` command ( **this will generate libraries that can be linked into shared libraries / normal program** ) :  

```shell
cmake .. -GNinja -DCMAKE_C_COMPILER=clang-14 \
-DCMAKE_CXX_COMPILER=clang++-14 \
-DCMAKE_BUILD_TYPE=Debug \
-DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON \
-DCMAKE_C_FLAGS="-fPIC" -DCMAKE_CXX_FLAGS="-fPIC"
```

After building successfully, you can go to the `build` directory, and use the following command to check if the library is built correctly :  
```shell
# Check if libprotobuf-mutator.so.0 exist
# To check other libraries just change the library name
find . | grep "libprotobuf-mutator.so.0"
```

## How to upgrade the environment  
* Upgrade Clang/LLVM & libfuzzer ( install a new version ) 
* Upgrade AFL++ ( git pull & rebuild )  
* Upgrade libprotobuf-mutator ( git pull & rebuild )  
    - Rebuild and re-install `libprotobuf-mutator-libfuzzer.so.0` and `libprotobuf-mutator.so.0`.  
    - Rebuild `libprotobuf-mutator-libfuzzer.a` and `libprotobuf-mutator.a`.  
* **Re-compile the protobuf with newer `protoc` and replace those `*.cc` & `*.h` with new ones.**

## FAQ  
Q : I ran into this error message while building the binary : `This file was generated by an old version of protoc.`  
A : If your protoc's version is newer, make sure to re-generate `test.pb.cc` and `test.pb.h`  with the original protobuf source code `test.proto` ( source code and steps to generate `*.cc` & `*.h` are all in [1_simple_protobuf](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/1_simple_protobuf) ).

## Learning  
* [Simple protobuf example](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/1_simple_protobuf)  
* [libprotobuf + libfuzzer](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/2_libprotobuf_libfuzzer)  
* [libprotobuf + libfuzzer ( custom mutator )](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/3_libprotobuf_libfuzzer_custom_mutator)  
* [How to combine libprotobuf-mutator and AFL++](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/4_libprotobuf_aflpp_custom_mutator)  
* [Handling input samples from AFL++ in custom mutator](https://github.com/bruce30262/libprotobuf-mutator_fuzzing_learning/tree/master/5_libprotobuf_aflpp_custom_mutator_input)

## Reference  
* [libprotobuf-mutator](https://github.com/google/libprotobuf-mutator)  
* [Deconstructing LibProtobuf/Mutator Fuzzing](https://bshastry.github.io/2019/01/18/Deconstructing-LPM.html)  
* [Custom Proto Mutation](https://bshastry.github.io/2019/12/27/Custom-Proto-Mutation.html)  
* [AFL++ custom mutator](https://github.com/vanhauser-thc/AFLplusplus/blob/master/docs/custom_mutators.md)  
* [afl-libprotobuf-mutator](https://github.com/thebabush/afl-libprotobuf-mutator/)
* [Advanced binary fuzzing using AFL++-QEMU and libprotobuf: a practical case of grammar-aware in-memory persistent fuzzing](https://airbus-seclab.github.io/AFLplusplus-blogpost/)  
  - [ref1](https://github.com/airbus-seclab/AFLplusplus-blogpost/blob/b0cfc7016bd60cf998969d79a78eabd8471c78eb/src/mutator/custom_mutator.cpp)  
  - [ref2](https://github.com/HexHive/Igor/blob/2f22a20ff7e82f6022c99f0a47c69796e4fd999d/IgorFuzz/utils/custom_mutators/custom_mutator_helpers.h#L304)  
  - [ref3](https://github.com/HexHive/Igor/blob/2f22a20ff7e82f6022c99f0a47c69796e4fd999d/IgorFuzz/custom_mutators/honggfuzz/custom_mutator_helpers.h)

## LICENSE  
MIT
