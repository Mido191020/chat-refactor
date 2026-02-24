## 🟡 Phase 1: The Handshake — Server Socket Setup

### Objective

Create the TCP endpoint and bind it to a network address so the OS knows our process is ready to receive connections.

### Tasks

- [ ] Include required headers: `<sys/socket.h>`, `<netinet/in.h>`, `<unistd.h>`
- [ ] Call `socket(AF_INET, SOCK_STREAM, 0)` — get the file descriptor
- [ ] Define `struct sockaddr_in` with:
  - `sin_family = AF_INET`
  - `sin_port = htons(8080)`
  - `sin_addr.s_addr = INADDR_ANY`
- [ ] Call `bind()` to attach address to socket
- [ ] Add error checking for both `socket()` and `bind()` return values

### Key Concepts

- Why `SOCK_STREAM` over `SOCK_DGRAM`? (TCP guarantees)
- Why `htons()`? (Network byte order vs host byte order)
- Why `INADDR_ANY`? (Bind to all available interfaces)

### Reference

- Beej's Guide: Sections 2.1, 3.2, 3.3, 5.2, 5.3
- `man 2 socket`, `man 2 bind`

### Success Criteria

- Server creates socket without error
- Socket is bound to port 8080
