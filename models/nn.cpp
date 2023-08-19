#include "all.hpp"
#include "neuralnetwork.hpp"
#include "activations.hpp"

int main(){

	Matrix a(2, 1);
	a[0][0] = 1; a[1][0] = 2;
	a.print();
	activate(&a, softmax);
	a.print();	
	activate(&a, softmaxD);
	a.print();


	return 0;
}
