// ProjectTwo_KING.cpp 
// Jas King
// CS-300 Project Two
// Date: June 21, 2025


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Define Course structure
struct Course {
    string id;
    string name;
    vector<string> prerequisites;
};

// Function declarations
void loadCourses(string filename, vector<Course>& courseList);
void printAllCourses(const vector<Course>& courseList);
void printCourseInfo(const vector<Course>& courseList, const string& courseId);
bool compareById(const Course& a, const Course& b);

int main() {
    vector<Course> courseList;
    int choice = 0;

    while (choice != 9) {
        cout << "\nMenu:\n";
        cout << "1. Load course data\n";
        cout << "2. Print course list\n";
        cout << "3. Print course information\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            loadCourses(filename, courseList);
            break;
        }
        case 2:
            printAllCourses(courseList);
            break;
        case 3: {
            if (courseList.empty()) {
                cout << "No course data loaded. Please load data first.\n";
                break;
            }
            string id;
            cout << "Enter course ID (e.g., CS101): ";
            cin >> id;
            printCourseInfo(courseList, id);
            break;
        }
        case 9:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

// Load course data from file
void loadCourses(string filename, vector<Course>& courseList) {
    courseList.clear();
    ifstream infile(filename);

    if (!infile) {
        cout << "Error opening file '" << filename << "'. Please check the name and try again.\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string id, name, prereq;

        getline(ss, id, ',');
        getline(ss, name, ',');

        Course course;
        course.id = id;
        course.name = name;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courseList.push_back(course);
    }

    infile.close();
    cout << "Course data loaded successfully.\n";
}
// Sort helper function
bool compareById(const Course& a, const Course& b) {
    return a.id < b.id;
}

// Print all courses
void printAllCourses(const vector<Course>& courseList) {
    if (courseList.empty()) {
        cout << "No course data loaded. Please load data first.\n";
        return;
    }

    vector<Course> sortedList = courseList;
    sort(sortedList.begin(), sortedList.end(), compareById);

    cout << "\nCourse List:\n";
    for (const Course& course : sortedList) {
        cout << course.id << ": " << course.name << endl;
    }
}

// Print info about one course
void printCourseInfo(const vector<Course>& courseList, const string& courseId) {
    for (const Course& course : courseList) {
        if (course.id == courseId) {
            cout << course.id << ": " << course.name << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const string& prereq : course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
            else {
                cout << "No prerequisites.\n";
            }
            return;
        }
    }

    cout << "Course not found.\n";
}

