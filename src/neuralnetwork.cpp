#include "neuralnetwork.hpp"

void NN::randomize(){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		Layers[i]->randomize();
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
		std::string index = std::to_string(i);
		Layers[i]->print(index);
	}
}

void NN::clear(){
	for(int i=0; i<Layers.size(); i++){
		if(Layers[i] == nullptr){
			break;
		}
		Layers[i]->clear();
	}
}

void NN::setloss(dataT(*lossf)(dataT, dataT)){
	assert(lossf != nullptr);
	if(lossf == mse){
		LossFunction = mse;
		LossFunctionD = mseD;
	}
	else{
		std::cout << "unknown loss function" << std::endl;
	}
}

void NN::train(int epochs, int batchsize){
	// Create copy of network
	std::vector<Layer*> LayerChanges; 
	for(int i=0; i<LayerStructure->cols-1; i++){
		Layer* L = new Layer((*LayerStructure)[0][i], (*LayerStructure)[0][i+1], linear);
		LayerChanges.push_back(L);
	}

	// updating batch size if it is greater than the training set
	if(batchsize > Data->TrainingData->rows){
		batchsize = Data->TrainingData->rows;
	}

	for(int ep=0; ep<epochs; ep++){
		dataT epoch_loss = 0;
		for(int i=0; i<Data->TrainingData->rows; i++){

			Matrix x(Data->Inputs, 1);
			Matrix y(Data->Outputs, 1);

			Data->getTrainingExample(i, &x, &y);
			forward(&x);

			Matrix y_hat(Data->Outputs, 1);
			y_hat.copy(Layers[LayerStructure->cols - 2]->a);

			Matrix l(Data->Outputs, 1);
			applyloss(&l, &y_hat, &y, LossFunction);
			epoch_loss += l.total();

			// Backpropagation
			int totallayers = LayerStructure->cols - 2;
			Matrix error(Data->Outputs, 1);

			for(int lb=totallayers; lb>=0; lb--){
				
				Layer* CurrentLayer = Layers[lb];
				Layer* PreviousLayer = Layers[lb+1];

				if(lb == totallayers){
					// Calculate initial error
					applyloss(&error, &y_hat, &y, LossFunctionD);
					Matrix temp(Data->Outputs, 1);
					temp.copy(CurrentLayer->z);
					activate(&temp, CurrentLayer->actfunctionD);
					error.hproduct(&temp);
				}
				else{
					// calculate subsequent errors
					Matrix temp1(PreviousLayer->w->rows, PreviousLayer->w->cols);
					temp1.copy(PreviousLayer->w);
					temp1.transpose();
					temp1.dot(&error);
				
					Matrix temp(CurrentLayer->z->rows, CurrentLayer->z->cols);
					temp.copy(CurrentLayer->z);
					activate(&temp, CurrentLayer->actfunctionD);

					temp1.hproduct(&temp);

					error.rows = temp1.rows;
					error.cols = temp1.cols;

					free(error.start);
					error.start = (dataT*)calloc(error.rows*error.cols, sizeof(dataT)); 
					error.copy(&temp1);
				}
				
				// weight changes
				if(lb == 0){
					// last layer weights are updated using the inputs
					for(int j=0; j<error.rows; j++){
						for(int k=0; k<x.rows; k++){
							(*(LayerChanges[lb]->w))[j][k] += x[k][0] * (error[j][0]) * LearningRate;
						}
					}
				}
				else{
					for(int j=0; j<error.rows; j++){
						for(int k=0; k<Layers[lb-1]->a->rows; k++){
							(*(LayerChanges[lb]->w))[j][k] += (*(Layers[lb-1]->a))[k][0] * (error[j][0]) * LearningRate;
						}
					}	
				}
				
				// bias changes error=dcdb
				Matrix tempb(error.rows, error.cols);
				tempb.copy(&error);
				tempb.scale(LearningRate);
				LayerChanges[lb]->b->add(&tempb);
			}
			
			if(i % batchsize == 0){
				for(int b=0; b<LayerChanges.size(); b++){
					if(LayerChanges[b] == nullptr){
						break;
					}
					Layers[b]->w->subtract(LayerChanges[b]->w);
					Layers[b]->b->subtract(LayerChanges[b]->b);
					LayerChanges[b]->clear();
				}
			}
		}
		
		epoch_loss /= Data->TrainingData->rows;
		std::cout << "Training epoch " << ep+1 << "| Cost = " << epoch_loss << std::endl;
	}

	// free layer changes after finished training
	for(int i=0; i<LayerChanges.size(); i++){
		if(LayerChanges[i] == nullptr){
			break;
		}
		free(LayerChanges[i]);
	}
}

void NN::test(){
	for(int i=0; i<Data->TestData->rows; i++){
		Matrix x(Data->Inputs, 1);
		Matrix y(Data->Outputs, 1);

		Data->getTestExample(i, &x, &y);
		forward(&x);

		Matrix y_hat(Data->Outputs, 1);
		y_hat.copy(Layers[LayerStructure->cols - 2]->a);

		Matrix l(Data->Outputs, 1);
		applyloss(&l, &y_hat, &y, LossFunction);

		printf("%f, %f = %f, | pred: %f\n", x[0][0], x[1][0], y[0][0], y_hat[0][0]);
	}

}

NN::NN(Matrix* l, Dataset* D, dataT lrate){
	assert(l->rows == 1);
	LayerStructure = l;
	Data = D;
	LearningRate = lrate;	
	
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

