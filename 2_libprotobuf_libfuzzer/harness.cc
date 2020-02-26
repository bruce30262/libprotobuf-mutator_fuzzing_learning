#include <stdint.h>
#include <stddef.h>

extern "C" int FuzzTEST(const uint8_t *data, size_t size) {
    if(data[0] == '\x01') {
        __builtin_trap();
    }
    return 0;
}
