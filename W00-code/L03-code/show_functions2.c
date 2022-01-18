#include <stdio.h>
#define ARR_LENGTH 5 //ARR_LENGTH will be replaced with 5

//Multiply 2 numbers
int multiply2(int x[]){
	int result = x[0]*x[1];
	return result;
}

//Sum of array elements
int add(int x[]){
	int sum = 0;
    for (int i=0; i< ARR_LENGTH; i++){
        sum += x[i];
    }
	return sum;
}

//Double an array's elements
void doubler(int x[]){
    for (int i=0; i< ARR_LENGTH; i++){
        x[i]*=2; //array is modified!
    }
}

int main() {
	int x[] = {2,3};
    int y[ARR_LENGTH] = {5,5,5,5,5};
    
	fprintf(stdout, "Multiplying x[0]*x[1] gives %d\n", multiply2(x));
	fprintf(stdout, "The sum of elements in y[] is %d\n", add(y));
    
    doubler(y); //array is modified!
    for (int i=0; i< ARR_LENGTH; i++){
        printf("%d ", y[0]);
    }
    return 0;
}
