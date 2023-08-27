#include "neuralnetwork.hpp"
#include "activations.hpp"

int main(){
	Matrix d("datasets/diabetes.csv");
	Dataset Data(&d, 1, 8);
	Matrix l(1, 2);
	l[0][0] = 8; l[0][1] = 1; 

	NN neuralnet(&l, &Data, 0.00001);
	neuralnet.Layers[0]->setactivation(linear);
	neuralnet.randomize();
	neuralnet.setloss(mse);

	neuralnet.train(100000, 1);
	neuralnet.test();

}
