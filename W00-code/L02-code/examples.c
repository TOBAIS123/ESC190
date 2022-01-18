#include <stdio.h>

int main() {

    // Student Question: Can we add 1 + c?
    printf("1 + 'c' is: %c\n", 1 + 'c');
    printf("1 + 'c' is: %d\n\n", 1 + 'c');
    

    //Some arithmetic examples
    
    //Division
    printf("Dividing integers: 2/5 evaluates to %d\n", 2/5);
    float float_result = 2/5;
    printf("Assigning to a float will give you: %f\n", float_result);
    printf("Dividing floating points: 2.0/5.0 evaluates to %f\n\n", 2.0/5.0);
    
    //Modulus
    printf("2 %% 5 is %d\n", 2%5);
    printf("0 %% 5 is %d\n", 0%5);
    printf("15 %% 5 is %d\n\n", 15%5);
    
    //Assignment and incr/decrement operators
    int n = 1, p = 2;
    
    n += p; //n is modified,  p is not
    printf("n is %d, p is %d\n", n, p);
    n = p++ + 2; //both modified, p modified after assignment
    printf("n is %d, p is %d\n", n, p);
    n = ++p + 2; //both modified, p modified before assignment
    printf("n is %d, p is %d\n\n", n, p);
    
    
    //Conditional statements
    //n = 1; //change n and check which statements would execute
    if (n==2){
        printf("n is 2\n");
    }
    else if (n%2==1){
        printf("n is an odd number\n");
    }
    else{
        printf("n is even and not equal to 2\n");
    }
    if (n>10){
        printf("n is larger than 10\n");
    }
    printf("\n");
    
    
    //Loops - can you write these as while loops?
    int i=0, j=10;
    
    //1 up to j
    for(i=1; i<=j; i++){
        printf("%d ",i);
    }
    printf("\n");
    
    // 0 up to j-1, steps of 2
    for(i=0; i<j; i+=2){
        printf("%d ", i);
    }
    printf("\n");
    
    // j-1 down to 0
    for(i=j-1; i>=0; i--){
        printf("%d ", i);
    }
    printf("\n");
    
    //j down to 1 - note this is not as readable as the others
    i = j;
    for(;i>0;){
        printf("%d ", i);
        i--;
    }
    printf("\n");
    
    return 0;
}