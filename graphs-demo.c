#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 100

/**
Struct definitions for Stack implementation as Linked List
*/

typedef struct StackNode {
	int cargo; // node's index
	struct StackNode* next;
} StackNode;

typedef struct Stack {
	StackNode* top;
	int num_el;
} Stack;

/**
Struct definitions for Graph implementation as Adj Mtx
*/
typedef struct GraphNode {
	char cargo[MAX_NAME_LEN]; 
	int idx;
	struct GraphNode* prev;
	int explored;
} GraphNode;

typedef struct Graph {
	GraphNode** nodes; // dynamically allocated array of size num_nodes * sizeof(GraphNode*)
	int** adj_mtx; // dynamically allocated array of size num_nodes * sizeof(int*)
	int num_nodes;
} Graph;

/**
Stack operations
*/
Stack* initialize_stack(){
	Stack* new_stack = (Stack*)malloc(sizeof(Stack));
	new_stack->top = NULL;
	new_stack->num_el = 0;
	return new_stack;
}

void push(Stack* s, int val){
	StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
	new_node->cargo = val;
	new_node->next = s->top;
	s->top = new_node;
	s->num_el++;
}

int pop(Stack* s){
	/** Assume non-empty stack*/
	StackNode* node_to_free = s->top;
	int result = s->top->cargo;
	
	s->top = s->top->next;
	s->num_el--;
	
	free(node_to_free);
	return result;
}

/**
Graph operations
*/

void print_graph(Graph* graph){
	fprintf(stdout, "Printing graph elements...\n");
	for (int i=0; i<graph->num_nodes; i++){
		fprintf(stdout, "Index %d is: %s \n", i, graph->nodes[i]->cargo);
	}
	
	fprintf(stdout, "Printing adjacency matrix...\n");
	for (int i=0; i<graph->num_nodes; i++){
		for (int j=0; j<graph->num_nodes; j++) {
			fprintf(stdout, "%d ", graph->adj_mtx[i][j]);
		} fprintf(stdout, "\n");
	}fprintf(stdout, "\n\n");
}

void add_node(Graph* graph, GraphNode* new_node){
	/** require that the node is not present in the graph
	and that the graph's adjacency matrix for other valus
	*/
	// update node array
	graph->nodes = realloc(graph->nodes, sizeof(GraphNode *)*(graph->num_nodes +1));
	graph->nodes[graph->num_nodes] = new_node;
	new_node->idx = graph->num_nodes;
	//update adj matrix
	graph->adj_mtx = realloc(graph->adj_mtx, sizeof(int *)*(graph->num_nodes+1)); //new row
	graph->adj_mtx[graph->num_nodes] = calloc((graph->num_nodes+1), sizeof(int)); //new row of zeros

	for(int i=0; i<graph->num_nodes; i++){
		graph->adj_mtx[i] = realloc(
			graph->adj_mtx[i], (graph->num_nodes+1)*sizeof(int));
		graph->adj_mtx[i][graph->num_nodes]=0;
	} // set last column to 0
	graph->num_nodes++;
}

void add_edge(Graph* graph, GraphNode* node1, GraphNode* node2){
	// require that node 1 and node 2 are already in the graph
	graph->adj_mtx[node1->idx][node2->idx]=1;
	graph->adj_mtx[node2->idx][node1->idx]=1;
	// add only one edge for directed and order will matter
	printf("Added edges between %s and %s.\n", node1->cargo, node2->cargo);
}

GraphNode* initialize_graph_node(char name[]){
	GraphNode *gn = malloc(sizeof(GraphNode));
	gn->prev = NULL;
	gn->idx = -1;
	gn->explored = 0; //unvisited
	strcpy(gn->cargo, name);
	return gn;
}

Graph* initialize_graph(){
	Graph *g = malloc(sizeof(Graph));
	g->nodes =NULL;
	g->adj_mtx = NULL;
	g->num_nodes = 0;
	return g;
}




