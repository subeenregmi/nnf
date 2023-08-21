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

		// Miscellaneous functions
		void copy(Matrix* m); 
		void copyrow(Matrix* m, int rowfrom, int rowto); 
		void copycol(Matrix*m, int colfrom, int colto); 
		void randomize();
		void print(std::string label = "");
		void clear();

		// Mathematical functions
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
