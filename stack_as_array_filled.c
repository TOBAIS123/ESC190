#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 200

/**
	Implements a stack data type using dynamic arrays;
	the end of the array is treated as the top of the
	stack
*/

typedef struct Person {
	int age;
	char name[MAX_NAME_LEN];
} Person;

typedef struct StackAsArray {
	// [Person*, Person*,Person*, Person*]
	Person** cargo; // end of the array is the top of the stack
	int max_el; // total capacity of the stack currently
	int count_el; // number of active stack elements
} StackAsArray;

/**
	Formatted printed output to stdout
*/
void print_person(Person* p){
	fprintf(stdout, "%s Age: %d", p->name, p->age);
}


void print_stack(StackAsArray* s){
	fprintf(stdout, "\n\n%d of %d elements on the stack\n", s->count_el, s->max_el);
	for (int i=s->count_el-1; i >= 0; i--){ // start from the end of the array, i.e., the top
		if (i == s->count_el - 1){
			// color formatting: red for the top of the stack
			fprintf(stdout, "\033[0;31m");
			fprintf(stdout, "[");
			fprintf(stdout, "\033[0m");
			print_person((s->cargo)[i]);
			fprintf(stdout, "\033[0;31m");
			fprintf(stdout, "] ---> TOP OF THE STACK\n");
			fprintf(stdout, "\033[0m");
		} else if (i == 0){
			// color formatting: green for the bottom of the stack
			fprintf(stdout, "\033[0;32m");
			fprintf(stdout, "[");
			fprintf(stdout, "\033[0m");
			print_person((s->cargo)[i]);
			fprintf(stdout, "\033[0;32m");
			fprintf(stdout, "] ---> BOTTOM OF THE STACK\n");
			fprintf(stdout, "\033[0m");
		} else {
			// middle of the stack
			fprintf(stdout, " ");
			print_person((s->cargo)[i]);
			fprintf(stdout, "\n");
		}
		
	}
}


/**
	Constructing needed structs (initializing)
*/
Person* person_from_info(char name[], int age){
	Person* p = (Person*)malloc(sizeof(Person));
	p->age = age;
	strcpy(p->name, name);
	return p;
}


StackAsArray* initialize_stack(int size){
	/**
		Initialize an empty stack with max_el as size
		and count_el as 0
	*/
	StackAsArray* s = (StackAsArray *)malloc(sizeof(StackAsArray));
	s->max_el = size;
	s->count_el = 0;
	s->cargo = (Person**)malloc(sizeof(Person *) * s->max_el);
	return s;
}

/**
	Stack push and pop
*/

void push(StackAsArray* s, Person* p){
	if (s->count_el == s->max_el){
		//max capacity, oh no
		s->cargo = realloc(s->cargo, sizeof(Person *) * s->max_el * 2);
		s->max_el = s->max_el * 2;
	}
	
	s->cargo[s->count_el] = p;
	s->count_el++;
}

Person* pop(StackAsArray* s){
	s->count_el--;
	return (s->cargo)[s->count_el];
}

int main(){
	StackAsArray* s = initialize_stack(10);
	Person* p;

	p = person_from_info("Zike Mucke", 20);
	push(s, p);
	print_stack(s);
	
	p = person_from_info("Jeve Stobs", 34);
	push(s, p);
	print_stack(s);
		
	p = person_from_info("Mike Bobbb", 55);
	push(s, p);
	print_stack(s);
	
	p = person_from_info("Jerry Chan", 24);
	push(s, p);
	print_stack(s);
	
	while (s->count_el != 0){
		Person* popped = pop(s);
		print_stack(s);
	}

	//exercise: free the memory so that everything runs Valgrind clean
}