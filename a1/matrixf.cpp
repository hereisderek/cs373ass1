#include "matrixf.h"

#include <iostream>

Matrixf::Matrixf(unsigned int rows, unsigned int cols) {
	rows_ = rows;
	cols_ = cols;
	data_ = new float[rows_ * cols_];

	// set all initial values to zero
	for (unsigned int r = 0; r < rows_; ++r) {
		for (unsigned int c = 0; c < cols_; ++c) {
			data_[r * cols_ + c] = 0;
		}
	}
}

Matrixf::~Matrixf() {
	delete data_;
}

Matrixf::Matrixf(Matrixf const& other) {
	rows_ = other.rows_;
	cols_ = other.cols_;
	data_ = new float[rows_ * cols_];
	for (unsigned int i = 0; i < rows_ * cols_; ++i) {
		data_[i] = other.data_[i];
	}
}

Matrixf& Matrixf::operator=(Matrixf const& other) {
	// handles self assignment
	if (this == &other) {
		return *this;
	}

	delete data_;
	rows_ = other.rows_;
	cols_ = other.cols_;
	data_ = new float[rows_ * cols_];
	for (unsigned int i = 0; i < rows_ * cols_; ++i) {
		data_[i] = other.data_[i];
	}
	return *this;
}

float Matrixf::get(unsigned int row, unsigned int col) const {
#ifndef NDEBUG
	if (row >= rows_ || col >= cols_) {
		throw std::runtime_error("Matrix index out of bounds.");
	}
#endif

	return data_[row * cols_ + col];
}

void Matrixf::set(unsigned int row, unsigned int col, float val) {
#ifndef NDEBUG
	if (row >= rows_ || col >= cols_) {
		throw std::runtime_error("Matrix index out of bounds.");
	}
#endif
	data_[row * cols_ + col] = val;
}

float& Matrixf::operator()(unsigned int row, unsigned int col) {
	return data_[row * cols_ + col];
}

float Matrixf::operator()(unsigned int row, unsigned int col) const {
	return data_[row * cols_ + col];
}

unsigned int Matrixf::nrows() const {
	return rows_;
}

unsigned int Matrixf::ncols() const {
	return cols_;
}

bool Matrixf::isVector() const {
	return (cols_ == 1);
}

Matrixf Matrixf::eye(unsigned int size) {
	Matrixf e(size, size);
	for (unsigned int i = 0; i < size; ++i) {
		e.set(i, i, 1);
	}

	return e;
}

std::ostream& operator << (std::ostream& os, Matrixf const& matrix) {
	for (unsigned int r = 0; r < matrix.nrows(); ++r) {
		for (unsigned int c = 0; c < matrix.ncols(); ++c) {
			os << matrix.data_[r * matrix.cols_ + c] << " ";
		}
		os << "\n";
	}

	return os;
}