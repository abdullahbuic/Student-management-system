// CPSemesterProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int maxStudents = 50;
const int maxDays = 30;

int rollNumbers[maxStudents];
string names[maxStudents];
int marks[maxStudents][3];
float averages[maxStudents];
char grades[maxStudents];
bool attendance[maxStudents][maxDays];

int totalStudents = 0;
int totalAttendanceDays = 0;

void addStudent(int r);
void displayAll();
void searchStudent(int r);
void updateMarks(int r);
void deleteStudent(int r);
void topThree();
void gradeSummary();
void markAttendance();
void displayAttendance(int r);
void attendanceReport();
void exportToFile();
void subjectToppers();
void gpaConverter();

int main() {
    int choice;

    do {
        cout << "=====================================\n";
        cout << "       STUDENT MANAGEMENT MENU       \n";
        cout << "=====================================\n";
        cout << "1. Add a New Student\n";
        cout << "2. Display all Student Records\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Update a Student's Marks\n";
        cout << "5. Delete a Student's Record\n";
        cout << "6. Show Top 3 Students\n";
        cout << "7. Grade Summary\n";
        cout << "8. Mark Daily Attendance\n";
        cout << "9. Display Attendance of a Student\n";
        cout << "10. Attendance Percentage Report\n";
        cout << "11. Show Subject-Wise Toppers\n";
        cout << "12. GPA Converter (All Students)\n";
        cout << "13. Export Summary to Text File\n";
        cout << "0. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
        case 1: {
            int r;
            cout << "Enter Roll Number: ";
            cin >> r;
            addStudent(r);
            break;
        }
        case 2: {
            displayAll();
            break;
        }
        case 3: {
            int r;
            cout << "Enter Roll Number: ";
            cin >> r;
            searchStudent(r);
            break;
        }
        case 4: {
            int r;
            cout << "Enter Roll Number: ";
            cin >> r;
            updateMarks(r);
            break;
        }
        case 5: {
            int r;
            cout << "Enter Roll Number: ";
            cin >> r;
            deleteStudent(r);
            break;
        }
        case 6: {
            topThree();
            break;
        }
        case 7: {
            gradeSummary();
            break;
        }
        case 8: {
            markAttendance();
            break;
        }
        case 9: {
            int r;
            cout << "Enter Roll Number: ";
            cin >> r;
            displayAttendance(r);
            break;
        }
        case 10: {
            attendanceReport();
            break;
        }
        case 11: {
            subjectToppers();
            break;
        }
        case 12: {
            gpaConverter();
            break;
        }
        case 13: {
            exportToFile();
            break;
        }
        case 0: {
            cout << "Exiting...\n";
            break;
        }
        default: cout << "Invalid entry. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}

void addStudent(int r) {
    if (totalStudents >= maxStudents) {
        cout << "Error: Limit Reached.\n";
        return;
    }

    if (r < 0) {
        cout << "Error: No negative roll numbers.\n";
        return;
    }

    for (int i = 0; i < totalStudents; i++) {
        if (rollNumbers[i] == r) {
            cout << "Error: Roll number already exists.\n";
            return;
        }
    }

    rollNumbers[totalStudents] = r;

    cout << "Enter Student Name: ";
    cin >> names[totalStudents];

    int totalMarks = 0;
    for (int j = 0; j < 3; j++) {
        int mark;
        do {
            cout << "Enter marks (0-100) for subject#" << j + 1 << ": ";
            cin >> mark;
            if (mark < 0 || mark > 100) cout << "Error: Invalid entry.\n";
        } while (mark < 0 || mark > 100);

        marks[totalStudents][j] = mark;
        totalMarks += mark;
    }

    averages[totalStudents] = totalMarks / 3.0;

    if (averages[totalStudents] >= 85) {
        grades[totalStudents] = 'A';
    }
    else if (averages[totalStudents] >= 70) {
        grades[totalStudents] = 'B';
    }
    else if (averages[totalStudents] >= 50) {
        grades[totalStudents] = 'C';
    }
    else {
        grades[totalStudents] = 'F';
    }

    for (int k = 0; k < maxDays; k++) {
        attendance[totalStudents][k] = false;
    }
    cout << "Student added successfully.\n";
    totalStudents++;
}

void displayAll() {
    if (totalStudents == 0) {
        cout << "No records to display.\n";
        return;
    }

    cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                                  All Student Records                                                  \n";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";

    cout << left
        << setw(14) << "Name"
        << setw(12) << "Roll No"
        << setw(14) << "Subject #1"
        << setw(14) << "Subject #2"
        << setw(14) << "Subject #3"
        << setw(12) << "Total"
        << setw(12) << "Average"
        << setw(12) << "Grade"
        << setw(14) << "Attendance (%)"
        << endl;

    cout << "----------------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < totalStudents; i++) {

        cout << left
            << setw(14) << names[i]
            << setw(12) << rollNumbers[i];

        int totalMarks = 0;

        for (int j = 0; j < 3; j++) {
            cout << setw(14) << marks[i][j];
            totalMarks += marks[i][j];
        }

        cout << setw(12) << totalMarks;
        cout << setw(12) << averages[i];
        cout << setw(12) << grades[i];

        int present = 0;

        for (int k = 0; k < totalAttendanceDays; k++) {
            if (attendance[i][k] == true) {
                present++;
            }
        }

        float att;

        if (totalAttendanceDays == 0) {
            att = 0;
        }
        else {
            att = (present * 100.0) / totalAttendanceDays;
        }
        int a = int(att);
        cout << setw(14) << a << endl;
    }

    cout << "----------------------------------------------------------------------------------------------------------------------\n";
}

void searchStudent(int r) {
    for (int i = 0; i < totalStudents; i++) {
        if (rollNumbers[i] == r) {
            cout << "Student found.\n";
            cout << "Name: " << names[i] << "\n";
            cout << "Roll Number: " << rollNumbers[i] << "\n";
            cout << "Average: " << averages[i] << "\n";
            cout << "Grade: " << grades[i] << "\n";

            int present = 0;
            for (int k = 0; k < totalAttendanceDays; k++) {
                if (attendance[i][k] == true) {
                    present++;
                }
            }
            float att = 0;
            if (totalAttendanceDays == 0) {
                att = 0;
            }
            else {
                att = (present * 100.0) / totalAttendanceDays;
            }
            cout << "Attendance: " << att << "%\n";
            return;
        }
    }
    cout << "Error: Student not found.\n";
}

void updateMarks(int r) {
    for (int i = 0; i < totalStudents; i++) {
        if (rollNumbers[i] == r) {
            cout << "Student Found: " << names[i] << "\n";
            cout << "1. All subjects\n";
            cout << "2. Subject #1\n";
            cout << "3. Subject #2\n";
            cout << "4. Subject #3\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1: {
                for (int j = 0; j < 3; j++) {
                    do {
                        cout << "Enter marks (0-100) for subject #" << j + 1 << ": ";
                        cin >> marks[i][j];
                        if (marks[i][j] < 0 || marks[i][j] > 100) {
                            cout << "Invalid entry. Please try again.";
                        }
                    } while (marks[i][j] < 0 || marks[i][j] > 100);
                }
                break;
            }
            case 2: {
                do {
                    cout << "Enter marks (0-100) for subject #1: ";
                    cin >> marks[i][0];
                    if (marks[i][0] < 0 || marks[i][0] > 100) {
                        cout << "Invalid entry. Please try again.";
                    }
                } while (marks[i][0] < 0 || marks[i][0] > 100);
                break;
            }
            case 3: {
                do {
                    cout << "Enter marks (0-100) for subject #2: ";
                    cin >> marks[i][1];
                    if (marks[i][1] < 0 || marks[i][1] > 100) {
                        cout << "Invalid entry. Please try again.";
                    }
                } while (marks[i][1] < 0 || marks[i][1] > 100);
                break;
            }
            case 4: {
                do {
                    cout << "Enter marks (0-100) for subject #3: ";
                    cin >> marks[i][2];
                    if (marks[i][2] < 0 || marks[i][2] > 100) {
                        cout << "Invalid entry. Please try again.";
                    }
                } while (marks[i][2] < 0 || marks[i][2] > 100);
                break;
            }
            default:
                cout << "Error: Invalid entry.\n";
                return;
            }

            int totalMarks = 0;
            for (int k = 0; k < 3; k++) {
                totalMarks += marks[i][k];
            }

            averages[i] = totalMarks / 3.0;

            if (averages[i] >= 85) {
                grades[i] = 'A';
            }
            else if (averages[i] >= 70) {
                grades[i] = 'B';
            }
            else if (averages[i] >= 50) {
                grades[i] = 'C';
            }
            else {
                grades[i] = 'F';
            }

            cout << "Marks updated successfully.\n";
            return;
        }
    }

    cout << "Error: Invalid Roll Number.\n";
}

