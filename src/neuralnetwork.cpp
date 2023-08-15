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

void NN::forward(Matrix* x = nullptr){
	if(x == nullptr){
		assert(TrainingSet != nullptr);
		x = TrainingSet;
	}
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

void NN::setTrainingSet(Matrix* TS){
	assert(TS != nullptr);
	assert(TS->rows == ((*LayerStructure)[0][0] + (*LayerStructure)[0][LayerStructure->cols-1]));
	TrainingSet = TS;
}

void NN::clear(){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		Layers[i]->w->clear();	
		Layers[i]->b->clear();	
		Layers[i]->z->clear();	
		Layers[i]->a->clear();	
	}
}

/*
void NN::train(int epochs=50, int batchsize=1){
	
	assert(TrainingSet != nullptr);	
	int samples = TrainingSet->rows;
	std::vector<Layer*> LayerCopy; 
	
	for(int i=0; i<LayerStruture->cols-1; i++){
		Layer L = new Layer(1, 1, linear);
		LayerCopy.push_back(L);
	}

	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		free(Layers[i]);
	}

	for(int c=0; c<epochs; c++){
		for(int s=0; s<samples; s++){
				
		}
	}
}
*/

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

