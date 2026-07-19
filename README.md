# Student Record Management System

A simple C++ console application for managing student records, built using core Object-Oriented Programming (OOP) principles as a university project.

## Features
- Add a new student record (ID, name, age, course)
- Display all stored student records
- Search for a student by ID
- Menu-driven console interface

## Concepts Used
- **Encapsulation** — student data and behavior are bundled inside the `Student` class
- **Abstraction** — users interact with simple menu options without needing to know how data is stored internally
- **Modularity** — separated into `Student` and `StudentManagement` classes for cleaner structure
- **Dynamic data storage** — uses `std::vector` to store an unlimited number of student records

## Tech Stack
- C++ (Standard Library: `<iostream>`, `<vector>`, `<string>`)

## How to Run
1. Clone the repository:
   ```
   git clone https://github.com/YOUR_USERNAME/student-record-management-system.git
   cd student-record-management-system
   ```
2. Compile the code:
   ```
   g++ main.cpp -o student_management
   ```
3. Run it:
   ```
   ./student_management
   ```
   (On Windows: `student_management.exe`)

## Possible Future Enhancements
- Edit/update existing student details
- Delete a student record
- Save/load records to a file for persistent storage
- Sort or filter students by name, age, or course

## Contributors
- Syeda Malika Zahra
- Daniea Jamal
- Muhammad Usman Tariq
