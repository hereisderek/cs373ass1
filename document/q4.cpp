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

float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest, Matrixf const& destRight){
	if (length(source) != 1 || length(dest) != 1 || length(destRight) != 1)
	{
		throw std::runtime_error("vector not normalized.");
	}
	
	float forwardDot = dot(source, dest);
	float rightDot = dot(source, destRight);

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

	if (rightDot < 0.0f)
	{
		angleBetween *= -1.0f;
	}

	return angleBetween;
}
float GetSignedAngleBetweenVectors(Matrixf const& source, Matrixf const& dest){
	Matrixf destRight(dest.nrows(), dest.ncols());
	//TODO: find destRight

	return GetSignedAngleBetweenVectors(source, dest, destRight);
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
