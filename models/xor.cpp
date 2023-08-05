#include "generic.hpp"
#include "matrix.hpp"
#include "activations.hpp"
#include "loss.hpp"

typedef NMatrix::Matrix MAT;

void forward(MAT* a, MAT* w, MAT* x, MAT* b){
	// a = wx+b
	NMatrix::DOT(a, w, x);
	NMatrix::ADD(a, a, b);
}

int main(){
	
	srand(time(0));

	MAT training(4, 3);
	training[0][0] = 0; training[0][1] = 0; training[0][2] = 0;
	training[1][0] = 0; training[1][1] = 1; training[1][2] = 1;
	training[2][0] = 1; training[2][1] = 0; training[2][2] = 1;
	training[3][0] = 1; training[3][1] = 1; training[3][2] = 0;

	MAT w1(2, 2);
	MAT w2(1, 2);
	MAT b1(2, 1);
	MAT b2(1, 1);

	NMatrix::RANDOMIZE(&w1);
	NMatrix::RANDOMIZE(&b1);
	NMatrix::RANDOMIZE(&w2);
	NMatrix::RANDOMIZE(&b2);

	int iterations = 50000000;
	dataT lrate = 0.01f;
}
