# Chat Application

A real-time chat application implemented in C++ using Windows Sockets (Winsock). The application consists of a server that can handle multiple client connections and clients that can send/receive messages in real-time.

## Features
- Multi-client support
- Real-time messaging
- Username identification
- Message history for new clients
- Clean console interface
- Graceful disconnection handling

## Requirements

- Operating system: Windows or Linux
- C++ compiler with C++11 support
- Windows: Winsock2 library (included in Windows SDK)
- Linux: POSIX sockets

## Building the Application

### Windows
```bash
# Build server
g++ chat_server.cpp -o chat_server.exe -lws2_32

# Build client
g++ chat_client.cpp -o chat_client.exe -lws2_32
```

### Make build system

### Build Instructions
To build both client and server:
```bash
make
```

To build individually:
```bash
make chat_server  # For server only
make chat_client  # For client only
```

### Clean Build Files
```bash
make clean
```

g++ .\chat_client.cpp -o .\chat_client.exe -lws2_32

 g++ .\chat_server.cpp -o .\chat_server.exe -lws2_32

## Running the Application

### Starting the Server

1. Run the server executable:
   ```
   .\chat_server.exe
   ```
2. The server will start and wait for client connections on port 12345.

### Connecting as a Client

1. Run the client executable:
   ```
   .\chat_client.exe
   ```
2. Enter your username when prompted.
3. Start chatting! Messages will be broadcast to all connected clients.
4. To exit, type 'exit' and press Enter.

## Implementation Details

### Server Features
- Maintains a list of connected clients
- Stores message history
- Broadcasts messages to all connected clients
- Handles client disconnections gracefully

### Client Features
- Connects to server using localhost (127.0.0.1)
- Sends messages to server
- Receives broadcast messages from other clients
- Supports clean exit with 'exit' command

## Notes

- The server runs on port 12345 by default
- The client connects to localhost (127.0.0.1) by default
- All messages are broadcast to all connected clients
- The application uses TCP/IP for reliable message delivery


## Threads
each client is given its own thread for communication 

## Critical Section 
there are two crital sections one for the clients and one for message history each with it's own mutex.
when a client is connected to the server it will lock the mutex for the clients for the duration of writing. 
after that the history mutex will be locked for the duration of sending previous messages to the client.

after inital setup the server awaits for messages from the clients, stores them in history(mutexed) and broadcasts them to all connected clients.



