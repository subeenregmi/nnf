#include "activations.hpp"

namespace tnsrf_act{
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
		if(x>0){
			return x;
		}
		return 0;
	}

	dataT reluD(dataT x){
		if(x>0){
			return 1;
		}
		return 0;
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
			return 1;
		}
		return LEAKY_RELU_SLOPE;
	}

	dataT elu(dataT x){
		if(x > 0){
			return x;
		}
		return (exp(x) - 1) * ELU_SLOPE;
	}

	dataT eluD(dataT x){
		if(x > 0){
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
}
