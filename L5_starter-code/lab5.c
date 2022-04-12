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

char **plan_route(Graph *gr, char *start, char *dest)
{
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
    Vnode *s = findNode(gr, start);
    Vnode *d = findNode(gr, dest);
    if (!s)
    {
        add(gr, start);
    }
    if (!d)
    {
        add(gr, dest);
    }
    if (!weight)
    {
        disruptEdge(s, dest);
    }
    else
    {
        Enode *e;
        Enode *prev = NULL;
        for (e = s->edges; e; e = e->next)
        {
            if (!strcmp(e->vertex, dest))
            {
                e->weight = weight;
                return;
            }
            prev = e;
        }
        Enode *edge = (Enode *)malloc(sizeof(Enode));
        strcpy(edge->vertex, dest);
        edge->weight = weight;
        edge->next = NULL;
        if (!prev)
        {
            s->edges = edge;
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
            while (cur->edges != NULL)
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
