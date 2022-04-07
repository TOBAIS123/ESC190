#include "lab5.h"

char **plan_route(Graph *gr, char *start, char *dest)
{
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
    for (int i = 0; i <= gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            return;
        }
    }
    Vnode *node = malloc(sizeof(Vnode));
    node->cost=0;
    node->edges=NULL;
    node->prev=NULL;
    node->visited=0;
    strcpy(node->station, station);
    gr->adj_list = realloc(gr->adj_list, sizeof(Vnode *) * (gr->count + 1)); // new row
    gr->adj_list[gr->count] = node;
    gr->count+=1;
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    // if weight 0
    if (weight == 0){
        /*
        check to see if start is in graph, find idx
            iterate edges of start until destination is reached
            if reached, delete node
            if niether found, return

        */
    }
    //if weight !0
    else{
        /*
        check to see if start is in graph, find idx
            if not, add to graph
        check if dest is in graph, find idx
            if not add to graph
        check to see if edge b/w start and dest exists
            do this by iterating from start nodes edge until destination is found
                add edge if not found
        change edge value b/w start and dest to weight
*/
    }
}

void disrupt(Graph *gr, char *station)
{
    //iterate to find if vertex w/ station exists
    for (int i = 0; i <= gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            return;
        }
    }
    //


}