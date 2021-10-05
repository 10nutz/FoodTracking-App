#include <iostream>
using namespace std;
#include "user.h"

void User::setName(std::string n)
{
	name = n;
}

string User::getName()
{
	return name;
}

void User::setAge(int a)
{
	age = a;
}

int User::getAge()
{
	return age;
}

void User::setSex(bool s)
{
	sex = s;
}

bool User::getSex()
{
	return sex;
}
void User::setHeight(double h)
{
	height = h;
}

double User::getHeight()
{
	return height;
}

void User::setWeight(double w)
{
	weight = w;
}

double User::getWeight()
{
	return weight;
}

void User::setBMI()
{
	double x;
	x = weight / (height * height);
	if (x <= 18)
		user_bmi = BMI::Under;
	else
		if (x <= 24)
			user_bmi = BMI::Normal1;
		else
			if (x <= 29)
				user_bmi = BMI::Over;
			else
				if (x <= 39)
					user_bmi = BMI::Obese;
				

}
 User::BMI User::getBMI()
{
	return user_bmi;
}
void User::setWeight_Goal(double wg)
{
	weight_goal = wg;
}

double User::getWeight_Goal()
{
	return weight_goal;
}

void User::setActivity(User::activity a)
{
	user_activity = a;
}

User::activity User::getActivity()
{
	return user_activity;
}

void User::setGoal(User::goal g)
{
	user_goal = g;
}

User::goal User::getGoal()
{
	return user_goal;
}

void User::setMetabolism()
{
	if (user_bmi == BMI::Under)
		if (user_activity == Sedentary || user_activity == Light || user_activity == Moderate)
			user_metabolism = metabolism::Fast;
		else
			user_metabolism = metabolism::Normal;
	else
		if (user_bmi == BMI::Normal1)
			if (user_activity == Sedentary || user_activity == Light)
				user_metabolism = metabolism::Fast;
			else
				user_metabolism = metabolism::Normal;
		else
			if (user_bmi == BMI::Over)
				if (user_activity == Intense)
					user_metabolism = metabolism::Slow;
				else
					user_metabolism = metabolism::Normal;
			else
				if (user_bmi == BMI::Obese)
					if (user_activity == Sedentary)
						user_metabolism = metabolism::Normal;
					else
						user_metabolism = metabolism::Slow;
				
}

User::metabolism User::getMetabolism()
{
	return user_metabolism;
}
