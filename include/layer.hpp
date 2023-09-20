#pragma once

#include <tensor.hpp>

class Layer{ 
	public:
		int neurons;
		dataT dropout;
		Tensor* w;
		Tensor* b;
		Tensor* z;
		Tensor* a;

		Layer(int neurons, int next_neurons, dataT dropout_rate);
		~Layer();
};

namespace tnsrf_layer{
	void randomize(Layer* l);
	void forward(Layer* l, Tensor* x);
	void copy(Layer* to, Layer* from);
	void clear(Layer* l);
}

