# Operating Systems Projects

This repository contains implementations of various operating systems concepts and applications.

## Available Modules

### 1. Dining Philosophers
An implementation of the classic dining philosophers problem demonstrating process synchronization and deadlock prevention.

**Location:** `philosophers/`

To get started with the Dining Philosophers simulation:
1. Navigate to the `philosophers` directory
2. Follow the compilation and usage instructions in the module's [README](philosophers/README.md)

### 2. Chat Application
A multi-client chat application demonstrating network programming and concurrent communication.

**Location:** `chatapp/`

To get started with the Chat Application:
1. Navigate to the `chatapp` directory
2. Follow the compilation and usage instructions in the module's [README](chatapp/README.md)

## Requirements

- Windows operating system
- C++ compiler with C++11 support
- For Chat Application: Winsock2 library (included in Windows SDK)
- For Dining Philosophers: POSIX threads support

## Project Structure

```
.
├── philosophers/     # Dining Philosophers implementation
├── chatapp/         # Chat Application implementation
└── README.md        # This file
```

Each module contains its own README with detailed compilation steps and usage instructions. Please refer to the individual module documentation for specific details.