#include <stdio.h> 

//prototype above main(), no header file needed, function defined below main() 
void adele();

int main() {
    printf("Hello world!\n");
    adele();
	return 0;
}


//function defined below main(), need prototype above main()
void adele() {
    printf("Hello hello from the other side!\n");
    return;
}

