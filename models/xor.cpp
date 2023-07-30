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

	MAT x(2, 1); 

	MAT z1(2, 1);
	MAT z2(1, 1);

	MAT yi(1, 1);
	MAT yb(1, 1);

	MAT L(1, 1);

	NMatrix::RANDOMIZE(&w1);
	NMatrix::RANDOMIZE(&b1);
	NMatrix::RANDOMIZE(&w2);
	NMatrix::RANDOMIZE(&b2);

	int iterations = 2;
	dataT lrate = 0.1f;

	for(int c = 0; c<iterations; c++){
		dataT total_cost = 0;
		for(int i=0; i<4; i++){
			MAT dcdw2(1, 2);
			MAT dcdb2(1, 1);
			MAT dcdw1(2, 2);
			MAT dcdb1(2, 1);
			MAT temp(1, 1);

			x[0][0] = training[i][0];
			x[1][0] = training[i][1];
			yb[0][0] = training[i][2];

			// first pass
			forward(&z1, &w1, &x, &b1);
		
			// second pass 
			forward(&z2, &w2, &z1, &b2);
			
			// activation
			NMatrix::COPY(&yi, &z2);
			ActivationF::NM_sigmoid(&yi);

			//cost 
			LossF::NM_squared_error(&L, &yi, &yb);
			total_cost += NMatrix::TOTAL(&L);

			// backpropegation w2
			LossF::NM_squared_error_D(&L, &yi, &yb);
			NMatrix::COPY(&yi, &z2);
			ActivationF::NM_sigmoidD(&yi);
			
			NMatrix::DOT(&temp, &L, &yi);
			NMatrix::TRANSPOSE(&z1);
			NMatrix::DOT(&dcdw2, &temp, &z1);
			NMatrix::TRANSPOSE(&z1);
			NMatrix::SCALE(&dcdw2, lrate/4);
			
			NMatrix::COPY(&dcdb2, &temp);
			NMatrix::SCALE(&dcdb2, lrate/4);



			//NMatrix::SUBTRACT(&w2, &w2, &dcdw2);
			//NMatrix::SUBTRACT(&b2, &b2, &temp);

		}
		std::cout << "Total Cost: " << total_cost << std::endl;
	}
}
