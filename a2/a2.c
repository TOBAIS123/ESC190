#include "a2.h"

int bitwise_xor(int value){
    dec_value = dec_to_bin(
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
    return value + numerator % 2 * pow(10, i);;
}

char *xor_encrypt(char c){
    //add code here
}

char xor_decrypt(char *s){
    //add code here
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

int main(void)
{
    printf("%d", dec_to_bin(83));
    return 0;
}