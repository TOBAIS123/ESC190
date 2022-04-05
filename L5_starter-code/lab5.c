#include "lab5.h"

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
    }

    // print the path and distance of each node
    for (i = 0; i < n; i++)
        if (i != startnode)
        {
            printf("\nDistance of node%d=%d", i, distance[i]);
            printf("\nPath=%d", i);
            j = i;
            do
            {
                j = pred[j];
                printf("<-%d", j);
            } while (j != startnode);
        }
        */
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
    gr->adj_list = realloc(gr->adj_list, sizeof(int *) * (gr->count + 1)); // new row
    gr->adj_list[gr->count] = node;
    gr->count+=1;
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    // Add code here
}

void disrupt(Graph *gr, char *station)
{
    // Add code here
}