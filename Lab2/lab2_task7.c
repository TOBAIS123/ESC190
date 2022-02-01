#include<stdio.h>
#include<stdlib.h>

void append(int** x, int* n, int val){
    *x = (int *)realloc(*x, (*n+1) * sizeof(int));
    *(*x+*n)= val;
    *n++;
}