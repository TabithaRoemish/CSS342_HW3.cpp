// FileName: Food.h
// Programmer: Tabitha Roemish
// Date: 10/12/2017
// File inludes: Food class declarations and definitions

#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <iostream>

using namespace std;

//Food class declaration
class Food
{

public:
	Food(string name = "", int cal = 0);
	~Food() {};
	int getCalories() const { return calories; };
	string getName() const { return name; };
	void setName(string nm) { name = nm; };
	void setCal(int cal) { calories = cal; };
	bool operator>(const Food &fd) const;
	bool operator<(const Food &fd) const;
	bool operator==(const Food &fd) const;
private:
	int calories;
	string name;
};

ostream& operator<<(ostream& out, const Food & fd)
{
	out << fd.getName() << ": " << fd.getCalories() << endl;
	return out;
}

Food::Food(string nm, int cal)
{
	name = nm;
	calories = cal;
}

bool Food::operator>(const Food &fd) const
{
	bool answer = false;
	if (fd.calories > calories)
		answer = true;
	return answer;
}

bool Food::operator<(const Food &fd) const
{
	bool answer = false;
	if (fd.calories < calories)
		answer = true;
	return answer;
}

bool Food::operator==(const Food &fd) const
{
	bool answer = false;
	if (fd.calories == calories)
		answer = true;
	return answer;
}
#endif
