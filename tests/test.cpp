#include "../include/matrix.hpp"

int main(){
	NMatrix::Matrix mat = {.rows=2, .cols=2};
	NMatrix::MEMORY_ALLOC(&mat);
	NMatrix::PRINT(&mat);
	mat[1][1] = 10.0f;
	NMatrix::PRINT(&mat);
	return 0;
}
