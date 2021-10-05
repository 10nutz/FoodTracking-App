#pragma once
#include <iostream>
#include <string>
#include "menu.h"
#include "progress.h"
class Meal
{
public:
	inline void setDate(std::string);
	inline std::string getDate();
	Menu breakfast;
	Menu lunch;
	Menu dinner;
	Menu snacks;
	Progress expected_total;
	Progress real_total;
private:
	std::string date;
};

