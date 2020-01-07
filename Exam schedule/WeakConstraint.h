#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>       
#include <algorithm>

using namespace std;
enum Types {
	// First Of All (WeakConstraint)

	// It is preferable that the examination halls in one subject be on one floor
	First_Constraint = 3,
	// It is preferred to fill the larger examination halls first and then the smaller ones
	Second_Constraint = 2,
	//- It is preferable not to open a large hall for a small number of students, 
	//so it is preferable to place them in a smaller runway to reduce the number of monitors appointed in each session.
	Third_Constraint = 5,
	//It is preferable that there are no blanks between observations on the same day for one person
	//(to monitor the first and third sessions without the second session)
	Fourth_Constraint = 2,
	//It is preferable to follow the person’s desire on the days and times when he prefers to watch
	Fifth_Constraint = 4,
	//It is preferable for the employee to monitor only one observation per day. 
	//While it is preferable that the number of controls specified for the president / non-employee 
	//observer be two per day, unless he specifies in his wishes otherwise
	Sixth_Constraint = 3,
	//It is preferred that the monitors be a college graduate student 
	//and if he is not available he may be from one of the college staff
	Seventh_Constraint = 4,

	// Secondly ( Preferential restrictions )

	//Favorite day
	First_Restriction = 10,
	//Favorite period
	Second_Restriction = 15
};

class WeakConstraint
{
public:
	Types Type;
	int Gravity;
	WeakConstraint() {}
	WeakConstraint(Types type, int gravity) {
		this->Type = type;
		this->Gravity = gravity;
	}
};

