# Simple HTTP Socket Server in C/C++

This is a simple HTTP server that server a index.html to the client.

## Requirements

- Unix Based System
- GCC C Compiler
- Web Browser

## How to run the example

1 - After cloning the repository open your terminal and compile the server files

```shell
gcc server.c -o ./build/server
```

this will compile the file to the build folder

2- Run the server

```shell
./build/server
```

3 - Open the browser and go to `localhost:8080`, it should return something on the page

4 - That's it!
