#include <stdio.h>

//Thanks Prof. Ali! Piazza @19
void func(char s[]){
	char tmp;
	int i = 0;
	tmp = s[i];
	
	while(tmp != '\0'){
		fprintf(stdout, "%c\n", tmp);
		i ++;
		tmp = s[i];
	}
}

//Counting '5's in a string, related to Piazza @13
int func2(char s[]){
	char tmp;
	int i = 0, count = 0;
	tmp = s[i];
	
	while(tmp != '\0'){
        //if(tmp=='5') works too (and is more readable!)
        if (tmp - 48 == 5){ //see the last lecture slide
            fprintf(stdout, "Found a 5!\n");
            count++;
        }
        i ++;
        tmp = s[i];
	}
    return count;
}

int main(){
	char s[] = "Three Cheese Pizza";
	func(s);
    
    char s2[] = "Three Chee5e Pi55a";
    printf("I found %d x 5s!\n", func2(s2));
	
    return 0;
}