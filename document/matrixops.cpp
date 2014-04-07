#include "matrixops.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

Matrixf multiply(Matrixf const& left, Matrixf const& right) {

	// error check
	if (left.ncols() != right.nrows()) {
		throw std::runtime_error("Unable to multiply: matrix dimensions not agree.");
	}

	/** implement matrix/vector multiplication ********************/

	Matrixf ret(left.nrows(), right.ncols());
	for (unsigned int row = 0; row < left.nrows(); row++){
		for (unsigned int col = 0; col < left.ncols(); col++){
			//ret(row, col) +=  
		}
	}

	return ret;
}

Matrixf multiply(Matrixf const& mat, float scalar) {

	/** implement matrix/vector multiplication ********************/

	Matrixf result(1, 1);

	return result;
}

Matrixf multiply(float scalar, Matrixf const& mat) {
	return multiply(mat, scalar);
}

float dot(Matrixf const& vec1, Matrixf const& vec2) {

	// error check
	if (!vec1.isVector() || !vec2.isVector()) {
		throw std::runtime_error("Unable to do dot product: not column vectors.");
	}
	if (vec1.nrows() != vec2.nrows()) {
		throw std::runtime_error("Unable to do dot product: vector lengths not equal.");
	}

	/** implement dot product *************************************/

	float ret = -1;

	return ret;
}

Matrixf cross(Matrixf const& vec1, Matrixf const& vec2) {

	// error check
	if (!vec1.isVector() || !vec2.isVector()) {
		throw std::runtime_error("Unable to do dot product: not column vectors.");
	}
	if (vec1.nrows() != 3 || vec2.nrows() != 3) {
		throw std::runtime_error("Unable to do cross product: vector lengths not 3.");
	}

	/** implement cross product ***********************************/

	Matrixf ret(1, 1);

	return ret;
}

// Sample implementation of matrix addition
Matrixf add(Matrixf const& mat1, Matrixf const& mat2) {

	// error check
	if (mat1.ncols() != mat2.ncols() ||
		mat1.nrows() != mat2.nrows())
	{
		throw std::runtime_error("Unable to add 2 matrix together: dimensions not identical.");
	}

	Matrixf result(mat1.nrows(), mat1.ncols());
	for (unsigned int r = 0; r < mat1.nrows(); ++r) {
		for (unsigned int c = 0; c < mat1.ncols(); ++c) {
			result(r, c) = mat1(r, c) + mat2(r, c);
		}
	}

	return result;
}

Matrixf transpose(Matrixf const& mat) {
	Matrixf result(mat.ncols(), mat.nrows());

	for (unsigned int r = 0; r < mat.nrows(); ++r) {
		for (unsigned int c = 0; c < mat.ncols(); ++c) {
			result(c, r) = mat(r, c);
		}
	}

	return result;
}

// Computes the length (L2 norm) of a vector
float length(Matrixf const& v) {
	// error check
	if (!v.isVector()) {
		throw std::runtime_error("Not a vector.");
	}

	float result = 0.0f;

	for (unsigned int r = 0; r < v.nrows(); ++r) {
		result += v(r, 0) * v(r, 0);
	}

	return std::sqrtf(result);
}