void deleteStudent(int r) {
    for (int i = 0; i < totalStudents; i++) {
        if (rollNumbers[i] == r) {
            cout << "Deleting record...\n";

            for (int j = i; j < totalStudents - 1; j++) {
                rollNumbers[j] = rollNumbers[j + 1];
                names[j] = names[j + 1];
                for (int k = 0; k < 3; k++) {
                    marks[j][k] = marks[j + 1][k];
                }
                averages[j] = averages[j + 1];
                grades[j] = grades[j + 1];
                for (int m = 0; m < totalAttendanceDays; m++) {
                    attendance[j][m] = attendance[j + 1][m];
                }
            }

            totalStudents--;
            cout << "Record deleted successfully.\n";
            return;
        }
    }

    cout << "Error: Invalid Roll Number.\n";
}

void topThree() {
    if (totalStudents < 3) {
        cout << "Error: Not enough records (Need at least 3).\n";
        return;
    }

    for (int i = 0; i < totalStudents - 1; i++) {
        for (int j = 0; j < totalStudents - i - 1; j++) {
            if (averages[j] < averages[j + 1]) {

                float tempAvg = averages[j];
                averages[j] = averages[j + 1];
                averages[j + 1] = tempAvg;

                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;

                int tempRoll = rollNumbers[j];
                rollNumbers[j] = rollNumbers[j + 1];
                rollNumbers[j + 1] = tempRoll;

                char tempGrade = grades[j];
                grades[j] = grades[j + 1];
                grades[j + 1] = tempGrade;

                for (int k = 0; k < 3; k++) {
                    int tempMark = marks[j][k];
                    marks[j][k] = marks[j + 1][k];
                    marks[j + 1][k] = tempMark;
                }

                for (int d = 0; d < totalAttendanceDays; d++) {
                    int tempAtt = attendance[j][d];
                    attendance[j][d] = attendance[j + 1][d];
                    attendance[j + 1][d] = tempAtt;
                }
            }
        }
    }

    cout << "\n-------------------------------------------------------------\n";
    cout << "                     TOP 3 STUDENTS                        \n";
    cout << "-------------------------------------------------------------\n";

    cout << left
        << setw(14) << "Rank"
        << setw(18) << "Name"
        << setw(21) << "Roll no"
        << setw(7) << "Average"
        << endl;

    cout << "-------------------------------------------------------------\n";

    for (int m = 0; m < 3; m++) {
        cout << left
            << setw(14) << m + 1
            << setw(18) << names[m]
            << setw(21) << rollNumbers[m]
            << setw(7) << averages[m]
            << endl;
    }

    cout << "------------------------------------------------------------\n";
}

