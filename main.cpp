#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;

class User {
public:
    string username;
    string password;
    virtual void display() const {
        cout << "Username: " << username << "\nPassword: " << password << endl;
    }
    virtual ~User() {}
};

class Student : public User {
public:
    int studentID;
    string name;
    int age;
    string email;
    string course;
    virtual void display() const {
        cout << "Student ID: " << studentID << "\nName: " << name
             << "\nAge: " << age << "\nEmail: " << email
             << "\nCourse: " << course << endl;
    }
    virtual ~Student() {}
};

class Undergraduate : public Student {
public:
    string semester;
    void display() const override {
        Student::display();
        cout << "Semester: " << semester << endl;
    }
};

class Graduate : public Student {
public:
    string thesisTopic;
    void display() const override {
        Student::display();
        cout << "Thesis Topic: " << thesisTopic << endl;
    }
};

class Record {
private:
    Student* students[MAX_STUDENTS];
    int studentCount;

    void loadFromFile() {
        ifstream inFile("students.txt");
        if (!inFile) return;
        studentCount = 0;
        while (studentCount < MAX_STUDENTS) {
            students[studentCount] = new Student();
            inFile >> students[studentCount]->studentID;
            inFile.ignore();
            getline(inFile, students[studentCount]->name);
            inFile >> students[studentCount]->age;
            inFile.ignore();
            getline(inFile, students[studentCount]->email);
            getline(inFile, students[studentCount]->course);
            studentCount++;
        }
        inFile.close();
    }

    void saveToFile() {
        ofstream outFile("students.txt");
        for (int i = 0; i < studentCount; i++) {
            outFile << students[i]->studentID << endl
                    << students[i]->name << endl
                    << students[i]->age << endl
                    << students[i]->email << endl
                    << students[i]->course << endl;
        }
        outFile.close();
    }

    int findStudentIndexByID(int id) const {
        for (int i = 0; i < studentCount; i++) {
            if (students[i]->studentID == id) return i;
        }
        return -1;
    }

public:
    Record() : studentCount(0) { loadFromFile(); }

    ~Record() {
        for (int i = 0; i < studentCount; i++) {
            delete students[i];
        }
    }

    void addStudent(Student* newStudent) {
        if (studentCount >= MAX_STUDENTS) {
            cout << "Cannot add more students. Limit reached." << endl;
            return;
        }
        if (findStudentIndexByID(newStudent->studentID) != -1) {
            cout << "Student with this ID already exists." << endl;
            return;
        }
        students[studentCount++] = newStudent;
        cout << "Student added successfully." << endl;
    }

    void displayAllStudents() const {
        if (studentCount == 0) {
            cout << "No students to display." << endl;
            return;
        }
        for (int i = 0; i < studentCount; i++) {
            cout << "\n--- Student " << (i + 1) << " ---\n";
            students[i]->display();
        }
    }

    void searchStudentByID(int id) const {
        int index = findStudentIndexByID(id);
        if (index != -1) {
            cout << "\n--- Student Found ---\n";
            students[index]->display();
        } else {
            cout << "Student not found." << endl;
        }
    }

    void editStudent(int id) {
        int index = findStudentIndexByID(id);
        if (index == -1) {
            cout << "Student not found." << endl;
            return;
        }
        cout << "Enter new Name (leave blank to keep current): ";
        string name;
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) students[index]->name = name;

        cout << "Enter new Age (0 to keep current): ";
        int age;
        cin >> age;
        if (age != 0) students[index]->age = age;
        cin.ignore();

        cout << "Enter new Email (leave blank to keep current): ";
        string email;
        getline(cin, email);
        if (!email.empty()) students[index]->email = email;

        cout << "Enter new Course (leave blank to keep current): ";
        string course;
        getline(cin, course);
        if (!course.empty()) students[index]->course = course;

