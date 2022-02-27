#include "a1.h"

Menu* load_menu(char* fname){
	Menu* menu= (Menu *)malloc(sizeof(Menu));

	FILE* fm = fopen(fname, "r");
	char* line= NULL;
	size_t len = 1000;

	int num_lines=0;

	while(getline(&line, &len, fm) != -1){
		num_lines++;
	}
	fclose(fm);

	FILE* f = fopen(fname, "r");
	line= NULL;
	
	menu->num_items=num_lines;
	menu->item_codes= (char**)malloc(sizeof(char*)*num_lines);
	menu->item_names= (char**)malloc(sizeof(char*)*num_lines);
	menu->item_cost_per_unit=(double*)malloc(sizeof(double*)*num_lines);

	for (int j=0; j<num_lines;j++){
		getline(&line, &len, f);
		char* split = strtok(line, MENU_DELIM);
		menu->item_codes[j]=(char*)malloc(sizeof(char)*ITEM_CODE_LENGTH);
		strcpy(menu->item_codes[j], split);

		split=strtok(NULL, MENU_DELIM);
		menu->item_names[j]=(char*)malloc(sizeof(char)*MAX_ITEM_NAME_LENGTH+1);
		strcpy(menu->item_names[j], split);

		split=strtok(NULL, MENU_DELIM);
		char* cost=split+1;
		menu->item_cost_per_unit[j] = strtod(cost,NULL);
	}
	free(line);
	fclose(f);
	return menu;
}

Restaurant* initialize_restaurant(char* name){
	Restaurant* r = (Restaurant*)malloc(sizeof(Restaurant));
	r->name = (char*)malloc(sizeof(char)*strlen(name)+1);
	strcpy(r->name, name);

	r->menu = load_menu(MENU_FNAME);
	r->num_completed_orders=0;
	r->num_pending_orders=0;

	Queue *new_node = (Queue*)malloc(sizeof(Queue));
    r->pending_orders= new_node;
	new_node->head = NULL;
    new_node->tail = NULL;

	return r;
}

Order* build_order(char* items, char* quantities){

	Order* order= (Order*)malloc(sizeof(Order));
	int item_len =strlen(items)/(ITEM_CODE_LENGTH-1);

	order->item_quantities=(int*)malloc(sizeof(int)*item_len);
	char* temp_quant = (char*)malloc(sizeof(char)*strlen(quantities));
	
	strcpy(temp_quant, quantities);
	char* split = strtok(temp_quant,MENU_DELIM);
	
	order->item_quantities[0]=(int) strtod(split,NULL);

	for (int i=1; i<item_len; i++){
		split= strtok(NULL, MENU_DELIM);
		order->item_quantities[i]= (int) strtod(split,NULL);
	}

	order->item_codes=(char**)malloc(sizeof(char*)*item_len);
	order->num_items= item_len;
	
	for (int j =0; j<item_len; j++){
		order->item_codes[j]= (char*)malloc(sizeof(char)*ITEM_CODE_LENGTH);
		strncpy(order->item_codes[j], items+(ITEM_CODE_LENGTH-1)*j,(ITEM_CODE_LENGTH-1));
	}

	free(temp_quant);
	return order;
}

/*
	Managing our order queue
*/
void enqueue_order(Order* order, Restaurant* restaurant){
	Restaurant* restaurent =

}
Order* dequeue_order(Restaurant* restaurant){}

/*
	Getting information about our orders and order status
*/
double get_item_cost(char* item_code, Menu* menu){
	for(int i=0; i<menu->num_items; i++){
		if(strcmp(menu->item_codes[i], item_code)==0){
			return menu->item_cost_per_unit[i]; 
		}
	}

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

int get_num_completed_orders(Restaurant* restaurant){}
int get_num_pending_orders(Restaurant* restaurant){}

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

int main (){
	print_menu(load_menu("menu.txt"));
	Order* order = build_order("A1B1", "12,13");
	print_order(order);
}