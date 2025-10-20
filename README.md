# 📡 Minitalk

**Minitalk** is a small project from 42 where you implement **inter-process communication (IPC)** between a client and a server using **UNIX signals**.  
It demonstrates how processes can exchange data reliably in C without shared memory.

---

## 🧠 Project Overview

Minitalk is designed to:

- Send strings from a client process to a server process using **signals**.
- Ensure messages are transmitted **bit by bit** reliably.
- Handle multiple messages without data loss.
- Display messages on the server console in real-time.

---

## ⚙️ Features

- **Signal-Based Communication**: Uses `SIGUSR1` and `SIGUSR2` to transmit each bit of the message.  
- **Acknowledgment System**: Server sends acknowledgment signals to confirm receipt of each byte.  
- **Multiple Clients**: Handles messages from multiple clients sequentially.  
- **Error Handling**: Detects invalid PIDs or interrupted transmissions.  
- **Dynamic Message Handling**: Supports strings of any length.

---

## 🚀 Usage

### Compilation

Use the provided Makefile to compile:

```bash
make
```
This creates two executables:
- server — starts the server process.
- client — sends messages to the server.
Running the Server:
```bash
./server
```
The server prints its PID, which the client will need to send messages.
Sending Messages with the Client.
```bash
./client <server_pid> "Your message here"
```
Example:
```bash
./client 12345 "Hello, 42!"
```

## 🔧 Implementation Details

- **Signals:** `SIGUSR1` represents bit `0`, `SIGUSR2` represents bit `1`.  
- **Bitwise Transmission:** Each character is sent bit by bit from client to server.  
- **Acknowledgments:** Server responds with a signal after receiving each byte to avoid data loss.  
- **Process IDs:** Server prints its PID; client reads it from command-line arguments.

---

## 🧵 Learning Outcomes

Through this project, I learned:

- How **UNIX signals** work for inter-process communication.  
- How to **encode and decode data at the bit level**.  
- How to implement **reliable communication between processes**.  
- How to handle **errors and edge cases** in IPC.  
- How to structure **modular C programs** for maintainability.
