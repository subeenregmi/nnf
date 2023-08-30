#include "neuralnetwork.hpp"
#include "generic.hpp"

int main(){

	std::fstream file("datasets/mnist_train.csv");	
	std::ofstream outfile("datasets/mnist_training_set.csv");
	std::string line;
	while(getline(file, line)){
		std::string start = "";
		start += line[0];
		int label = std::stoi(start);
		line.erase(line.begin());
		line.erase(line.begin());
		line += ",";
		for(int i=0; i<10; i++){
			if(i==label){
				line += '1';
			}
			else{
				line += '0';
			}
			if(i != 9){
				line += ',';
			}
		}
		outfile << line << std::endl;
	}



	


	return 0;
	
}
