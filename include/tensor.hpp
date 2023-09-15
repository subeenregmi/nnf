#ifndef TENSOR
#define TENSOR

typedef double dataT;
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <initializer_list>
#include <cstdlib>
#include <time.h>

class Tensor{
	public: 
		dataT* start; 
		int items;
		int rank;
		int* dimensions;
		Tensor(int s[], int r);
		~Tensor(); 
};

// functions relating to tensors 
namespace tnsrf{
	dataT getItem(Tensor *tensor, std::initializer_list<int> index);
	void copy(Tensor *to, Tensor *from);
	void randomize(Tensor *t);

}


#endif // TENSOR
