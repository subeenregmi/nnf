#ifndef LAYER
#define LAYER

#include "matrix.hpp"
#include "activations.hpp"
#include "generic.hpp"

class Layer{
	
	public: 
		int neurons;
		Matrix* w; 
		Matrix* b;
		Matrix* z;
		Matrix* a;
		dataT(*actfunction)(dataT);

		void randomize();
		void forward(Matrix* x);
		void setactivation(dataT(*act)(dataT));

		Layer(int n, int nnext, dataT(*act)(dataT));
		~Layer();
};

#endif
