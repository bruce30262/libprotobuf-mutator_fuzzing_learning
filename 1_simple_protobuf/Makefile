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
