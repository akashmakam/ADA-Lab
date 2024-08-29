// Topological Sorting Algorithm
#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int n;
    int *visited, *parent, *path;
    int **matrix;
} graph;

graph *createGraph(int n) {
    graph *g = (graph *) malloc(sizeof(graph));
    g -> n = n;
    g -> visited = (int *) malloc(n * sizeof(int));
    g -> parent = (int *) malloc(n * sizeof(int));
    g -> path = (int *) malloc(n * sizeof(int));
    g -> matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        g -> parent[i] = -1;
        g -> visited[i] = 0;
        g -> path[i] = 0;
        g -> matrix[i] = (int *) calloc(n, sizeof(int));
    }
    return g;
}

void freeGraph(graph *g) {
    free(g -> visited);
    free(g -> parent);
    free(g -> path);
    for (int i = 0; i < g -> n; i++) {
        free(g -> matrix[i]);
    }
    free(g -> matrix);
    free(g);
}

static int count = 0, orderCount = 0, isCyclic = 0;

void depthFirstSearch(graph *g, int start, int *stack, int *stackIndex) {
    g -> visited[start] = 1;
    g -> path[start] = 1;
    count++;
    for (int i = 0; i < g -> n; i++) {
        if (g -> matrix[start][i] == 1) {
            orderCount++;
            if (!(g -> visited[i])) {
                g -> parent[i] = start;
                depthFirstSearch(g, i, stack, stackIndex);
            } else if ((g -> path[i])) {
                isCyclic = 1;
            }
        }
    }
    g -> path[start] = 0;
    orderCount++;
    stack[++(*stackIndex)] = start;
}

void topologicalSort(graph *g, int mode) {
    int *stack = (int *) malloc((g -> n) * sizeof(int));
    int stackIndex = -1;
    for (int i = 0; i < g -> n; i++) {
        if (!(g -> visited[i])) {
            depthFirstSearch(g, i, stack, &stackIndex);
        }
    }
    if (mode == 0 && !isCyclic) {
        printf("\nThe topological sort order is:\n");
        for (int i = stackIndex; i >= 0; i--) {
            printf("-> %c ", stack[i] + 65);
        }
        printf("\n");
    } else if (mode == 0) {
        printf("\nThe input graph is cyclic, so no topological ordering!\n");
    }
    free(stack);
}

void tester() {
    int n;
    printf("\nEnter the number of vertices of the graph: ");
    scanf("%d", &n);
    graph *g = createGraph(n);
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(g -> matrix[i][j]));
        }
    }
    topologicalSort(g, 0);
    freeGraph(g);
}

void plotter(int mode) {
    FILE *f1 = fopen("topoBest.txt", "a");
    FILE *f2 = fopen("topoWorst.txt", "a");
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
        orderCount = count = 0;
        topologicalSort(g, 1);
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