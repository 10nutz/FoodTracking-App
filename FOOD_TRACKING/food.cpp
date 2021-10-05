#include <iostream>
#include "food.h"
using namespace std;

void Food::setName(std::string n)
{
	name = n;
}

std::string Food::getName()
{
	return name;
}

void Food::setCalories(int c)
{
	calories = c;
}

int Food::getCalories()
{
	return calories;
}

void Food::setFat(double f)
{
	fat = f;
}

double Food::getFat()
{
	return fat;
}

void Food::setCarbohydrates(double c)
{
	carbohydrates = c;
}

double Food::getCarbohydrates()
{
	return carbohydrates;
}


void Food::setProtein(double p)
{
	protein = p;
}

double Food::getProtein()
{
	return protein;
}

























