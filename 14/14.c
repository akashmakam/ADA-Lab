#include <stdio.h>
#include <limits.h>

#define V 5 // number of vertices in the graph

// function to find the minimum key value in the key array
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// function to print the minimum spanning tree
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

// Prim's algorithm to find the minimum spanning tree
void primMST(int graph[V][V]) {
    int key[V]; // key values used to pick minimum weight edge
    int parent[V]; // array to store the parent of each vertex
    int mstSet[V]; // array to keep track of vertices included in MST

    // initialize key values as infinite and parent as -1
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        mstSet[i] = 0;
    }

    // start with vertex 0
    key[0] = 0;

    // loop until all vertices are included in MST
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        // update key values and parent index of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // print the minimum spanning tree
    printMST(parent, graph);
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    printf("Minimum Spanning Tree:\n");
    primMST(graph);

    return 0;
}