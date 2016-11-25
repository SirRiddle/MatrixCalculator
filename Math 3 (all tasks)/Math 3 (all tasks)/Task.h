#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Matrix
{
private:
	int rows, columns;
	double **mat;
	bool valid, aug;
public:
	Matrix();
	bool isValid();
	bool isAug();
	friend istream &operator>>(istream&, Matrix&);
	friend ostream &operator<<(ostream&, Matrix&);
	int getrows();
	int getcolumns();
	double **getmat();
	Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	Matrix operator*(int);
	Matrix operator^(int);
	Matrix transpose();
	Matrix Echelon();
	Matrix ReducedEchelon();
	void Add_I();
	Matrix Inverse();
};

double det(int, double**);
void Run(Matrix, Matrix);