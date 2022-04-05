#include "a2.h"

int bitwise_xor(int value){
    // int bin_value = dec_to_bin(value);
    // int bin_key = dec_to_bin(KEY);
    // int return_val = 0;
    // for (int i = 0; i < 7; i++)
    // {
    //     return_val += 
    return value ^ KEY;
}

int dec_to_bin(int dec)
{
    int i = 0;
    int numerator = dec;
    int value = 0;
    do
    {
        value += numerator % 2 * pow(10, i);
        numerator = (int)(numerator/2);
        i++;
    } while ((numerator / 2) >= 1);
    return value + numerator % 2 * pow(10, i);
}

int bin_to_dec(int bin)
{
    
}

char *xor_encrypt(char c){
    char* encrypted_string = malloc(7);
    int value = dec_to_bin(bitwise_xor((int)c));
    printf("%d\n", value);
    for (int i = 0; i < 7; i++)
    {
        printf("char: %c\n", (char)((value % 10)+48));
        encrypted_string[6-i] = (char)((value % 10)+48);
        value = (int)(value/10);
    }
    printf("encrypted_string: %s\n", encrypted_string);
    return encrypted_string;
}

char xor_decrypt(char *s){
    int value = 0;
    for (int i = 0; i < 7; i++)
    {
        value += ((int)(s[6-i])-48)*pow(10, i);
    }
    bitwise_xor(value
    printf("value: %d\n", value);
}

char *gen_code(char *msg){
    //add code here;
}

char *read_code(char *code){
    //add code here
}

char *compress(char *code){
    //add code here
}

char *decompress(char *code){
    //add code here
}

int calc_ld(char *sandy, char *cima){
    //add code here
}

// int main(void)
// {
//     printf("%d", dec_to_bin(83));
//     return 0;
// }