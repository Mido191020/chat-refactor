# 🏛️ Titan — Hardcore TCP Chat Server

> A multi-threaded TCP chat system built from scratch using raw Linux system calls in C++ and a Node.js CLI client. No frameworks, no shortcuts — just pure systems programming.

[![Language](https://img.shields.io/badge/Server-C%2B%2B17-blue?logo=cplusplus)](https://isocpp.org/)
[![Client](https://img.shields.io/badge/Client-Node.js-green?logo=node.js)](https://nodejs.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## 📖 Overview

**Titan** is a systems-level chat application designed for deep understanding of:

- **Socket Programming** — raw TCP using `socket()`, `bind()`, `listen()`, `accept()`, `send()`, `recv()`
- **Concurrency** — multi-threaded client handling with `std::thread` and `std::mutex`
- **OS Concepts** — processes, threads, file I/O, memory management (OSTEP-inspired)
- **Protocol Design** — a custom text-based application protocol (no HTTP)
- **Cross-Language Communication** — C++ server ↔ Node.js client over TCP

This is not a tutorial project — it is a **production-style distributed system** built from first principles.

---

## 🏗️ Architecture

```
┌──────────────────┐          ┌─────────────────────────────────────┐
│  Node.js Client  │◄──TCP──►│           C++ Server                │
│  (CLI / net)     │          │                                     │
├──────────────────┤          │  ┌─────────┐  ┌──────────────────┐  │
│  Node.js Client  │◄──TCP──►│  │ Thread  │  │ Shared State     │  │
├──────────────────┤          │  │  Pool   │  │ (mutex-guarded)  │  │
│  Node.js Client  │◄──TCP──►│  └─────────┘  └──────────────────┘  │
└──────────────────┘          │       │              │              │
                              │       ▼              ▼              │
                              │  ┌─────────┐  ┌──────────────┐     │
                              │  │  Auth   │  │  File Logger │     │
                              │  │ Module  │  │  (server.log)│     │
                              │  └─────────┘  └──────────────┘     │
                              └─────────────────────────────────────┘
```

---

## 🔌 Protocol Specification

Titan uses a custom text-based protocol for all communication:

```
[COMMAND] [LENGTH] [BODY]
```

| Command  | Direction       | Description                |
|----------|-----------------|----------------------------|
| `LOGIN`  | Client → Server | Authenticate with username |
| `SEND`   | Client → Server | Broadcast a message        |
| `LOGOUT` | Client → Server | Disconnect gracefully      |
| `OK`     | Server → Client | Success response           |
| `MSG`    | Server → Client | Broadcast message delivery |
| `ERROR`  | Server → Client | Error response             |

**Examples:**

```
LOGIN 5 Ahmed          →  OK Welcome Ahmed
SEND 11 Hello World    →  MSG Ahmed: Hello World
LOGOUT 0               →  (connection closed)
```

---

## 🗺️ Project Milestones

Development is organized into incremental, testable milestones:

| #  | Milestone                       | Focus                                |
|----|---------------------------------|--------------------------------------|
| M1 | Core TCP Server (Single Client) | `socket`, `bind`, `listen`, `accept` |
| M2 | Custom Protocol Parsing         | Message framing & validation         |
| M3 | Multi-Client Concurrency        | Threads, mutex, race conditions      |
| M4 | Broadcast Messaging             | Fan-out to all connected clients     |
| M5 | Authentication System           | Login, credentials, access control   |
| M6 | Logging & Persistence           | Thread-safe file I/O with timestamps |
| M7 | Node.js CLI Client              | Interactive terminal chat UX         |
| M8 | Robustness & Error Handling     | Crash resistance, cleanup, timeouts  |
| M9 | Advanced Mode *(optional)*      | `epoll`, chat rooms, rate limiting   |

> Track progress via [GitHub Issues](https://github.com/Mido191020/chat-refactor/issues).

---

## 🚀 Getting Started

### Prerequisites

- **Server:** GCC/G++ with C++17 support, CMake, Linux (or WSL)
- **Client:** Node.js ≥ 16

### Build & Run the Server

```bash
# Clone the repository
git clone https://github.com/Mido191020/chat-refactor.git
cd chat-refactor

# Build
mkdir -p build && cd build
cmake ..
make

# Run
./titan_server
```

### Run the Client

```bash
cd client/
node client.js
```

---

## 🧰 Tech Stack

| Component | Technology             | Constraint                          |
|-----------|------------------------|-------------------------------------|
| Server    | C++17                  | Raw Linux syscalls only             |
| Client    | Node.js (`net` module) | Raw TCP — no Socket.io or HTTP libs |
| Build     | CMake                  | —                                   |
| Debugging | GDB + Valgrind         | Memory leak & logic verification    |

---

## 📚 Learning Resources

- 📘 [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- 📙 [OSTEP — Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
- 📗 Linux `man` pages (`man 2 socket`, `man 2 bind`, etc.)

---

## 🧱 Project Rules (Hardcore Mode)

| ✅ Allowed                    | ❌ Not Allowed       |
|------------------------------|----------------------|
| Linux system calls           | Boost.Asio           |
| `std::thread` / `pthread`    | POCO framework       |
| Manual protocol parsing      | HTTP / WebSockets    |
| `std::mutex` for sync        | Socket.io            |
| Raw `net` module in Node.js  | Any networking framework |

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

<p align="center">
  <b>Built from scratch. No frameworks. No shortcuts.</b><br>
  <i>Systems programming the hard way.</i>
</p>
