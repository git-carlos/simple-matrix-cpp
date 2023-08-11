#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix
{
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
	
	public:
	
	Matrix(unsigned int row = 5, unsigned int column = 5, unsigned int defaultvalue = 0); // default constructor
	Matrix(const Matrix &m); // copy constructor
	~Matrix();
	
	int numofrows(); // return number of rows
	int numofcols(); // return number of columns
	
	int get(unsigned int r, unsigned int c); // get val at specified row value & column value
	bool set(unsigned int r, unsigned int c, unsigned int value); // set val at specified row value & column value
	
	void torowmajor(); // store the matrix row oriented
	void tocolumnmajor(); // store the matrix column oriented 
	void printinternal(); // output values of the array
	
	Matrix operator+(const Matrix& m) const;
	Matrix& operator=(const Matrix& m);
	
	Matrix transpose();
	
	private:
	int rows; // number of rows in the matrix
	int columns; // number of columns in the matrix
	int num; // number of values in the array
	
	int* array; // values in the matrix
	bool isrowmajor; // is the matrix row oriented or not, if not its column oriented
};
#endif
