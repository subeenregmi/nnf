#ifndef ACTIVATIONS
#define ACTIVATIONS

#include "generic.hpp"
#include "matrix.hpp"

dataT sigmoid(dataT x);
dataT sigmoidD(dataT x);

dataT relu(dataT x);
dataT reluD(dataT x);

dataT tanh(dataT x);
dataT tanhD(dataT y);

void applyactivation();
// Matrix Functions
void sigmoid(Matrix* m);
void sigmoidD(Matrix* m);
void relu(Matrix* m);
void reluD(Matrix* m);

#endif // ACTIVATIONS
