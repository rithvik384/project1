#include <iostream>
#include <string>
using namespace std;

class Teacher;
class Student;
class Timetable;
class Attendance;

class Timetable {
public:
    void createTimetable();   
    void viewTimetable();     
};

class Attendance {
public:
    void markAttendance();    
    void viewAttendance();   
};

class Teacher {
private:
    string name;
    string id;
    string password;

public:
    Teacher(string n, string i, string p) : name(n), id(i), password(p) {}

    bool login(string enteredId, string enteredPass) {
        return (id == enteredId && password == enteredPass);
    }

    void teacherMenu();   // after login
};

class Student {
private:
    string name;
    string rollNo;
    string password;

public:
    Student(string n, string r, string p) : name(n), rollNo(r), password(p) {}

    bool login(string enteredRoll, string enteredPass) {
        return (rollNo == enteredRoll && password == enteredPass);
    }

    void studentMenu();   // after login
};

void Timetable::createTimetable() {
    cout << "Timetable created (placeholder)." << endl;
}
void Timetable::viewTimetable() {
    cout << "Showing timetable (placeholder)." << endl;
}

void Attendance::markAttendance() {
    cout << "Attendance marked (placeholder)." << endl;
}
void Attendance::viewAttendance() {
    cout << "Showing attendance (placeholder)." << endl;
}

void Teacher::teacherMenu() {
    int choice;
    Timetable t;
    Attendance a;

    do {
        cout << "\n--- Teacher Menu ---\n";
        cout << "1. Create/View Timetable\n";
        cout << "2. Mark/View Attendance\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: 
                t.createTimetable();
                t.viewTimetable();
                break;
            case 2: 
                a.markAttendance();
                a.viewAttendance();
                break;
            case 3: 
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 3);
}

void Student::studentMenu() {
    int choice;
    Timetable t;
    Attendance a;

    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. Create/View Timetable\n";
        cout << "2. Mark/View My Attendance\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: 
                t.createTimetable();
                t.viewTimetable();
                break;
            case 2: 
                a.markAttendance();
                a.viewAttendance();
                break;
            case 3: 
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 3);
}

int main() {
    Teacher teacher1("Alice", "T001", "pass123");
    Student student1("Bob", "S001", "pass456");

    int userType;
    cout << "--- Academic Management System ---\n";
    cout << "1. Teacher Login\n";
    cout << "2. Student Login\n";
    cout << "Enter choice: ";
    cin >> userType;

    string id, pass;
    if(userType == 1) {
        cout << "Enter Teacher ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> pass;

        if(teacher1.login(id, pass)) {
            cout << "Login successful (Teacher)\n";
            teacher1.teacherMenu();
        } else {
            cout << "Invalid login.\n";
        }
    } 
    else if(userType == 2) {
        cout << "Enter Student Roll No: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> pass;

        if(student1.login(id, pass)) {
            cout << "Login successful (Student)\n";
            student1.studentMenu();
        } else {
            cout << "Invalid login.\n";
        }
    } 
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
