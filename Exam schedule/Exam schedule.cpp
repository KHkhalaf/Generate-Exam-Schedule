#include <iostream>
#include <vector>
#include <list>
#include <queue>       
#include <algorithm>
#include <string> 
#include <map>
#include "Subject.h"
#include "WeakConstraint.h"
#include "Grade.h"
#include "State.cpp"

using namespace std;

map<State, int> visitor;
vector<Grade> grades;
vector<Subject> subjects;
vector<Person> persons;
vector<vector<vector<Person>>> PersonsByDate;

bool CheckVisited(vector<State> states, State state);
bool checkStatusForGrade(vector<Grade> grades, Grade grade);
bool checkTheSameFloor(State state);
bool ContainsPersident(int countPersident, vector<Person> persons);
void Init();
void SortPersonsByDate();
vector<State> Function_Transition(vector<State> states);
vector<State> UCF(int size);
pair<int, vector<Grade>> count_persons(Subject subject);


int main()
{
	Init();
	SortPersonsByDate();
	int TotalCost = 0;
	vector<State> states = UCF(subjects.size());
	cout << " Day   | Subject | period | Grade | Numbers students | Grade president | Grade secretary | Observers";
	cout << "\n--------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < states.size(); i++) {
		for (int j = 0; j < states[i].grades.size(); j++) {
			int first = states[i].grades[j].RangeForStudents.first;
			int second = states[i].grades[j].RangeForStudents.second;
			cout << " " + to_string(states[i].grades[j].subject.day) + "\t  " + states[i].grades[j].subject.Name
				+ "\t   " + to_string(states[i].grades[j].subject.period)
				+ "\t   " + states[i].grades[j].Name + "\t\t" + to_string(first) + "-" + to_string(second)
				+ "\t\t" + states[i].grades[j].gradePresident.Name + "\t\t  " + states[i].grades[j].gradeSecretary.Name
				+ "\t   ";
			for (int o = 0; o < states[i].grades[j].Observers.size(); o++) {
				cout << states[i].grades[j].Observers[o].Name + "  ";
			}
			cout << endl;
		}
		cout << "\n-------------------------------------------------------------------------------------------------------\n";
	}
	cout << "\nDetails :\n\n";
	for (int i = 0; i < states.size(); i++) {
		for (int j = 0; j < states[i].Details.size(); j++) {
			cout << "\n" + states[i].Details[j] + "\n";
		}
		TotalCost += states[i].Cost;
	}
	cout << "\nTotal Cost = " + to_string(TotalCost) + "\n";
	return 0;
}

vector<State> UCF(int size)
{
	int current = 0; vector<State> States;
	priority_queue<State, vector<State>, Comparison> pq;

	State vstart;

	vstart.grades.push_back(Grade());
	vstart.Cost = 0;

	vector<int>::iterator i;
	pq.push(vstart);

	while (!pq.empty())
	{
		State top;

		top = pq.top();
		if (top.Cost > 0)
			States.push_back(top);
		int _size = pq.size();
		for (int i = 0; i < _size; i++)
			pq.pop();
		if (States.size() == size)
		{
			return States;
		}
		else
		{
			vector<State> _states = Function_Transition(States);
			for (int i = 0; i < _states.size(); i++) {
				pq.push(_states[i]);
			}
		}
	}
	return States;
}

