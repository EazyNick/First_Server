# First_Server Project

This repository contains a basic server application implemented in C++ using the Boost Asio library. It demonstrates setting up a TCP server that accepts connections from clients and responds with a simple message.

## Project Structure

- `First_Server.sln` : Solution file for Visual Studio.
- `First_Server.cpp`: Main entry for a basic TCP server.
- `Server.cpp`: An extended server example with asynchronous read and write capabilities, utilizing Boost Asio's asynchronous features.

## Requirements

- **Boost Library**: This project requires the Boost Asio library for networking functionalities. Ensure you have Boost installed on your system.
- **C++17**: The code utilizes modern C++17 features, so it requires a compatible compiler (e.g., GCC, Clang, or MSVC).
- **Visual Studio**: This project is configured with Visual Studio 17.8, but can be built with other C++ IDEs with minor adjustments.

## Features

### First_Server.cpp

The `First_Server.cpp` file contains a basic TCP server setup:
- **Port Number**: The server listens on port `12333`.
- **Synchronous Operation**: The server uses synchronous read and write operations for simplicity.
- **Client Interaction**: When a client connects, the server reads data sent by the client and responds with a message, "Hello, client! 한글돼!", demonstrating UTF-8 support.
- **Error Handling**: It includes basic error handling and logs errors to the console.

### Server.cpp

The `Server.cpp` file demonstrates an advanced TCP server with asynchronous handling:
- **Port Number**: Listens on port `51236`.
- **Asynchronous Operation**: Uses asynchronous `read` and `write` operations to handle multiple client connections concurrently.
- **Session Management**: Each client connection is managed by a `session` class, allowing the server to handle multiple clients simultaneously.
- **I/O Event Loop**: The `io_service.run()` function manages asynchronous events, providing a non-blocking event loop.

## Usage

### Compiling the Project

To compile and run this project, ensure that you have the Boost library installed and set up in your development environment.

#### Using Visual Studio

1. Open `First_Server.sln` in Visual Studio.
2. Choose the build configuration (`Debug` or `Release`).
3. Build and run the solution.

#### Using Command Line (Linux / MacOS)

1. Install Boost libraries if not installed:
    ```bash
    sudo apt-get install libboost-all-dev
    ```
2. Compile the project:
    ```bash
    g++ -o First_Server First_Server.cpp -lboost_system -lpthread
    g++ -o Async_Server Server.cpp -lboost_system -lpthread
    ```
3. Run the executables:
    ```bash
    ./First_Server
    ./Async_Server
    ```

### Running the Server

1. After starting the server, it listens on the designated port (12333 for `First_Server`, 51236 for `Server`).
2. Connect a client (such as `telnet` or a custom client script) to the server using:
    ```bash
    telnet localhost 12333
    ```
   or for the asynchronous server:
    ```bash
    telnet localhost 51236
    ```

3. The server will respond with a welcome message and print any data received from the client.

## Code Overview

### First_Server.cpp Code Highlights

- **Boost Asio TCP Acceptor**: Sets up a TCP connection on port 12333.
- **Data Handling**: Reads data sent by the client in a synchronous manner and sends a "Hello, client!" message back.
- **Error Management**: Any error encountered during reading or writing is thrown and handled with an exception message.

### Server.cpp Code Highlights

- **Session Class**: Manages individual client sessions, allowing asynchronous read and write.
- **Async Accept and IO Handling**: Uses async handlers to continuously accept and manage incoming connections.
- **Thread Safety**: Utilizes `shared_from_this` to safely handle asynchronous operations.

## Troubleshooting

- **Boost Library Issues**: Ensure Boost is correctly installed and linked. Common issues arise if the linker does not find Boost Asio or if incompatible Boost versions are used.
- **Port Conflicts**: If the port is in use, modify the port number in the code or free the port.
- **Permissions**: On some systems, binding to a port may require elevated privileges. Run with `sudo` if necessary.

## License

This project is open-source and licensed under the MIT License.

## Acknowledgments

- Boost Asio documentation and examples provided guidance on implementing asynchronous server features.
- UTF-8 encoding handled to ensure message readability for international characters.
