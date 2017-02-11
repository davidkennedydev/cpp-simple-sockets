CXX=clang++
DEBUG=-g -D_GLIBCXX_DEBUG
FLAGS=-std=c++1z -lboost_system -lpthread

all: bin/output_client bin/input_client

bin:
	mkdir -p $@

bin/output_client: output_client.cpp | bin
	$(CXX) $(FLAGS) $^ -o $@

bin/input_client: input_client.cpp | bin
	$(CXX) $(FLAGS) $^ -o $@

test: bin/output_client bin/input_client
	./bin/output_client
	./bin/input_client

clean: bin
	-rm -rf $^
	
