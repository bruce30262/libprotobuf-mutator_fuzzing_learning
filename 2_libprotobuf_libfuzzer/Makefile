TARGET=lpm_libfuzz
CXX=clang++-9
CXXFLAGS=-g -fsanitize=fuzzer,address
PB_SRC=test.pb.cc

PROTOBUF_DIR=$(HOME)/libprotobuf-mutator/build/external.protobuf
LPM_DIR=$(HOME)/libprotobuf-mutator
PROTOBUF_LIB=$(PROTOBUF_DIR)/lib/libprotobufd.a
LPM_LIB=$(LPM_DIR)/build/src/libfuzzer/libprotobuf-mutator-libfuzzer.a $(LPM_DIR)/build/src/libprotobuf-mutator.a
INC=-I$(PROTOBUF_DIR)/include -I$(LPM_DIR)
DFUZZ=-DLLVMFuzzerTestOneInput=FuzzTEST

all: $(TARGET)

# for testing libprotobuf + libfuzzer
# compile harness first
# then link lpm_libfuzz with harness.o & static libraries
harness.o: harness.cc
	$(CXX) $(CXXFLAGS) -c $(DFUZZ) $<

$(TARGET): harness.o $(TARGET).cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(PB_SRC) $(LPM_LIB) $(PROTOBUF_LIB) $(INC) # $(LPM_LIB) must be placed before $(PROTOBUF_LIB)

.PHONY: clean
clean: 
	rm $(TARGET) *.o
