#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// -----------------------
// Adjacency list structure
// -----------------------
struct Node {
    int vertex;
    struct Node* next;
};

struct Node* graph[MAX];
int visited[MAX], disc[MAX], low[MAX], parent[MAX];
int timeCounter = 0;
int articulationFound = 0;

// Add edge to adjacency list (undirected)
void addEdge(int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = graph[u];
    graph[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = u;
    newNode->next = graph[v];
    graph[v] = newNode;
}

// -----------------------
// DFS to check articulation points
// -----------------------
void DFS(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    int childCount = 0;

    struct Node* temp = graph[u];

    while (temp != NULL) {
        int v = temp->vertex;

        if (!visited[v]) {
            parent[v] = u;
            childCount++;

            DFS(v);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // Articulation point conditions
            if (parent[u] == -1 && childCount > 1)
                articulationFound = 1;

            if (parent[u] != -1 && low[v] >= disc[u])
                articulationFound = 1;

        }
        else if (v != parent[u]) {
            // Update low value (back edge)
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }

        temp = temp->next;
    }
}

// -----------------------
// Check if graph is connected
// -----------------------
int isConnected(int n) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    // Start from 0
    DFS(0);

    // Check if any vertex unvisited
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            return 0; // not connected
    }
    return 1;
}

// -----------------------
// MAIN
// -----------------------
int main() {
    int n, e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize graph
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
        visited[i] = 0;
        parent[i] = -1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // First check connectedness
    if (!isConnected(n)) {
        printf("\nGraph is NOT Biconnected (Not connected)\n");
        return 0;
    }

    // If articulation point exists → Not biconnected
    if (articulationFound)
        printf("\nGraph is NOT Biconnected (Articulation point exists)\n");
    else
        printf("\nGraph IS Biconnected\n");

    return 0;
}

