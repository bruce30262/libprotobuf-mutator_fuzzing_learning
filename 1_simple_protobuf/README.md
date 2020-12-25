# Simple protobuf example

* Create a simple protobuf message structure  

```
syntax = "proto2";

message TEST {
  required uint32 a = 1;
  required string b = 2;
}
```

* Compile the protobuf  

```
mkdir genfiles  
protoc ./test.proto --cpp_out=./genfiles
```

`protoc` can be found in `libprotobuf-mutator/build/external.protobuf/bin/`  

This will create `test.pb.cc` and `test.pb.h` in the genfiles directory  

* Write a simple protobuf testing program  

```cpp
#include "test.pb.h"

#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    TEST t;
    t.set_a(101);
    t.set_b("testtest");
    cout << t.a() << endl;
    cout << t.b() << endl;   
    return 0;
} 
```

* Compile the program & test it

```makefile
CXX=clang++-11
PB_SRC=test.pb.cc

PROTOBUF_DIR=$(HOME)/libprotobuf-mutator/build/external.protobuf
PROTOBUF_LIB=$(PROTOBUF_DIR)/lib/libprotobufd.a
INC=-I$(PROTOBUF_DIR)/include

test_proto: test_proto.cc $(PB_SRC)
	$(CXX) -o $@ $^ $(PROTOBUF_LIB) $(INC)

.PHONY: clean
clean: 
	rm test_proto
```

You might have to replace `PROTOBUF_DIR` with your own protobuf installation directory ( Will be `libprotobuf-mutator/build/external.protobuf` if you follow the installation instructions in libprotobuf-mutator's readme file )  

Compile the program with `make` and test it with `./test_proto`, it should print out the member data of the `TEST` protobuf ( `101` and `testtest` )

## Reference  
* [Protocol Buffer Basics: C++](https://developers.google.com/protocol-buffers/docs/cpptutorial)

