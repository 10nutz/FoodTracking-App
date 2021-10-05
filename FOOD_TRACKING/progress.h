#pragma once
class Progress
{
public:
	Progress()
	{
		consumption = 0;
		protein = 0; 
		carbohydrate = 0;
		fat = 0;
	}
	Progress operator%(int p)
	{
		Progress k;

		k.consumption = consumption * p / 100;
		k.protein = protein * p / 100;
		k.carbohydrate = carbohydrate * p / 100;
		k.fat = fat * p / 100;

		return k;
	}

	Progress operator+(Progress p)
	{
		Progress k;

		k.consumption = consumption + p.consumption;
		k.protein = protein + p.protein;
		k.carbohydrate = carbohydrate + p.carbohydrate;
		k.fat = fat + p.fat;

		return k;
	}
	inline void setConsumption(int);
	inline int getConsumption();
	inline void setProtein(double);
	inline double getProtein();
	inline void setCarbohydrate(double);
	inline double getCarbohydrate();
	inline void setFat(double);
	inline double getFat();
private:
	int consumption;
	double protein;
	double carbohydrate;
	double fat;
};
