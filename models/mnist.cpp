#include "neuralnetwork.hpp"
#include "generic.hpp"

int main(){

	Matrix data("datasets/mnist/mnist_training_set.csv");
	Matrix test("datasets/mnist/mnist_testing_set.csv");
	Dataset D(&data, 1.00f, 784);
	D.TestData = &test;
	std::cout << "Dataset Loaded!" << std::endl;
	Matrix Layers(1, 3);
	Layers[0][0] = 784; Layers[0][1] = 10; Layers[0][2] = 10; 

	NN neuralnet(&Layers, &D, 0.00003f);
	neuralnet.Layers[0]->setactivation(sigmoid);
	neuralnet.Layers[1]->setactivation(softmax);
	neuralnet.setloss(cel);
	neuralnet.setreg(L2);

	neuralnet.randomize();
	std::cout << "Starting training..." << std::endl;
	neuralnet.train(600, 50);

	neuralnet.test(true);
	D.TestData = nullptr;

	return 0;
}
