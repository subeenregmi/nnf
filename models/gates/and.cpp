#include "matrix.hpp"
#include "activations.hpp"
#include "loss.hpp"

typedef NMatrix::Matrix mat;

// forwarding function, takes x, w and b, and performs dot and add, stores in z

void forward(mat* z, mat* w, mat* x, mat*b){
	NMatrix::DOT(z, w, x);
	NMatrix::ADD(z, z, b);
}

int main(){
	// and require two inputs, one neuron(sigmoid) with a bias and one output
	
	// setup training data as a matrix
	mat training(4, 3);
	training[0][0] = 0; training[0][1] = 0; training[0][2] = 0;
	training[1][0] = 0; training[1][1] = 1; training[1][2] = 0;
	training[2][0] = 1; training[2][1] = 0; training[2][2] = 0;
	training[3][0] = 1; training[3][1] = 1; training[3][2] = 1;

	// setup weight matrix as a 1x2 as, in output and two inputs
	mat w(1, 2);

	// setup bias as 1x1 matrix
	mat b(1, 1);

	// randomize our weights and biases 
	NMatrix::RANDOMIZE(&w);
	NMatrix::RANDOMIZE(&b);

	// setup how much times to iterate through backprop and learning rate
	int iterations = 10000;
	dataT lrate = 0.01f;
	
	// main loop
	for(int i=0; i<iterations; i++){
		// we need another loop to go through the training data 
		dataT dcdb = 0;
		mat dcdw(1, 2);
		dataT totalcost = 0;

		for(int c=0; c<4; c++){
			//setup our x(current input) a 2x1 matrix and y(what should our output should be)
			mat x(2, 1);
			mat y(1, 1);
			// setup our z matrix and act matrix this way we can use it in back prop
			mat z(1, 1);
			mat a(1, 1);

			// forward propegation 
			x[0][0] = training[c][0];
			x[1][0] = training[c][1];
			y[0][0] = training[c][2];

			forward(&z, &w, &x, &b);
			NMatrix::COPY(&a, &z);
			// applying non linear activation
			ActivationF::NM_sigmoid(&a);

			// taking cost (maybe useful to print)
			
			mat cost(1, 1);
			LossF::NM_squared_error(&cost, &a, &y);
			totalcost += cost[0][0];
			
			// backpropegation 
			
			// calculating error
			// error = (a - y) ~ sigmoidD(z)
			mat error(1, 1);
			mat temp_1(1, 1);
			NMatrix::SUBTRACT(&error, &a, &y);
			NMatrix::COPY(&temp_1, &z);
			ActivationF::NM_sigmoidD(&temp_1);
			NMatrix::HPRODUCT(&error, &error, &temp_1);
			
			// dcdb is just the error 
			dcdb += error[0][0] * lrate/4;

			// dcdw is the activation of the previous layer(input) x by error
			
			dcdw[0][0] += x[0][0] * error[0][0] * lrate;
			dcdw[0][1] += x[1][0] * error[0][0] * lrate;
		}
		
		b[0][0] -= dcdb;
		NMatrix::SUBTRACT(&w, &w, &dcdw);
		std::cout << "total cost: " << totalcost << std::endl;
	}


	// testing network
	for(int c=0; c<4; c++){
		//setup our x(current input) a 2x1 matrix and y(what should our output should be)
		mat x(2, 1);
		mat y(1, 1);
		// setup our z matrix and act matrix this way we can use it in back prop
		mat z(1, 1);
		mat a(1, 1);

		// forward propegation 
		x[0][0] = training[c][0];
		x[1][0] = training[c][1];
		y[0][0] = training[c][2];

		forward(&z, &w, &x, &b);
		NMatrix::COPY(&a, &z);
		// applying non linear activation
		ActivationF::NM_sigmoid(&a);
		std::cout << x[0][0] << " " << x[1][0] << " " << a[0][0] << std::endl;
	}
		
}
