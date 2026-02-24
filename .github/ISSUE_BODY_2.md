## 🟡 Phase 1: The Handshake — Listen & Accept Loop

### Objective

Make the server wait for incoming connections and accept a single client.

### Tasks

- [ ] Call `listen(server_fd, backlog)` to mark the socket as passive
- [ ] Understand the `backlog` parameter (connection queue size)
- [ ] Call `accept()` in a blocking loop to grab the incoming client
- [ ] Store the client file descriptor returned by `accept()`
- [ ] Print "Client Connected" with client address info
- [ ] Add error checking for `listen()` and `accept()` return values
- [ ] Handle clean shutdown: close both server and client sockets

### Key Concepts

- What does `listen()` actually change in the kernel?
- `accept()` returns a **new** file descriptor — why?
- Blocking vs Non-blocking I/O (for now, we use blocking)

### Reference

- Beej's Guide: Sections 5.5, 5.6
- `man 2 listen`, `man 2 accept`

### Success Criteria

- Server waits for connections after `listen()`
- `telnet localhost 8080` connects and server prints confirmation
- Server shuts down cleanly with `close()`
