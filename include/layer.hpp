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
		dataT(*actfunctionD)(dataT);
		dataT dropout;

		void randomize();
		void forward(Matrix* x, bool testing=false);
		void setactivation(dataT(*act)(dataT));
		void copy(Layer* x);
		void clear();
		void print(std::string label="");

		Layer(int n, int nnext, dataT(*act)(dataT), dataT dr=0.0f);
		~Layer();
};

#endif
