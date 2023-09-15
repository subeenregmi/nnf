#include "tensor.hpp"

Tensor::Tensor(int s[], int r){
	assert(r > -1); // lowest rank tensor is zero (scalar)

	items = 1;
	dimensions = s;
	rank = r;

	for(int i=0; i<rank; i++){
		assert(s[i] > 0);
		items *= s[i];
	}

	start = (dataT*)calloc(items, sizeof(dataT)); 
	// allocating memory from the heap to store tensor
}

Tensor::~Tensor(){
	if(start != nullptr){
		free(start);
	}
}

namespace tnsrf{
	dataT getItem(Tensor *tensor, std::initializer_list<int> index){

		int memslot = 0; 
		int dmul = 0; // used to calculate index
		int i=0;

		for(int x : index){ // check if index is valid and bounded between dimensions
			if(i==0){
				memslot+=x;
			}
			assert(x > -1);
			assert(tensor->dimensions[i] > x);
			i++;
		}

		assert(i == tensor->rank); // making sure the index has exactly n dimensions
		i=0;

		for(int x : index){ // calculate memory location
			dmul *= tensor->dimensions[i];
			memslot += x*dmul;
			i++;
		}	
		return tensor->start[memslot];
	}

	void copy(Tensor *to, Tensor* from){

		assert(to->rank == from->rank); // ensure that dimensions all match up
		for(int i=0; i<to->rank; i++){
			assert((to->dimensions)[i] == (from->dimensions)[i]);
		}

		for(int i=0; i<to->items; i++){
			(from->start[i]) = (to->start)[i];
		}
	}

	void randomize(Tensor *t){
		for(int i=0; i<t->items; i++){
			(t->start)[i] = (dataT) rand() / (dataT) RAND_MAX;
		}
	}

	void clear(Tensor *t){
		for(int i=0; i<t->items; i++){
			(t->start)[i] = 0;
		}
	}
}
