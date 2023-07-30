#include "../include/doublesubscript.hpp"

DoubleSubscript::DoubleSubscript(dataT* m, int r, int MAX_COLS){
	mat = m;
	row = r;
	COLS = MAX_COLS;
}

dataT &DoubleSubscript::operator[](int col){
	assert(col >= 0);
	assert(col < COLS);
	return mat[row*COLS + col];
}
