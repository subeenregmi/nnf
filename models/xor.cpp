#include "matrix.hpp"
#include "activations.hpp"
#include "loss.hpp"
#include "generic.hpp"

void forward(Matrix* z, Matrix* w, Matrix*x, Matrix*b){
	Matrix c(w->rows, w->cols);
	c.copy(w);
	c.dot(x);
	z->copy(&c);
	z->add(b);
}


int main(){

	srand(time(0));

	Matrix XOR(4, 3);
	XOR[0][0] = 0; XOR[0][1] = 0; XOR[0][2] = 0;
	XOR[1][0] = 0; XOR[1][1] = 1; XOR[1][2] = 1;
	XOR[2][0] = 1; XOR[2][1] = 0; XOR[2][2] = 1;
	XOR[3][0] = 1; XOR[3][1] = 1; XOR[3][2] = 0;

	Matrix w1(2, 2);
	Matrix b1(2, 1);	
	Matrix w2(1, 2);
	Matrix b2(1, 1);
	Matrix x(2, 1);
	Matrix y(1, 1);
	
	w1.randomize();
	b1.randomize();
	w2.randomize();
	b2.randomize();

	int iterations = 50000; 
	dataT lrate = 0.1f;
	dataT totalcost;

	for(int i=0; i<iterations; i++){
		totalcost = 0;
		Matrix dcdw1(2, 2);
		Matrix dcdb1(2, 1);
		Matrix dcdw2(1, 2);
		Matrix dcdb2(1, 1);
		Matrix a1(2, 1);
		Matrix z1(2, 1);
		Matrix z2(1, 1);
		Matrix a2(1, 1);


		for(int h=0; h<4; h++){

			x[0][0] = XOR[h][0];
			x[1][0] = XOR[h][1];
			y[0][0] = XOR[h][2];

			forward(&z1, &w1, &x, &b1);
			a1.copy(&z1);
			activate(&a1, sigmoid);
				
			forward(&z2, &w2, &a1, &b2);
			a2.copy(&z2);
			activate(&a2, sigmoid);

			Matrix Loss(1, 1);
			Loss.copy(&a2);
			squaredloss(&Loss, &y);
			totalcost += Loss.total();

			// error2
			Matrix error2(1, 1);
			Matrix temp1(1, 1);
			error2.copy(&a2);
			error2.subtract(&y);
			temp1.copy(&z2);
			activate(&temp1, sigmoidD);
			error2.hproduct(&temp1);

			// b2 changes
			dcdb2.add(&error2);

			// w2 changes 
			for(int j=0; j<a2.rows; j++){
				for(int k=0; k<a1.rows; k++){
					dcdw2[j][k] += a1[k][0] * error2[j][0];
				}
			}

			// error1
			Matrix error1(1, 2);
			Matrix temp2(2, 1);
			error1.copy(&w2);
			error1.transpose();
			error1.dot(&error2);
			temp2.copy(&z1);
			activate(&temp2, sigmoidD);
			error1.hproduct(&temp2);

			// b1 changes
			dcdb1.add(&error1);

			// w1 changes
			for(int j=0; j<a1.rows; j++){
				for(int k=0; k<x.rows; k++){
					dcdw1[j][k] += x[k][0] * error1[j][0];
				}
			}
		}
		std::cout << "Cost for training set: " << i << ": " << totalcost << std::endl;
		dcdw1.scale(lrate);
		dcdb1.scale(lrate);
		dcdw2.scale(lrate);
		dcdb2.scale(lrate);
		w1.subtract(&dcdw1);
		b1.subtract(&dcdb1);
		w2.subtract(&dcdw2);
		b2.subtract(&dcdb2);
	}

	Matrix a1(2, 1);
	Matrix z1(2, 1);
	Matrix z2(1, 1);
	Matrix a2(1, 1);

	for(int h=0; h<4; h++){
		x[0][0] = XOR[h][0];
		x[1][0] = XOR[h][1];
		y[0][0] = XOR[h][2];

		forward(&z1, &w1, &x, &b1);
		a1.copy(&z1);
		activate(&a1, sigmoid);
			
		forward(&z2, &w2, &a1, &b2);
		a2.copy(&z2);
		activate(&a2, sigmoid);
		

		std::cout << x[0][0] << ", " << x[1][0] << " = " << y[0][0] << " | " << a2[0][0] << std::endl;
	}


	return 0;
}
