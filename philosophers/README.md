# Dining Philosophers Problem

This program implements the classic Dining Philosophers problem using C++ threads and mutexes. It provides a visual representation of philosophers' states and fork usage.

## Problem Description
The Dining Philosophers problem is a classic synchronization problem that illustrates challenges in resource allocation and deadlock prevention. Five philosophers sit around a circular table, alternating between thinking and eating. Between each pair of philosophers is a single fork, and a philosopher needs both adjacent forks to eat.

## Features
- Visual representation of philosophers' states
- Real-time fork usage tracking
- Deadlock prevention using resource hierarchy
- Configurable number of philosophers and timing

## Building the Program

### Prerequisites
- C++ compiler with C++11 support
- CMake (version 3.10 or higher)

### Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

### Clean Build Files
```bash
rm -rf build/
```

## Running the Program
```bash
./dining_philosophers <number_of_philosophers> <timer_in_ms>
```

Example:
```bash
./dining_philosophers 5 500
```

### Parameters
- `number_of_philosophers`: Number of philosophers (minimum 2)
- `timer_in_ms`: Time in milliseconds for thinking/eating cycles (minimum 100ms)

## Implementation Details
- Uses C++11 threads for concurrent execution
- Implements mutex locks for fork synchronization
- Prevents deadlock through resource hierarchy
- Provides real-time state visualization
## Threads
Each thread represent one philosopher whose only  goal in life is to eat.
after each meal the philosopher will think for some time 

## Critical Section
The critical section is the fork usage.
To solve it I used mutexes representing forks.
Only one thread can use a fork at a time.

each philosopher has two forks one on the left and one on the right.
each thread(philosopher) will try to use two forks.
first it will block the first one and then the second one.
if any of the forks is already used by another thread the thread will wait until the fork is available.

the philosophers forks are on indexes n and n+1 in the forks array.
if the philosophers number is even it will use the forks in the opposite order to mitigate deadlocks.