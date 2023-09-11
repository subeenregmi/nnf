#ifndef TENSOR
#define TENSOR

typedef double dataT;
#include <cstdlib>
#include <cassert>
#include <iostream>

class Tensor{
	public: 
		dataT* start; 
		int items;
		int rank;
		Tensor(int s[], int r);
};


#endif // TENSOR
