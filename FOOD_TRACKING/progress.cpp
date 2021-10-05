#include "progress.h"
#include <iostream>
using namespace std;

void Progress::setConsumption(int c)
{
	consumption = c;
}

int Progress::getConsumption()
{
	return consumption;
}

void Progress::setProtein(double p)
{
	protein = p;
}

double Progress::getProtein()
{
	return protein;
}


void Progress::setCarbohydrate(double c)
{
	carbohydrate = c;
}

double Progress::getCarbohydrate()
{
	return carbohydrate;
}


void Progress::setFat(double f)
{
	fat = f;
}

double Progress::getFat()
{
	return fat;
}