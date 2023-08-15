#include "layer.hpp"

void Layer::randomize(){
	w->randomize();
	b->randomize();
}

void Layer::forward(Matrix* x){
	assert(actfunction != nullptr);
	Matrix c(w->rows, w->cols);
	c.copy(w);
	c.dot(x);
	c.add(b);
	z->copy(&c);
	a->copy(z);
	activate(a, actfunction);
}

void Layer::setactivation(dataT(*act)(dataT)){
	assert(act != nullptr);
	actfunction = act;	
}

void Layer::copy(Layer* x){
	neurons = x->neurons;
	w->copy(x->w);
	b->copy(x->b);
	z->copy(x->z);
	a->copy(x->a);
	actfunction = x->actfunction;
}

Layer::Layer(int n, int nnext, dataT(*act)(dataT)){
	neurons = n;
	actfunction = act;

	Matrix* weight = new Matrix(nnext, n);
	Matrix* bias = new Matrix(nnext, 1);
	Matrix* zterms = new Matrix(nnext, 1);
	Matrix* activations = new Matrix(nnext, 1);

	w = weight;
	b = bias;
	z = zterms;
	a = activations;
}

Layer::~Layer(){
	free(w);
	free(b);
	free(z);
	free(a);
}
