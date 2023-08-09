#include "matrix.hpp"
#include "activations.hpp"

Matrix::Matrix(int r, int c, bool identity=false){
	assert(r != 0);
	assert(c != 0);

	rows = r; 
	cols = c;	

	start = (dataT*)calloc(r*c, sizeof(dataT));

	if(identity){
		assert(r == c);
		this->makeIdentity();
	}
}

Matrix::~Matrix(){
	free(start);
}	

DoubleSubscript Matrix::operator[](int r){
	assert(r >= 0);
	assert(r < rows);
	DoubleSubscript DS(start, r, cols);
	return DS;
}

void Matrix::copy(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*this)[i][j] = (*m)[i][j];
		}
	}
}

void Matrix::randomize(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] = randD();
		}
	}
}

void Matrix::print(std::string label=""){
	if(label != ""){
		std::cout << label <<  " = [" << std::endl << std::endl;
	}
	else{
		std::cout << "[" << std::endl << std::endl;
	}

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			printf("%f	", (*this)[i][j]);
		}
		printf("\n\n");
	}
	std::cout << "]" << std::endl;
}

void Matrix::dot(Matrix* m){

	assert(cols == m->rows);	
	Matrix d(rows, m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<m->cols; j++){
			for(int k=0; k<cols; k++){
				d[i][j] += (*this)[i][k] * (*m)[k][j];
			}
		}
	}
	
	free(start);
	cols = m->cols;
	start = (dataT*)calloc(rows*cols, sizeof(dataT));

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] = d[i][j];
		}
	}
}

void Matrix::add(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] += (*m)[i][j];
		}
	}
}

void Matrix::subtract(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] -= (*m)[i][j];
		}
	}
}

void Matrix::scale(dataT sf){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] *= sf;
		}
	}
}

void Matrix::transpose(){
	Matrix d(cols, rows);
	
	for(int i=0; i<cols; i++){
		for(int j=0; j<rows; j++){
			d[j][i] = (*this)[i][j];
		}
	}

	free(start);
	rows = d.rows;
	cols = d.cols;
	start = (dataT*)calloc(rows*cols, sizeof(dataT));

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] = d[i][j];
		}
	}	
}

void Matrix::hproduct(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*this)[i][j] *= (*m)[i][j];
		}
	}
}

dataT Matrix::total(){
	dataT total = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			total += (*this)[i][j];
		}
	}
	return total; 
}

void Matrix::makeIdentity(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			if(i == j){
				(*this)[i][j] = 1;
			}
		}
	}
}

int main(){
	Matrix d(3, 3);
	d.randomize();
	d.scale(5.0);
	activate(&d, softmax);
	d.print();
	std::cout << d.total();
}
