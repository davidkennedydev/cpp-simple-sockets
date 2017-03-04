FROM ubuntu:14.04

WORKDIR /app

RUN apt-get update 

# Install build tools
RUN apt-get install -y \
	clang++-3.8 \
	g++ \
	make; \
	cd /usr/bin && ln -s clang++-3.8 clang++ # Configure clang++ alias

# Install dependencies
RUN apt-get install -y \
	libstdc++6 \
	libpthread-stubs0-dev \
	libboost-dev \
	libboost-system-dev

ADD . /app

# Build and run tests
CMD cd ./test/SocketBuffer; echo "Build and runing tests..."; make test; echo "Done."
