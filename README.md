# NNF (Neural Network Framework) 

nnf is a neural network framework coded in C++ that allows for easy creation and training of neural networks. Supporting CSV it can be used to train most datasets. Although not being the best framework for machine learning, it is can be used for small neural networks and serves greately for educational purposes. There are a set of models that come with nnf in the models folder. 

Example: (binary adder)
```
int main(){

  Matrix D("datasets/adder.csv");
  Dataset data(&D, 1.00f, 3);
  Matrix Layers(1, 3);
  Layers[0][0] = 3; Layers[0][1] = 3; Layers[0][2] = 2;

  NN neuralnet(&Layers, &data, 0.051f);
  neuralnet.Layers[0]->setactivation(sigmoid);
  neuralnet.Layers[1]->setactivation(sigmoid);

  neuralnet.setloss(mse);
  neuralnet.randomize();

  neuralnet.train(1000000, 8);
  neuralnet.test(false);
}
```

TODO:
*   ~~Finish implementing XOR~~ 
*   CMAKE
*   ~~Add forward function in matrix.hpp~~
*   ~~Start working on nn class~~
*   ~~Implement Backprop algorithm in nn class~~
*   ~~Implement datasets, and a way to import datasets~~
*   Implement more loss functions
*	~~Implement MNIST~~
*	Implement softmax derivative properly
* 	~~Implement softmax with entropy loss rule~~
* 	Start working on convolutional nets
*	Implement Tensors (Total Redo)
*	Make way to share datasets and models
* 	~~Add more optimisation techniques (Regularization)~~
* 	Implements RNNs
