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
	dataT getItem(Tensor* tensor, std::initializer_list<int> index){

		int memslot = 0; 
		int dmul = 1; // used to calculate index
		int i=0;
		int first=0;

		for(int x : index){ // check if index is valid and bounded between dimensions
			if(i==0){
				first = x;
			}
			if(i==1){
				memslot+=x;
			}
			assert(x > -1);
			assert(tensor->dimensions[i] > x);
			i++;
		}

		assert(i == tensor->rank); // making sure the index has exactly n dimensions

		if(tensor->rank == 0){ // if scalar just return the first element
			return tensor->start[0];
		}

		if(tensor->rank == 1){ // if rank 1 tensor (array) return element that was indexed
			return tensor->start[first];
		}

		if(tensor->rank == 2){ // if matrix return x*cols + y (i*cols + j)
			assert((memslot + first*tensor->dimensions[1]) < tensor->items);
			return tensor->start[memslot + first*tensor->dimensions[1]];
		}

		i=0; 
		memslot += first*tensor->dimensions[1];
		dmul = tensor->dimensions[0] * tensor->dimensions[1];

		for(int x: index){ // if n dimensional follow algo
			if(i==0 || i==1){
				i++;
				continue;	
			}
			memslot += x*dmul;
			dmul *= tensor->dimensions[i];
			i++;
		}

		assert(memslot < tensor->items); // last check 
		return tensor->start[memslot];
	}
	
	void setItem(Tensor* tensor, std::initializer_list<int> index, dataT val){
		
		int memslot = 0; 
		int dmul = 1; // used to calculate index
		int i=0;
		int first=0;

		for(int x : index){ // check if index is valid and bounded between dimensions
			if(i==0){
				first = x;
			}
			if(i==1){
				memslot+=x;
			}
			assert(x > -1);
			assert(tensor->dimensions[i] > x);
			i++;
		}

		assert(i == tensor->rank); // making sure the index has exactly n dimensions

		if(tensor->rank == 0){ // if scalar just return the first element
			tensor->start[0] = val;
		}
		else if(tensor->rank == 1){ // if rank 1 tensor (array) return element that was indexed
			tensor->start[first] = val;
		}
		else if(tensor->rank == 2){ // if matrix return x*cols + y (i*cols + j)
			assert((memslot + first*tensor->dimensions[1]) < tensor->items);
			tensor->start[memslot + first*tensor->dimensions[1]] = val;
		}
		else{
			i=0; 
			memslot += first*tensor->dimensions[1];
			dmul = tensor->dimensions[0] * tensor->dimensions[1];

			for(int x: index){ // if n dimensional follow algo
				if(i==0 || i==1){
					i++;
					continue;	
				}
				memslot += x*dmul;
				dmul *= tensor->dimensions[i];
				i++;
			}

			assert(memslot < tensor->items); // last check 
			tensor->start[memslot] = val;
		}
}

	void copy(Tensor* to, Tensor* from){

		assert(to->rank == from->rank); // ensure that dimensions all match up
		for(int i=0; i<to->rank; i++){
			assert((to->dimensions)[i] == (from->dimensions)[i]);
		}

		for(int i=0; i<to->items; i++){
			(from->start[i]) = (to->start)[i];
		}
	}

	void randomize(Tensor* t){
		for(int i=0; i<t->items; i++){
			(t->start)[i] = ((dataT) rand() / (dataT) RAND_MAX) - 0.5;
			// this will get us a float between 0.5 to -0.5
		}
	}

	void clear(Tensor* t){
		for(int i=0; i<t->items; i++){
			(t->start)[i] = 0;
		}
	}

	bool tensorEqual(Tensor* a, Tensor* b){
		if(a->rank != b->rank){ // ensure ranks are the same
			return false;
		}
		for(int i=0; i<a->rank; i++){ // ensure dimensions are the same
			if((a->dimensions)[i] != (b->dimensions)[i]){
				return false;
			}	
		}			
		
		for(int i=0; i<a->items; i++){ // ensure items are the same
			if((a->start)[i] != (b->start)[i]){
				return false;
			}
		}
		return true;
	}

	void reshape(Tensor* a, int newd[], int rank){
		int newitems = 1;
		for(int i=0; i<rank; i++){
			assert(newd[i] != 0);
			newitems *= newd[i];
		}
		free(a->start);
		a->items = newitems;
		a->rank = rank;
		a->dimensions = newd;
		a->start = (dataT*)calloc(newitems, sizeof(dataT)); 
	}
	

	void add(Tensor* d, Tensor* a, Tensor* b){
		assert(a->rank == b->rank);
		assert(a->rank == d->rank);
		for(int i=0; i<a->rank; i++){
			assert((a->dimensions)[i] == (b->dimensions)[i]);
			assert((a->dimensions)[i] == (d->dimensions)[i]);
		} // ensure a and b are compatible to add together and that d is compatible

		for(int i=0; i<a->items; i++){
			(d->start)[i] = (a->start)[i] + (b->start)[i];
		}
	}

	void subtract(Tensor* d, Tensor* a, Tensor* b){
		assert(a->rank == b->rank);
		assert(a->rank == d->rank);
		for(int i=0; i<a->rank; i++){
			assert((a->dimensions)[i] == (b->dimensions)[i]);
			assert((a->dimensions)[i] == (d->dimensions)[i]);
		}

		for(int i=0; i<a->items; i++){
			(d->start)[i] = (a->start)[i] - (b->start)[i];
		}
	}	

	void scale(Tensor* a, dataT scalar){
		for(int i=0; i<a->items; i++){
			(a->start)[i] *= scalar; 
		}
	}

	void hproduct(Tensor* d, Tensor* a, Tensor* b){
		assert(a->rank == b->rank);
		assert(a->rank == d->rank);
		for(int i=0; i<a->rank; i++){
			assert((a->dimensions)[i] == (b->dimensions)[i]);
			assert((a->dimensions)[i] == (d->dimensions)[i]);
		}

		for(int i=0; i<a->items; i++){
			(d->start)[i] = (a->start)[i] * (b->start)[i];
		}
	}	

	dataT total(Tensor* a){
		dataT total = 0;
		for(int i=0; i<a->items; i++){
			total += (a->start)[i];
		}
		return total;
	}

	void dot2d(Tensor* d, Tensor* a, Tensor* b){
		assert(a->rank == 2);
		assert(a->rank == b->rank);
		assert(a->rank == d->rank);

		assert(a->dimensions[1] == b->dimensions[0]);
		assert(d->dimensions[0] == a->dimensions[0]);
		assert(d->dimensions[1] == b->dimensions[1]);

		for(int i=0; i<a->dimensions[0]; i++){
			for(int j=0; j<b->dimensions[1]; j++){
				for(int k=0; k<a->dimensions[1]; k++){
					(d->start)[i*a->dimensions[1] + j] += (a->start)[i*a->dimensions[1] + k] * (b->start)[k*b->dimensions[1] + j];	
				}
			}
		}
	}

	void transpose2d(Tensor *d, Tensor* a){
		assert(d->rank == a->rank);
		assert(a->rank == 2);				

		assert(d->dimensions[0] == a->dimensions[1]);
		assert(d->dimensions[1] == a->dimensions[0]);

		for(int i=0; i<a->dimensions[0]; i++){
			for(int j=0; j<a->dimensions[1]; j++){
				(d->start)[j*a->dimensions[0] + i] = (a->start)[i*a->dimensions[1]+ j];
			}
		}
	}
}
