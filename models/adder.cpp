#include "generic.hpp"
#include "neuralnetwork.hpp"

int main(){
	Matrix D("datasets/adder.csv");
	Dataset data(&D, 1.00f, 3);
	Matrix Layers(1, 3);
	Layers[0][0] = 3; Layers[0][1] = 3; Layers[0][2] = 2; 
	
	NN neuralnet(&Layers, &data, 0.05f);
	neuralnet.Layers[0]->setactivation(swish);
	neuralnet.Layers[1]->setactivation(swish);
	neuralnet.setloss(mse);
	neuralnet.randomize();
	neuralnet.train(50000, 8);
	neuralnet.test();
}
