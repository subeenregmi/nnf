#include "../include/generic.hpp"
#include "../include/matrix.hpp"

typedef NMatrix::Matrix MAT;

void forward(MAT* Z, MAT* W, MAT* X, MAT* B){
	
}

int main(){

	// xor gate represented as (A + B) * ~(A * B)
	// neural network requires 5 nodes, 2 input nodes
	
	// X (input data)
	// 0 0 , 0 1, 1 0 , 1 1
	
	MAT X = {.rows = 2, .cols = 4}; 
	NMatrix::MEMORY_ALLOC(&X);
	NMatrix::SET_ITEM(&X, 0, 0, 0);
	NMatrix::SET_ITEM(&X, 0, 1, 0);

	NMatrix::SET_ITEM(&X, 0, 0, 1);
	NMatrix::SET_ITEM(&X, 1, 1, 1);
	
	NMatrix::SET_ITEM(&X, 1, 0, 2);
	NMatrix::SET_ITEM(&X, 0, 1, 2);

	NMatrix::SET_ITEM(&X, 1, 0, 3);
	NMatrix::SET_ITEM(&X, 1, 1, 3);

	// Y (output data)
	MAT Y = {.rows = 1, .cols = 4};
	NMatrix::MEMORY_ALLOC(&Y);
	NMatrix::SET_ITEM(&Y, 0, 0, 0);
	NMatrix::SET_ITEM(&Y, 1, 0, 1);
	NMatrix::SET_ITEM(&Y, 1, 0, 2);
	NMatrix::SET_ITEM(&Y, 0, 0, 3);

	// Weights
	MAT W1 = {.rows = 2, .cols = 2};
	MAT W2 = {.rows = 1, .cols = 2};
	NMatrix::MEMORY_ALLOC(&W1);
	NMatrix::MEMORY_ALLOC(&W2);
	NMatrix::RANDOMIZE(&W1);
	NMatrix::RANDOMIZE(&W2);

	// Biases
	MAT b1 = {.rows = 2, .cols = 1};
	MAT b2 = {.rows = 1, .cols = 1};
	NMatrix::MEMORY_ALLOC(&b1);
	NMatrix::MEMORY_ALLOC(&b2);
	NMatrix::RANDOMIZE(&b1);
	NMatrix::RANDOMIZE(&b2);
	
	/*
	std::cout << "X: " << std::endl;
	NMatrix::PRINT(&X);

	std::cout << "Weights in layer 1: " << std::endl;
	NMatrix::PRINT(&W1);

	std::cout << "Weights in layer 2: " << std::endl;
	NMatrix::PRINT(&W2);

	std::cout << "Biases in layer 1: " << std::endl;
	NMatrix::PRINT(&b1);

	std::cout << "Biases in layer 2: " << std::endl;
	NMatrix::PRINT(&b2);
	*/

	int iterations = 10;
	dataT x0;
	dataT x1;
	MAT A1 = {.rows = 2, .cols = 1};
	MAT A2 = {.rows = 1, .cols = 1};
	NMatrix::MEMORY_ALLOC(&A1);
	NMatrix::MEMORY_ALLOC(&A2);

	for(int i=0; i<10; i++){
		for(int j=0; j<4; j++){
			x0 = GET_ITEM(&X, 0, j);
			x1 = GET_ITEM(&X, 1, j);
			MAT x = {.rows = 2, .cols = 1};
			NMatrix::MEMORY_ALLOC(&x);
			NMatrix::SET_ITEM(&x, x0, 0, 0);
			NMatrix::SET_ITEM(&x, x1, 1, 0);


		}

		NMatrix::MEMORY_DEALLOC(&x);
	}
	
	NMatrix::MEMORY_DEALLOC(&X);
	NMatrix::MEMORY_DEALLOC(&Y);
	NMatrix::MEMORY_DEALLOC(&W1);
	NMatrix::MEMORY_DEALLOC(&W2);
	NMatrix::MEMORY_DEALLOC(&b1);
	NMatrix::MEMORY_DEALLOC(&b2);

	return 0;
}
