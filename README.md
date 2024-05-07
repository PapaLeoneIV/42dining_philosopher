# Dining Philosophers Problem

## Introduction
This project is an implementation of the classic synchronization problem known as the Dining Philosophers Problem. It is designed as part of the curriculum for the 42 School. The implementation is done entirely in C and demonstrates the usage of various synchronization techniques to avoid common problems like deadlocks.

## Problem Statement
The Dining Philosophers Problem involves a certain number of philosophers, each of whom spends their life thinking and eating. The philosophers share a circular table surrounded by their seats and a bowl of spaghetti. Between each pair of adjacent philosophers, there is a single fork. The challenge is that each philosopher needs both forks (the one on their left and the one on their right) to eat. The problem is how to design a protocol that allows philosophers to never be starved by their neighbors, avoiding deadlock.

## How to Run
### Prerequisites
- GCC compiler
- Make (optional)

### Compilation
To compile the program, run the following command in your terminal:
```bash
 make
```
###Execution
To execute the program, run the following command in your terminal
```bash
./philo time_to_die time_to_eat time_to_sleep [num_of_time_they_must_eat(optional)]
```
