#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>       
#include <algorithm>
#include "Person.h"
#include "Subject.h"
#include "Grade.h"

using namespace std;

class State {
public:
	vector<Grade> grades;
	int Cost;
	vector<string> Details;
	bool operator>(const State& rhs) const
	{
		return Cost > rhs.Cost;
	}
};
class Comparison
{
public:
	bool operator() (State State1, State State2) const
	{
		//by default comparing the integer values
		return (State1 > State2);
	}
};