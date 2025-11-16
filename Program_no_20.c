#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* graph[MAX];
int indegree[MAX];
int queue[MAX], front = 0, rear = -1;

void addEdge(int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = graph[u];
    graph[u] = newNode;

    indegree[v]++;  // Increase in-degree
}

void enqueue(int v) {
    queue[++rear] = v;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front > rear;
}

void topologicalSort(int n) {
    // Enqueue all nodes with in-degree 0
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            enqueue(i);

    printf("Topological Sort (Kahn's Algorithm): ");

    while (!isEmpty()) {
        int v = dequeue();
        printf("%d ", v);

        struct Node* temp = graph[v];
        while (temp != NULL) {
            indegree[temp->vertex]--;
            if (indegree[temp->vertex] == 0)
                enqueue(temp->vertex);

            temp = temp->next;
        }
    }

    printf("\n");
}

int main() {
    int n, e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
        indegree[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter directed edges (u v) meaning u → v:\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    topologicalSort(n);

    return 0;
}

