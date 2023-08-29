#include "activations.hpp"

dataT LEAKY_RELU_SLOPE = 0.1;
dataT ELU_SLOPE = 1.0;

dataT linear(dataT x){
	return x;
}

dataT linearD(dataT x){
	return 1;
}

dataT sigmoid(dataT x){
	return 1 / (1 + exp(-x));
}

dataT sigmoidD(dataT x){
	return sigmoid(x) * (1-sigmoid(x));
}

dataT relu(dataT x){
	if(x<=0){
		return 0;
	}
	return x;
}

dataT reluD(dataT x){
	if(x<=0){
		return 0;
	}
	return 1;
}

dataT Ntanh(dataT x){
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

dataT NtanhD(dataT x){
	return 1 - pow(tanh(x), 2);
}

dataT leakyrelu(dataT x){
	return std::max(LEAKY_RELU_SLOPE*x, x);
}

dataT leakyreluD(dataT x){
	if(x>0){
		return x;
	}
	return LEAKY_RELU_SLOPE;
}

dataT elu(dataT x){
	if(x >= 0){
		return x;
	}
	return (exp(x) - 1) * ELU_SLOPE;
}

dataT eluD(dataT x){
	if(x >= 0){
		return 1;
	}
	return elu(x) * ELU_SLOPE;
}

dataT softmax(dataT x){
	return exp(x);	
}

dataT softmaxD(dataT x){
	return x;
}

dataT swish(dataT x){
	return x * sigmoid(x);
}

dataT swishD(dataT x){
	return sigmoid(x) + sigmoidD(x)*x;
}

void activate(Matrix* m, dataT (*activation)(dataT)){
	assert(activation != nullptr);
	dataT eTotal = 0;
	int c = m->cols;

	for(int i=0; i<m->rows; i++){
		for(int j=0; j<c; j++){
			m->start[i*c + j] = activation(m->start[i*c + j]);
			if(activation == softmax){
				eTotal += m->start[i*c + j];
			}
		}
	}
	if(activation == softmax){
		for(int i=0; i<m->rows; i++){
			for(int j=0; j<m->cols; j++){
				m->start[i*c + j] /= eTotal;
			}
		}
	}
	if(activation == softmaxD){
		int r = (*m).rows;
		Matrix d(r, r, false);
		
		for(int i=0; i<d.rows; i++){
			for(int j=0; j<d.cols; j++){
				if(i==j){
					d.start[i*r + j] = m->start[i*m->cols] * (1 - m->start[i*m->cols]);	
				}
				else{
					d.start[i*r + j] = - (m->start[i*m->cols]) * m->start[j*m->cols];		
				}
			}
		}

		m->cols = d.cols;
		free(m->start);
		m->start = (dataT*)calloc(m->rows*m->cols, sizeof(dataT));
		m->copy(&d);
	}
}
