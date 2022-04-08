#include "lab5.h"

Vnode *findNode(Graph *gr, char *station)
{
    for (int i = 0; i < gr->count; i++)
    {
        if (!strcmp(gr->adj_list[i]->station, station))
        {
            return gr->adj_list[i];
        }
    }
    return NULL; // not found
}

void disruptNode(Graph *gr, char *station)
{
    int idx;
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            idx = i;
            break;
        }
    }
    free(gr->adj_list[idx]);

    // move entire adj list down
    for (int i = idx; i < gr->count - 1; i++)
    {
        gr->adj_list[i] = gr->adj_list[i + 1];
    }

    // resize list
    if (gr->count > 1)
    {
        gr->adj_list = (Vnode **)realloc(gr->adj_list, sizeof(Vnode *) * (--(gr->count)));
    }
    else
    {
        free(gr->adj_list);
        gr->adj_list = NULL;
    }
}

void disruptEdge(Vnode *node, char *station)
{
    Enode *prev = NULL;
    while (node->edges != NULL)
    { // loop through edges of cur (until becomes NULL)
        if (strcmp(node->edges->vertex, station) == 0)
        {
            Enode *temp = node->edges;
            if (!prev)
            {
                node->edges = NULL;
            }
            else
            {
                prev->next = node->edges->next;
            }
            free(temp);
            return;
        }
        prev = node->edges;
        node->edges = node->edges->next;
    }
}

/*
char **plan_route(Graph *gr, char *start, char *dest)
{

    // Add code here
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
    return;
}
*/
void add(Graph *gr, char *station)
{
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            return;
        }
    }
    if (gr->count == 0)
    { // if no nodes
        gr->adj_list = (Vnode **)malloc(sizeof(Vnode *));
    }
    else
    {
        gr->adj_list = realloc(gr->adj_list, sizeof(Vnode *) * (gr->count + 1)); // new row
    }
    Vnode *node = malloc(sizeof(Vnode));
    node->cost = 0;
    node->edges = NULL;
    node->prev = NULL;
    node->visited = 0;
    strcpy(node->station, station);
    gr->adj_list[gr->count] = node;
    gr->count += 1;
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    Vnode *startn = findNode(gr, start);
    Vnode *destn = findNode(gr, dest);
    if (!startn)
    {
        add(gr, start);
    }
    if (!destn)
    {
        add(gr, dest);
    }

    if (weight == 0)
    {
        disruptEdge(startn, dest);
    }
    else
    {
        Enode *prev = NULL;
        while (startn->edges != NULL)
        {
            if (strcmp(startn->edges->vertex, dest)==0)
            {
                startn->edges->weight = weight;
                return;
            }
            prev = startn->edges;
            startn->edges= startn->edges->next;
        }
        // no edge
        Enode *edge = (Enode *)malloc(sizeof(Enode));
        strcpy(edge->vertex, dest);
        edge->weight = weight;
        edge->next = NULL;
        if (!prev)
        {
            startn->edges = edge;
        }
        else
        {
            prev->next = edge;
        }
    }
}

void disrupt(Graph *gr, char *station)
{
    int idx;
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            idx = i;
        }
    }

    Vnode *cur = gr->adj_list[idx];

    if (!(cur))
    {
        return;
    }
    cur = NULL;
    for (int i = 0; i < gr->count; i++)
    {
        cur = gr->adj_list[i];
        if (strcmp(cur->station, station) == 0 && cur->edges != NULL)
        {
            while (cur->edges!= NULL)
            { 
                Enode *temp_edge = cur->edges;
                cur->edges = cur->edges->next;
                free(temp_edge);
                temp_edge = NULL;
            }
            cur->edges = NULL;
        }
        else
        {
            disruptEdge(cur, station);
        }
    }
    disruptNode(gr, station);
}
