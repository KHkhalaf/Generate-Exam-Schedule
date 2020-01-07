#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>       
#include <algorithm>
#include "Person.h"
#include "Subject.h"

using namespace std;

class Grade
{
public:
	string Name;
	int Size;
	bool Status; // true is free  ,   false is blocked
	int Floor;  //  1 first floor , 2 second floor , 3 third floor
	int Count_Observers;
	pair<int, int> RangeForStudents;
	Person gradePresident;
	Person gradeSecretary;
	vector<Person> Observers;
	Subject subject;
	Grade(string name, int size, int countObservers, int floor) {
		Name = name;
		Size = size;
		Count_Observers = countObservers;
		Floor = floor;
		Status = true;
		if (size <= 30)
			Observers.push_back(Person());
		else if (size > 30 && size < 60) {
			Observers.push_back(Person());
			Observers.push_back(Person());
		}
		else if (size >= 60) {
			Observers.push_back(Person());
			Observers.push_back(Person());
			Observers.push_back(Person());
			Observers.push_back(Person());
		}
	}
	Grade() {}
	vector<Grade> Seed() {

		vector<Grade> Grades;
		Grades.push_back(Grade("G10", 70, 4, 1));
		Grades.push_back(Grade("G4", 70, 4, 2));
		Grades.push_back(Grade("G9", 60, 3, 3));
		Grades.push_back(Grade("G3", 60, 3, 1));
		Grades.push_back(Grade("G8", 50, 2, 2));
		Grades.push_back(Grade("G2", 50, 2, 3));
		Grades.push_back(Grade("G11", 30, 1, 1));
		Grades.push_back(Grade("G1", 30, 1, 2));
		Grades.push_back(Grade("G5", 30, 1, 3));
		Grades.push_back(Grade("G7", 30, 1, 1));
		Grades.push_back(Grade("G12", 20, 1, 2));
		Grades.push_back(Grade("G6", 20, 1, 3));

		return Grades;
	}
};

