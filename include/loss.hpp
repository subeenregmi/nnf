#ifndef LOSS
#define LOSS

#include "generic.hpp"
#include "matrix.hpp"

dataT mse(dataT x, dataT y);
dataT mseD(dataT x, dataT y);

void applyloss(Matrix* l, Matrix* x, Matrix* y, dataT(*lossf)(dataT, dataT));
#endif
