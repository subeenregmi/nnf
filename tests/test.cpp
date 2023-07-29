#include "../include/matrix.hpp"

int main(){
	NMatrix::Matrix mat(2, 2);
	NMatrix::PRINT(&mat, "w1");
	mat[1][1] = 10.0f;
	NMatrix::PRINT(&mat, "w1");
	return 0;
}