void SortPersonsByDate() {
	vector<vector<Person>> Ps;
	PersonsByDate.push_back(Ps);
	PersonsByDate.push_back(Ps);
	PersonsByDate.push_back(Ps);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 40; j++) {
			vector<Person> Vp;
			PersonsByDate[i].push_back(Vp);
		}
	for (int i = 0; i < persons.size(); i++) {
		Person p = persons[i];
		if (p.Periods.size() > 0 && p.ListofDaysGood.size() > 0) {
			for (int j = 0; j < p.ListofDaysGood.size(); j++) {
				int day = stoi(p.ListofDaysGood[j]);
				if (p.Periods[0])
					PersonsByDate[0][day].push_back(p);
				if (p.Periods[1])
					PersonsByDate[1][day].push_back(p);
				if (p.Periods[2])
					PersonsByDate[2][day].push_back(p);
			}
		}
		else if (p.Periods.size() == 0 && p.ListofDaysGood.size() > 0) {
			for (int i = 0; i < p.ListofDaysGood.size(); i++) {
				int day = stoi(p.ListofDaysGood[i]);
				PersonsByDate[0][day].push_back(p);
				PersonsByDate[1][day].push_back(p);
				PersonsByDate[2][day].push_back(p);
			}
		}
		else if (p.Periods.size() > 0 && p.ListofDaysGood.size() == 0) {
			for (int i = 0; i < 40; i++) {
				if (p.Periods[0])
					PersonsByDate[0][i].push_back(p);
				if (p.Periods[1])
					PersonsByDate[1][i].push_back(p);
				if (p.Periods[2])
					PersonsByDate[2][i].push_back(p);
			}
		}
		else if (p.Periods.size() == 0 && p.ListofDaysGood.size() == 0) {
			for (int i = 0; i < 40; i++) {
				PersonsByDate[0][i].push_back(p);
				PersonsByDate[1][i].push_back(p);
				PersonsByDate[2][i].push_back(p);
			}
		}
	}
}

void Init() {

	subjects = Subject().Seed();

	grades = Grade().Seed();

	persons = Person().Seed();
}

vector<State> Function_Transition(vector<State> _states) {
	State state;
	vector<State> states;
	int cost = 0, num_subject = _states.size();
	pair<int, vector<Grade>> p = count_persons(subjects[num_subject]);
	vector<Grade> _grades = p.second;
	int countObservers = p.first;
	for (int k = 0; k < 3; k++) {
		for (int d = 0; d < PersonsByDate[k].size(); d++) {
			if (countObservers + (_grades.size() * 2) <= PersonsByDate[k][d].size() && ContainsPersident(_grades.size(), PersonsByDate[k][d])) {
				PersonsByDate.clear();
				SortPersonsByDate();
				for (int g = 0; g < _grades.size(); g++) {
					Grade grade = _grades[g];
					grade.subject.day = d;
					grade.subject.period = k + 1;
					Person gradePresident;
					Person gradeSecretary;
					vector<Person> Observers;
					for (int p = 0; p < PersonsByDate[k][d].size(); p++) {
						if ((PersonsByDate[k][d][p].type == Prof || PersonsByDate[k][d][p].type == Eng)
							&& !gradePresident.Status_Observation && !PersonsByDate[k][d][p].Status_Observation) {
							PersonsByDate[k][d][p].Status_Observation = true;
							gradePresident.Status_Observation = true;
							gradePresident = PersonsByDate[k][d][p];
						}
						if (PersonsByDate[k][d][p].type == Staff && !gradeSecretary.Status_Observation
							&& !PersonsByDate[k][d][p].Status_Observation) {
							PersonsByDate[k][d][p].Status_Observation = true;
							gradeSecretary.Status_Observation = true;
							gradeSecretary = PersonsByDate[k][d][p];
						}
						if ((PersonsByDate[k][d][p].type == GraduateStudent || PersonsByDate[k][d][p].type == Staff)
							&& !PersonsByDate[k][d][p].Status_Observation && Observers.size() < grade.Count_Observers) {
							PersonsByDate[k][d][p].Status_Observation = true;
							Observers.push_back(PersonsByDate[k][d][p]);
						}
					}
					// Periods
					if (gradePresident.Favorite_Periods.size() > 0 && !gradePresident.Favorite_Periods[k]) {
						cost += Second_Restriction;
						state.Details.push_back("Subject : " + subjects[num_subject].Name
							+ " for grade President " + gradePresident.Name + " period " + to_string(k + 1) + " not compatible , Cost=" + to_string(Second_Restriction));
					}
					for (int o = 0; o < Observers.size(); o++)
						if (Observers[o].Favorite_Periods.size() > 0 && !Observers[o].Favorite_Periods[k]) {
							cost += Second_Restriction;
							state.Details.push_back("Subject : " + subjects[num_subject].Name
								+ " for Observer " + Observers[o].Name + " period "
								+ to_string(k + 1) + " not compatible , Cost=" + to_string(Second_Restriction));
						}
					// Days
					for (int dd = 0; dd < gradePresident.Favorite_Days.size(); dd++)
						if (gradePresident.Favorite_Days[dd] != d) {
							cost += First_Restriction;
							state.Details.push_back("Subject : " + subjects[num_subject].Name
								+ " for grade President " + gradePresident.Name + " day "
								+ to_string(d) + " not compatible , Cost=" + to_string(First_Restriction));
						}
					for (int o = 0; o < Observers.size(); o++)
						for (int dd = 0; dd < Observers[o].Favorite_Days.size(); dd++)
							if (Observers[o].Favorite_Days[dd] != d) {
								cost += First_Restriction;
								state.Details.push_back("Subject : " + subjects[num_subject].Name
									+ " for Observer " + Observers[o].Name + " day "
									+ to_string(d) + " not compatible , Cost=" + to_string(First_Restriction));
							}
					grade.gradePresident = gradePresident;
					grade.gradeSecretary = gradeSecretary;
					grade.Observers = Observers;
					state.grades.push_back(grade);
				}
				if (!checkTheSameFloor(state)) {
					cost += First_Constraint;
					state.Details.push_back("Subject : " + subjects[num_subject].Name
						+ " for Floors not compatible , Cost=" + to_string(First_Constraint));
				}
				if (cost == 0)
					cost = 1;
				state.Cost = cost;
				if (CheckVisited(_states, state))
				{
					states.push_back(state);
					_states.push_back(state);
				}
				State state1;
				state = state1;
				cost = 0;
			}
		}
	}

	return states;
}

