# MyContainer Project

## Overview

This project implements a generic container class `MyContainer<T>` in C++ with multiple custom iterator types.  
You can iterate over the container in various orders: ascending, descending, reverse, side-cross, insertion order, and middle-out.  
Unit tests are provided using the [doctest](https://github.com/doctest/doctest) framework.

---
## Code Explanation

- **MyContainer**: A generic container class similar to `std::vector`, but with custom iterators.
- **Iterators**:  
  - `AscendingOrder`: Iterates elements in ascending order.
  - `DescendingOrder`: Iterates elements in descending order.
  - `ReverseOrder`: Iterates elements in reverse insertion order.
  - `Order`: Iterates elements in insertion order.
  - `SideCrossOrder`: Alternates from start and end towards the center.
  - `MiddleOutOrder`: Starts from the middle and alternates outwards.
- **Tests**: Comprehensive doctest-based tests for all iterator types and edge cases.

---
## File Structure

- `main.cpp` - Main program (edit as needed)
- `Test/test.cpp` - Unit tests using doctest
- `MyContainer.hpp` - Main container class
- `AscendingOrder.hpp`, `DescendingOrder.hpp`, `SideCrossOrder.hpp`, `ReverseOrder.hpp`, `Order.hpp`, `MiddleOutOrder.hpp` - Iterator implementations
- `Makefile` - Build and test automation

---

## How to Build and Run

### 1. Build Main Program

To compile the main program, run:

    make

This creates an executable called `main`.

To run the main program:

    ./main

---

### 2. Run Unit Tests

To compile and run the tests, run:

    make test

This builds and runs the `test` executable, which runs all doctest-based unit tests.

---

### 3. Memory Checking (Optional)

To check for memory leaks using Valgrind (after building):

    make valgrind

---

### 4. Clean Build Files

To remove all build artifacts:

    make clean

---




