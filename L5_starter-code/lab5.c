#include "lab5.h"


Vnode* findNode(Graph* gr, char* station){
    for (int i=0; i<gr->count;i++){
        if (!strcmp(gr->adj_list[i]->station, station)) { 
            return gr->adj_list[i]->station;
        }
    }
        return NULL; // not found
}



char **plan_route(Graph *gr, char *start, char *dest)
{

    // Add code here
    /*
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;
    // pred[] stores the predecessor of each node
    // count gives the number of nodes seen so far
    // create the cost matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];
    // initialize pred[],distance[] and visited[]
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1)
    {
        mindistance = INFINITY;
        // nextnode gives the node at minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        // check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }*/
}

void add(Graph *gr, char *station)
{
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            return;
        }
    }
    if (gr->count == 0) { // if no nodes
        gr->adj_list = (Vnode**) malloc(sizeof(Vnode*));
    }
    else{
        gr->adj_list = realloc(gr->adj_list, sizeof(Vnode *) * (gr->count + 1)); // new row
    }
    Vnode *node = malloc(sizeof(Vnode));
    node->cost=0;
    node->edges=NULL;
    node->prev=NULL;
    node->visited=0;
    strcpy(node->station, station);
    gr->adj_list[gr->count] = node;
    gr->count+=1;
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    Vnode* startn=NULL;
    Vnode* destn=NULL;
    if(!(startn = findNode(gr, start))){
      add(gr, start);
    }
    if(!(destn = findNode(gr, start))){
      add(gr, dest);
    }

    if (weight==0){

    }
    else{

    }
}

void disrupt(Graph *gr, char *station)
{
    if(!(findNode(gr, station))){
        return;
    }
    Enode* temp_edge=NULL;
    for (int i = 0; i < gr->count; i++) {
        if (strcmp(gr->adj_list[i]->station, station)==0) {
        while (gr->adj_list[i]->edges->next != NULL) { 
            temp_edge = gr->adj_list[i]->edges;
            gr->adj_list[i]->edges = gr->adj_list[i]->edges->next;
            free(temp_edge);
            temp = NULL;
        }
        gr->adj_list[i]->edges = NULL;
        } else {
              for (gr->adj_list[i]->edges->next != null) { 
                Enode* prev = NULL;
                if (strcmp(gr->adj_list[i]->edges->vertex, station)==0) { 
                Enode* temp = prev->next;
                prev->next = prev->next->next;
                free(temp);
                break; 
                }
                gr->adj_list[i]->edges=gr->adj_list[i]->edges->next
            }
        }
    }
}