#include "../include/generic.hpp"
#include "../include/matrix.hpp"
#include "../include/activations.hpp"
#include "../include/loss.hpp"

typedef NMatrix::Matrix MAT;

int main(){
	MAT m(2, 2);
	m[0][1] = 1.0f;
	NMatrix::PRINT(&m,"m1");
}
