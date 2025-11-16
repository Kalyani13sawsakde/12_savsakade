#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];     // Adjacency matrix
int visited[MAX];
int queue[MAX], front = -1, rear = -1;

// ----------------------------
// BFS FUNCTION
// ----------------------------
void BFS(int start, int n) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    front = rear = -1;
    queue[++rear] = start;
    visited[start] = 1;

    printf("BFS: ");

    while (front != rear) {
        int node = queue[++front];
        printf("%d ", node);

        for (int i = 0; i < n; i++) {
            if (adj[node][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// ----------------------------
// DFS FUNCTION (Recursive)
// ----------------------------
void DFS_util(int v, int n) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++) {
        if (adj[v][i] == 1 && visited[i] == 0) {
            DFS_util(i, n);
        }
    }
}

void DFS(int start, int n) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS: ");
    DFS_util(start, n);
    printf("\n");
}

// ----------------------------
// MAIN PROGRAM
// ----------------------------
int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1; // Undirected graph
    }

    int start;
    printf("Enter starting vertex: ");
    scanf("%d", &start);

    BFS(start, n);
    DFS(start, n);

    return 0;
}

