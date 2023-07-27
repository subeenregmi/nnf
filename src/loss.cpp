#include "../include/loss.hpp"

namespace LossF{
	dataT squared_error(dataT x, dataT y){
		return pow(y-x, 2);
	}
}
