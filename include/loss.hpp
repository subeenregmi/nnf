#pragma once

#include "generic.hpp"
#include <cmath>

namespace tnsrf_loss{
	dataT mse(dataT x, dataT y);
	dataT mseD(dataT x, dataT y);
	dataT cel(dataT x, dataT y);
	dataT celD(dataT x, dataT y);
}
