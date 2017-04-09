[![Codecov](https://img.shields.io/codecov/c/github/DavidUser/cpp-simple-sockets.svg)](https://codecov.io/gh/DavidUser/cpp-simple-sockets/)

[![Travis](https://img.shields.io/travis/DavidUser/cpp-simple-sockets.svg?maxAge=3600&label=build:%20GCC%205%20|%20C%2b%2b17%20)](https://travis-ci.org/DavidUser/cpp-simple-sockets)
[![Travis](https://img.shields.io/travis/DavidUser/cpp-simple-sockets.svg?maxAge=3600&label=build:%20Clang%203.3%20|%20C%2b%2b17%20)](https://travis-ci.org/DavidUser/cpp-simple-sockets)

# cpp-simple-sockets
An stupid library to use sockets easy. 

## Client-Server
Client-server applications can be **simple** writed like below.

### Client side

```c++
Connection server("localhost", "12345"); // Open a connection with the server.

server << "Hey server, are you here?" << std::endl; 

string response;
server >> response;
```

### Server side

```c++
Connection client(12345); // Waits for client connections on 12345

// Everything bellow will be asynchronously executed to each client connected.
string question;
client >> question;

client << "Hi client. I'm your server." << std::endl;
```


# Current features
* Output buffer to socket asio;
* Input buffer to sockets asio;
* Client socket stream;
* Server socket stream;
* Server socket stream factory;
* Connection behaviour like client side and multiclient server side;

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
* The .travis.yml configure build on [**travis-ci**](https://travis-ci.org/DavidUser/cpp-simple-sockets)


