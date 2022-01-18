#include <stdio.h> 
 
int main() {
    
    int small_num = 42, overflow_test;
    char a_letter = 'c';
    int unpredictable_num;
    
    //Printing integers and characters
    printf("The value of small_num is: %d\n", small_num);
    printf("We can print small_num as a character: %c\n\n", small_num);
    
    printf("Let's print a_letter: %c\n", a_letter);
    printf("We can print a_letter as an integer: %d\n\n", a_letter);
    
    // Overflow example - avoid this!
    overflow_test = 123456789123456789;
    printf("The value stored in overflow_test is: %d\n", overflow_test);
    
    //The value of predictable_num can vary if we don't assign a value
    printf("unpredictable_num is: %d\n\n", unpredictable_num);
    
    // Integer and floating point casting
    small_num = 42.9999;
    printf("Implicit casting (float value to int variable) - small_num is %d\n", small_num);
    printf("The part of the float value %f was lost during casting \n\n", 42.9999);
    
    printf("Explicit casting (int to float) - (float) %d is %f\n", 2, (float) 2);
    printf("Explicit casting (float to int) - (int) %f is: %d\n\n", 42.9999, (int)42.9999);
    
    printf("We can control the number of decimal places printed:\n");
    printf("42.9999 printed to 2 decimal places is: %.2f\n", 42.9999);
    printf("80.4561 printed to 1 decimal places is: %.1f\n", 123.456-42.9999);
    
    //Try some other examples on your own!
    
	return 0;
}