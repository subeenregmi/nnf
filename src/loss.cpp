#include "loss.hpp"

namespace tnsrf_loss{
	dataT mse(dataT x, dataT y){
		return pow(y-x, 2);
	}

	dataT mseD(dataT x, dataT y){
		return -2*(y-x);
	}

	dataT cel(dataT x, dataT y){
		return -(y*log(x) + (1-y)*log(1-x));
	}

	dataT celD(dataT x, dataT y){
		return (-y/x) + ((1-y)/(1-x));
	}
}
