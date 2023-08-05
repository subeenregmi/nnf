#include "../include/matrix.hpp"

namespace NMatrix{

	DoubleSubscript Matrix::operator[](int r){
		assert(r >= 0);
		assert(r < rows);
		DoubleSubscript DS(start, r, cols);
		return DS;
	}

	Matrix::Matrix(int row, int col){
		assert(row != 0);
		assert(col != 0);
		rows = row;
		cols = col;
		start = (dataT*)malloc(sizeof(dataT)*rows*cols);
	}

	Matrix::~Matrix(){
		free(start);
	}

	// Init functions

	void IDENTITY(Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->rows == M->cols);

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
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				M->start[i*M->cols + j] = randD();
			}
		}
	}

	void COPY(Matrix* D, Matrix* M){
		assert(D->rows == M->rows);
		assert(D->cols == M->cols);

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
		
		for(int i=0; i<A->rows; i++){
			for(int j=0; j<A->cols; j++){
				D->start[i*A->cols + j] = A->start[i*A->cols + j] - B->start[i*A->cols + j];
			}
		}
	}

	void SCALE(Matrix* M, dataT scalar){
		assert(M->rows != 0);
		assert(M->cols != 0);

		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				M->start[i*M->cols + j] *= scalar;
			}
		}
	}

	void TRANSPOSE(Matrix* M){
		dataT arr[M->rows][M->cols];
		int rows = M->rows;
		int cols = M->cols;
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				arr[i][j] = M->start[i*M->cols + j];
			}
		}
		free(M->start);
		M->rows = cols;
		M->cols = rows;
		M->start = (dataT*)malloc(sizeof(dataT)*rows*cols);
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				M->start[i*M->cols + j] = arr[j][i];
			}
		}
	}

	dataT TOTAL(Matrix* M){

		dataT total = 0;
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				total += M->start[i*M->cols + j];
			}
		}
		return total;
	}

	void HPRODUCT(Matrix* D, Matrix* A, Matrix* B){
		assert(A->rows == B->rows);
		assert(A->cols == B->cols);
		assert(D->rows == B->rows);
		assert(D->rows == B->rows);
	
		for(int i=0; i<A->rows; i++){
			for(int j=0; j<A->cols; j++){
				D->start[i*D->cols + j] = A->start[i*D->cols +j] * B->start[i*D->cols + j];
			}
		}
	}

	// Miscellaneous functions 
	void PRINT(Matrix* M, std::string label){
		std::cout << label << " = [" << std::endl << std::endl;
		for(int i=0; i<M->rows; i++){
			for(int j=0; j<M->cols; j++){
				printf("%f	", M->start[i*M->cols + j]);
			}
			printf("\n\n");
		}
		std::cout << "]" << std::endl;
	}

	/*
	dataT GET_ITEM(Matrix* M, int rows, int cols){
		return M->start[rows*M->cols + cols];
	}

	void SET_ITEM(Matrix* M, dataT item, int rows, int cols){
		assert(M->start != nullptr);
		assert(M->rows > rows);
		assert(M->cols > cols);
		
		M->start[rows*M->cols + cols] = item;
	}
	*/
}
