#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *left, *right;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// ---------------------------------------------
// PRINT NODES IN RANGE [L, R]
// ---------------------------------------------
void printRange(struct Node* root, int L, int R) {
    if (root == NULL)
        return;

    // If root->data is greater than L, left subtree may have values in range
    if (root->data > L)
        printRange(root->left, L, R);

    // If root->data is in range, print it
    if (root->data >= L && root->data <= R)
        printf("%d ", root->data);

    // If root->data is less than R, right subtree may have values in range
    if (root->data < R)
        printRange(root->right, L, R);
}

// Driver code
int main() {
    struct Node* root = NULL;

    int arr[] = {40, 20, 10, 30, 60, 50, 70};
    for (int i = 0; i < 7; i++)
        root = insert(root, arr[i]);

    int L = 25, R = 65;

    printf("Nodes in range [%d, %d]: ", L, R);
    printRange(root, L, R);

    return 0;
}
