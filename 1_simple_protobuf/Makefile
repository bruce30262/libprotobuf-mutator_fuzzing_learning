CXX=clang++-14
PB_SRC_DIR=./genfiles
PB_SRC=$(PB_SRC_DIR)/test.pb.cc

PROTOBUF_DIR=$(HOME)/libprotobuf-mutator/build/external.protobuf
PROTOC=$(PROTOBUF_DIR)/bin/protoc
PROTOBUF_LIB=$(PROTOBUF_DIR)/lib/libprotobufd.a
INC=-I$(PROTOBUF_DIR)/include

all: proto test_proto

proto: test.proto
	mkdir -p $(PB_SRC_DIR)  
	$(PROTOC) $^ --cpp_out=$(PB_SRC_DIR)

test_proto: test_proto.cc $(PB_SRC)
	$(CXX) -I$(PB_SRC_DIR) -o $@ $^ $(PROTOBUF_LIB) $(INC)

.PHONY: clean
clean: 
	rm -rf test_proto $(PB_SRC_DIR)
