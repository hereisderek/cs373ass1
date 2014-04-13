//-------------------------------------------------------------------
// Framework for Q3
//
// TODO: Please fix any errors within this file yourself!
//
// Format of Input File:
// ----------------------
// X Y Z --> Arbitrary vertex of triangle
// X Y Z --> Arbitrary verter of triangle
// X Y Z --> Arbitrary vertex of triangle
// NOTE: The order of the vertices are random!!!
//
// Example:
// --------
// 0 0 0
// 10 0 0
// 20 10 0
//-------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <stdexcept>
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
    if (argumentCount != 2) throw runtime_error("USAGE: q3 <fileName>");

    Matrixf matrix = ReadFile(arguments[1]);
    Matrixf point1 = GetMatrixRow(matrix, 0);
    Matrixf point2 = GetMatrixRow(matrix, 1);
    Matrixf point3 = GetMatrixRow(matrix, 2);
	
    Matrixf normal(3,1);
    // TODO: Calculate normal values and add them to the normal vector 
	Matrixf edge12 = add(point2, multiply(point1, -1));
	//point1.printMatrix();
	//point2.printMatrix();
	//multiply(edge12, -1).printMatrix();
	Matrixf edge13 = add(point3, multiply(point1, -1));
	// TODO: Make  sure  to  provide  the  right  direction  for  the  normal  as  exemplified  in  lecture  3 slide 7.
	normal = normalize(cross(edge12, edge13));
	//Matrixf edge13 = subtract(point3, multiply(point1, 1));
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

/**
 * Read the data file that we have been given
 * @param fileName The name of the file that we are reading
 * @return The matrix that we read from the file
 */
Matrixf ReadFile(string fileName) 
{
  Matrixf matrix(3,3);
  ifstream file; file.open(fileName.c_str());
  if (!file.is_open()) throw runtime_error("Error: " + fileName + " could not be found!");
 
  float value = 0;
  for (int row=0; row<3; row++) 
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
