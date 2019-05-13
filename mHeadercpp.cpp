#include "stdafx.h"
#include "mHeader.h"

//private functions
void Mmatrix::CopyFrom(const Mmatrix &other) {
	setN(other.n);
	this->matrix = new (std::nothrow) char*[height];
	if (!matrix) {
		std::cout << "Error in Mmatrix::CopyFrom()" << std::endl;
		setEmpty();
	}
	else {
		for (int i = 0; i < height; ++i) {
			matrix[i] = new (std::nothrow) char[width];
			if (!matrix[i]) {
				std::cout << "Error in Mmatrix::CopyFrom(), 1" << std::endl;
				setEmpty();
			}
		}
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
	}
}
void Mmatrix::Free() {
	for (int i = 0; i < height; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	this->n = 0;
	this->width = 0;
	this->height = 0;
}
void Mmatrix::setEmpty() {
	matrix = nullptr;
	this->n = 0;
	this->height = 0;
	this->width = 0;
}
void Mmatrix::initMatrix() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j == halfWidth && i >= halfHeight )
				matrix[i][j] = STAR;
			else
				matrix[i][j] = MINUS;
		}
	}
}
void Mmatrix::fillUpperPart() {
	for (int i = 0; i < halfHeight; ++i) {
		int cntMinus = n - i;
		int cntStar = n + i * 2;
		int br = 0;
		bool placeStars = false;
		for (int j = 0; j < halfWidth; ++j) {
			if (br == cntMinus && placeStars == false) {
				placeStars = true;
				br = 0;

			}
			else if (br == cntStar && placeStars == true) {
				placeStars = false;
				br = 0;
			}

			if (placeStars) {
				matrix[i][j] = STAR;
				matrix[i][width - j - 1] = STAR;
			}

			br++;
		}
	}
}
void Mmatrix::fillLowerPart() {
	int cntSecMinus = 1,
		cntSecStars = n;
	for (int i = halfHeight; i < height; ++i) {
		int cntFirstMinus = n - i,
			firstStars = n,
			br = 0;
		bool firstMin = false,
			placeStarsFirst = false,
			placeSecondStars = false,
			secondMin = false;

		cntSecStars--;

		if (i > halfHeight)
			cntSecMinus += 2;
		for (int j = 0; j < halfWidth; ++j) {
			if (firstMin == false) {
				br++;
				if (br == cntFirstMinus) {
					firstMin = true;
					placeStarsFirst = true;
					br = 0;
				}
				else if (cntFirstMinus == 0) {
					j--;
					firstMin = true;
					placeStarsFirst = true;
					br = 0;
				}
			}
			else if (placeStarsFirst == true) {
				br++;
				if (br == firstStars) {
					secondMin = true;
					placeStarsFirst = false;
					br = 1;
				}
				matrix[i][j] = STAR;
				matrix[i][width - j - 1] = STAR;
			}
			else if (secondMin == true) {

				if (br >= cntSecMinus) {
					secondMin = false;
					placeSecondStars = true;
					br = 0;
				}br++;
			}
			else if (placeSecondStars == true) {
				if (br == cntSecStars) {
					placeSecondStars = false;
					br = 0;
				}
				br++;
				matrix[i][j] = STAR;
				matrix[i][width - j - 1] = STAR;
			}
		}
	}
}

//constructors
Mmatrix::Mmatrix() {
	setEmpty();
}
Mmatrix::Mmatrix(int n) {
	setN(n);
	this->matrix = new (std::nothrow) char*[height];
	if (!matrix) {
		std::cout << "Error in Mmatrix::Mmatrix(int n)" << std::endl;
		setEmpty();
	}
	else {
		for (int i = 0; i < height; ++i) {
			matrix[i] = new (std::nothrow) char[width];
			if (!matrix[i]) {
				std::cout << "Error in Mmatrix::Mmatrix(int n), 1" << std::endl;
				setEmpty();
			}
		}
	}
	initMatrix();
	fillUpperPart();
	fillLowerPart();

}
Mmatrix::Mmatrix(const Mmatrix &other) {
	CopyFrom(other);
}

//operators
std::ostream& operator<<(std::ostream &os, const Mmatrix &obj) {

	os << "N = " << obj.n << std::endl;
	for (int i = 0; i < obj.height; ++i) {
		bool isRepeated = false;
		for (int j = 0; j < obj.width; ++j) {
			os << obj.matrix[i][j];
			if ((j == obj.width - 1) && !isRepeated) {
				j = -1;
				isRepeated = true;
			}
		}
		os << std::endl;
	}
	return os;
}
Mmatrix& Mmatrix::operator=(const Mmatrix &other) {
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

//get and set 
int Mmatrix::getHeight() const {
	return this->height;
}
int Mmatrix::getN() const {
	return this->n;
}
int Mmatrix::getWidth() const {
	return this->width;
}
int Mmatrix::getHalfWidth() const {
	return this->halfWidth;
}
int Mmatrix::getHalfHeight() const {
	return this->halfHeight;
}
void Mmatrix::setN(int n) {
	if (n < MINIMUM || n > MAXIMUM || n%2 == 0)
		n = MINIMUM;
	this->height = n + 1;
	this->width = n * MULTIPL;
	this->halfHeight = height / 2;
	this->halfWidth = width / 2;
	this->n = n;
}
char** Mmatrix::getMatrix() const{
	return matrix;
}

//Destructor
Mmatrix::~Mmatrix() {
	Free();
}