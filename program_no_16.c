#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *left, *right;
};

// Create a new node
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
// FIND MINIMUM VALUE IN BST
// ---------------------------------------------
int findMin(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

// ---------------------------------------------
// FIND MAXIMUM VALUE IN BST
// ---------------------------------------------
int findMax(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }

    while (root->right != NULL)
        root = root->right;

    return root->data;
}

// Driver code
int main() {
    struct Node* root = NULL;

    int arr[] = {40, 20, 10, 30, 60, 50, 70};
    for (int i = 0; i < 7; i++)
        root = insert(root, arr[i]);

    printf("Minimum element in BST = %d\n", findMin(root));
    printf("Maximum element in BST = %d\n", findMax(root));

    return 0;
}

