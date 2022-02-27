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
    else {
        struct party_node *remove = *head;
        *head = remove->next;
        free(remove->item);
        free(remove->ta);
        free(remove);

    }
}

//Sort party item requests - in place?
void make_sorted(struct party_node **head){
    int swap = 1;
    struct party_node *current = *head;
    struct party_node *last = NULL;
    if (*head == NULL){
        return;
    }
    else{
        while (swap){
            current = *head;
            swap = 0;
            while(current->next != last)
            {
                if(current->next->price > current->price)
                {
                    //temp node for swap
                    char *tempTa = current->next->ta;
                    char *tempItem = current->next->item;
                    double tempPrice = current->next->price;
                    swap = 1; 
                    //swap next with current
                    current->next->ta = current->ta;
                    current->next->item = current->item;
                    current->next->price = current->price;
                    //swap temp with current
                    current->price = tempPrice;
                    current->ta = tempTa;
                    current->item = tempItem;
                }
                current = current->next;
            }
            last = current;
        }   
    }
}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    struct party_node* current = *head;
    struct party_node* prev = NULL;

    while (current != NULL){
        if (current->price > budget){
            if (current!= *head){
                prev->next = current->next;
                current->next = (*head);
                *head = current;
                remove_request(head);
                current = prev->next;
            }
            else {
                current = current->next;
                remove_request(head);
            }
        }
        else{
            budget -= current->price;
            prev = current;
            current=current->next;
        }
    }
    return budget;
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