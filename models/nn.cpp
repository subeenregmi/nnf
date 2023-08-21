#include "all.hpp"
#include "neuralnetwork.hpp"
#include "activations.hpp"
#include "dataset.hpp"

int main(){

	Matrix a(840, 4);
	for(int i=0; i<840; i++){
		a[i][0] = i; a[i][1] = 3*i; a[i][2] = i*i; a[i][3] = i+5;
	}

	Dataset D(&a, 0.65);
	std::cout << D.TrainingData->rows << std::endl;
	std::cout << D.TestData->rows;



	return 0;
}
