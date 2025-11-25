#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

struct Student {
    string name;
    double grade;
    double attendance;
    double studyHours;
    double score;
    string category;
};

class StudentPredictor {
private:
    vector<Student> students;

    double gradeWeight;
    double attendanceWeight;
    double studyHoursWeight;
    double maxStudyHours;

    double calculateScore(const Student& student) {
        if (student.grade < 0 || student.grade > 100 ||
            student.attendance < 0 || student.attendance > 100 ||
            student.studyHours < 0) {
            return -1;
        }

        double normalizedStudyHours = student.studyHours / maxStudyHours * 100;
        if (normalizedStudyHours > 100.0)
            normalizedStudyHours = 100.0;

        return (student.grade * gradeWeight) +
               (student.attendance * attendanceWeight) +
               (normalizedStudyHours * studyHoursWeight);
    }

    string predictCategory(const Student& s) {
        if (s.studyHours < 5) {
            if (s.attendance < 60)
                return "Needs Improvement";
            else
                return "Average";
        } else {
            if (s.grade >= 75) return "Excellent";
            else if (s.grade >= 50) return "Good";
            else return "Average";
        }
    }

    bool validateName(const string& name) {
        if (name.empty()) return false;
        for (size_t i = 0; i < name.length(); ++i) {
            char c = name[i];
            if (!isalpha(c) && !isspace(c) && c != '.') {
                return false;
            }
        }
        return true;
    }

    bool validateNumber(double value, double min, double max) {
        return value >= min && value <= max;
    }

public:
    StudentPredictor() {
        gradeWeight = 0.5;
        attendanceWeight = 0.3;
        studyHoursWeight = 0.2;
        maxStudyHours = 40.0;
    }

    void addStudent() {
        Student student;
        string input;

        do {
            cout << "Enter student name: ";
            getline(cin, student.name);
            if (!validateName(student.name)) {
                cout << "Invalid name. Use letters, spaces, or periods only.\n";
            }
        } while (!validateName(student.name));

        bool valid = false;
        do {
            cout << "Enter grade (0-100): ";
            getline(cin, input);
            stringstream ss(input);
            if (ss >> student.grade && validateNumber(student.grade, 0, 100)) valid = true;
            else cout << "Invalid grade.\n";
        } while (!valid);

        valid = false;
        do {
            cout << "Enter attendance (0-100): ";
            getline(cin, input);
            stringstream ss(input);
            if (ss >> student.attendance && validateNumber(student.attendance, 0, 100)) valid = true;
            else cout << "Invalid attendance.\n";
        } while (!valid);

        valid = false;
        do {
            cout << "Enter weekly study hours: ";
            getline(cin, input);
            stringstream ss(input);
            if (ss >> student.studyHours && validateNumber(student.studyHours, 0, numeric_limits<double>::max())) valid = true;
            else cout << "Invalid study hours.\n";
        } while (!valid);

        student.score = calculateScore(student);
        student.category = (student.score == -1) ? "Invalid" : predictCategory(student);
        students.push_back(student);
    }

    void displayResults() {
        if (students.empty()) {
            cout << "\nNo students added.\n";
            return;
        }

        cout << "\nStudent Performance:\n";
        cout << left << setw(20) << "Name"
             << setw(10) << "Grade"
             << setw(12) << "Attendance"
             << setw(12) << "Study Hrs"
             << setw(10) << "Score"
             << setw(18) << "Category" << "\n";
        cout << string(80, '-') << "\n";

        for (size_t i = 0; i < students.size(); ++i) {
            Student s = students[i];
            cout << left << setw(20) << s.name
                 << setw(10) << fixed << setprecision(2) << s.grade
                 << setw(12) << s.attendance
                 << setw(12) << s.studyHours;

            if (s.score == -1)
                cout << setw(10) << "Invalid";
            else
                cout << setw(10) << fixed << setprecision(2) << s.score;

            cout << setw(18) << s.category << "\n";
        }
    }

    void sortByScore() {
        sort(students.begin(), students.end(), compareByScore);
    }

    static bool compareByScore(const Student& a, const Student& b) {
        return a.score > b.score;
    }
};

int main() {
    StudentPredictor predictor;
    char choice;

    cout << "============================\n";
    cout << " Student Performance Tool\n";
    cout << "============================\n";

    do {
        predictor.addStudent();
        cout << "Add another student? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (tolower(choice) != 'y' && tolower(choice) != 'n') {
            cout << "Invalid choice. Enter y or n: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (tolower(choice) == 'y');

    predictor.sortByScore();
    predictor.displayResults();

    return 0;
}

