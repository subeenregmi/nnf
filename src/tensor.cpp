#include "tensor.hpp"

Tensor::Tensor(int s[], int r){
	items = 1;
	assert(r > -1);
	rank = r;
	for(int i=0; i<rank; i++){
		assert(s[i] > 0);
		items *= s[i];
	}
	start = (dataT*)calloc(items, sizeof(dataT)); 
}
