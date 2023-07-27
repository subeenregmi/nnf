#include "../include/matrix.hpp"

namespace NMatrix{

	Matrix::~Matrix(){
		if(start != nullptr){
			free(start);
		}
	}

	// Init functions
	void MEMORY_ALLOC(Matrix* M){
		assert(M->rows != 0);	
		assert(M->cols != 0);
		assert(M->start == nullptr && "Matrix has already been allocated, destroy/free memory first");
		M->start = (dataT*)malloc(sizeof(dataT)*M->rows*M->cols);
		assert(M->start != nullptr);
	}

	void MEMORY_DEALLOC(Matrix* M){
		assert(M->start != nullptr && "Matrix has not been allocated.");
		free(M->start);
		M->start = nullptr;
	}

	void IDENTITY(Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				if(i == j){
					M->start[i*M->cols + j] = 1.0f;
				}
				else{
					M->start[i*M->cols + j] = 0.0f;
				}
			}
		}
	}

	void RANDOMIZE(Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				M->start[i*M->cols + j] = randD();
			}
		}
	}

	void COPY(Matrix* D, Matrix* M){
		assert(D->rows == M->rows);
		assert(D->cols == M->cols);
		assert(M->start != nullptr);
		assert(D->start != nullptr);

		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				D->start[i*M->cols + j] = M->start[i*M->cols + j];
			}
		}
	}

	// Mathematical functions

	void DOT(Matrix* D, Matrix* A, Matrix* B){
		// D = A * B
		assert(A->cols == B->rows);	
		assert(D->rows == A->rows);
		assert(D->cols == B->cols);

		for(int i=0; i<A->rows; i++){
			for(int j=0; j<B->cols; j++){
				for(int k=0; k<A->cols; k++){
					D->start[i*D->cols+j] += A->start[i*A->cols+k] * B->start[k*B->rows+j];
				}
			}
		}
	}

	void ADD(Matrix* D, Matrix* A, Matrix* B){
		assert(A->rows == B->rows);
		assert(A->cols == B->cols);
		assert(D->rows == A->rows);
		assert(D->cols == A->cols);
		assert(A->start != nullptr && "Matrix A (2nd param) has not been allocated");
		assert(B->start != nullptr && "Matrix B (3rd param) has not been allocated");
		assert(D->start != nullptr && "Matrix D (1nd param) has not been allocated");
		
		for(int i=0; i<A->rows; i++){
			for(int j=0; j<A->cols; j++){
				D->start[i*A->cols + j] = A->start[i*A->cols + j] + B->start[i*A->cols + j];
			}
		}
	}
	
	void SUBTRACT(Matrix* D, Matrix* A, Matrix* B){
		assert(A->rows == B->rows);
		assert(A->cols == B->cols);
		assert(D->rows == A->rows);
		assert(D->cols == A->cols);
		assert(A->start != nullptr && "Matrix A (2nd param) has not been allocated");
		assert(B->start != nullptr && "Matrix B (3rd param) has not been allocated");
		assert(D->start != nullptr && "Matrix D (1nd param) has not been allocated");
		
		for(int i=0; i<A->rows; i++){
			for(int j=0; j<A->cols; j++){
				D->start[i*A->cols + j] = A->start[i*A->cols + j] - B->start[i*A->cols + j];
			}
		}
	}

	void SCALE(Matrix* M, dataT scalar){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				M->start[i*M->cols + j] *= scalar;
			}
		}
	}

	void TRANSPOSE(Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		Matrix D = {.rows = M->cols, .cols = M->rows};
		MEMORY_ALLOC(&D);

		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				D.start[j*D.cols + i] = M->start[i*M->cols + j];
			}
		}

		MEMORY_DEALLOC(M);
		M->rows = D.rows;
		M->cols = D.cols;
		M->start = D.start;
	}

	dataT TOTAL(Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		dataT total = 0;
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				total += M->start[i*M->cols + j];
			}
		}
		return total;
	}


	// Miscellaneous functions 
	void PRINT(Matrix* M){
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				printf("%f	", GET_ITEM(M, i, j));
			}
			printf("\n\n");
		}
	}

	dataT GET_ITEM(Matrix* M, int rows, int cols){
		return M->start[rows*M->cols + cols];
	}

	void SET_ITEM(Matrix* M, dataT item, int rows, int cols){
		assert(M->start != nullptr);
		assert(M->rows > rows);
		assert(M->cols > cols);
		
		M->start[rows*M->cols + cols] = item;
	}
}
