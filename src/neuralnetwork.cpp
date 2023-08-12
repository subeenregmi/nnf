#include "neuralnetwork.hpp"

void NN::randomize(){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		Layers[i]->w->randomize();
		Layers[i]->b->randomize();
	}
}

void NN::forward(Matrix* x){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		Layers[i]->forward(x);
		x = Layers[i]->a;
	}	
}

void NN::print(){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		std::string index = std::to_string(i+1);
		Layers[i]->w->print("w" + index);
		Layers[i]->b->print("b" + index);
		Layers[i]->z->print("z" + index);
		Layers[i]->a->print("a" + index);
	}
}

void NN::setactivation(int layer, dataT(*actf)(dataT)){
	assert(layer >= 0);	
	assert(layer < LayerStructure->cols);
	assert(actf != nullptr);
	Layers[layer]->setactivation(actf);
}

NN::NN(Matrix* l){
	assert(l->rows == 1);
	LayerStructure = l;
	
	// check if any layer has zero or less neurons (illegal)
	for(int i=0; i<l->cols; i++){
		assert((*l)[0][i] > 0);
	}

	for(int i=0; i<l->cols-1; i++){
		Layer* L = new Layer((*l)[0][i], (*l)[0][i+1], linear);
		Layers.push_back(L);
	}
}

NN::~NN(){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		free(Layers[i]);
	}
}

