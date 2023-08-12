#include "all.hpp"
#include "neuralnetwork.hpp"
#include "activations.hpp"

int main(){

	srand(time(0));
	Matrix L(1, 2);
	L[0][0] = 2;
	L[0][1] = 1;

	Matrix x(2, 1);
	x[0][0] = randD();
	x[1][0] = randD();

	NN neuralnet(&L);
	neuralnet.randomize();

	neuralnet.setactivation(0, sigmoid);

	neuralnet.forward(&x);
	
	neuralnet.print();

	return 0;
}
