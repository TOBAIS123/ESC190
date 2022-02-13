#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct qu_node{
    char item;
    struct qu_node *next;
};

//Double pointer for functions that modify the head pointer
void enqueue(struct qu_node **qhead, struct qu_node **qtail, char value);
char dequeue(struct qu_node **qhead, struct qu_node **qtail);
char peek(struct qu_node *qhead);
void print_ql(struct qu_node *qhead);

int main(){

    struct qu_node *qhead= NULL;
    struct qu_node *qtail= NULL;

    printf("Enqueue 10 items to the queue: \n");
    char *letters = "!sEDI 3< I";  //10 items, not pushing '\0'
    for(int i=0; i<(int)strlen(letters);i++){
        enqueue(&qhead, &qtail, letters[i]);    
    }
    print_ql(qhead);
    printf("Let's peek: %c\n", peek(qhead));

    printf("Popping 3 items from the queue: \n");
    for(int j=0; j<3;j++){
        printf("%c", dequeue(&qhead, &qtail));    
    }
    printf("\n");
    print_ql(qhead);
    printf("Let's peek: %c\n", peek(qhead));

    printf("Pushing 4 items to the queue: \n");
    enqueue(&qhead, &qtail, '/');    //1 item
    letters = "< I";        //3 items 
    for(int i=0; i<(int)strlen(letters);i++){
        enqueue(&qhead, &qtail, letters[i]);    
    }
    print_ql(qhead);
    printf("Let's peek: %c\n", peek(qhead));

    printf("Popping all items from the queue..\n");
    while(qhead!=NULL){
        dequeue(&qhead, &qtail);
    }
    printf("Extra pop..\n");
    dequeue(&qhead, &qtail);
    printf("Let's peek: %c\n", peek(qhead));

    printf("Done - allocated memory was freed.\n");
    return 0;
}

void enqueue(struct qu_node **qhead, struct qu_node **qtail, char value){
    //Allocate memory for new node, initialize fields, connect to queue
    struct qu_node *new_node = malloc(sizeof(struct qu_node));
    new_node->item = value;
    new_node->next = NULL;
    //Enqueuing first node to empty list
    if(*qhead==NULL){
        *qhead=new_node;
        *qtail=new_node;
    }
    else{
        (*qtail)->next = new_node;
        *qtail = new_node;
    }
    return;
}

char dequeue(struct qu_node **qhead, struct qu_node **qtail){
    //Check if queue is empty
    if ((*qhead)==NULL){
        printf("no pop!\n");
        return '\0';
    }
    //Store node address and value before free/moving head pointer
    struct qu_node *bye_node = *qhead;
    char dequ_val = bye_node->item;
    *qhead = (*qhead)->next;
    free(bye_node);

    //If the last node was removed
    if((*qhead)==NULL){
        *qtail = NULL;
    }
    return dequ_val;
}

char peek(struct qu_node *qhead){
    //Check if queue is empty
    if (qhead==NULL){
        printf("queue is empty!\n");
        return '\0';
    }
    return qhead->item;
}

void print_ql(struct qu_node *qhead){
    //Print from front (front of linked list)
    printf("Printing the queue: \n");
    while(qhead!=NULL){
        printf("%c", qhead->item);
        qhead = qhead->next;
    }
    printf("\n");
}