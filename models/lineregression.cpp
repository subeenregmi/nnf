#include "activations.hpp"
#include "matrix.hpp"
#include "loss.hpp"
#include "generic.hpp"



void forward(Matrix* z, Matrix* w, Matrix* x, Matrix* b){
	
	Matrix c(w->rows, w->cols);
	c.copy(w);
	c.dot(x);
	z->copy(&c);
	z->add(b);
}

int main(){
	
	Matrix Points(5, 2);
	Points[0][0] = 1; Points[0][1] = 3;
	Points[1][0] = 2; Points[1][1] = 7;
	Points[2][0] = 3; Points[2][1] = 6;
	Points[3][0] = 4; Points[3][1] = 8.5;
	Points[4][0] = 5; Points[4][1] = 11;

	Matrix w(1, 1);	
	Matrix x(1, 1);
	Matrix z(1, 1);
	Matrix b(1, 1);
	Matrix y(1, 1);

	w.randomize();
	b.randomize();

	int iterations = 100000;
	dataT lrate = 0.01f;
	dataT totalcost = 0;

	for(int i=0; i<iterations; i++){
		totalcost = 0;
		Matrix dcdw(1, 1);
		Matrix dcdb(1, 1);
		for(int j=0; j<5; j++){
			x[0][0] = Points[j][0];
			y[0][0] = Points[j][1];
		
			forward(&z, &w, &x, &b);	
	
			Matrix Loss(1, 1);
			Loss.copy(&z);
			squaredloss(&Loss, &y);
			// std::cout << "Loss for current example: " << Loss[0][0] << std::endl;
			totalcost += Loss[0][0];

			Matrix error(1, 1);
			error.copy(&z);
			squaredlossD(&error, &y);
			
			// bias change 
			dcdb.add(&error);

			// weight change
			error.hproduct(&x);	
			dcdw.add(&error);	
		}
		//std::cout << "Cost for training set " << i << ": " << totalcost << std::endl;
		dcdw.scale(lrate);
		dcdb.scale(lrate);
		w.subtract(&dcdw);
		b.subtract(&dcdb);
	}

	w.print();
	b.print();
	std::cout << "Cost for last training set " << iterations << ": " << totalcost << std::endl;

	
	return 0;
}

