#include <stdio.h>


void print_matrix(char s[], double m[], size_t rows, size_t cols){
	printf("%4s=\n", s);
	for(size_t i = 0; i < rows; i++){
		for(size_t j=0; j < cols; j++){
			printf("  %4g",m[cols * i + j]);
		}
		printf("\n");
	}	
}

void transpose(double m[],size_t rows, size_t cols, double r[]){
	for(size_t i=0; i < rows; i++){
		for(size_t j=0; j < cols; j++){
			r[j*rows + i] = m[i*cols + j];
		}
	}	
}

void add(double m1[], double m2[], size_t rows, size_t cols, double r[]){
	for(size_t i = 0;i < rows; i++){
		for(size_t j=0; j<cols;j++){
			r[i*cols +j] = m1[i*cols+j] + m2[i*cols+j];
		}
	}
}

void mul(double m1[], double m2[], size_t r1, size_t c1, size_t c2, double r[]){

	for(size_t r0 = 0;r0 < r1; r0++){
		for(size_t c = 0;c < c2; c++){
			double res = 0;
			for(size_t col =0;col < c1; col++){
				res += m1[r0 * c1 + col] * m2[col*c2+c];
			}
			r[r0 * r1+c]= res;
		}
	}

}
