#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

class Teacher;
class Student;
class Timetable;
class Attendance;

class Timetable {
private:
    string subjects[10];
    string timings[10];
    int count;

    string filename;  // each user has a file

public:
    Timetable(string userId) { // pass TeacherID or StudentID
        count = 0;
        filename = userId + "_timetable.txt";
        loadFromFile();  // load timetable if file exists
    }

    void createTimetable() {
        cout << "\n--- Create Timetable ---\n";
        cout << "How many subjects do you want to add? ";
        cin >> count;
        cin.ignore();

        for(int i = 0; i < count; i++) {
            cout << "Enter subject name: ";
            getline(cin, subjects[i]);

            cout << "Enter timing (e.g., Mon 9AM-10AM): ";
            getline(cin, timings[i]);
        }

        saveToFile();  // save after creation
        cout << "Timetable created successfully!\n";
    }

    void viewTimetable() {
        if(count == 0) {
            cout << "No timetable created yet!\n";
            return;
        }

        cout << "\n--- Your Timetable ---\n";
        for(int i = 0; i < count; i++) {
            cout << subjects[i] << " -> " << timings[i] << endl;
        }
    }

    void saveToFile() {
        ofstream fout(filename);
        fout << count << endl;
        for(int i = 0; i < count; i++) {
            fout << subjects[i] << endl;
            fout << timings[i] << endl;
        }
        fout.close();
    }

    void loadFromFile() {
        ifstream fin(filename);
        if(!fin) return; // file doesn't exist

        fin >> count;
        fin.ignore(); // remove newline after number
        for(int i = 0; i < count; i++) {
            getline(fin, subjects[i]);
            getline(fin, timings[i]);
        }
        fin.close();
    }
};

class Attendance {
private:
    int totalClasses;
    int attendedClasses;
    string filename;

public:
    Attendance(string userId) {
        totalClasses = 0;
        attendedClasses = 0;
        filename = userId + "_attendance.txt";
        loadFromFile();  // load saved attendance
    }

    void markAttendance() {
        int choice;
        cout << "\nMark Attendance (1 = Present, 0 = Absent): ";
        cin >> choice;

        totalClasses++;
        if(choice == 1) attendedClasses++;

        saveToFile();  // save after marking
        cout << "Attendance marked.\n";
    }

    void viewAttendance() {
        if(totalClasses == 0) {
            cout << "No classes recorded yet.\n";
            return;
        }

        double percent = (attendedClasses * 100.0) / totalClasses;
        cout << "Attendance: " << attendedClasses << "/" << totalClasses
             << " (" << percent << "%)\n";

        if(percent < 75.0)
            cout << "⚠ Warning: Attendance below 75%!\n";
    }

    void saveToFile() {
        ofstream fout(filename);
        fout << totalClasses << " " << attendedClasses << endl;
        fout.close();
    }

    void loadFromFile() {
        ifstream fin(filename);
        if(!fin) return;
        fin >> totalClasses >> attendedClasses;
        fin.close();
    }
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

void Teacher::teacherMenu() {
    int choice;
    Timetable tTeacher("T001");
    Attendance aTeacher("T001");

    do {
        cout << "\n--- Teacher Menu ---\n";
        cout << "1. Create/View Timetable\n";
        cout << "2. Mark/View Attendance\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: 
                tTeacher.createTimetable();
                tTeacher.viewTimetable();
                break;
            case 2: 
                aTeacher.markAttendance();
                aTeacher.viewAttendance();
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
    Timetable tStudent("S001");
    Attendance aStudent("S001");

    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. Create/View Timetable\n";
        cout << "2. Mark/View My Attendance\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: 
                tStudent.createTimetable();
                tStudent.viewTimetable();
                break;
            case 2: 
                aStudent.markAttendance();
                aStudent.viewAttendance();
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
