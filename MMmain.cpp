﻿#include "stdafx.h"
#include "mHeader.h"

int main()
{
	int n;
	std::cin >> n;

	while (n < MINIMUM || n > MAXIMUM || n % 2 == 0) {
		std::cout << "Enter an odd number between 2 and 10000" << std::endl;
		std::cin >> n;
	}

	Mmatrix matrix(n);
	std::cout << matrix << std::endl;

    return 0;
}

