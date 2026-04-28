#include <iostream>
#include "Student.h"
using namespace std;

int main() {
	Student students[10];
	int count = 0;

	int role;

	do {
		cout << "\n======= SYSTEM LOGIN ==========\n";
		cout << "1. Admin\n2. Teacher\n3. Student\n4. Exit\nChoice: ";
		cin >> role;

		// ---------------- ADMIN ----------------
		if (role == 1) {
			int op;
			do {
				cout << "\n====== Admin Dashboard =======\n";
				cout << "1. Add Student\n2. View All Records\n3. Logout\nChoice: ";
				cin >> op;

				if (op == 1) {
					if (count >= 10) {
						cout << "Student limit reached!\n";
						continue;
					}

					int id, attendance;
					string name;
					float marks;

					cout << "Enter ID: ";
					cin >> id;
					cout << "Enter Name: ";
					cin >> name;
					cout << "Enter Marks: ";
					cin >> marks;
					cout << "Enter Attendance: ";
					cin >> attendance;

					students[count] = Student(id, name);
					students[count].addMarks(marks);
					students[count].markAttendance(attendance);

					count++;
					cout << "Student Added Successfully!\n";
				}

				else if (op == 2) {
					cout << "\n======= All Records ========\n";
					for (int i = 0; i < count; i++) {
						cout << "ID: " << students[i].getId() << " -> "
							<< students[i] << endl;
					}
				}

			} while (op != 3);
		}

		// ---------------- TEACHER ----------------
		else if (role == 2) {
			int op;
			do {
				cout << "\n======= Teacher Dashboard =======\n";
				cout << "1. Add/Update Marks\n2. Mark Attendance\n3. View Students\n4. Logout\nChoice: ";
				cin >> op;

				if (op == 1) {
					int id;
					float q, m, f;

					cout << "\n--- Student List ---\n";
					for (int i = 0; i < count; i++) {
						cout << "ID: " << students[i].getId() << " -> "
							<< students[i] << endl;
					}

					cout << "Enter Student ID: ";
					cin >> id;

					int index = -1;
					for (int i = 0; i < count; i++) {
						if (students[i].getId() == id) {
							index = i;
							break;
						}
					}

					if (index != -1) {
						cout << "Enter Quiz, Mid, Final: ";
						cin >> q >> m >> f;
						students[index].addMarks(q, m, f);
						cout << "Marks Updated!\n";
					}
					else {
						cout << "Student not found!\n";
					}
				}

				else if (op == 2) {
					int id, days;

					cout << "\n--- Student List ---\n";
					for (int i = 0; i < count; i++) {
						cout << "ID: " << students[i].getId() << " -> "
							<< students[i] << endl;
					}

					cout << "Enter Student ID: ";
					cin >> id;

					int index = -1;
					for (int i = 0; i < count; i++) {
						if (students[i].getId() == id) {
							index = i;
							break;
						}
					}

					if (index != -1) {
						cout << "Enter Attendance Days: ";
						cin >> days;
						students[index].markAttendance(days);
						cout << "Attendance Updated!\n";
					}
					else {
						cout << "Student not found!\n";
					}
				}

				else if (op == 3) {
					cout << "\n--- Student Records ---\n";
					for (int i = 0; i < count; i++) {
						cout << "ID: " << students[i].getId() << " -> "
							<< students[i] << endl;
					}
				}

			} while (op != 4);
		}

		// ---------------- STUDENT ----------------
		else if (role == 3) {
			int id;
			cout << "Enter Your Student ID: ";
			cin >> id;

			int index = -1;
			for (int i = 0; i < count; i++) {
				if (students[i].getId() == id) {
					index = i;
					break;
				}
			}

			if (index != -1) {
				cout << "\n====== Your Record =======\n";
				students[index].display();
			}
			else {
				cout << "Student not found!\n";
			}
		}

	} while (role != 4);

	cout << "\nSystem Exit\n";
	return 0;
}