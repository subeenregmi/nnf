#ifndef NNS
#define NNS

#include "matrix.hpp"
#include "activations.hpp"
#include "layer.hpp"
#include "generic.hpp"
#include "dataset.hpp"
#include "loss.hpp"

class NN{
	public:
		std::vector<Layer*> Layers; 
		Matrix* LayerStructure;
		Dataset* Data; 
		dataT(*LossFunction)(dataT, dataT);
		dataT(*LossFunctionD)(dataT, dataT);
		dataT LearningRate;
		bool printFlag = true;

		void randomize();
		void forward(Matrix* x);
		void print();
		void clear();
		void setloss(dataT(*lossf)(dataT, dataT));
		void train(int epochs=100, int batchsize=10);
		void test(bool accuracy);
		
		NN(Matrix* l, Dataset* D, dataT lrate);
		~NN();
};

#endif // NNS