void delete_graph(Graph** graph){
	for (int i=0; i<(*graph)->num_nodes; i++){
		free((*graph)->nodes[i]); // remove the individual nodes
		free((*graph)->adj_mtx[i]); // remove the rows
	}	
	
	free((*graph)->nodes);
	free((*graph)->adj_mtx);
	free(*graph);
	*graph = NULL;
}
/**
DFS
*/


void reset_graph_post_dfs(Graph* graph){
	for(int i=0; i<graph->num_nodes;i++){
		graph->nodes[i]->prev = NULL;
		graph->nodes[i]->explored = 0;
	}
}


int dfs(Graph* graph, int start_idx, int end_idx){	
	printf("Starting DFS to find path between %s and %s...\n",
		graph->nodes[start_idx]->cargo, graph->nodes[end_idx]->cargo);

	int curr_idx = start_idx;

	Stack *s = initialize_stack();
	push(s, start_idx);

	//while stack not empty and end_idx not found
	while (s->num_el != 0 && curr_idx != end_idx){
		//pop from stack
		curr_idx = pop(s);
		graph->nodes[curr_idx]->explored = 1;
		printf("Visiting node %s...\n", graph->nodes[curr_idx]->cargo);

		for(int i=0; i<graph->num_nodes;i++){
			//if edge exists and is unvisited, add node to stack
			if(graph->adj_mtx[i][curr_idx]==1 && graph->nodes[i]->explored==0){
				push(s, i);
				printf("\tFound unexplored neighbour: %s\n", graph->nodes[i]->cargo);
				//set previous to back-track later
				graph->nodes[i]->prev = graph->nodes[curr_idx];
			}
		}

	}
	//empty the stack if anything is left
	while(s->num_el !=0){
		pop(s);
	}
	
	//if found
	if(curr_idx == end_idx){
		printf("Found path between %s and %s!\n", 
			graph->nodes[start_idx]->cargo, 
			graph->nodes[end_idx]->cargo);
		printf("Now printing DFS path found...\n");
		GraphNode *node = graph->nodes[end_idx];
		while(node->idx != start_idx){
			printf("\t %s \n", node->cargo);
			node = node->prev;
		}
		printf("\t %s \n)", node->cargo);
	}
	//else not found
	else{
		printf("Path between %s and %s not found :( \n",
			graph->nodes[start_idx]->cargo, 
			graph->nodes[end_idx]->cargo);
	}
	reset_graph_post_dfs(graph);
}


int main(){
	Graph* graph = initialize_graph();
	
	GraphNode* node0 = initialize_graph_node("Will C");
	GraphNode* node1 = initialize_graph_node("Michael G");
	GraphNode* node2 = initialize_graph_node("Justina L");
	GraphNode* node3 = initialize_graph_node("Stephen J");
	GraphNode* node4 = initialize_graph_node("Saima A");
	GraphNode* node5 = initialize_graph_node("Cindy B");

	add_node(graph, node0);
	add_node(graph, node1);
	add_node(graph, node2);
	add_node(graph, node3);
	add_node(graph, node4);
	add_node(graph, node5);
	
	print_graph(graph);
	
	add_edge(graph, node0, node1); //Will + Michael
	print_graph(graph);
	add_edge(graph, node0, node4); //Will + Saima
	print_graph(graph);
	add_edge(graph, node0, node5); //Will + Cindy
	print_graph(graph);
	add_edge(graph, node4, node5); //Saima + Cindy
	print_graph(graph);
	add_edge(graph, node4, node2); //Saima + Justina
	print_graph(graph);
	add_edge(graph, node4, node3); //Saima + Stephen
	print_graph(graph);
	add_edge(graph, node2, node3); //Justina + Stephen
	print_graph(graph);
	
	dfs(graph, 4, 1); //Saima and Michael
	dfs(graph, 2, 1); //Justina and Michael
	delete_graph(&graph);

	return 0;
}