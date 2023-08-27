#include "neuralnetwork.hpp"

int main(){
	Matrix data("datasets/quadratic.csv");
	data.print();
	
	Dataset p(&data, 1.0f, 2);
	Matrix layers(1, 4);
	layers[0][0] = 2; layers[0][1] = 9; layers[0][2] = 6; 
	layers[0][3] = 1; 

	NN neuralnet(&layers, &p, 0.001f);
	neuralnet.Layers[0]->setactivation(Ntanh);
	neuralnet.Layers[1]->setactivation(relu);
	neuralnet.Layers[2]->setactivation(sigmoid);

	neuralnet.randomize();
	neuralnet.setloss(mse);
	neuralnet.train(100000, 1);

	Matrix point(2, 1);
	point[0][0] = 3; point[1][0] = 9; 
	neuralnet.forward(&point);
	neuralnet.Layers[2]->a->print();

	point[0][0] = 2; point[1][0] = -6;
	neuralnet.forward(&point);
	neuralnet.Layers[2]->a->print();

	point[0][0] = 2; point[1][0] = 5;
	neuralnet.forward(&point);
	neuralnet.Layers[2]->a->print();

	point[0][0] = -7; point[1][0] = 49;
	neuralnet.forward(&point);
	neuralnet.Layers[2]->a->print();
}
