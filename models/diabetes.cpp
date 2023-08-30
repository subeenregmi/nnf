#include "neuralnetwork.hpp"
#include "activations.hpp"

int main(){
	Matrix d("datasets/diabetes.csv");
	Dataset Data(&d, 0.7, 8);

	Matrix Layers(1, 5);
	Layers[0][0] = 8; Layers[0][1] = 10; Layers[0][2] = 6; Layers[0][3] = 4; 
	Layers[0][4] = 1; 

	NN neuralnet(&Layers, &Data, 0.0005f);
	neuralnet.Layers[0]->setactivation(Ntanh);
	neuralnet.Layers[1]->setactivation(sigmoid);
	neuralnet.Layers[2]->setactivation(relu);
	neuralnet.Layers[3]->setactivation(sigmoid);
	
	neuralnet.setloss(mse);
	neuralnet.randomize();
	neuralnet.train(100, 1);

}
