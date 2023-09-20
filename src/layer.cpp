#include <layer.hpp>

Layer::Layer(int neurons, int next_neurons, dataT dropout_rate){
	this.neurons = neurons;
	this.dropout = dropout_rate;
	int Wd[2] = {next_neurons, neurons};
	int Bd[2] = {next_neurons, 1};

	w = new Tensor(Wd, 2);
	b = new Tensor(Bd, 2);
	z = new Tensor(Bd, 2);
	a = new Tensor(Bd, 2);
}

Layer::~Layer(){
	free(w);
	free(b);
	free(z);
	free(a);
}

namespace tnsrf_layer{
	void randomize(Layer* l){
		
	}
}
