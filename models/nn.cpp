#include "all.hpp"
#include "neuralnetwork.hpp"


int main(){

	srand(time(0));
	Matrix L(1, 6);
	L[0][0] = 2;
	L[0][1] = 19;
	L[0][2] = 20;
	L[0][3] = 5;
	L[0][4] = 7;
	L[0][5] = 1;

	Matrix x(2, 1);
	x[0][0] = -99;
	x[1][0] = -99;

	NN neuralnet(&L);
	neuralnet.randomize();

	for(int i=0; i<neuralnet.Layers.size(); i++){
		if(neuralnet.Layers[i] == nullptr){
			break;
		}	
		neuralnet.Layers[i]->w->print();		
		neuralnet.Layers[i]->b->print();		
		neuralnet.Layers[i]->z->print();		
		neuralnet.Layers[i]->a->print();		
	}

	neuralnet.forward(&x);

	for(int i=0; i<neuralnet.Layers.size(); i++){
		if(neuralnet.Layers[i] == nullptr){
			break;
		}	
		neuralnet.Layers[i]->w->print();		
		neuralnet.Layers[i]->b->print();		
		neuralnet.Layers[i]->z->print();		
		neuralnet.Layers[i]->a->print();		
	}


	return 0;
}
