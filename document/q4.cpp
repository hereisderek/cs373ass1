//-------------------------------------------------------------------
// Framework for Q4
//
// TODO: Please fix any errors within this file yourself!
//
// Format of Input File:
// ----------------------
// N --> Amount of vertices in the polygon
// X Y Z --> Arbitrary vertex of polygon
// X Y Z --> Next arbitrary vertex of the polygon (repeat N times)
// NOTE: The order of the vertices RANDOM
//
// Example:
// --------
// 5
// 1 2 3
// 4 5 6
// 7 8 9
// 10 11 12
// 13 14 15
//
//
// TODO: handle more than 2(3) points sharing a line (including cendroid)
//
//
//-------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES

//#define NDEBUG
#ifndef NDEBUG
#define _DEBUG_
#endif
#include <math.h>
using namespace std;

#include "matrixf.h"
#include "matrixops.h"

//-------------------------------------------------------------------
// Global Constants
//-------------------------------------------------------------------
const int SUCCESS = 0;
const int FAILURE = 1;
static Matrixf axisInGetSignedAngleBetweenVectors(3,1);

//-------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------
Matrixf ReadFile(string fileName);
Matrixf GetMatrixRow(Matrixf & matrix, int rowNumber);
vector<Matrixf> reorder(Matrixf matrix);
vector<Matrixf> reorder(vector<Matrixf> original);
float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest, Matrixf const& destLeft);
float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest);
Matrixf robustNomal(vector<Matrixf> const& vec);
Matrixf robustNomal(vector<Matrixf> const& vec, int i);
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
    if (argumentCount != 2) throw runtime_error("USAGE: q4 <fileName>");

    Matrixf matrix = ReadFile(arguments[1]);
	int size = matrix.nrows();
	vector<Matrixf> vertices(size, Matrixf(1, 1));
	for (int row = 0; row < matrix.nrows(); row++)
	{
		Matrixf vertex = GetMatrixRow(matrix, row);
		vertices.at(row) = vertex;
	}
	
	vertices = reorder(vertices);

    Matrixf normal(3,1);
	normal = robustNomal(vertices);
#ifndef NDEBUG
	cout << "sorted: " << endl;
	for each (Matrixf var in vertices)
	{
		transpose(var).printMatrix();
	}
	normal.printMatrix();
	getchar();
#endif
    // TODO: Calculate the robust normal here!
    // NOTE: How do I get the vertices out of the matrix? See below!
    // for (int row=0; row<matrix.nrows(); row++) 
    // {
    //	 Matrixf vertex = GetMatrixRow(matrix, row);
    //   cout << transpose(vertex);
    // }
       
    cout << transpose(normal);
  }
  catch(runtime_error error) 
  {
      cerr << "ERROR: " << error.what() << endl;
      return FAILURE;
  }
  return SUCCESS;
}

//-------------------------------------------------------------------
// Helper Methods
//-------------------------------------------------------------------

//Matrixf reOrder(Matrixf const matrixs[]){
//	Matrixf newMatrixs()[5];
//	return newMatrixs;
//}
/**
 * Read the data file that we have been given
 * @param fileName The name of the file that we are reading
 * @return The matrix that we read from the file
 */

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
		normal = add(normal, normalize(robustNomal(vec, i)));
	}
	//cout << "normal: " << endl;
	//normal.printMatrix();
	return normalize(normal);
}
Matrixf robustNomal(vector<Matrixf> const& vec, int i){
	int size = vec.size();
	return cross(
		//subtract(vec.at((i - 1 + size) % size), vec.at(i)),
		subtract(vec.at((i + 1 + size) % size), vec.at(i))
		, subtract(vec.at((i - 1 + size) % size), vec.at(i))
		);
}

