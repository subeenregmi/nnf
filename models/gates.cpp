#include "matrix.hpp"
#include "activations.hpp"
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
	srand(time(0));
	Matrix AND(4, 3);
	AND[0][0] = 0; AND[0][1] = 0; AND[0][2] = 0;		
	AND[1][0] = 0; AND[1][1] = 1; AND[1][2] = 0;		
	AND[2][0] = 1; AND[2][1] = 0; AND[2][2] = 0;		
	AND[3][0] = 1; AND[3][1] = 1; AND[3][2] = 1;		

	Matrix OR(4, 3);
	OR[0][0] = 0; OR[0][1] = 0; OR[0][2] = 0;		
	OR[1][0] = 0; OR[1][1] = 1; OR[1][2] = 1;		
	OR[2][0] = 1; OR[2][1] = 0; OR[2][2] = 1;		
	OR[3][0] = 1; OR[3][1] = 1; OR[3][2] = 1;		

	Matrix NAND(4, 3);
	NAND[0][0] = 0; NAND[0][1] = 0; NAND[0][2] = 1;		
	NAND[1][0] = 0; NAND[1][1] = 1; NAND[1][2] = 1;		
	NAND[2][0] = 1; NAND[2][1] = 0; NAND[2][2] = 1;		
	NAND[3][0] = 1; NAND[3][1] = 1; NAND[3][2] = 0;		

	Matrix curr(4, 3);
	curr.copy(&AND);

	Matrix w(1, 2);
	Matrix b(1, 1);
	Matrix z(1, 1);
	Matrix a(1, 1); 
	Matrix x(2, 1);
	Matrix y(1, 1);

	w.randomize();
	b.randomize();
	
	int iterations = 20000;
	dataT lrate = 0.1f;
	dataT totalcost;

	for(int i=0; i<iterations; i++){
		totalcost = 0;
		Matrix dcdw(1, 2);
		Matrix dcdb(1, 1);
		for(int jc=0; jc<4; jc++){
			x[0][0] = curr[jc][0];
			x[1][0] = curr[jc][1];
			y[0][0] = curr[jc][2];

			forward(&z, &w, &x, &b);
			
			a.copy(&z);
			activate(&a, sigmoid);
			
			Matrix Loss(1, 1);
			Loss.copy(&a);
			squaredloss(&Loss, &y);
			totalcost += Loss.total();

			Matrix error(1, 1); 
			Matrix temp(1, 1);
			error.copy(&a);
			error.subtract(&y);
			temp.copy(&z);
			activate(&temp, sigmoidD);
			error.hproduct(&temp);

			dcdb.add(&error);

			for(int j=0; j<a.rows; j++){
				for(int k=0; k<x.rows; k++){
					dcdw[j][k] += x[k][0] * error[j][0];
				}
			}
		}
		std::cout << "Cost for training set " << i << ": " << totalcost << std::endl;
		dcdb.scale(lrate);
		dcdw.scale(lrate);
		w.subtract(&dcdw);
		b.subtract(&dcdb);
	}
	for(int i=0; i<4; i++){
		x[0][0] = curr[i][0];
		x[1][0] = curr[i][1];
		y[0][0] = curr[i][2];

		forward(&z, &w, &x, &b);
		
		a.copy(&z);
		activate(&a, sigmoid);
		std::cout << x[0][0] << ", " << x[1][0] << " = " << y[0][0] << "| " << a[0][0] << std::endl;

	}
	return 0;
}
