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
    int dec = 0;
    int i=0;
    while (bin > 0)
    {
        dec += (2 * bin % 10)*pow(2, i);
        bin = (int)(bin / 10);
        i++;
    }
    return dec;
}

char *xor_encrypt(char c){
    char* encrypted_string = malloc(8);
    encrypted_string[7] = '\0';
    int value = dec_to_bin(bitwise_xor((int)c));
    for (int i = 0; i < 7; i++)
    {
        encrypted_string[6-i] = (char)((value % 10)+48);
        value = (int)(value/10);
    }
    return encrypted_string;
}

char xor_decrypt(char *s){
    int value = 0;
    for (int i = 0; i < 7; i++)
    {
        value += (((int)(s[6-i]))-48)*(int)(pow(2, i));
        //printf("value+=%d\n", (((int)(s[6-i]))-48)*(int)(pow(2, i)));
    }
    return (char)(bitwise_xor(value));
}

char *gen_code(char *msg){
    char* code = malloc(257);
    char full_msg[255];
    int msg_len = 0;
    while (msg[msg_len] != '\0')
    {
        msg_len++;
    }
    for (int x = 0; x<256;x++)
    {
        code[x] = '0';
        full_msg[x] = '0';
    }
    //printf("msg_len: %d\n", msg_len);
    for (int x = 0; x < msg_len+1; x++)
    {
        char* this_msg = xor_encrypt(msg[x]);
        //printf("msg[x]: %c %s %c\n", msg[x], xor_encrypt(msg[x]), xor_decrypt(xor_encrypt(msg[x])));
        for (int k = 0; k < 7; k++)
        {
            full_msg[x*7+k] = this_msg[k];
        }
        free(this_msg);
    }
    code[256] = '\0';
    int x = 0;
    for (int i = 0; i < 256; i++)
    {
        if ((i / 16 == 0 || i / 16 == 4 || (i / 16 == 11 && (int)(i%16) < 5) || i / 16 == 15 && (int)(i%16) < 5) && ((int)(i%15) < 5 || (int)(i%16) > 10)) // Outer box rows
        {
            code[i] = '1';
        }
        else if ((int)(i / 16) == 4 && i%16 > -1 && i%16<5) // Rows
        {
            code[i] = '1';
        }
        else if ((int)(i / 16) == 11 && (i%16)<5)
        {
            code[i] = '1';
        }
        else if ((i % 16 == 0 || i % 16 == 4 || (i % 16 == 11 && (int)(i/16) < 5) || i % 16 == 15 && (int)(i/16) < 5) && ((int)(i/15) < 5 || (int)(i/16) > 10)) // Outer box columns
        {
            code[i] = '1';
        }
        else if ((((i % 16) == 2) && ((int)(i/16) == 2||(int)(i/16) == 13))|| (((i % 16) == 13) && (int)(i/16)==2)) // Inner squares
        {
            code[i] = '1';
        }
        else if (i == 255) // Bottom right square
        {
            code[i] = '1';
        }
        else if ((i%16) < 5 && (int)(i/16)<5)
        {

        }
        else if ((i%16) > 10 && (int)(i/16)<5)
        {

        }
        else if ((i%16) < 5 && (int)(i/16)>10)
        {
            
        }
        else
        {
            code[i] = full_msg[x];
            x++;
        }
    }
    // for (int j = 0; j<16; j++)
    // {
    //     for (int x = 0; x<16;x++)
    //     {
    //         printf("%c", code[16*j+x]);
    //     }
    //     printf("\n");
    // }
    // printf("\n\n");
    printf("done1\n");
    printf("code: %s\n", code);
    return code;
}

char *read_code(char *code){
    //printf("hi\n");
    char* msg = malloc(26);
    char full_msg[8] = "";
    int x = 0;
    int r = 0;
    for (int i = 0; i < 256; i++)
    {
        if ((i / 16 == 0 || i / 16 == 4 || (i / 16 == 11 && (int)(i%16) < 5) || i / 16 == 15 && (int)(i%16) < 5) && ((int)(i%15) < 5 || (int)(i%16) > 10)) // Outer box rows
        {
        }
        else if ((int)(i / 16) == 4 && i%16 > -1 && i%16<5) // Rows
        {
        }
        else if ((int)(i / 16) == 11 && (i%16)<5)
        {
        }
        else if ((i % 16 == 0 || i % 16 == 4 || (i % 16 == 11 && (int)(i/16) < 5) || i % 16 == 15 && (int)(i/16) < 5) && ((int)(i/15) < 5 || (int)(i/16) > 10)) // Outer box columns
        {
        }
        else if ((((i % 16) == 2) && ((int)(i/16) == 2||(int)(i/16) == 13))|| (((i % 16) == 13) && (int)(i/16)==2)) // Inner squares
        {
        }
        else if (i == 255) // Bottom right square
        {
        }
        else if ((i%16) < 5 && (int)(i/16)<5)
        {
        }
        else if ((i%16) > 10 && (int)(i/16)<5)
        {
        }
        else if ((i%16) < 5 && (int)(i/16)>10)
        {
        }
        else
        {
            //printf("code[i]: %c\n", code[i]);
            full_msg[x] = code[i];
            if (x == 6)
            {
                //printf("full_msg: %s\n", full_msg);
                //printf("xor_decrypt: %c\n", xor_decrypt(full_msg));
                msg[r] = xor_decrypt(full_msg);
                x = -1;
                r++;
            }
            x++;
        }
    }
    //printf("hello");
    //printf("msg: %s\n", msg);
    return msg;
}

char *compress(char *code){
    char* hex_code = malloc(65);
    hex_code[64] = '\0';
    int cur_val = 0;
    char cur_char = '0';
    for (int i = 0; i < 256; i+=4)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("iteration: %d, num: %d, code: %c, vals: %d\n", i+j, (int)code[i+4-j], code[i+3-j], (((int)(code[i+3-j]))-48)*((int)(pow(2, j))));
            cur_val += (((int)(code[i+3-j]))-48)*((int)(pow(2, j)));
        }
        cur_char = (char)(cur_val+48);
        cur_val = 0;
        if (cur_char > '9')
        {
            cur_char += 7;
        }
        printf("char: %c\n", (char)(cur_char));
        hex_code[(int)(i/4)] = cur_char;
    }
    return hex_code;
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