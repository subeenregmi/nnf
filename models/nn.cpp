#include "all.hpp"
#include "neuralnetwork.hpp"


int main(){

	Matrix L(1, 3);
	L[0][0] = 2;
	L[0][1] = 2;
	L[0][2] = 1;
	NN n(&L);	
	
	for(int i=0; n.weights.size(); i++){ 
		if(n.weights[i] == nullptr){
			break;
		}
		n.weights[i]->print();
	}
	for(int i=0; n.biases.size(); i++){ 
		if(n.biases[i] == nullptr){
			break;
		}
		n.biases[i]->print();
	}

	return 0;
}
