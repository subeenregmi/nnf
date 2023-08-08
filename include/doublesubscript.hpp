#ifndef DOUBLE_SUBSCRIPT
#define DOUBLE_SUBSCRIPT

#include "generic.hpp"

class DoubleSubscript{
	private:
		dataT* mat;
		int row;
		int COLS;
	public:
		DoubleSubscript(dataT* m, int r, int MAX_COLS);
		dataT& operator[](int col);
};

#endif // DOUBLE_SUBSCRIPT
