#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    string course;

public:
    Student(int id, string name, int age, string course) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->course = course;
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
    }

    int getId() { return id; }
};

class StudentManagement {
private:
    vector<Student> students;

public:
    void addStudent(int id, string name, int age, string course) {
        students.push_back(Student(id, name, age, course));
        cout << "Student added successfully." << endl;
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students found." << endl;
            return;
        }
        for (const auto& student : students) {
            student.display();
            cout << "--------------------\n";
        }
    }

    void searchStudentById(int id) const {
        for (const auto& student : students) {
            if (student.getId() == id) {
                cout << "Student found:\n";
                student.display();
                return;
            }
        }
        cout << "No student found with ID " << id << ".\n";
    }
};

int main() {
    StudentManagement system;
    int choice;

    do {
        cout << "\n--- Student Record Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, age;
                string name, course;
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter Course: ";
                getline(cin, course);
                system.addStudent(id, name, age, course);
                break;
            }
            case 2:
                system.displayAllStudents();
                break;
            case 3: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                system.searchStudentById(id);
                break;
            }
            case 4:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
