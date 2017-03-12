[![Travis](https://img.shields.io/travis/DavidUser/cpp-simple-sockets.svg)](https://travis-ci.org/DavidUser/cpp-simple-sockets)
[![Codecov](https://img.shields.io/codecov/c/github/DavidUser/cpp-simple-sockets.svg)](https://codecov.io/gh/DavidUser/cpp-simple-sockets/)

# cpp-simple-sockets
An stupid library to use sockets easy. 

# Current features
* Output buffer to socket asio.
* Input buffer to sockets asio.

## Builds
* This Dockerfile build and test on ubuntu with gcc.
    Build and run that container with command:

    ```
    sudo docker build -t daviduser/cpp-simple-sockets

    sudo docker run --rm -it daviduser/cpp-simple-sockets
    ```
    To run that and get a command line use the docker run command:

    ```
    sudo docker run --rm -it daviduser/cpp-simple-sockets /bin/bash

    ```
* The .travis.yml build a _Ubuntu Trusty_ with _GCC g++ 5_ on *travis-ci*