void gradeSummary() {
    int countA = 0, countB = 0, countC = 0, countF = 0;

    for (int i = 0; i < totalStudents; i++) {
        if (grades[i] == 'A') {
            countA++;
        }
        else if (grades[i] == 'B') {
            countB++;
        }
        else if (grades[i] == 'C') {
            countC++;
        }
        else {
            countF++;
        }
    }

    cout << "\n----------------------\n";
    cout << "     Grade Summary    \n";
    cout << "----------------------\n";

    cout << left
        << setw(6) << "A"
        << setw(6) << "B"
        << setw(6) << "C"
        << setw(6) << "F"
        << endl;

    cout << left
        << setw(6) << countA
        << setw(6) << countB
        << setw(6) << countC
        << setw(6) << countF
        << endl;

    cout << "----------------------\n";

    if (countF > 0) {
        cout << "\n------------------------\n";
        cout << " Students with Grade F  \n";
        cout << "------------------------\n";
        cout << left
            << setw(15) << "Name"
            << setw(15) << "Roll No"
            << endl;
        for (int j = 0; j < totalStudents; j++) {
            if (grades[j] == 'F') {
                cout
                    << setw(15) << names[j]
                    << setw(15) << rollNumbers[j]
                    << endl;
            }
        }
    }
}

void markAttendance() {
    if (totalStudents == 0) {
        cout << "No students available.\n";
        return;
    }

    if (totalAttendanceDays >= maxDays) {
        cout << "Attendance limit reached.\n";
        return;
    }

    cout << "Marking Attendance for Day: " << totalAttendanceDays + 1 << "\n";
    for (int i = 0; i < totalStudents; i++) {
        char att;
        do {
            cout << "Is " << names[i] << " Present? (Enter P/p for present and A/a for absent): ";
            cin >> att;
            if (!(att == 'P' || att == 'p' || att == 'A' || att == 'a')) {
                cout << "Invalid entry. Please try again.";
            }
        } while (!(att == 'P' || att == 'p' || att == 'A' || att == 'a'));

        if (att == 'P' || att == 'p') {
            attendance[i][totalAttendanceDays] = true;
        }
        else {
            attendance[i][totalAttendanceDays] = false;
        }
    }
    cout << "Attendance recorded.\n";
    totalAttendanceDays++;
}

