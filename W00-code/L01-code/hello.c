// This is a single line comment. It is useful for adding short comments

// Start your file with directives (pre-processor commands)
#include <stdio.h> 
// This directive tells the compiler that we want to link the standard 
// input/output library


/* This is a multi-line comment. It is useful for adding documentation.
 * Document: brief description of what the function does, inputs (parameters), 
 * outputs (return values).
 *
 * For example:
 * Description: This main() function prints "Hello World!".
 * Input: the default main() parameters (optional)
 * Output: returns 0
 */
int main(int argc, char **argv) { 
    // int main(void) or int main() would work as well since no arguments 
    //are required
	
    // This is the function body, statements go here
    // Use ; to end statements and use indenting (tabs or spaces) to make the 
    // code easy to read
    
    // printf() is a function from stdio.h
    printf("Hello World!\n"); // \n is used to print a new-line character
	
    return 0; // return the integer value 0
} // The function body is enclosed in {}

// Note: this is too many comnments, future code demos will have fewer comments.
