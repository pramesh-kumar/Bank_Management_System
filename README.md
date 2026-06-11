# Bank Management System

A console-based Bank Management System written in C++ demonstrating core software engineering practices relevant to embedded systems development.

## Features
- Create, search, edit, delete accounts
- Deposit, withdraw, transfer funds
- Bill payment with transaction log
- ATM simulation with PIN + password authentication
- Unit tested core logic

## Project Structure
```
├── bank_management.cpp       # Main application
├── test_bank_management.cpp  # Unit tests
├── Makefile                  # Build system
└── README.md
```

## Build & Run

**Build the app:**
```bash
make
./bank_app
```

**Run unit tests:**
```bash
make test
```

**Clean build artifacts:**
```bash
make clean
```

## Tech
- Language : C++ (C++11)
- Build    : GNU Make
- Compiler : g++ with -Wall warnings
- Storage  : File-based (pipe-delimited .txt)
- Tests    : Custom unit test framework
