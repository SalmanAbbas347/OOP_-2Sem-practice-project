#include "Student.h"

Student::Student() {
    id = 0;
    name = "Unknown";
    marks = 0;
    attendance = 0;
}


Student::Student(int i, string n) {
    id = i;
    name = n;
    marks = 0;
    attendance = 0;
}


Student::Student(const Student& s) {
    id = s.id;
    name = s.name;
    marks = s.marks;
    attendance = s.attendance;
}

int Student::getId() const {
    return id;
}

void Student::markAttendance(int days) {
    attendance += days;
}

void Student::addMarks(float m) {
    marks += m;
}

void Student::addMarks(float quiz, float mid, float final) {
    marks = quiz + mid + final;
}


void Student::display() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Marks: " << marks << endl;
    cout << "Attendance: " << attendance << endl;
}


Student Student::operator+(const Student& s) {
    Student temp;
    temp.marks = this->marks + s.marks;
    return temp;
}


Student Student::operator-(const Student& s) {
    Student temp;
    temp.marks = this->marks - s.marks;
    return temp;
}

bool Student::operator>(const Student& s) {
    return this->marks > s.marks;
}

bool Student::operator==(const Student& s) {
    return this->id == s.id;
}

ostream& operator<<(ostream& out, const Student& s) {
    out << "ID: " << s.id
        << ", Name: " << s.name
        << ", Marks: " << s.marks
        << ", Attendance: " << s.attendance;
    return out;
}