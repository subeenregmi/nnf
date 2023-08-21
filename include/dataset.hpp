#ifndef DATASET
#define DATASET

#include "matrix.hpp"
#include "generic.hpp"

class Dataset{
	public:
		dataT Percentage;
		Matrix* Data; 
		Matrix* TrainingData;
		Matrix* TestData;

		void allocate();

		Dataset(Matrix* data, dataT percentage); // percentage allocated to training data
		~Dataset();
};

#endif //DATASET
