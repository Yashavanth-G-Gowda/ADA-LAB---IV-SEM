#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int heapCount = 0, graphCount = 0, n;

typedef struct pair
{
    int node;
    int val;
} *Pair;

Pair createPair(int n, int val)
{
    Pair p = (Pair)malloc(sizeof(struct pair));
    p->val = val;
    p->node = n;
    return p;
}

typedef struct PriorityQ
{
    Pair *arr;
    int currSize;
} *PriorityQueue;

PriorityQueue init(int edges)
{
    PriorityQueue pq = (PriorityQueue)malloc(sizeof(struct PriorityQ));
    pq->arr = (Pair *)malloc(edges * sizeof(struct pair));
    pq->currSize = 0;

    return pq;
}

void add(PriorityQueue pq, Pair p)
{
    pq->arr[pq->currSize] = p;
    pq->currSize += 1;

    int x = pq->currSize - 1;
    int parIdx = (x - 1) / 2;

    while (pq->arr[x]->val < pq->arr[parIdx]->val)
    {
        Pair temp = pq->arr[x];
        pq->arr[x] = pq->arr[parIdx];
        pq->arr[parIdx] = temp;

        x = parIdx;
        parIdx = (x - 1) / 2;
    }
}

void heapify(PriorityQueue pq, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int minIdx = i;
    heapCount++;

    if (left < pq->currSize && pq->arr[minIdx]->val > pq->arr[left]->val)
    {
        minIdx = left;
    }

    if (right < pq->currSize && pq->arr[minIdx]->val > pq->arr[right]->val)
    {
        minIdx = right;
    }

    if (minIdx != i)
    {
        Pair temp = pq->arr[i];
        pq->arr[i] = pq->arr[minIdx];
        pq->arr[minIdx] = temp;

        heapify(pq, minIdx);
    }
}

Pair delete(PriorityQueue pq)
{
    Pair p = pq->arr[0];

    Pair temp = p;
    pq->arr[0] = pq->arr[pq->currSize - 1];
    pq->arr[pq->currSize - 1] = temp;

    pq->currSize -= 1;

    heapify(pq, 0);
    return p;
}

int prims(int n, int adjMat[n][n])
{
    int vis[n], finalCost = 0;
    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
    }
    int edges = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && adjMat[i][j] != INT_MAX)
                edges++;
        }
    }

    PriorityQueue pq = init(edges);
    add(pq, createPair(0, 0));

    while (pq->currSize != 0)
    {
        Pair curr = delete (pq);
        if (!vis[curr->node])
        {
            vis[curr->node] = 1;
            finalCost+=curr->val;

            for (int i = 0; i < n; i++)
            {
                if (curr->node != i && adjMat[curr->node][i] != INT_MAX)
                {
                    graphCount++;
                    add(pq, createPair(i, adjMat[curr->node][i]));
                }
            }
        }
    }

    return finalCost;
}

void tester()
{
    int source;
    printf("Enter the number of nodes : ");
    scanf("%d", &n);
    printf("Enter adjacency matrix :\n");
    int adjMat[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMat[i][j] == -1)
                adjMat[i][j] = INT_MAX;

    printf("\nMinimum cost of MST : %d\n",prims(n, adjMat));
}

void plotter()
{
    FILE *f = fopen("prims.txt", "w");
    for (int i = 0; i < 5; i++)
    {
        heapCount = 0;
        graphCount = 0;
        tester();
        fprintf(f, "%d\t%d\n", n, graphCount > heapCount ? graphCount : heapCount);
    }

    fclose(f);
}

void main()
{
    int ch;
    printf("\n\nEnter\n1.Tester\n2.Plotter\n");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid Input!");
    }
}

Prims algo