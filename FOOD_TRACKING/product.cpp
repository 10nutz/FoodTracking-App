#include "product.h"
#include <iostream>
using namespace std;

void Product::setQuantity(double q)
{
	quantity = q;
}

double Product::getQuantity()
{
	return quantity;
}

void Product::setServings(int s)
{
	servings = s;
}

int Product::getServings()
{
	return servings;
}