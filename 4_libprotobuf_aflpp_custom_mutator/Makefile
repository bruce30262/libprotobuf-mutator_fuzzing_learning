TARGET=lpm_aflpp_custom_mutator
CXX=clang++-9
AFLCC=$(HOME)/AFLplusplus/afl-gcc
PB_SRC=test.pb.cc

PROTOBUF_DIR=$(HOME)/libprotobuf-mutator/build/external.protobuf
LPM_DIR=$(HOME)/libprotobuf-mutator
LPM_LIB=$(LPM_DIR)/build/src/libprotobuf-mutator.so
INC=-I$(PROTOBUF_DIR)/include -I$(LPM_DIR)

all: $(TARGET).so

$(TARGET).so: $(TARGET).cc $(PB_SRC)
	$(CXX) -fPIC -c $^ $(INC)
	$(CXX) -shared -Wall -O3 -o $@ *.o $(LPM_LIB)

vuln: vuln.c
	$(AFLCC) -o $@ $^

.PHONY: clean
clean: 
	rm *.so *.o vuln
