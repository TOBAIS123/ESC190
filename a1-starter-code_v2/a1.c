#include "a1.h"

Menu* load_menu(char* fname){
	Menu* menu= (Menu *)malloc(sizeof(Menu));

	FILE* f = fopen(fname, "r");
	char* line= NULL;
	size_t len = 1000;

	int num_lines=0;

	while(getline(&line, &len, f) != -1){
		for (int i = 0; i<strlen(line); i++){
			if (line[i] != ' ' && line[i] != '\n' && line[i]!= '\0'&& line[i]!= '\r')
			{
				num_lines++;
				break;
			}
		}
	}
		
	menu->num_items=num_lines;
	menu->item_codes= (char**)malloc(sizeof(char*)*num_lines);
	menu->item_names= (char**)malloc(sizeof(char*)*num_lines);
	menu->item_cost_per_unit=(double*)malloc(sizeof(double*)*num_lines);

	fseek(f, 0, SEEK_SET);

	for (int j=0; j<num_lines;j++){
		getline(&line, &len, f);

		int nwp;
		
		for (int i = 0; i<strlen(line); i++){
			if (line[i] != '\0' && line[i] != '\n' && line[i]!= '\r'&& line[i]!= ' ') {
				nwp = i;
				break;
			}
		}
		
		char * l = (char*)malloc(sizeof(char)*(strlen(line)-nwp+1));
		for (int k = 0; k<strlen(line); k++){
			l[k] = line[k+nwp];
		}
		
		l[strlen(line)-nwp] = '\0';
		char *split = strtok(l, MENU_DELIM);

		//insert whitespace stuff
		menu->item_codes[j]=(char*)malloc(sizeof(char)*ITEM_CODE_LENGTH);
		strcpy(menu->item_codes[j], split);

		split=strtok(NULL, MENU_DELIM);
		menu->item_names[j]=(char*)malloc(sizeof(char)*MAX_ITEM_NAME_LENGTH+1);
		strcpy(menu->item_names[j], split);

		split=strtok(NULL, MENU_DELIM);
		char* cost=split+1;
		menu->item_cost_per_unit[j] = strtod(cost,NULL);
		free(l);
	}
	free(line);
	fclose(f);
	return menu;
}
/*
Inputs <name> is a string literal.
Output Return a pointer to a Restaurant with:
- name field set equal to the input parameter <name>
- menu initialized to the contents of MENU FNAME (see load menu(...))
- num completed orders set to 0
- num pending orders set to 0
- pending orders intialized to an empty Queue. An empty Queue is defined as a Queue
with its head and tail set to NULL
*/
Restaurant* initialize_restaurant(char* name){
	Restaurant* r = (Restaurant*)malloc(sizeof(Restaurant));
	r->name = (char*)malloc(sizeof(char)*strlen(name)+1);
	strcpy(r->name, name);

	r->menu = load_menu(MENU_FNAME);
	r->num_completed_orders=0;
	r->num_pending_orders=0;

	Queue *new_node = (Queue*)malloc(sizeof(Queue));
	new_node->head = NULL;
    new_node->tail = NULL;
	r->pending_orders= new_node;

	return r;
}

Order* build_order(char* items, char* quantities){

	int item_len =strlen(items)/(ITEM_CODE_LENGTH-1);

	Order* order= (Order*)malloc(sizeof(Order));
	order->item_quantities=(int*)malloc(sizeof(int)*item_len);
	char* temp_quant = (char*)malloc(sizeof(char)*(strlen(quantities)+1));
	
	strcpy(temp_quant, quantities);
	char* split = strtok(temp_quant,MENU_DELIM);
	
	order->item_quantities[0]=(int) strtod(split,NULL);

	for (int i=1; i<item_len; i++){
		split= strtok(NULL, MENU_DELIM);
		order->item_quantities[i]= (int) strtod(split,NULL);
	}

	order->item_codes=(char**)malloc(sizeof(char*)*(item_len));
	order->num_items= item_len;
	
	for (int j =0; j<item_len; j++){
		order->item_codes[j]= (char*)malloc(sizeof(char)*ITEM_CODE_LENGTH);
		strncpy(order->item_codes[j], items+(ITEM_CODE_LENGTH-1)*j,(ITEM_CODE_LENGTH-1));
		order->item_codes[j][ITEM_CODE_LENGTH-1] = '\0'; 
	}

	free(temp_quant);
	return order;
}


/*
	Managing our order queue
*/

void enqueue_order(Order* order, Restaurant* restaurant){
	(restaurant->num_pending_orders)++;
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	//Order* ord = (Order*)malloc(sizeof(Order));
	node->order = order;

	if (restaurant->pending_orders->head==NULL){
		restaurant->pending_orders->head=node;
		restaurant->pending_orders->tail=node;
		node->next=NULL;
	}else {
		//node->next=restaurant->pending_orders->head;//makes the new node point to the head node
		restaurant->pending_orders->tail->next=node;//makes the head point to the new node
		restaurant->pending_orders->tail=node;
		node->next=NULL;



		//node->next=restaurant->pending_orders->head->next;
		//restaurant->pending_orders->head->next=node;
		//restaurant->pending_orders->head=node;
	}

}


