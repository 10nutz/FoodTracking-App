#pragma once
#include <string>
class Food
{
public:
	inline void setName(std::string);
	inline std::string getName();
	inline void setCalories(int);
	inline int getCalories();
	inline void setFat(double);
	inline double getFat();
	inline void setCarbohydrates(double);
	inline double getCarbohydrates();
	inline void setProtein(double);
	inline double getProtein();


private:
	std::string name;
	int calories;
	double fat;
	double carbohydrates;
	double protein;
};

