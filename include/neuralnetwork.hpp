#ifndef NNS
#define NNS

#include "matrix.hpp"
#include "activations.hpp"
#include "loss.hpp"
#include "layer.hpp"
#include "generic.hpp"

class NN{
	public:
		std::vector<Layer*> Layers; 
		Matrix* LayerStructure;

		void randomize();
		void forward(Matrix* x);
		void print();
		void setactivation(int layer, dataT(*actf)(dataT));
		
		NN(Matrix* l);
		~NN();
};

#endif // NNS