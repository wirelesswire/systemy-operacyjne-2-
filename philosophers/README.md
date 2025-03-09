# Dining Philosophers Problem

This program implements the classic Dining Philosophers problem using C++ threads and mutexes. 
It provides a visual representation of philosophers' states and fork usage.

## Compilation

To compile the program, use:

```bash
g++ dining_philosophers.cpp -o dining_philosophers.exe -pthread
```
To run the program use:
```bash 
.\dining_philosophers.exe 5 1000 
```
## Threads
Each thread represent one philosopher whose only  goal in life is to eat.
after each meal the philosopher will sleep for some time 

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