bool ContainsPersident(int countPersident, vector<Person> persons) {
	int count = 0;
	for (int i = 0; i < persons.size(); i++)
		if (persons[i].type == Prof || persons[i].type == Eng)
			count++;
	if (count >= countPersident)
		return true;
	return false;
}

bool CheckVisited(vector<State> states, State state) {
	for (int j = 0; j < states.size(); j++) {
		int _min = min(states[j].grades.size(), state.grades.size());
		for (int i = 0; i < _min; i++) {
			if (states[j].grades[i].subject.day == state.grades[i].subject.day &&
				states[j].grades[i].subject.period == state.grades[i].subject.period)
				return false;
		}
	}
	return true;
}

bool checkTheSameFloor(State state) {
	int floor = state.grades[0].Floor;
	for (int i = 0; i < state.grades.size(); i++) {
		if (state.grades[i].Floor != floor)
			return false;
	}
}

bool checkStatusForGrade(vector<Grade> grades, Grade grade)
{
	for (int i = 0; i < grades.size(); i++) {
		if (grade.Name == grades[i].Name)
			return false;
	}
	return true;
}

pair<int, vector<Grade>> count_persons(Subject subject) {
	int students = subject.Count_ofStudents, sum = 0, countObservers = 0;
	vector<Grade> _grades;
	for (int j = 0; j < grades.size() && students > 0; j++) {
		if (grades[j].Status) {  //  grade free not blocked
			if (grades[j].Size <= students) {
				Grade grade = grades[j];
				students -= grade.Size;
				grade.Status = false;
				grade.subject = subject;
				grade.RangeForStudents.first = sum + 1;
				grade.RangeForStudents.second = sum + grade.Size;
				sum += grade.Size;
				grade.subject = subject;
				_grades.push_back(grade);
				if (grade.Size <= 30)
					countObservers++;
				else if (grade.Size > 30 && grade.Size < 60) {
					countObservers++, countObservers++;
				}
				else if (grade.Size >= 60) {
					countObservers++, countObservers++, countObservers++, countObservers++;
				}
			}
			else {
				for (int k = grades.size() - 1; k >= 0 && students > 0; k--) {
					if (grades[k].Status && grades[k].Size >= students) {
						Grade grade = grades[k];
						grade.Status = false;
						grade.subject = subject;
						grade.RangeForStudents.first = sum + 1;
						grade.RangeForStudents.second = sum + students;
						sum += grade.Size;
						grade.subject = subject;
						students = 0;
						_grades.push_back(grade);
						if (grade.Size <= 30)
							countObservers++;
						else if (grade.Size > 30 && grade.Size < 60) {
							countObservers++, countObservers++;
						}
						else if (grade.Size >= 60) {
							countObservers++, countObservers++, countObservers++, countObservers++;
						}
					}
				}
			}
		}
	}
	return make_pair(countObservers, _grades);
}
