CXX ?= g++
DEBUG = -g -D_GLIBCXX_DEBUG
GCOV_FLAGS = -coverage
FLAGS = -std=c++1y
LLVM_STANDARD_lIBRARIES = -stdlib=libc++
LIBRARIES = -lboost_system -pthread 

ifeq ($(CXX), g++)
	FLAGS += $(GCOV_FLAGS)
endif
ifeq ($(CXX), clang++)
	LIBRARIES += $(LLVM_STANDARD_lIBRARIES)	
endif

BIN_PATH = bin

DRIVERS = output_client.cpp input_client.cpp
RUNABLE = $(%.cpp:bin/%)

all: $(RUNABLE)


$(BIN_PATH):
	mkdir -p $@

bin/%: %.cpp | bin
	$(CXX) $(FLAGS) $^ -o $@ $(LIBRARIES)

test: bin/output_client bin/input_client
	./bin/output_client
	./bin/input_client
ifeq ($(CXX), g++)
	gcov -r $(DRIVERS)
endif

clean:
	-@rm -rf $(BIN_PATH) 2> /dev/null || true
	-@rm *.gcno 2> /dev/null || true
	-@rm *.gcda 2> /dev/null || true
	-@rm *.gcov 2> /dev/null || true
	
