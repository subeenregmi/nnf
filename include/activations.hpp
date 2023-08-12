#ifndef ACTIVATIONS
#define ACTIVATIONS

#include "generic.hpp"
#include "matrix.hpp"

dataT linear(dataT x);
dataT linearD(dataT x);

dataT sigmoid(dataT x);
dataT sigmoidD(dataT x);

dataT relu(dataT x);
dataT reluD(dataT x);

dataT Ntanh(dataT x);
dataT NtanhD(dataT y);

dataT leakyrelu(dataT x);
dataT leakyreluD(dataT x);

dataT elu(dataT x);
dataT eluD(dataT x);

dataT softmax(dataT x);
dataT softmaxD(dataT x);

dataT swish(dataT x);
dataT swishD(dataT x);

void activate(Matrix* m, dataT(*activation)(dataT));

#endif // ACTIVATIONS
