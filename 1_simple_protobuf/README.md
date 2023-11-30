# Simple protobuf example

* Create a simple protobuf message structure ( `test.proto` ): 

```
syntax = "proto2";

message TEST {
  required uint32 a = 1;
  required string b = 2;
}
```

* Use `make proto` to compile the protobuf. **Make sure there's a `protoc` binary in `libprotobuf-mutator/build/external.protobuf/bin/` before compiling**.
    - This will create a directory `genfiles` and generate `test.pb.cc` & `test.pb.h` inside the directory.

* Write a simple protobuf testing program:  

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

* Use `make` to compile the program.

In `Makefile`, you might have to replace `PROTOBUF_DIR` with your own protobuf installation directory ( `libprotobuf-mutator/build/external.protobuf` if you follow the installation instructions in libprotobuf-mutator's README file ).  

* Test it with `./test_proto`, it should print out the member data of the `TEST` protobuf ( `101` and `testtest` ).

## Reference  
* [Protocol Buffer Basics: C++](https://developers.google.com/protocol-buffers/docs/cpptutorial)

