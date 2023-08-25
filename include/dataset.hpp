#ifndef DATASET
#define DATASET

#include "matrix.hpp"
#include "generic.hpp"

class Dataset{
	public:
		dataT Percentage;
		Matrix* TrainingData;
		Matrix* TestData;
		int Inputs;
		int Outputs;

		void allocate();
		void getTrainingExample(int r, Matrix* x, Matrix* y);
		void getTestExample(int r, Matrix* x, Matrix* y);

		Dataset(Matrix* data, dataT percent, int input); // percentage allocated to training data
		~Dataset();
};

#endif //DATASET
