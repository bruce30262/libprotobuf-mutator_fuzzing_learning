TARGET=lpm_aflpp_custom_mutator_input
CXX=clang++-9
AFLCC=$(HOME)/AFLplusplus/afl-gcc
PB_SRC=test.pb.cc

PROTOBUF_DIR=$(HOME)/libprotobuf-mutator/build/external.protobuf
PROTOBUF_LIB=$(PROTOBUF_DIR)/lib/libprotobufd.a

LPM_DIR=$(HOME)/libprotobuf-mutator
LPM_LIB=$(LPM_DIR)/build/src/libfuzzer/libprotobuf-mutator-libfuzzer.a $(LPM_DIR)/build/src/libprotobuf-mutator.a

INC=-I$(PROTOBUF_DIR)/include -I$(LPM_DIR)

all: $(TARGET).so

$(TARGET).so: $(TARGET).cc $(PB_SRC)
	$(CXX) -fPIC -c $^ $(INC)
	$(CXX) -shared -Wall -O3 -o $@ *.o $(LPM_LIB) $(PROTOBUF_LIB)

vuln: vuln.c
	$(AFLCC) -o $@ $^

test_proto_serializer: test_proto_serializer.cc $(PB_SRC)
	$(CXX) -o $@ $^ $(PROTOBUF_LIB) $(INC)

.PHONY: clean
clean: 
	rm *.so *.o vuln test_proto_serializer
