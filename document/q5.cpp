//-------------------------------------------------------------------
// Framework for Q5
//
// TODO: Please fix any errors within this file yourself!
//
// Format of Input File:
// ----------------------
// N --> Amount of vertices in the polygon
// X Y Z --> Arbitrary vertex of polygon
// X Y Z --> Next arbitrary vertex of the polygon (repeat N times)
// NOTE: The order of the vertices are RANDOM!!!
//
// Example:
// --------
// 5
// 1 2 3
// 4 5 6
// 7 8 9
// 10 11 12
// 13 14 15
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
    if (argumentCount != 2) throw runtime_error("USAGE: q5 <fileName>");

    Matrixf matrix = ReadFile(arguments[1]);

    Matrixf weakVertex(3,1), newNormal(3,1);
    // TODO: 1. Compute the normal to the polygon at each vertex
    // TODO: 2. Compute the robust vertex as per Q4
    // TODO: 3. Find the weakest vertex
    // TODO: 4. Remove the weakest vertex from the polygon
    // TODO: 5. Recompute the robust normal to the new n-1 polygon    
    
    // NOTE: How do I get the vertices out of the matrix? See below!
    // for (int row=0; row<matrix.nrows(); row++) 
    // {
    //	 Matrixf vertex = GetMatrixRow(matrix, row);
    //   cout << transpose(vertex);
    // }
       
    cout << transpose(weakVertex) << transpose(newNormal);
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
