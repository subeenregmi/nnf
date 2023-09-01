#include "neuralnetwork.hpp"

int main(){
	
	Matrix data("datasets/quadratic.csv");
	
	Dataset p(&data, 1.0f, 2);
	Matrix layers(1, 4);
	layers[0][0] = 2; layers[0][1] = 9; layers[0][2] = 6; 
	layers[0][3] = 1;  

	NN neuralnet(&layers, &p, 0.0005f);
	neuralnet.Layers[0]->setactivation(Ntanh);
	neuralnet.Layers[1]->setactivation(elu);
	neuralnet.Layers[2]->setactivation(sigmoid);

	neuralnet.randomize();
	neuralnet.setloss(mse);
	neuralnet.setreg(L2);
	neuralnet.Lambda = 0.001f;
	//neuralnet.printFlag = false;

	neuralnet.train(1000000, 10);

	/*
	float totaltime = 0;
	for(int i=0; i<10; i++){
		float starttime = time(0);
		neuralnet.train(100000, 10);
		neuralnet.randomize();
		float finishtime = time(0);
		totaltime += finishtime - starttime;
		std::cout << "Test " << i << " Completed in " << finishtime-starttime << " seconds.\n";
	}

	totaltime /= 10;

	std::cout << "Average time taken: " << totaltime;

*/

}
