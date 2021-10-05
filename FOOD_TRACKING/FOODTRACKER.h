#pragma once
#include <vector>
#include "user.h"
#include "meal.h"
#include "food.h"

class FoodTracker {
public:
	User acc;
	vector<Food> vf;
	vector<Meal> vm;
};