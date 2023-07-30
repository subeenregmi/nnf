#include "matrix.hpp"
#include "activations.hpp"
#include "doublesubscript.hpp"
#include "generic.hpp"
#include "loss.hpp"
#include <vector>

template <typename T>
bool TEST(T x, T Expected){
	if(x == Expected){
		return true;
	}
	return false;
}

void Tester(){
	int total_tests = 0;
	int passed_tests = 0;
	bool passed;
	std::vector<std::string> FailedTests;

	NMatrix::Matrix m(2, 2);
	passed = TEST(m[0][0], 0.0f);
	total_tests++;
	if(passed){
		passed_tests++;
	}
	else{
		FailedTests.push_back("Checking Matrix Initiliase");
	}
	
	std::cout << passed_tests << "/" << total_tests << " passed." << std::endl;
	std::cout << "Failed tests" << std::endl;
	std::cout << "-----------------------" << std::endl;
	for(int i=0; i<(int)FailedTests.size(); i++){
		std::cout << FailedTests[i] << std::endl;
	}
}

int main(){
	Tester();
	return 0;
}
