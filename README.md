# chat-app-v2

An improved version of my old C# Windows Forms chat application, rewritten in **C++** with a **Node.js CLI client** to focus on networking, concurrency, and system-level programming.

---

## Project Overview

This is a **multi-client chat application** with:

- **C++ Server** using Linux system calls (socket, bind, listen, accept, send, recv)  
- **Node.js CLI Client** using raw TCP (`net` module)  
- **Custom protocol**: `[COMMAND] [LENGTH] [BODY]`  
- **Multi-threaded server** handling multiple clients concurrently  
- **Thread-safe broadcast messaging**  
- **Simple authentication** and **logging**  
- **Clean modular architecture**  

This project demonstrates **OS-level programming**, **networking**, **concurrency**, and **cross-language communication**.  

---

## Features

- Multi-client support
- LOGIN / SEND / LOGOUT commands
- Broadcast messages to all connected clients
- Thread-safe handling of shared resources
- Logs all events with timestamps
- CLI-based Node.js client

---

## Getting Started

### Prerequisites

- Linux environment (Ubuntu recommended)  
- C++ compiler (g++ / clang)  
- Node.js (v14+)

### Running the Server

```bash
cd server
g++ -std=c++17 -pthread server.cpp -o server
./server
```

### Running the Client

```bash
cd client
node client.js
```

---

## Protocol

Simple text-based protocol between client and server:

```
[COMMAND] [LENGTH] [BODY]
```

Examples:

```
LOGIN 5 Ahmed
SEND 11 Hello World
LOGOUT 0
```

Server responses:

```
OK Welcome Ahmed
MSG Ahmed: Hello World
ERROR Invalid password
```

---

## Project Structure

```
chat-app-v2/
├── server/         # C++ server files
├── client/         # Node.js client files
├── README.md
└── users.txt       # optional for authentication
```

---

## Future Improvements

* Replace threads with `epoll` for advanced concurrency
* Chat rooms & private messaging
* Message history persistence
* Unit tests

---

## License

MIT License