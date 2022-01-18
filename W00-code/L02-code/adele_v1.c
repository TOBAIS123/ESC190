#include <stdio.h> 

//function defined above main(), no prototype or header file needed
void adele() {
    printf("Hello from the other side!\n");
    return;
}

int main() {
    printf("Hello world!\n");
    adele();
	return 0;
}
