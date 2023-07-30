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

	NMatrix::PRINT(&training, "training");

	MAT w1(2, 2);
	MAT w2(1, 2);
	MAT b1(2, 1);
	MAT b2(1, 1);
	MAT x0(2, 1); 

	MAT z1(2, 1);
	MAT z2(1, 1);

	MAT yi(1, 1);

	NMatrix::RANDOMIZE(&w1);
	NMatrix::RANDOMIZE(&b1);
	NMatrix::RANDOMIZE(&w2);
	NMatrix::RANDOMIZE(&b2);

	
	// first pass
//	forward(&z1, &w1, &x0, &b1);
//	NMatrix::PRINT(&z1, "z1");
//
//	// second pass 
//	forward(&z2, &w2, &z1, &b2);
//	NMatrix::PRINT(&z2, "z2");
//
//	// activation
//	NMatrix::COPY(&yi, &z2);
//	ActivationF::NM_sigmoid(&yi);
//	NMatrix::PRINT(&yi, "yi");
			
	// cost 


	NMatrix::RANDOMIZE(&w1);		
}
