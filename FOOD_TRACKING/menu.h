#pragma once
#include <iostream>
#include "product.h"
#include "progress.h"
#include <vector>
class Menu
{
public:
	std::vector <Product> suggested;
	std::vector <Product> consumed;
	Progress p_expected;
	Progress p_real;
};

