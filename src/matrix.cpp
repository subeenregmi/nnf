#include "matrix.hpp"
#include "activations.hpp"
#include "loss.hpp"

Matrix::Matrix(int r, int c, bool identity){
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

Matrix::Matrix(std::string filename){
	std::ifstream file(filename);
	assert(file != NULL);
	rows = 0;
	cols = 0;
	std::string line;
	std::string element = "";
	std::vector<std::string> elements; 
	while(getline(file, line)){
		rows++;
		cols=0;
		for(char& c: line){
			if(c == ','){
				elements.push_back(element);
				element = "";
				cols++;
			}
			else if(c == ' '){
				continue;
			}
			else{
				element += c;
			}
		}	
		elements.push_back(element);
		element = "";
		cols++;
	}

	start = (dataT*)calloc(rows*cols, sizeof(dataT));

	int c=0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			double val = std::stod(elements[c]);
			start[i*cols + j] = val; // TODO  
			c++;
		}
	}

	file.close();
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
			start[i*cols + j] = m->start[i*cols + j];
		}
	}
}

void Matrix::copyrow(Matrix* m, int rowfrom, int rowto){
	assert(cols == m->cols);
	assert((rowfrom > 0) && (rowto > 0));
	assert(m->rows >= rowfrom);
	assert(rows >= rowto);

	for(int i=0; i<cols; i++){
		start[(rowto-1)*cols +  i] = m->start[(rowfrom-1)*cols + i]; 
	}
}

void Matrix::copycol(Matrix* m, int colfrom, int colto){
	assert(rows == m->rows);
	assert((colfrom > 0) && (colto > 0));
	assert(m->cols >= colfrom);
	assert(cols >= colto);

	for(int i=0; i<rows; i++){
		start[(i * cols) + colto-1] = m->start[(i*m->cols) + colfrom-1]; 
	}
}

void Matrix::randomize(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			start[i*cols + j] = randD();
		}
	}
}

void Matrix::print(std::string label){
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

void Matrix::clear(){
	free(start);
	start = (dataT*)calloc(rows*cols, sizeof(dataT));
}

void Matrix::dot(Matrix* m){

	assert(cols == m->rows);	
	Matrix d(rows, m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<m->cols; j++){
			for(int k=0; k<cols; k++){
				d.start[i*m->cols + j] += start[i*cols + k] * m->start[k*m->cols+ j];
			}
		}
	}
	
	free(start);
	cols = m->cols;
	start = (dataT*)calloc(rows*cols, sizeof(dataT));

	this->copy(&d);
}

void Matrix::add(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			start[i*cols + j] += m->start[i*cols + j];
		}
	}
}

void Matrix::subtract(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			start[i*cols + j] -=  m->start[i*cols + j];
		}
	}
}

void Matrix::scale(dataT sf){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			start[i*cols + j] *= sf;
		}
	}
}

void Matrix::transpose(){
	Matrix d(cols, rows);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			d.start[j*rows + i] = start[i*cols + j];
		}
	}

	free(start);
	rows = d.rows;
	cols = d.cols;
	start = (dataT*)calloc(rows*cols, sizeof(dataT));

	this->copy(&d);
}

void Matrix::hproduct(Matrix* m){
	assert(rows == m->rows);
	assert(cols == m->cols);

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			start[i*cols + j] *= m->start[i*cols + j];
		}
	}
}

dataT Matrix::total(){
	dataT total = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			total += start[i*cols + j];
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
