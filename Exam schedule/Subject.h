#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>       
#include <algorithm>

using namespace std;

class Subject
{
public:
	string Name;
	int Count_ofStudents;
	int day;
	int period;   //  1 first period , 2 second preriod , 3 third period 
	vector<string> NamesOfgrades;
	Subject(string name, int Count_ofStudents) {
		this->Name = name;
		this->Count_ofStudents = Count_ofStudents;
	}
	Subject() {}
	vector<Subject> Seed() {

		vector<Subject> subjects;
		subjects.push_back(Subject("S2", 100));
		subjects.push_back(Subject("S3", 80));
		subjects.push_back(Subject("S1", 50));
		subjects.push_back(Subject("S4", 120));
		//subjects.push_back(Subject("S4", 200));
		//subjects.push_back(Subject("S5", 90));
		return subjects;
	}
};

