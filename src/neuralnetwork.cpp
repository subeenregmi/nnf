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
	else if(lossf == cel){
		LossFunction = cel;
		LossFunctionD = celD;
	}
	else{
		std::cout << "unknown loss function" << std::endl;
	}
}

void NN::setreg(Regularizers r){
	Reg = r;
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
		dataT reg_loss = 0;
		for(int i=0; i<Data->TrainingData->rows; i++){

			Matrix x(Data->Inputs, 1);
			Matrix y(Data->Outputs, 1);

			Data->getTrainingExample(i, &x, &y);
			forward(&x);

			Matrix y_hat(Data->Outputs, 1);
			y_hat.copy(Layers[LayerStructure->cols - 2]->a);

			Matrix l(Data->Outputs, 1);
			applyloss(&l, &y_hat, &y, LossFunction);
			if(Reg == L2){
				for(Layer* x : Layers){
					Matrix* w = x->w;
					for(int iw=0; iw<w->rows; iw++){
						for(int jw=0; jw<w->cols; jw++){
							reg_loss += pow(w->start[iw*w->cols + jw], 2);
						}
					}
				}
			}
			epoch_loss += l.total();

			// Backpropagation
			int totallayers = LayerStructure->cols - 2;
			Matrix error(Data->Outputs, 1);

			for(int lb=totallayers; lb>=0; lb--){
				
				// lb = 0 
				Layer* CurrentLayer = Layers[lb];
				Layer* PreviousLayer = Layers[lb+1];

				if(lb == totallayers){
					// Calculate initial error
					if(LossFunction == cel && CurrentLayer->actfunction == softmax){
						error.copy(&y_hat);
						error.subtract(&y);
					}
					else{
						applyloss(&error, &y_hat, &y, LossFunctionD);
						Matrix temp(Data->Outputs, 1);
						temp.copy(CurrentLayer->z);
						activate(&temp, CurrentLayer->actfunctionD);
						error.hproduct(&temp);
					}
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
							LayerChanges[lb]->w->start[j*LayerChanges[lb]->w->cols + k] += x.start[k] * error.start[j] * LearningRate;

							if(Reg == L2){
								dataT regl =  (Lambda * CurrentLayer->w->start[j*LayerChanges[lb]->w->cols + k]) / (dataT)Data->TrainingData->rows;
							LayerChanges[lb]->w->start[j*LayerChanges[lb]->w->cols + k] += regl * LearningRate;
							}

						}
					}
					/*
					Matrix dcdw(error.rows, error.cols);
					dcdw.copy(&error);
					x.transpose();
					dcdw.dot(&x);
					x.transpose();
					dcdw.scale(LearningRate);
					LayerChanges[lb]->w->add(&dcdw);
					*/
				}
				else{
					for(int j=0; j<error.rows; j++){
						for(int k=0; k<Layers[lb-1]->a->rows; k++){
							LayerChanges[lb]->w->start[j*LayerChanges[lb]->w->cols + k] += Layers[lb-1]->a->start[k] * error.start[j] * LearningRate;

							if(Reg == L2){
								dataT regl =  (Lambda * CurrentLayer->w->start[j*LayerChanges[lb]->w->cols + k]) / (dataT)Data->TrainingData->rows;
							LayerChanges[lb]->w->start[j*LayerChanges[lb]->w->cols + k] += regl * LearningRate;
							}
						}
					}	
					/*
					Matrix dcdw(error.rows, error.cols);
					dcdw.copy(&error);
					Layers[lb-1]->a->transpose();
					dcdw.dot(Layers[lb-1]->a);
					Layers[lb-1]->a->transpose();
					dcdw.scale(LearningRate);
					LayerChanges[lb]->w->add(&dcdw);
					*/
				}
				
				// bias changes error=dcdb
				Matrix t(error.rows, error.cols);
				t.copy(&error);
				t.scale(LearningRate);
				LayerChanges[lb]->b->add(&t);

			}
			
			if((i % batchsize == 0 && i != 0) || Data->TrainingData->rows == 1){
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
		
		for(int b=0; b<LayerChanges.size(); b++){
			if(LayerChanges[b] == nullptr){
				break;
			}
			Layers[b]->w->subtract(LayerChanges[b]->w);
			Layers[b]->b->subtract(LayerChanges[b]->b);
			LayerChanges[b]->clear();
		}
		epoch_loss /= Data->TrainingData->rows;
		reg_loss *= Lambda / (dataT)(2*Data->TrainingData->rows);
		epoch_loss += reg_loss;
		if(printFlag){
			std::cout << "Training epoch " << ep+1 << "| Cost = " << epoch_loss << std::endl;
		}
	}

	// free layer changes after finished training
	for(int i=0; i<LayerChanges.size(); i++){
		if(LayerChanges[i] == nullptr){
			break;
		}
		free(LayerChanges[i]);
	}
}

void NN::test(bool accuracy){
	int success = 0;
	dataT testL=0;
	for(int i=0; i<Data->TestData->rows; i++){
		Matrix x(Data->Inputs, 1);
		Matrix y(Data->Outputs, 1);

		Data->getTestExample(i, &x, &y);
		forward(&x);

		Matrix y_hat(Data->Outputs, 1);
		y_hat.copy(Layers[LayerStructure->cols - 2]->a);

		Matrix l(Data->Outputs, 1);
		applyloss(&l, &y_hat, &y, LossFunction);

		//std::cout << "y: " << y[0][0] << ", y^: "<< y_hat[0][0] << std::endl;
		if(accuracy){
			int index = 0;
			int highprobindex = 0;
			for(int i=0; i<y.rows; i++){
				if(y[i][0] == 1){
					index = i;
				}
				if(y_hat[highprobindex][0] < y_hat[i][0]){
					highprobindex = i;
				}
			}
			if(index == highprobindex){
				success++;	
			}
		}
		testL+=l.total();
	}
	std::cout << "Total Test Loss: " << testL/Data->TestData->rows << std::endl;
	if(accuracy){
		std::cout << "Successes: " << success << std::endl;
		dataT ac = (float)success / (float)Data->TestData->rows;
		std::cout << "Test Accuracy: " << ac << "%" << std::endl;
	}
}

NN::NN(Matrix* l, Dataset* D, dataT lrate){
	assert(l->rows == 1);
	LayerStructure = l;
	Data = D;
	LearningRate = lrate;	
	Lambda = 0.001f;
	
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

