#ifndef MATRIX
#define MATRIX

#include "generic.hpp"
#include "doublesubscript.hpp"

class Matrix{
	public:
		int rows; 
		int cols;
		dataT* start;
		Matrix(int r, int c, bool identity = false);
		DoubleSubscript operator[](int r);
		~Matrix();

		void copy(Matrix* m);
		void randomize();
		void print(std::string label = "");
		void clear();

		void dot(Matrix* m);
		void add(Matrix* m);
		void subtract(Matrix* m);
		void scale(dataT sf);
		void transpose();
		void hproduct(Matrix* m);
		dataT total();

	private: 
		void makeIdentity();
};

#endif
