#include "neuralnetwork.hpp"

int main(){
	Matrix points("datasets/points.csv");
	Dataset D(&points, 1.00f, 1);
	Matrix l(1, 2);
	l[0][0] = 1; l[0][1] = 1;

	NN neuralnet(&l, &D, 0.01f);
	neuralnet.Layers[0]->setactivation(linear);

	neuralnet.setloss(mse);
	neuralnet.train(100000, 5);
	neuralnet.print();
}