Order* dequeue_order(Restaurant* restaurant){
	(restaurant->num_pending_orders)--;
	(restaurant->num_completed_orders)++;
	//(restaurant->num_pending_orders)--;
	//Order* returnval = malloc(sizeof(Order*)); // allocates storage for the return value
	//returnval = restaurant->pending_orders->tail->order; // sets the value that will be returned to the first order which was entered to the queue (FIFO order)
	//if (restaurant->num_pending_orders == 1)
	//{
		//free(&(restaurant->pending_orders->head->order));
		//free(&(restaurant->pending_orders->tail->next)); // frees the value of next not sure if this is needed - todo check
		//free((restaurant->pending_orders->tail)); // frees the value of tail node (the node)
		//restaurant->pending_orders->head=NULL;
		//restaurant->pending_orders->tail=NULL;
	//}

	//QueueNode* cur = restaurant->pending_orders->head->next;
	//for(int i = 1; i<restaurant->num_pending_orders-2; i++) // loop iterates to the third last element of the linkedlist
	//{
		//cur = cur->next;
	//}
	// loop iterates to the third last element of the linkedlist, gets the value of the node's 'next' pointer because that will soon be the pointer to the tail of the linkedlist, then it frees and sets the value of the next node's 'next' to null and makes tail point to the second last node
	
	struct Queue *q = restaurant->pending_orders;
	struct Order *o = q->head->order;
	struct QueueNode *t = q->head;
	
	q->head = q->head->next;
	if(q->head==NULL){
		q->tail = NULL;
	}
	free(t);
	
	return o;

}


/*
	Getting information about our orders and order status
*/

double get_item_cost(char* item_code, Menu* menu){
	for(int i=0; i<menu->num_items; i++){
		if(strcmp(menu->item_codes[i], item_code)==0){
			return menu->item_cost_per_unit[i]; 
		}
	}
	//return 0;
}

double get_order_subtotal(Order* order, Menu* menu){
	double sum=0;
	for (int i=0; i<order->num_items;i++){
		for(int j=0; j<menu->num_items;j++){
			if (strcmp(menu->item_codes[j], order->item_codes[i]) ==0){
				sum += (menu->item_cost_per_unit[j])*order->item_quantities[i];
			}
		}
	}
	return sum;
}

double get_order_total(Order* order, Menu* menu){
	double total= get_order_subtotal(order, menu);
	return total*(1.0+(TAX_RATE/100.0));
}

int get_num_completed_orders(Restaurant* restaurant){
	return restaurant->num_completed_orders;
}
int get_num_pending_orders(Restaurant* restaurant){
	return restaurant->num_pending_orders;
}

/*
	Closing down and deallocating memory
*/
void clear_order(Order** order){
	for(int i=0; i<(*order)->num_items;i++){
		free((*order)->item_codes[i]);
	}
	free((*order)->item_codes);
	free((*order)->item_quantities);
	free(*order);
	*order=NULL;
}

void clear_menu(Menu** menu){
	for(int i=0; i<(*menu)->num_items;i++){
		free((*menu)->item_codes[i]);
		free((*menu)->item_names[i]);
	}
	free((*menu)->item_codes);
	free((*menu)->item_cost_per_unit);
	free((*menu)->item_names);
	free(*menu);
	*menu = NULL;
}


void close_restaurant(Restaurant** restaurant){
	clear_menu(&((*restaurant)->menu));
	while((*restaurant)->num_pending_orders > 0){
		Order* o = dequeue_order((*restaurant));
		clear_order(&o);
	}
	free((*restaurant)->name);
	free((*restaurant)->pending_orders);
	free(*restaurant);
	*restaurant = NULL;
}

void print_menu(Menu* menu){
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++){
		fprintf(stdout, "(%s) %s: %.2f\n", 
			menu->item_codes[i], 
			menu->item_names[i], 
			menu->item_cost_per_unit[i]	
		);
	}
}


void print_order(Order* order){
	for (int i = 0; i < order->num_items; i++){
		fprintf(
			stdout, 
			"%d x (%s)\n", 
			order->item_quantities[i], 
			order->item_codes[i]
		);
	}
}


void print_receipt(Order* order, Menu* menu){
	for (int i = 0; i < order->num_items; i++){
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout, 
			"%d x (%s)\n @$%.2f ea \t %.2f\n", 
			order->item_quantities[i],
			order->item_codes[i], 
			item_cost,
			item_cost * order->item_quantities[i]
		);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);
	
	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}

/*
int main (){
	Menu* m = load_menu("menu.txt");
	print_menu(m);
	//clear_menu(&m);
	//Order* order_1 = build_order("A1B1", "12,13");
	//print_order(order_1);
	
	/*Restaurant* restaurant = initialize_restaurant("menu.txt");
	Order* order_1 = build_order("A1B1", "12,13");
	Order* order_2 = build_order("A1B1C1", "12,10,9");
	
	
	enqueue_order(order_1 , restaurant );
	enqueue_order(order_2 , restaurant );
	clear_order(&order_1);
	clear_order(&order_2);
	close_restaurant (& restaurant );
}*/
