#include<stdio.h>
#include<math.h>
#include<string.h>

double split_bill(double base_amount , double tax_rate , double tip_rate , int num_people) {
    double total_split=(base_amount*(1.0+tax_rate))*(1.0+tip_rate)/num_people;
    return (ceil(total_split*100))/100;


}

double adjust_price(double original_price) {
    return 10*pow(original_price,0.5);
}


int sandy_eats(char menu_item []){
    
    //convert all uppercase chars to lowercase
    for(int i = 0; menu_item[i]; i++){
         if (menu_item[i] >= 'A' && menu_item[i] <= 'Z') {
            menu_item[i] = menu_item[i] + 32;
        }  
    }
    
    int count = 0;  
    //Counts each char  except space  
    for(int i = 0; i < strlen(menu_item); i++) {  
        if(menu_item[i]  >= 'a' && menu_item[i] <= 'z')  
            count++;  
    }

    if (count%2==1){
        return 0;
    }

    char flag_chars[4][5]= {"j","k","l","fish"};

    for (int j=0; j<4; j++){
        if (strstr(menu_item, flag_chars[j]) != NULL){
            return 0;
        }
    }
    return 1;
}


void imagine_fish(char thing[]){
    int str_len= strlen(thing);
    char word[]= "fish";

    for (int i=0; i<5; i++){
        thing[str_len+i]=word[i];
    }
}
