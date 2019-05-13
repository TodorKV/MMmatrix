#ifndef mHeader
#define mHeader
#include<iostream>
const int MINIMUM = 3;
const int MAXIMUM = 10000;
const int MULTIPL = 5;
const char STAR = '*';
const char MINUS = '-';
class Mmatrix {
private:
	int n; 
	int height, halfHeight;
	int width, halfWidth;
	char** matrix;

	void CopyFrom(const Mmatrix &other);
	void Free();

	void setEmpty();

	void initMatrix();
	void fillUpperPart();
	void fillLowerPart();
public:
	//get & set
	void setN(int n);
	int getN() const;
	int getHeight() const;
	int getWidth() const;
	int getHalfWidth() const;
	int getHalfHeight() const;
	char** getMatrix() const;
	//constructors
	Mmatrix();
	Mmatrix(int n);
	Mmatrix(const Mmatrix &other);
	//operators
	Mmatrix& operator=(const Mmatrix& other);
	friend std::ostream& operator<<(std::ostream  &os, const Mmatrix &obj);
	//destructor
	~Mmatrix();
};
#endif