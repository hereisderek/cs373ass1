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
Matrixf ReadFile(string fileName);
Matrixf GetMatrixRow(Matrixf & matrix, int rowNumber);
Matrixf CreateSolutionMatrix(float height, float area);
void WriteSolution(Matrixf & solution);

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

    Matrixf matrix = ReadFile(arguments[1]);
    Matrixf a = GetMatrixRow(matrix, 0);
    Matrixf b = GetMatrixRow(matrix, 1);
  
    // TODO: Add your Height and Area logic here!
	Matrixf crossResult = cross(a, b);
	float area = length(crossResult);
	float height = area / length(a);
    Matrixf solution = CreateSolutionMatrix(height, area);
	//Matrixf solution = CreateSolutionMatrix(-1/*TODO: HEIGHT VALUE GOES HERE*/, -1/* TODO: AREA VALUE GOES HERE*/);
    WriteSolution(solution);
	
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
  Matrixf matrix(2,3);
  ifstream file; file.open(fileName.c_str());
  if (!file.is_open()) throw runtime_error("Error: " + fileName + " could not be found!");
 
  float value = 0;
  for (int row=0; row<2; row++) 
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

/**
 * Generates a solution matrix
 * @param height The height solution
 * @param area The area solution
 * @return The solution in a matrix
 */
Matrixf CreateSolutionMatrix(float height, float area) 
{
  Matrixf matrix(1,2);
  matrix.set(0,0, height);
  matrix.set(0,1, area);
  return matrix;
}

/**
 * Write the solution on the screen
 */
void WriteSolution(Matrixf & solution) 
{
    cout << solution;
}
