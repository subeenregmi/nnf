#ifndef NNS
#define NNS

#include "matrix.hpp"
#include "activations.hpp"
#include "loss.hpp"
#include "generic.hpp"

class NN{
	public:
		Matrix* layers;
		std::vector<Matrix*> weights;
		std::vector<Matrix*> biases;
		std::vector<Matrix*> zterms;
		std::vector<Matrix*> activations;


		NN(Matrix* l);
		void forward();
		


	private:

};



#endif // NNS
