#include "matrix.hpp"
#include "activations.hpp"
#include "doublesubscript.hpp"
#include "generic.hpp"
#include "loss.hpp"
#include <vector>

int total_tests = 0;
int passed_tests = 0;
bool passed;
std::vector<std::string> FailedTests;

template <typename T>
bool TEST(T x, T Expected){
	if(x == Expected){
		return true;
	}
	return false;
}

void printTest(){
	std::string s;
	if(passed){
		s = "passed";
	}
	else{
		s = "failed";
	}
	std::cout << total_tests << ". Test " << s << "!" << std::endl ;
}

void HandleTest(std::string TestName){
	total_tests++;
	if(passed){
		passed_tests++;
	}
	else{
		FailedTests.push_back(TestName);
	}
	printTest();
}

void Tester(){
	
	if(true){
		NMatrix::Matrix m(2, 2);
		passed = TEST(m[0][0], 0.0f);
		HandleTest("Checking Matrix Initialized Properly");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		m[1][1] = 1.5f;
		passed = TEST(m[1][1], 1.5f);
		HandleTest("Checking if assignment with double brackets works");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		m[0][1] = 5; m[1][1] = 6;
		passed = TEST((m[0][1] == 5) && (m[1][1] == 6), true);
		HandleTest("Checking if assignments with double brackets twice works");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		NMatrix::IDENTITY(&m);
		passed = TEST((m[0][0] == 1) && (m[1][1] == 1), true);
		HandleTest("Checking if identity 2x2 matrix creates like expected");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		NMatrix::RANDOMIZE(&m);
		passed = TEST((m[0][0] != 0) && (m[0][1] != 0) && (m[1][0] != 0) && (m[1][1] != 0), true);
		HandleTest("Checking if randomizing matrix works like expected");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		m[0][0] = 1.0f;
		NMatrix::Matrix d(2, 2);
		NMatrix::COPY(&d, &m);
		passed = TEST((d[0][0] == 1) && (d[0][1]==0) && (d[1][1]==0) && (d[1][0]==0), true);
		HandleTest("Checking if copy works");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		m[0][0] = 1; 
		m[0][1] = 2;
		m[1][0] = 3;
		m[1][1] = 4;
		NMatrix::Matrix d(2, 2);
		NMatrix::COPY(&d, &m);
		passed = TEST((d[0][0] == 1) && (d[0][1]==2) && (d[1][1]==4) && (d[1][0]==3), true);
		HandleTest("Checking if copying 2x2 full matrix works like expected");
		passed = (NMatrix::TOTAL(&m), 10);
		HandleTest("Checking if total works properly");
		NMatrix::PRINT(&m, "pretranspose");
		NMatrix::TRANSPOSE(&m);
		NMatrix::PRINT(&m, "transposed");
	}

	if(true){
		NMatrix::Matrix m(2, 2);
		NMatrix::Matrix d(2, 2);
		NMatrix::Matrix c(2, 2);
		NMatrix::RANDOMIZE(&m);
		NMatrix::IDENTITY(&d);
		NMatrix::DOT(&c, &d, &m);
		passed = TEST((m[0][0] == c[0][0]) && (m[0][1] == c[0][1]) && (m[1][0] == c[1][0]) && (m[1][1] == c[1][1]), true);
		HandleTest("Checking if dot product with indentity works like expected");
	}
	
	if(true){

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
