#include "meal.h"
#include <iostream>
using namespace std;

void Meal::setDate(std::string s)
{
	date = s;
}

std::string Meal::getDate()
{
	return date;
}
