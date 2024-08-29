// Breadth First Search Algorithm
#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int n;
    int *visited, *parent;
    int **matrix;
} graph;

graph *createGraph(int n) {
    graph *g = (graph *) malloc(sizeof(graph));
    g -> n = n;
    g -> visited = (int *) malloc(n * sizeof(int));
    g -> parent = (int *) malloc(n * sizeof(int));
    g -> matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        g -> parent[i] = -1;
        g -> visited[i] = 0;
        g -> matrix[i] = (int *) calloc(n, sizeof(int));
    }
    return g;
}

void freeGraph(graph *g) {
    free(g -> visited);
    free(g -> parent);
    for (int i = 0; i < g -> n; i++) {
        free(g -> matrix[i]);
    }
    free(g -> matrix);
    free(g);
}

static int count = 0, orderCount = 0, isCyclic = 0;

void breadthFirstSearch(graph *g, int start, int mode) {
    int *queue = (int *) malloc(g -> n * sizeof(int));
    int front = 0, rear = 0;
    if (mode == 0) {
        isCyclic = count = orderCount = 0;
    }
    g -> visited[start] = 1;
    queue[rear++] = start;
    count++;
    while (front < rear) {
        int current = queue[front++];
        if (mode == 0) {
            printf("-> %c ", current + 65);
        }
        for (int i = 0; i < g -> n; i++) {
            if (g -> matrix[current][i] == 1) {
                if (g -> visited[i] == 0) {
                    g -> visited[i] = 1;
                    g -> parent[i] = current;
                    queue[rear++] = i;
                    count++;
                } else if (g -> parent[current] != i) {
                    isCyclic = 1;
                }
                orderCount++;
            }
        }
    }
    free(queue);
}

void tester() {
    int n, start;
    printf("\nEnter the number of vertices of the graph: ");
    scanf("%d", &n);
    graph *g = createGraph(n);
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(g -> matrix[i][j]));
        }
    }
    printf("\nEnter the vertex to start the breadth first search from: ");
    scanf("%d", &start);
    printf("\nBFS traversal from vertex %c:\n", start + 65);
    breadthFirstSearch(g, start, 0);
    if (count == n) {
        printf("\n\nThe input graph is connected.\n");
    } else {
        printf("\n\nThe input graph is not connected.\n");
    }
    if (isCyclic)
        printf("The input graph is cyclic.\n");
    else
        printf("The input graph is not cyclic.\n");
    freeGraph(g);
}

void plotter(int mode) {
    FILE *f1 = fopen("bfsBest.txt", "a");
    FILE *f2 = fopen("bfsWorst.txt", "a");
    for (int k = 1; k <= 10; k++) {
        graph *g = createGraph(k);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (mode == 0) {
                    if (i != j)
                        g -> matrix[i][j] = 1;
                } else {
                    if (i == (j - 1))
                        g -> matrix[i][j] = 1;
                }
            }
        }
        orderCount = k;
        breadthFirstSearch(g, 0, 1);
        if (mode == 0)
            fprintf(f2, "%d\t%d\n", k, orderCount);
        else
            fprintf(f1, "%d\t%d\n", k, orderCount);
        freeGraph(g);
    }
    fclose(f1);
    fclose(f2);
}

int main() {
    int option;
    printf("\nChoose any one of the following:\n"
    "1. Tester\n"
    "2. Plotter\n"
    "3. Exit\n");
    scanf("%d", &option);
    switch(option) {
        case 1: tester(); break;
        case 2: plotter(0); plotter(1); break;
        case 3: exit(0);
        default: printf("\nInvalid option!\n");
    }
    return 0;
}