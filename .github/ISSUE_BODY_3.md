## 🟡 Phase 1: The Handshake — Node.js Test Client

### Objective

Build a minimal Node.js CLI client that connects to the C++ server over raw TCP to verify the handshake.

### Tasks

- [ ] Create `client/client.js`
- [ ] Use `net.createConnection({ port: 8080, host: 'localhost' })` to connect
- [ ] Handle the `connect` event — print "Connected to Server"
- [ ] Handle the `data` event — print received bytes to stdout
- [ ] Handle the `close` event — print "Disconnected" and exit
- [ ] Handle the `error` event — print error and exit gracefully
- [ ] Add basic `stdin` input to send raw text to the server

### Key Concepts

- Node.js `net` module = raw TCP (no HTTP, no Socket.io)
- TCP is a byte stream — `data` events may arrive in chunks
- This client is for **testing only** at this stage

### Reference

- Node.js docs: `net.createConnection()`
- ROADMAP Phase 1: Client Task

### Success Criteria

- `node client.js` connects to the running C++ server
- Client prints "Connected to Server"
- Client can send text and receive echo response
- Client exits gracefully on server disconnect
