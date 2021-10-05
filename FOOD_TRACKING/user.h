#pragma once
#include <iostream>
using namespace std;
class User
{
public:
	inline enum activity { Sedentary, Light, Moderate, Intense };
	inline enum goal { Weight_loss, Mentain, Weight_gain };
	inline enum  metabolism { Slow, Normal, Fast };
	inline enum  BMI { Under, Normal1, Over, Obese};
	inline void setName(string);
	inline string getName();
	inline void setAge(int);
	inline int getAge();
	inline void setSex(bool);
	inline bool getSex();
	inline void setHeight(double);
	inline double getHeight();
	inline void setWeight(double);
	inline double getWeight();
	inline void setWeight_Goal(double);
	inline double getWeight_Goal();
	inline void setActivity(User::activity);
	inline activity getActivity();
	inline void setGoal(User::goal);
	inline goal getGoal();
	inline void setMetabolism();
	inline metabolism getMetabolism();
	inline void setBMI();
	inline BMI getBMI();
private:
	std::string name;
	int age;
	bool sex;
	double height;
	double weight;
	double weight_goal;
	activity user_activity;
	goal user_goal;
	metabolism user_metabolism;
	BMI user_bmi;
};

