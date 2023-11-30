TARGET=lpm_aflpp_custom_mutator
PB_SRC_DIR=../1_simple_protobuf/genfiles
PB_SRC=$(PB_SRC_DIR)/test.pb.cc

CXX=clang++-14
CXXFLAGS=-I$(PB_SRC_DIR)

AFLCC=$(HOME)/AFLplusplus/afl-gcc

PROTOBUF_DIR=$(HOME)/libprotobuf-mutator/build/external.protobuf
LPM_DIR=$(HOME)/libprotobuf-mutator
LPM_LIB=$(LPM_DIR)/build/src/libprotobuf-mutator.so
INC=-I$(PROTOBUF_DIR)/include -I$(LPM_DIR)

all: $(TARGET).so

$(TARGET).so: $(TARGET).cc $(PB_SRC)
	$(CXX) $(CXXFLAGS) -fPIC -c $^ $(INC)
	$(CXX) -shared -Wall -O3 -o $@ *.o $(LPM_LIB)

vuln: vuln.c
	$(AFLCC) -o $@ $^

.PHONY: clean
clean: 
	rm *.so *.o vuln
