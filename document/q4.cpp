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
//
//
//
//-------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
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
Matrixf ReadFile(string fileName);
Matrixf GetMatrixRow(Matrixf & matrix, int rowNumber);
vector<Matrixf> reorder(Matrixf matrix);
vector<Matrixf> reorder(vector<Matrixf> original);
void swapVector(vector<Matrixf> v, int pos1, int pos2);
float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest, Matrixf const& destLeft);
float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest);
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

	vector<Matrixf> vertices(5, Matrixf(1, 1));
	for (int row = 0; row < matrix.nrows(); row++)
	{
		Matrixf vertex = GetMatrixRow(matrix, row);
		vertices.at(row) = vertex;
	}
	vertices = reorder(vertices);
    Matrixf normal(3,1);
    
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
	Matrixf centroid(3, 1);
	float x = 0, y = 0, z = 0;
	for each (Matrixf mat in originalVertices)
	{
		x += mat.get(0, 0);
		y += mat.get(1, 0);
		z += mat.get(2, 0);
	}
	centroid(0, 0) = (x / size);
	centroid(1, 0) = (y / size);
	centroid(2, 0) = (z / size);
	
	// compute centroidToVertex
	for (int i = 0; i < size; ++i){
		centroidToVertex.at(i) = subtract(originalVertices.at(i), centroid);
	}
	int angles[5]; 
	angles[0] = 0;
	// read angles
	for (int i = 1; i < size; ++i){
		centroidToVertex.at(i).printMatrix();
		angles[i] = GetSignedAngleBetweenVectors(originalVertices.at(0), centroidToVertex.at(i)) * 180 / M_PI;
		cout << "angle: " << angles[i] << endl;
	}
	newVertices.at(0) = originalVertices.at(0);

	// sort
	int minAngle, lastMinAngle = 0, angleIndex = 1;
	for (int i = 1; i < size; i++){
		for (int j = i; j < size; j++){
			if (angles[j] < angles[j - 1]) {
				int temp = angles[j];
				angles[j] = angles[j - 1];
				angles[j - 1] = temp;
				swap(newVertices.at(j), newVertices.at(j - 1));
			}
		}
	}
	for each (int var in angles)
	{
		cout << var << " ";
	}
	cout << endl;
	//centroidToVertex.at(0).printMatrix();
	//centroidToVertex.at(1).printMatrix();
	////swapVector(centroidToVertex, 0, 1);
	//swap(centroidToVertex[0], centroidToVertex[1]);
	//centroidToVertex.at(0).printMatrix();
	//centroidToVertex.at(1).printMatrix();
  
	// start point
	newVertices.at(0) = originalVertices.at(0);
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
	Matrixf destLeft(dest.nrows(), dest.ncols());
	//TODO: find destLeft
	Matrixf axis(dest.nrows(), 1);
	axis = cross(source, dest);
	// detect parallel
	if (length(axis) == 0){
		return (dot(dest, source) == 1 ? 0 : M_PI / 2);
	}
	//if (axis.get(0, 0) == 0) axis = multiply(axis, -1);

	// parelle 
	int x = axis.get(0, 0), y = axis.get(1, 0), z = axis.get(2, 0);
	if (x != 0 ){
		if (x < 0) axis = multiply(axis, -1); 
	}
	else if (y != 0){
		if (y < 0) axis = multiply(axis, -1);
	}
	else if (z < 0) axis = multiply(axis, -1);
	//if (!(x != 0 && x > 0) || (y != 0 && y > 0) || (z != 0 && z > 0)) axis = multiply(axis, -1);
	//normal.printMatrix();
	destLeft = cross(axis, dest);
	cout << "dest: " << endl;
	dest.printMatrix();
	cout << "destleft: " << endl;
	destLeft.printMatrix();
	cout << "normal: " << endl;
	axis.printMatrix();
	destLeft = normalize(destLeft);
	//destLeft.printMatrix();
	return GetSignedAngleBetweenVectors(normalize(source), normalize(dest), destLeft);
}
void swapVector(vector<Matrixf> v, int pos1, int pos2){
	//Matrixf *mat = &v.at(pos1);
	//v.at(pos1) = v.at(pos2);
	//v.at(pos2) = *mat;
	swap(v[pos1], v[pos2]);
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
