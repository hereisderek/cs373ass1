#ifndef MATRIXF_H__
#define MATRIXF_H__

#include <iosfwd>

class Matrixf {

public:
	// Constructors and Destructor
	// Creates a matrix of size rows and cols with all values set to zero
	Matrixf(unsigned int rows, unsigned int cols) ;
	virtual ~Matrixf() ;

	// copy and assign
	// performs deep copy of data
	Matrixf(Matrixf const& other) ;
	// replaces existing data with data from another matrix (can be of different size)
	virtual Matrixf& operator = (Matrixf const& other) ;

	// accessors and mutators
	// row index and column index are 0-based
	virtual float get(unsigned int row, unsigned int col) const ;
	virtual void set(unsigned int row, unsigned int col, float val) ;

	virtual float& operator()(unsigned int row, unsigned int col) ;
	virtual float operator()(unsigned int row, unsigned int col) const ;

	// gets the size of the matrix
	virtual unsigned int nrows() const ;
	virtual unsigned int ncols() const ;

	virtual bool isVector() const ;

protected: // Member variables
	unsigned int rows_;
	unsigned int cols_;
	float* data_;

public: // helper static methods
	static Matrixf eye(unsigned int size) ;

public: // iostream functions
	friend std::ostream& operator << (std::ostream& os, Matrixf const& matrix) ;

}; // class Matrixf

#endif // MATRIXF_H__
