#pragma once
#include <iostream>
#include <vector>
#include <queue>       
#include <algorithm>
#include "WeakConstraint.h"
#include "WeakConstraint.h"

using namespace std;
enum TypePerson {
	Prof,
	Eng,
	GraduateStudent,
	Staff
};
class Person
{
public:
	string Name;
	int CountOfObservations;
	TypePerson type;
	bool Status_Observation; //   true  observing  ,  false  not observing
	vector<string> ListofDaysGood;
	vector<string> ListofDaysNotGood;
	vector<bool> Periods;
	vector<int> Favorite_Days;
	vector<bool> Favorite_Periods;
	Person() {	}
	Person(string name, int countOfObservations, TypePerson type, vector<string>goodDays, vector<string>notgoodDys,
		vector<bool>periods, vector<int>favorite_Days, vector<bool>favorite_Periods) {
		Name = name;
		CountOfObservations = countOfObservations;
		this->type = type;
		ListofDaysGood = goodDays;
		ListofDaysNotGood = notgoodDys;
		Periods = periods;
		Favorite_Days = favorite_Days;
		Favorite_Periods = favorite_Periods;
		Status_Observation = false;
	}
	vector<Person> Seed() {
		vector<Person> Persons;

		// Person Dr.A
		{
			ListofDaysGood.push_back("1"); ListofDaysGood.push_back("5"); ListofDaysGood.push_back("8");
			ListofDaysNotGood.push_back("7"); ListofDaysNotGood.push_back("12"); ListofDaysNotGood.push_back("3");
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(false);
			Favorite_Days.push_back(8);
			Favorite_Periods.push_back(true);// for first period
			Favorite_Periods.push_back(false);// for first period
			Favorite_Periods.push_back(false);// for first period
			Persons.push_back(Person("Dr.A", 5, Prof, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Dr.B
		{
			ListofDaysGood.push_back("1"); ListofDaysGood.push_back("5"); ListofDaysGood.push_back("7");
			ListofDaysNotGood.push_back("9");
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(true);
			Favorite_Days.push_back(5);
			Favorite_Periods.push_back(false);// for first period
			Favorite_Periods.push_back(true);// for second period
			Favorite_Periods.push_back(false);// for third period
			Persons.push_back(Person("Dr.B", 4, Prof, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Eng.A
		{
			ListofDaysGood.push_back("10"); ListofDaysGood.push_back("6"); ListofDaysGood.push_back("2");
			ListofDaysNotGood.push_back("1"); ListofDaysNotGood.push_back("9");
			Periods.push_back(true);// for first period
			Periods.push_back(true);// for second period
			Periods.push_back(false);// for third period
			Favorite_Days.push_back(6);
			Persons.push_back(Person("Eng.A", 5, Eng, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Eng.B
		{
			ListofDaysGood.push_back("5"); ListofDaysGood.push_back("6"); ListofDaysGood.push_back("9");
			ListofDaysNotGood.push_back("10");
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(true);
			Favorite_Days.push_back(5);
			Favorite_Periods.push_back(false);// for first period
			Favorite_Periods.push_back(true); // for second period
			Favorite_Periods.push_back(true); // for third period
			Persons.push_back(Person("Eng.B", 4, Eng, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person GraduateStudent.A
		{
			Persons.push_back(Person("GraduateStudent.A", 5, GraduateStudent, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person GraduateStudent.B
		{
			ListofDaysGood.push_back("1"); ListofDaysGood.push_back("4"); ListofDaysGood.push_back("7");
			ListofDaysNotGood.push_back("5");
			Periods.push_back(false); Periods.push_back(true); Periods.push_back(true);
			Favorite_Days.push_back(1);
			Favorite_Days.push_back(7);
			Favorite_Periods.push_back(false);// for first period
			Favorite_Periods.push_back(true);// for second period
			Favorite_Periods.push_back(false);// for third period
			Persons.push_back(Person("GraduateStudent.B", 4, GraduateStudent, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person GraduateStudent.C
		{
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(false);
			Persons.push_back(Person("GraduateStudent.C", 5, GraduateStudent, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person GraduateStudent.D
		{
			ListofDaysGood.push_back("5"); ListofDaysGood.push_back("2"); ListofDaysGood.push_back("10");
			ListofDaysNotGood.push_back("10");
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(true);
			Favorite_Days.push_back(2);
			Favorite_Days.push_back(10);
			Favorite_Periods.push_back(true);// for first period
			Favorite_Periods.push_back(true);// for second period
			Favorite_Periods.push_back(true);// for third period
			Persons.push_back(Person("GraduateStudent.D", 4, GraduateStudent, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person GraduateStudent.E
		{
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(false);
			Persons.push_back(Person("GraduateStudent.E", 5, GraduateStudent, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person GraduateStudent.F
		{
			ListofDaysGood.push_back("5"); ListofDaysGood.push_back("2"); ListofDaysGood.push_back("10");
			ListofDaysNotGood.push_back("6"); ListofDaysNotGood.push_back("8");
			Periods.push_back(true); Periods.push_back(true); Periods.push_back(false);
			Favorite_Days.push_back(2);
			Favorite_Periods.push_back(true);// for first period
			Favorite_Periods.push_back(false);// for second period
			Favorite_Periods.push_back(true);// for third period
			Persons.push_back(Person("GraduateStudent.F", 4, GraduateStudent, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.A
		{
			Persons.push_back(Person("Staff.A", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.B
		{
			Persons.push_back(Person("Staff.B", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.C
		{
			Persons.push_back(Person("Staff.C", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.D
		{
			Persons.push_back(Person("Staff.B", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.E
		{
			Persons.push_back(Person("Staff.E", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.F
		{
			Persons.push_back(Person("Staff.F", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.G
		{
			Persons.push_back(Person("Staff.G", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();

		// Person Staff.H
		{
			Persons.push_back(Person("Staff.H", 5, Staff, ListofDaysGood, ListofDaysNotGood, Periods, Favorite_Days, Favorite_Periods));
		}
		FreeUpSpace();
		return Persons;
	}
	// free up space
	void FreeUpSpace() {
		ListofDaysGood.clear(); ListofDaysNotGood.clear();
		Periods.clear(); Favorite_Days.clear(); Favorite_Periods.clear();
	}
};