void displayAttendance(int r) {
    for (int i = 0; i < totalStudents; i++) {
        if (rollNumbers[i] == r) {
            cout << "Attendance Record for " << names[i] << ":\n";
            if (totalAttendanceDays == 0) {
                cout << "No attendance taken yet.\n";
                return;
            }
            for (int d = 0; d < totalAttendanceDays; d++) {
                cout << "Day " << d + 1 << ": ";
                if (attendance[i][d] == true) {
                    cout << "Present" << endl;
                }
                else {
                    cout << "Absent" << endl;
                }
            }
            return;
        }
    }
    cout << "Error: Student not found.\n";
}
void attendanceReport() {

    if (totalStudents == 0) {
        cout << "No records.\n";
        return;
    }

    cout << "\n---------------------------------------------------------\n";
    cout << "               Attendance Percentage Report               \n";
    cout << "---------------------------------------------------------\n";
    cout << left
        << setw(12) << "Name"
        << setw(12) << "Roll no"
        << setw(15) << "Attendance %"
        << setw(12) << "Status"
        << endl;

    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < totalStudents; i++) {

        int presentCount = 0;
        for (int d = 0; d < totalAttendanceDays; d++) {
            if (attendance[i][d]) {
                presentCount++;
            }
        }

        float percentage = ((presentCount * 100.0) / totalAttendanceDays);
        int p = int(percentage);

        cout << left
            << setw(12) << names[i]
            << setw(12) << rollNumbers[i]
            << setw(15) << p;

        if (percentage < 75) {
            cout << setw(12) << "WARNING";
        }
        else {
            cout << setw(12) << "OK";
        }

        cout << endl;
    }

    cout << "---------------------------------------------------------\n";
}

void subjectToppers() {
    if (totalStudents == 0) {
        cout << "No records available.\n";
        return;
    }

    cout << "\n---------------------------------------\n";
    cout << "             Subject Toppers           \n";
    cout << "---------------------------------------\n";
    cout << left
        << setw(14) << "Subject"
        << setw(14) << "Name"
        << setw(14) << "Marks"
        << endl;
    cout << "---------------------------------------\n";

    for (int i = 0; i < 3; i++) {
        int highestMarkIndex = 0;
        int highestMark = marks[0][i];

        for (int j = 1; j < totalStudents; j++) {
            if (marks[j][i] > highestMark) {
                highestMark = marks[j][i];
                highestMarkIndex = j;
            }
        }

        cout << left
            << setw(14) << i + 1
            << setw(14) << names[highestMarkIndex]
            << setw(14) << highestMark
            << endl;
    }

    cout << "---------------------------------------\n";
}

void gpaConverter() {
    if (totalStudents == 0) {
        cout << "No records to convert.\n";
        return;
    }

    cout << "\n---------------------------------------------\n";
    cout << "                 GPA Converter                \n";
    cout << "---------------------------------------------\n";
    cout << left
        << setw(14) << "Name"
        << setw(14) << "Roll no"
        << setw(14) << "Average"
        << setw(14) << "GPA"
        << endl;
    cout << "---------------------------------------------\n";

    for (int i = 0; i < totalStudents; i++) {

        float gpa;

        if (averages[i] >= 85) {
            gpa = 4.0;
        }
        else if (averages[i] >= 70) {
            gpa = 3.0;
        }
        else if (averages[i] >= 50) {
            gpa = 2.0;
        }
        else {
            gpa = 0.0;
        }

        cout << left
            << setw(14) << names[i]
            << setw(14) << rollNumbers[i]
            << setw(14) << averages[i]
            << setw(14) << gpa
            << endl;
    }

    cout << "---------------------------------------------\n";
}

void exportToFile() {
    if (totalStudents == 0) {
        cout << "No data to export.\n";
        return;
    }

    ofstream outFile("summary.txt");

    if (!outFile) {
        cout << "Error: Could not create file.\n";
        return;
    }

    outFile << "\n-------------------------------------------------\n";
    outFile << "       STUDENT MANAGEMENT SYSTEM REPORT             \n";
    outFile << "-------------------------------------------------\n";

    outFile << left
        << setw(12) << "Name"
        << setw(12) << "Roll no"
        << setw(12) << "Grade"
        << setw(15) << "Attendance %"
        << endl;

    outFile << "-------------------------------------------------\n";
    for (int i = 0; i < totalStudents; i++) {
        outFile << left
            << setw(12) << names[i]
            << setw(12) << rollNumbers[i]
            << setw(12) << grades[i];

        int presentCount = 0;
        for (int d = 0; d < totalAttendanceDays; d++) {
            if (attendance[i][d]) {
                presentCount++;
            }
        }

        float percentage = ((presentCount * 100.0) / totalAttendanceDays);
        int p = int(percentage);

        outFile << setw(15) << p << endl;
    }

    outFile << "-------------------------------------------------\n";

    outFile.close();
    cout << "Data exported to 'summary.txt'.\n";
}
