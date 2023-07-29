#include "../include/doublesubscript.hpp"

DoubleSubscript::DoubleSubscript(dataT* m, int r, int MAX_COLS){
	mat = m;
	row = r;
	COLS = MAX_COLS;
}

dataT &DoubleSubscript::operator[](int col){
	return mat[row*COLS + col];
}
