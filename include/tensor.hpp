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
	dataT getItem(Tensor* tensor, std::initializer_list<int> index);
	void setItem(Tensor* tensor, std::initializer_list<int> index, dataT val);
	void copy(Tensor* to, Tensor* from);
	void randomize(Tensor* t);
	void clear(Tensor* t);
	bool tensorEqual(Tensor* a, Tensor* b);

	void add(Tensor* d, Tensor* a, Tensor* b);
	void subtract(Tensor* d, Tensor* a, Tensor* b);
	void scale(Tensor* a, dataT scalar);	
	void hproduct(Tensor* d, Tensor* a, Tensor* b);
	dataT total(Tensor* a);
	void dot2d(Tensor* d, Tensor* a, Tensor* b); // a * b
}


#endif // TENSOR
