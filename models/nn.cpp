#include "all.hpp"
#include "neuralnetwork.hpp"
#include "activations.hpp"
#include "dataset.hpp"
#include "loss.hpp"

int main(){

	srand(time(0));
	// Xor Model
	Matrix XOR(4, 3);
	XOR[0][0] = 0; XOR[0][1] = 0; XOR[0][2] = 0;
	XOR[1][0] = 0; XOR[1][1] = 1; XOR[1][2] = 1;
	XOR[2][0] = 1; XOR[2][1] = 0; XOR[2][2] = 1;
	XOR[3][0] = 1; XOR[3][1] = 1; XOR[3][2] = 0;

	Dataset d(&XOR, 1.00, 2);

	// Xor network layer
	Matrix layers(1, 3);
	layers[0][0] = 2; layers[0][1] = 2; layers[0][2] = 1;

	NN neuralnet(&layers, &d, 0.1f);
	neuralnet.Layers[0]->setactivation(sigmoid);
	neuralnet.Layers[1]->setactivation(sigmoid);
	neuralnet.setloss(mse);
	neuralnet.randomize();
	neuralnet.train(10000, 1);
	neuralnet.test();

	return 0;
}
