#ifndef MATRIXOPS_H__
#define MATRIXOPS_H__

#include "matrixf.h"

// Multiplies two matrices together. The matrices dimensionis must agree with the rules of matrix multiply.
// This function must handle both matrix-matrix multiplication and matrix-vector multiplication (in which the vector is a single column matrix).
Matrixf multiply(Matrixf const& left, Matrixf const& right) ;

// Scales all elements of a matrix by a scalar.
Matrixf multiply(Matrixf const& mat, float scalar) ;
Matrixf multiply(float scalar, Matrixf const& mat) ;

// Normalize a vector
Matrixf normalize(Matrixf const& vector);

// Finds the dot product of two vectors of the same length.
float dot(Matrixf const& vec1, Matrixf const& vec2) ;

// Computes the cross product of two 3x3 vectors.
Matrixf cross(Matrixf const& vec1, Matrixf const& vec2) ;

// Computes the sum of two matrices of the same size.
Matrixf add(Matrixf const& mat1, Matrixf const& mat2) ;
Matrixf subtract(Matrixf const& mat1, Matrixf const& mat2);

// Compute the transpose of a matrix.
Matrixf transpose(Matrixf const& mat) ;

// Computes the length (L2 norm) of a vector.
float length(Matrixf const& v) ;

float tan(Matrixf const& vec1, Matrixf const& vec2);
#endif // MATRIXOPS_H__

