//-------------------------------------------------------------------
// Framework for Q2
//
// TODO: Please fix any errors within this file yourself!
//
// Format of Input File:
// ----------------------
// i_1 j_1 k_1 --> Vector A
// i_2 j_2 k_2 --> Vector B
//
// Example:
// --------
// 10 0 0
// 3 4 0
//-------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
//#include "stdafx.h"
using namespace std;

#include "matrixf.h"
#include "matrixops.h"

//-------------------------------------------------------------------
// Global Constants
//-------------------------------------------------------------------
const int SUCCESS = 0;
const int FAILURE = 1;

//-------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------
//Matrixf ReadFile(string fileName);
Matrixf GetMatrixRow(Matrixf & matrix, int rowNumber);
Matrixf CreateSolutionMatrix(float height, float area);
void WriteSolution(Matrixf & solution);
float sin(Matrixf const& v1, Matrixf const& v2);
float cos(Matrixf const& v1, Matrixf const& v2);
void show(Matrixf const& a, Matrixf const& b);
void show(Matrixf const& a, Matrixf const& b, int no);
Matrixf robustNomal(vector<Matrixf> const& vec);
//-------------------------------------------------------------------
// Main application entry point
//-------------------------------------------------------------------

/**
* Main application entry point
* @param argumentCount The amount of arguments comment in
* @param arguments The list of incomming arguments
* @returns SUCCESS or FAILURE
*/

int main(int argumentCount, char **arguments)
{
	try
	{
		//if (argumentCount != 2) throw runtime_error("USAGE: q2 <fileName>");

		
		Matrixf a(3, 1);
		Matrixf b(3, 1);
		Matrixf c(3, 1);
		Matrixf d(3, 1);
		Matrixf e(3, 1);

		//// 1
		//a(0, 0) = 1;
		//a(1, 0) = 0;
		//a(2, 0) = 0;

		//b(0, 0) = 1;
		//b(1, 0) = 1;
		//b(2, 0) = 0;
		//// 2
		//a(0, 0) = 2;
		//a(1, 0) = 0;
		//a(2, 0) = 0;

		//b(0, 0) = 2;
		//b(1, 0) = 1;
		//b(2, 0) = 0;
		//show(a, b, 2);
		////3
		//a(0, 0) = 1;
		//a(1, 0) = 0;
		//a(2, 0) = 0;

		//b(0, 0) = -1;
		//b(1, 0) = 1;
		//b(2, 0) = 0;
		//show(a, b, 3);
		////4
		//a(0, 0) = 1;
		//a(1, 0) = 0;
		//a(2, 0) = 0;

		//b(0, 0) = -1;
		//b(1, 0) = -1;
		//b(2, 0) = 0;
		//show(a, b, 4);

		//5
		a(0, 0) = -0.8;
		a(1, 0) = 0;
		a(2, 0) = -1.2;

		b(0, 0) = 0.2;
		b(1, 0) = 0;
		b(2, 0) = -1.2;
		cross(a, b).printMatrix();
		getchar();
		a(0, 0) = 1;
		a(1, 0) = 0;
		a(2, 0) = 0;

		b(0, 0) = 2;
		b(1, 0) = 0;
		b(2, 0) = -1;

		c(0, 0) = 3;
		c(1, 0) = -1;
		c(2, 0) = -2;

		d(0, 0) = 0;
		d(1, 0) = 1;
		d(2, 0) = 0;

		e(0, 0) = 0;
		e(1, 0) = 0;
		e(2, 0) = 1;

		vector<Matrixf> v(5, Matrixf(3, 1));
		v.at(0) = (a); v.at(1) = (b); v.at(2) = (c);
		v.at(3) = d; v.at(4) = e;
		//v.push_back(b); v.push_back(c);

		robustNomal(v).printMatrix();


		a.printMatrix();
		getchar();

	}
	catch (runtime_error error)
	{
		cerr << "ERROR: " << error.what() << endl;
		return FAILURE;
	}
	return SUCCESS;
}
void show(Matrixf const& a, Matrixf const& b){
	transpose(a).printMatrix();
	transpose(b).printMatrix();
	cout << " ======================== " << endl;
}
void show(Matrixf const& a, Matrixf const& b, int no){
	cout << "Test No: " << no << endl;
	show(a, b);
}
float sin(Matrixf const& v1, Matrixf const& v2){
	// TODO: n! normal vector
	return length(cross(v1, v2)) / (length(v1) * length(v2)) ;
}
float cos(Matrixf const& v1, Matrixf const& v2){
	return dot(v1, v2) / (length(v1) * length(v2));
}


/**
* Extract a row from a matrix
* @param matrix The matrix that we are extracting the row for
* @param rowNumber The number of the row that we are working
* @return The matrix row that we are retrieving
*/
Matrixf GetMatrixRow(Matrixf & matrix, int rowNumber)
{
	Matrixf result(matrix.ncols(), 1);
	for (int column = 0; column<matrix.ncols(); column++)
	{
		float value = matrix.get(rowNumber, column);
		result.set(column, 0, value);
	}
	return result;
}

/**
* Generates a solution matrix
* @param height The height solution
* @param area The area solution
* @return The solution in a matrix
*/
Matrixf CreateSolutionMatrix(float height, float area)
{
	Matrixf matrix(1, 2);
	matrix.set(0, 0, height);
	matrix.set(0, 1, area);
	return matrix;
}

/**
* Write the solution on the screen
*/
void WriteSolution(Matrixf & solution)
{
	cout << solution;
}

Matrixf robustNomal(vector<Matrixf> const& vec){

#ifndef NDEBUG 
	cout << "computing vectors" << endl;
	for each (Matrixf var in vec)
	{
		transpose(var).printMatrix();
	}
#endif
	int size = vec.size();
	Matrixf normal(vec.at(0).nrows(), 1);
	for (int i = 0; i < size; i++){
		cout << "crossing: " << (i + 1 + size) % size << " " << i << " " << (i - 1 + size) % size << endl;
		subtract(vec.at((i + 1 + size) % size), vec.at(i)).printMatrix();
		subtract(vec.at((i - 1 + size) % size), vec.at(i)).printMatrix();
		vec.at((i) % size).printMatrix();
		Matrixf newMat(3, 1);
		newMat = cross(
			//subtract(vec.at((i - 1 + size) % size), vec.at(i)),
			subtract(vec.at((i + 1 + size) % size), vec.at(i))
			, subtract(vec.at((i - 1 + size) % size), vec.at(i))
			);
		cout << "new normal: " << endl;
		newMat.printMatrix();
		normal = add(normal,newMat);

	}
	cout << "normal: " << endl;
	normal.printMatrix();
	return normalize(normal);
}