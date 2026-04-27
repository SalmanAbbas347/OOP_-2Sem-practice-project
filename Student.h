#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student {
private:
    int id;
    string name;
    float marks;
    int attendance;

public:
    
    Student();
    Student(int i, string n);
    Student(const Student& s);

    void markAttendance(int days);
    int getId() const;
    
    void addMarks(float m);
    void addMarks(float quiz, float mid, float final);

    void display() const;

    
    Student operator+(const Student& s);   
    Student operator-(const Student& s);   
    bool operator>(const Student& s);      
    bool operator==(const Student& s);     

    friend ostream& operator<<(ostream& out, const Student& s);
};

#endif