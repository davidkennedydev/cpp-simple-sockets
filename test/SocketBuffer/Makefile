CXX=clang++
DEBUG=-g -D_GLIBCXX_DEBUG
FLAGS=-std=c++1z -lboost_system -lpthread

all: bin/output_client

bin:
	mkdir -p bin

bin/output_client: output_client.cpp bin
	$(CXX) $(FLAGS) $< -o $@

clean: bin
	-rm -rf $^
	
