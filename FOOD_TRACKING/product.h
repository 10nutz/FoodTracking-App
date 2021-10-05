#pragma once
#include "food.h"
class Product
{
public:
	inline void setQuantity(double);
	inline double getQuantity();
	inline void setServings(int);
	inline int getServings();
	Food foodstuff;
private:
	double quantity;
	int servings;
};

