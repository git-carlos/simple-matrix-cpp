#include "matrix.h"
#include <iostream>

// default constructor
Matrix::Matrix(unsigned int row, unsigned int column, unsigned int defaultvalue)
{
	rows = row; // assign user specified amount of rows to rows varible
	columns = column; // assign user specified amount of columns to columns variable
	num = columns  * rows; // assign number of arrays
	
	isrowmajor = true; // make array row oriented as default
	
	array = new int[num]; // initialize array
	for(int i = 0; i < num; i++) // assign each value with specified default value
	{
		array[i] = defaultvalue;
	}
	
}

// copy constructor
Matrix::Matrix(const Matrix &m)
{
	rows = m.rows; // copy rows
	columns = m.columns; // copy columns
	num = rows * columns; // calc num of values
	
	isrowmajor = m.isrowmajor; // copy over whether its row major
	
	array = new int[num];
	for(int i = 0; i < num; i++) // copy over values
	{
		array[i] = m.array[i];
	}
}

// destructor
Matrix::~Matrix()
{
	delete[] array;
}

// return number of rows
int Matrix::numofrows()
{
	return rows;
}

// return number of columns
int Matrix::numofcols()
{
	return columns;
}

// store array as row oriented
void Matrix::torowmajor()
{
	// convert array to row orientation
	if(isrowmajor == false)
	{
		int index = 0; // index variable
		int reducer = 0; // reducer variable
		int* rowarray = new int[num]; // temparray
		
		for(int i = 0; i < rows; i++) // go through rows
		{
			for(int j = 0; j < columns; j++) // go through columns
			{
				rowarray[index] = array[i + (reducer * rows)]; // move value depending on reducer value to spot indicated by column loop
				index++;
				reducer++;
			}
			reducer = 0;
		}
		
		delete[] array; // free mem
		array = rowarray; // copy over
		
		isrowmajor = true; // array is now row oriented 
	} else
	{
		std::cout<< "Already row oriented..." << std::endl;
	}
}

// store array as column oriented
void Matrix::tocolumnmajor()
{
	if(isrowmajor == true) // if its row oriented conver to column orientation
	{
		
		int index = 0; // index value
		int multiplier = 0; // multiplier value for row 
		int* colarray = new int[num];
    
		for(int i = 0; i < columns; i++)
		{
			for(int j = 0; j < rows; j++)
			{
			colarray[index] = array[i + (multiplier * columns)]; // move over at spot dependent on row value at this column
			index++;
			multiplier++; // increase index and mulitplier
			}
			multiplier = 0; // rest otherwise youll get larger numbers
		}

		delete[] array; // free mem
		array = colarray;
		
		isrowmajor = false; // array now is column oriented
		
	} else
	{
		std::cout<< "Already column oriented..." << std::endl;
	}
}

void Matrix::printinternal()
{
	std::cout<< "Array Output: " << std::endl;
	for(int i = 0; i < num; i++) // print out array values
	{
		std::cout<< array[i] << "\t"; 
	}
	std::cout<< "\n " <<std::endl;
}

int Matrix::get(unsigned int r, unsigned int c)
{
	bool reversal = false; // reverse back to column major if needed
	int val = 0; // val we are returning
	
	if(r < 1 || r > rows) // check if rows in bounds
	{
		return -1;
	} else if(c < 1 || c > columns) // check if columns in bounds
	{
		return -1;
	} else
	{
		if(isrowmajor == false) // if its column major
		{
			torowmajor(); // make row major to make life easier
			reversal = true; 
		}
		
		int search = 0;
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				if(i == (r-1) && j == (c-1))
				{
				val = array[search]; // find value in array and set val to it
				}
				search++; // keep looping through until found
			}
		}
		if(reversal == true) // if we switched to row major reverse it back
		{
			tocolumnmajor();
		}
		return val; // return the val
	}
}

bool Matrix::set(unsigned int r, unsigned int c, unsigned int value)
{
	bool reversal = false; // reverse if we gotta
	 
	if(r < 1 || r > rows) // make sure rows are in bounds
	{
		return false;
	} else if(c < 1 || c > columns)
	{
		return false; // make sure columns in bounds
	} else
	{
		if(isrowmajor == false) // if not row major make it 
		{
			torowmajor();
			reversal = true;
		}
		
		int search = 0;
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				if(i == (r-1) && j == (c-1))
				{
				 array[search] = value; // same as get only we make the array value the specified value variable
				}
				search++;
			}
		}
		if(reversal == true) // set back to column major if was reversed
		{
			tocolumnmajor();
		}
		return true; // return true if everything good
	}
}

// friend function
std::ostream& operator<<(std::ostream& os, const Matrix& m) // friend function output stream
{
	int counter = 0;
	for(int i = 0; i < m.rows; i++)
	{
		for(int j = 0; j < m.columns; j++)
		{
			os<< m.array[counter] << "\t"; // output with tab by row
			counter++;
		}
		os<<"\n";
	}
	
	os<< std::endl;
	return os;
}

Matrix Matrix::operator+(const Matrix& m) const
{
	if(rows != m.rows)
	{
		return Matrix(rows, columns, 0);
	}
	else if(columns != m.columns)
	{
		return Matrix(rows, columns, 0);
	} else
	{
		Matrix combined(rows, columns, 0);
		
		int counter  = 0;
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				combined.array[counter] = array[counter] + m.array[counter];
				counter++;
			}
		}
		
		return combined;
	}
}

Matrix& Matrix::operator=(const Matrix &m)
{
	if(this != &m) // make sure not self assigning
	{
	rows = m.rows; // copy rows
	columns = m.columns; // copy columns
	num = rows * columns; // calc num of values
	
	isrowmajor = m.isrowmajor; // copy over whether its row major
	
	delete[] array; // free up array
	array = new int[num];
	
	for(int i = 0; i < num; i++) // reset array
	{
		array[i] = 0;
	}
	
	for(int i = 0; i < num; i++) // copy over values
	{
		array[i] = m.array[i];
	}
	
	return *this;
	}
}

Matrix Matrix::transpose()
{
	int trows = columns;
	int tcolumns = rows;
	Matrix tm(trows, tcolumns, 0); // make a matrix with columns and row values reversed...
	bool reversal = false; // reverse if we gotta
	
	if(isrowmajor == false) // if not row major make it 
	{
		torowmajor();
		reversal = true;
	}
	
	int counter = 0;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++) // copy over values by row
		{
			tm.array[counter] = array[counter];
			counter++;
		}
	}
	if(reversal == true) // set back to column major if was reversed
	{
		tocolumnmajor();
	}
	
	return tm; // return newly transposed matrix
}
