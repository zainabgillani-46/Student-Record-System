#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAX_STUDENTS = 100;

struct Student {
    int rollNo;
    string name;
    string gender;
    int age;
    float cgpa;
    char grade;
    string city;
    string mobile;
    float marks1, marks2, marks3;
    float totalMarks;
    bool scholarship;
};

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent();
void displayStudents();
void saveToFile();
void loadFromFile();
void searchByName();
void updateByMobile();
void deleteByRollNo();
void sortByRollNo();
void calculateGrade(Student &s);

int main() {
    int choice;
    do {
        cout << "\n=====================================================\n";
        cout << "       C++ SEMESTER PROJECT - ASSIGNMENT 4\n";
        cout << "        Student Record Management System\n";
        cout << "=====================================================\n";
        cout << "\n1. Add New Student Record";
        cout << "\n2. Display All Student Records";
        cout << "\n3. Save Records to File";
        cout << "\n4. Load Records from File";
        cout << "\n5. Search Student by Name";
        cout << "\n6. Delete Record by Roll No";
        cout << "\n7. Update Record by Mobile No";
        cout << "\n8. Sort Records by Roll No";
        cout << "\n0. Exit";
        cout << "\n-----------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: saveToFile(); break;
            case 4: loadFromFile(); break;
            case 5: searchByName(); break;
            case 6: deleteByRollNo(); break;
            case 7: updateByMobile(); break;
            case 8: sortByRollNo(); break;
            case 0: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

void calculateGrade(Student &s) {
    s.totalMarks = s.marks1 + s.marks2 + s.marks3;
    if (s.totalMarks >= 270) s.grade = 'A';
    else if (s.totalMarks >= 240) s.grade = 'B';
    else if (s.totalMarks >= 210) s.grade = 'C';
    else if (s.totalMarks >= 180) s.grade = 'D';
    else if (s.totalMarks >= 150) s.grade = 'E';
    else s.grade = 'F';


}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum student limit reached.\n";
        return;
    }

    Student s;

    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Name: ";
    getline(cin, s.name);
    for (int i = 0; i < s.name.length(); i++) if (s.name[i] == ' ') s.name[i] = '_';

    cout << "Gender (Please Enter M for Male and F for Female): ";
    getline(cin, s.gender);

    cout << "Age: ";
    cin >> s.age;

    if (s.age < 0) {
        cout << "? Error: Negative values are not allowed.\n";
        return;
    }

    cout << "CGPA: ";
    cin >> s.cgpa;
    cin.ignore();
    cout << "City: ";
    getline(cin, s.city);
    cout << "Mobile (03XXXXXXXXX): ";
    cin >> s.mobile;
    if (s.mobile.length() != 11){
    	cout << "Invalid Mobile Number. Please Enter Valid Value.\n";
	}
    cout << "Marks in Subject 1: ";
    cin >> s.marks1;
    cout << "Marks in Subject 2: ";
    cin >> s.marks2;
    cout << "Marks in Subject 3: ";
    cin >> s.marks3;

    if (s.marks1 < 0 || s.marks2 < 0 || s.marks3 < 0 || s.marks1 > 100 || s.marks2 > 100 || s.marks3 > 100) {
        cout << "? Error: Negative values and Values Greater than 100 are not allowed.\n";
        return;
    }

    calculateGrade(s);
    students[studentCount++] = s;
    cout << "Student added successfully.\n";
}

void displayStudents() {
    if (studentCount == 0) {
        cout << "No records found.\n";
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        string printableName = students[i].name;
        for (int j = 0; j < printableName.length(); j++)
            if (printableName[j] == '_') printableName[j] = ' ';

        cout << "\n--- Student Record ---\n";
        cout << "Roll No: " << students[i].rollNo << endl;
        cout << "Name: " << printableName << endl;
        cout << "Gender: " << students[i].gender << endl;
        cout << "Age: " << students[i].age << endl;
        cout << "CGPA: " << students[i].cgpa << endl;
        cout << "Total Marks Achieved (Out of 300): " << students[i].totalMarks << endl;
        cout << "Grade: " << students[i].grade << endl;
        cout << "City: " << students[i].city << endl;
        cout << "Mobile: " << students[i].mobile << endl;
    }
}

void saveToFile() {
    ofstream file("students.txt");
    char=grade;
    ;if (grade=='A'|| grade=='B'){
        scholarship = true;
    }
    else {scholarship= false;}

    if (!file) {
        cout << "? Error: Could not open file for writing.\n";
        return;
    }


    for (int i = 0; i < studentCount; i++) {
        file << students[i].rollNo << " "
             << students[i].name << " "
             << students[i].gender << " "
             << students[i].age << " "
             << students[i].cgpa << " "
             << students[i].grade << " "
             << students[i].city << " "
             << students[i].mobile << " "
             << students[i].marks1 << " "
             << students[i].marks2 << " "
             << students[i].marks3 <<" "
             << students[i].scholarship << "\n";
    }


    file.close();
    cout << "Records saved to file successfully.\n";
}

void loadFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cout << "? Error: Could not open file for reading.\n";
        return;
    }

    studentCount = 0;
    while (!file.eof() && studentCount < MAX_STUDENTS) {
        Student s;
        file >> s.rollNo >> s.name >> s.gender >> s.age >> s.cgpa >> s.grade >> s.city >> s.mobile >> s.marks1 >> s.marks2 >> s.marks3;

        if (file.fail()) break;

        calculateGrade(s);
        students[studentCount++] = s;
    }

    file.close();
    cout << "Records loaded from file successfully.\n";
}

void searchByName() {
    string name;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, name);
    for (int i = 0; i < name.length(); i++)
        if (name[i] == ' ') name[i] = '_';

    for (int i = 0; i < studentCount; i++) {
        if (students[i].name == name) {
            cout << "\nRecord Found:\n";
            cout << "Roll No: " << students[i].rollNo << endl;
            string printableName = students[i].name;
            for (int j = 0; j < printableName.length(); j++)
                if (printableName[j] == '_') printableName[j] = ' ';
            cout << "Name: " << printableName << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "CGPA: " << students[i].cgpa << endl;
            cout << "Total Marks: " << students[i].totalMarks << endl;
            cout << "Grade: " << students[i].grade << endl;
            cout << "City: " << students[i].city << endl;
            cout << "Mobile: " << students[i].mobile << endl;
            return;
        }
    }

    cout << "Student not found.\n";
}

void updateByMobile() {
    string mobile;
    cout << "Enter mobile number to update: ";
    cin >> mobile;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].mobile == mobile) {
            cout << "Enter new city: ";
            cin.ignore();
            getline(cin, students[i].city);
            cout << "Record updated successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

void deleteByRollNo() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == roll) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Record deleted successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

void sortByRollNo() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].rollNo > students[j].rollNo) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    cout << "Student records sorted by Roll No.\n";
}