        cout << "Student updated successfully." << endl;
    }

    void deleteStudent(int id) {
        int index = findStudentIndexByID(id);
        if (index == -1) {
            cout << "Student not found." << endl;
            return;
        }
        delete students[index];
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        cout << "Student deleted successfully." << endl;
    }
};

class Admin : public User {
public:
    void display() const override {
        cout << "Admin: " << username << " has admin privileges." << endl;
    }

    void manageStudents(class Record& record) {
        int choice;
        do {
            cout << "\n--- Manage Students ---\n";
            cout << "1. Add Student\n";
            cout << "2. View All Students\n";
            cout << "3. Delete Student\n";
            cout << "4. Edit Student\n";
            cout << "5. Back to Admin Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    int type;
                    cout << "Choose student type: 1. Undergraduate, 2. Graduate: ";
                    cin >> type;
                    Student* newStudent = nullptr;
                    if (type == 1) {
                        newStudent = new Undergraduate();
                    } else if (type == 2) {
                        newStudent = new Graduate();
                    }
                    cout << "Enter Student ID: ";
                    cin >> newStudent->studentID;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, newStudent->name);
                    cout << "Enter Age: ";
                    cin >> newStudent->age;
                    cin.ignore();
                    cout << "Enter Email: ";
                    getline(cin, newStudent->email);
                    cout << "Enter Course: ";
                    getline(cin, newStudent->course);
                    if (type == 1) {
                        cout << "Enter Semester: ";
                        getline(cin, static_cast<Undergraduate*>(newStudent)->semester);
                    } else if (type == 2) {
                        cout << "Enter Thesis Topic: ";
                        getline(cin, static_cast<Graduate*>(newStudent)->thesisTopic);
                    }
                    record.addStudent(newStudent);
                    break;
                }
                case 2:
                    record.displayAllStudents();
                    break;
                case 3: {
                    int id;
                    cout << "Enter Student ID to delete: ";
                    cin >> id;
                    record.deleteStudent(id);
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter Student ID to edit: ";
                    cin >> id;
                    record.editStudent(id);
                    break;
                }
                case 5:
                    cout << "Back to Admin Menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 5);
    }
};

class SRMS {
private:
    Record record;
    User* loggedInUser;

public:
    SRMS() : loggedInUser(nullptr) {}

    void menu() {
        int choice;
        do {
            cout << "\n--- Student Record Management System ---\n";
            cout << "1. Login\n";
            cout << "2. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: login(); break;
                case 2: cout << "Exiting..." << endl; break;
                default: cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 2);
    }

    void login() {
        string username, password;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        if (username == "admin" && password == "admin123") {
            loggedInUser = new Admin();
            loggedInUser->username = username;
            loggedInUser->password = password;
            cout << "Logged in as Admin." << endl;
            adminMenu();
        } else if (username == "student" && password == "student123") {
            loggedInUser = new User();
            loggedInUser->username = username;
            loggedInUser->password = password;
            cout << "Logged in as Student." << endl;
            studentMenu();
        } else {
            cout << "Invalid username or password." << endl;
        }
    }

    void adminMenu() {
        int choice;
        Admin* admin = dynamic_cast<Admin*>(loggedInUser);
        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Manage Students\n";
            cout << "2. Log out\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: admin->manageStudents(record); break;
                case 2: cout << "Logging out..." << endl; loggedInUser = nullptr; break;
                default: cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 2);
    }

    void studentMenu() {
        int choice;
        do {
            cout << "\n--- Student Menu ---\n";
            cout << "1. View All Students\n";
            cout << "2. Search Student by ID\n";
            cout << "3. Log out\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: record.displayAllStudents(); break;
                case 2: {
                    int id;
                    cout << "Enter Student ID: ";
                    cin >> id;
                    record.searchStudentByID(id);
                    break;
                }
                case 3: cout << "Logging out..." << endl; loggedInUser = nullptr; break;
                default: cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 3);
    }
};

int main() {
    SRMS srms;
    srms.menu();
    return 0;
}
