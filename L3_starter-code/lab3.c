#include "lab3.h"

//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    if (strcmp(item,"IDE") !=0) {    
        struct party_node* Element = (struct party_node *)malloc(sizeof(struct party_node)); 
        Element->item = (char*)malloc(sizeof(char)*strlen(item)+1);
        strcpy(Element->item,item);
        Element->price=price;
        Element->ta=(char*)malloc(sizeof(char)*strlen(ta)+1);
        strcpy(Element->ta,ta);
        Element->next = *head;  
        (*head) = Element; 
        return 0; 
    }
    else{
        return -1;
    }
}


//Remove the last item added
void remove_request(struct party_node **head){
    if (*head == NULL){
        return;
    }
    struct party_node *temp = *head;
    *head = temp->next;
    free(temp->item);
    free(temp->ta);
    free(temp);
}

//Sort party item requests - in place?
void make_sorted(struct party_node **head){
    int flag = 1;
    struct party_node *curr = *head;
    struct party_node *last = NULL;

    if (*head == NULL){
        return;
    }

    while (flag){
        flag = 0;
        curr = *head;

        while(curr->next != last){
            if(curr->next->price > curr->price){
                double temp_price = curr->next->price;
                char *temp_ta = curr->next->ta;
                char *temp_item = curr->next->item;

                curr->next->price = curr->price;
                curr->next->ta = curr->ta;
                curr->next->item = curr->item;

                curr->price = temp_price;
                curr->ta = temp_ta;
                curr->item = temp_item;

                flag = 1;
            }
            curr = curr->next;
        }
        last = curr;
 
    }
}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    //Add code here
}

//Print the current list - hope this is helpful!
void print_list(struct party_node *head){
    int count = 1;
    printf("The current list contains:\n");
    while(head!=NULL){
        printf("Item %d: %s, %.2lf, requested by %s\n",
            count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}