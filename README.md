# Student Record Management System

A C++ console application for managing student records, built as a university OOP project. Features role-based access (Admin / Student), inheritance-based student types, and persistent file storage.

## Features
- **Login system** with separate Admin and Student roles
- **Admin**: add, view, search, edit, and delete student records
- **Student**: view all records and search by ID (read-only access)
- **Two student types** — Undergraduate (tracks semester) and Graduate (tracks thesis topic) — both derived from a common `Student` base class
- **Persistent storage** — records are saved to and loaded from `students.txt`

## OOP Concepts Used
- **Inheritance** — `Admin` and `Student` inherit from `User`; `Undergraduate` and `Graduate` inherit from `Student`
- **Polymorphism** — `display()` is a virtual method overridden at each level of the hierarchy, so the correct details print based on the actual object type
- **Encapsulation** — the `Record` class keeps student data and file I/O logic private, exposing only clean public methods (add, edit, delete, search)
- **Abstraction** — users interact through simple numbered menus without needing to know how data is stored or searched internally
- **Dynamic memory management** — student records are stored as `Student*` pointers, allocated with `new` and properly cleaned up with `delete` in the destructor

## Class Diagram
```
                SRMS
               /    \
          User        Record
         /    \
     Admin    Student
                /   \
        Graduate   Undergraduate
```
`SRMS` has-a `User` (composition) and has-a `Record` (composition). `Admin` and `Student` inherit from `User`. `Graduate` and `Undergraduate` inherit from `Student`.

## Tech Stack
- C++ (Standard Library: `<iostream>`, `<fstream>`, `<string>`)

## How to Run
1. Clone the repository:
   ```
   git clone https://github.com/YOUR_USERNAME/student-record-management-system.git
   cd student-record-management-system
   ```
2. Compile the code:
   ```
   g++ main.cpp -o srms
   ```
3. Run it:
   ```
   ./srms
   ```
   (On Windows: `srms.exe`)

## Demo Credentials
| Role    | Username  | Password     |
|---------|-----------|--------------|
| Admin   | admin     | admin123     |
| Student | student   | student123   |

## Possible Future Enhancements
- Hash passwords instead of storing them in plain text
- Input validation for menu choices and student type selection
- Sort/filter students by name, age, or course
- Save/restore Undergraduate/Graduate-specific fields (semester, thesis topic) to file (currently only base fields persist)

## Contributors
- Syeda Malika Zahra
- Daniea Jamal
- Muhammad Usman Tariq