Matrixf getCendroid(vector<Matrixf> const& vec){
	Matrixf centroid(3, 1);
	int size = vec.size();
	float x = 0, y = 0, z = 0;
	for each (Matrixf mat in vec)
	{
		x += mat.get(0, 0);
		y += mat.get(1, 0);
		z += mat.get(2, 0);
	}
	centroid(0, 0) = (x / size);
	centroid(1, 0) = (y / size);
	centroid(2, 0) = (z / size);
	return centroid;
}
vector<Matrixf> reorder(Matrixf matrix){
	vector<Matrixf> vertices(matrix.nrows(), Matrixf(1, 1));
	for (int row = 0; row < matrix.nrows(); row++)
	{
		Matrixf vertex = GetMatrixRow(matrix, row);
		vertices.at(row) = vertex;
	}
	return reorder(vertices);
}
vector<Matrixf> reorder(vector<Matrixf> originalVertices){
	const int size = originalVertices.size();
	int correctOrder[5];

	vector<Matrixf> newVertices(size, Matrixf(3, 1));
	for (int i = 0; i < size; i++){
		newVertices.at(i) = originalVertices.at(i);
	}
	
	vector<Matrixf> centroidToVertex(size, Matrixf(3, 1));

	// compute centroid
	Matrixf centroid = getCendroid(originalVertices);

	// compute centroidToVertex
	for (int i = 0; i < size; ++i){
		centroidToVertex.at(i) = subtract(originalVertices.at(i), centroid);
	}

	int angles[5]; 
	angles[0] = 0;
	// read angles
	for (int i = 1; i < size; ++i){
		angles[i] = GetSignedAngleBetweenVectors(centroidToVertex.at(0), centroidToVertex.at(i)) * 180 / M_PI;
	}
#ifndef NDEBUG
	cout << "angles in origin order: ";
	for (int i = 0; i < size; ++i){
		cout << angles[i] << " ";
	}
	cout << endl;
#endif
	newVertices.at(0) = originalVertices.at(0);

	// sort
	for (int i = 1; i < size; i++){
		for (int j = i; j < size; j++){
			if (angles[i] > angles[j]) {
				int temp = angles[i];
				angles[i] = angles[j];
				angles[j] = temp;
				swap(newVertices.at(i), newVertices.at(j));
			}
		}
	}
#ifndef NDEBUG
	cout << "angles after sorted: ";
	for (int i = 0; i < size; i++)
	{
		cout << angles[i] << " ";
	}
	cout << endl;
	cout << "newVertices after sorted: ";
	for (int i = 0; i < size; i++)
	{
		cout << transpose(newVertices.at(i)) << " ";
	}
	cout << endl;
#endif
	return newVertices;
}

float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest, Matrixf const& destLeft){
	/*if (length(source) != 1.0f || length(dest) != 1.0f || length(destLeft) != 1.0f)
	{
		cout << "error: length not 1: source: " << length(source) << " dest: " << length(dest) << " destLeft: " << length(destLeft) << endl;
		throw std::runtime_error("vector not normalized.");
	}*/
	
	float forwardDot = dot(source, dest);
	float leftDot = dot(source, destLeft);

	// Make sure we stay in range no matter what, so Acos
	// doesn't fail later
	if (forwardDot < -1.0f)
	{
		forwardDot = -1.0f;
	}
	else if (forwardDot > 1.0f)
	{
		forwardDot = 1.0f;
	}

	float angleBetween = acos(forwardDot);

	if (leftDot > 0.0f)
	{
		//angleBetween *= -1.0f ;
		angleBetween = 2 * M_PI - angleBetween;
	}
	return angleBetween;
}

float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest){
	//http://stackoverflow.com/questions/3982877/opengl-rotation-of-an-object-around-a-line

	//TODO: find destLeft
	Matrixf destLeft(dest.nrows(), dest.ncols());


	if (axisInGetSignedAngleBetweenVectors.get(0, 0) == 0 && axisInGetSignedAngleBetweenVectors.get(1, 0) == 0 && axisInGetSignedAngleBetweenVectors.get(2, 0) == 0)
	{
		axisInGetSignedAngleBetweenVectors = cross(source, dest);
		int x = axisInGetSignedAngleBetweenVectors.get(0, 0), y = axisInGetSignedAngleBetweenVectors.get(1, 0), z = axisInGetSignedAngleBetweenVectors.get(2, 0);
		if ((x < 0) || (x == 0 && y < 0) || (x == 0 && y == 0 && z < 0))
		{
			axisInGetSignedAngleBetweenVectors = multiply(axisInGetSignedAngleBetweenVectors, -1);
		}
	}

	// detect parallel
	if (length(axisInGetSignedAngleBetweenVectors) == 0){
		return (dot(dest, source) == 1 ? 0 : M_PI );
	}


	//if (!(x != 0 && x > 0) || (y != 0 && y > 0) || (z != 0 && z > 0)) axis = multiply(axis, -1);
	//normal.printMatrix();
	destLeft = cross(axisInGetSignedAngleBetweenVectors, dest);
	//destLeft = multiply(destLeft, -1);
#ifndef NDEBUG
	cout << "source: " << transpose(source) << endl;
	cout << "dest: " << transpose(dest) << endl;
	cout << "destleft: " << transpose(destLeft) << endl;
	cout << "normal: " << transpose(axisInGetSignedAngleBetweenVectors) << endl;
#endif
	destLeft = normalize(destLeft);
	//destLeft.printMatrix();
	return GetSignedAngleBetweenVectors(normalize(source), normalize(dest), destLeft);
}

Matrixf ReadFile(string fileName) 
{
  ifstream file; file.open(fileName.c_str());
  if (!file.is_open()) throw runtime_error("Error: " + fileName + " could not be found!");
 
  int pointCount; file >> pointCount;
  Matrixf matrix(pointCount,3);
  float value = 0;
  for (int row=0; row<pointCount; row++) 
  {
    for (int column=0; column<3; column++) 
    {
	  file >> value; matrix.set(row, column, value);
    }
  }
  
  file.close();
  return matrix;  
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
  for (int column=0; column<matrix.ncols(); column++) 
  {
      float value = matrix.get(rowNumber, column);
      result.set(column, 0, value);
  }
  return result;
}
