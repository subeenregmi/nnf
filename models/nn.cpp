#include "all.hpp"
#include "neuralnetwork.hpp"
#include "activations.hpp"

int main(){

	Matrix L(1, 2);
	L[0][0] = 2;
	L[0][1] = 1;

	NN neuralnet(&L);
	neuralnet.randomize();
	
	neuralnet.print();

	neuralnet.clear();

	neuralnet.print();

	return 0;
}
