#include <stdio.h>
#include <stdlib.h>

// -----------------------------
// Node structure
// -----------------------------
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

// -----------------------------
// INSERT INTO BST
// -----------------------------
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// -----------------------------
// TREE TRAVERSALS
// -----------------------------
// Inorder (LNR)
void inorder(struct Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder (NLR)
void preorder(struct Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder (LRN)
void postorder(struct Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// -----------------------------
// BFS (Level Order Traversal)
// -----------------------------
// Queue for BFS
struct Node* queue[100];
int front = -1, rear = -1;

void enqueue(struct Node* node) {
    queue[++rear] = node;
}

struct Node* dequeue() {
    return queue[++front];
}

int isEmpty() {
    return front == rear;
}

void BFS(struct Node* root) {
    if (!root) return;
    front = rear = -1;

    enqueue(root);

    while (!isEmpty()) {
        struct Node* temp = dequeue();
        printf("%d ", temp->data);
        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
}

// -----------------------------
// DFS (same as preorder)
// -----------------------------
void DFS(struct Node* root) {
    preorder(root);
}

// -----------------------------
// MIRROR OF A TREE
// -----------------------------
struct Node* mirror(struct Node* root) {
    if (root == NULL) return NULL;

    struct Node* left = mirror(root->left);
    struct Node* right = mirror(root->right);

    root->left = right;
    root->right = left;

    return root;
}

// -----------------------------
// FIND A NODE
// -----------------------------
struct Node* search(struct Node* root, int key) {
    if (!root || root->data == key) return root;

    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

// -----------------------------
// FIND PARENT
// -----------------------------
struct Node* findParent(struct Node* root, int key) {
    if (!root || root->data == key) return NULL;

    if ((root->left && root->left->data == key) ||
        (root->right && root->right->data == key))
        return root;

    if (key < root->data)
        return findParent(root->left, key);
    return findParent(root->right, key);
}

// -----------------------------
// FIND CHILDREN OF A NODE
// -----------------------------
void findChildren(struct Node* root, int key) {
    struct Node* node = search(root, key);
    if (!node) {
        printf("Node not found!\n");
        return;
    }

    printf("Children of %d: ", key);
    if (node->left) printf("Left = %d ", node->left->data);
    else printf("Left = NULL ");

    if (node->right) printf("Right = %d\n", node->right->data);
    else printf("Right = NULL\n");
}

// -----------------------------
// FIND SIBLING
// -----------------------------
void findSibling(struct Node* root, int key) {
    struct Node* parent = findParent(root, key);

    if (!parent) {
        printf("No sibling (node is root or not found)\n");
        return;
    }

    if (parent->left && parent->left->data == key && parent->right)
        printf("Sibling = %d\n", parent->right->data);
    else if (parent->right && parent->right->data == key && parent->left)
        printf("Sibling = %d\n", parent->left->data);
    else
        printf("No sibling exists\n");
}

// -----------------------------
// GRANDPARENT (GP)
// -----------------------------
void findGP(struct Node* root, int key) {
    struct Node* parent = findParent(root, key);
    if (!parent) {
        printf("No Grandparent (parent not found)\n");
        return;
    }

    struct Node* gp = findParent(root, parent->data);
    if (!gp) {
        printf("No Grandparent exists\n");
        return;
    }

    printf("Grandparent = %d\n", gp->data);
}

// -----------------------------
// UNCLE NODE
// -----------------------------
void findUncle(struct Node* root, int key) {
    struct Node* parent = findParent(root, key);
    if (!parent) {
        printf("No Uncle (parent not found)\n");
        return;
    }

    struct Node* gp = findParent(root, parent->data);
    if (!gp) {
        printf("No Uncle (grandparent missing)\n");
        return;
    }

    if (gp->left && gp->left->data == parent->data && gp->right)
        printf("Uncle = %d\n", gp->right->data);
    else if (gp->right && gp->right->data == parent->data && gp->left)
        printf("Uncle = %d\n", gp->left->data);
    else
        printf("No Uncle exists\n");
}

// -----------------------------
// MAIN PROGRAM
// -----------------------------
int main() {
    struct Node* root = NULL;

    // Create BST
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
        root = insert(root, arr[i]);

    printf("Inorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nPostorder: ");
    postorder(root);

    printf("\nBFS (Level Order): ");
    BFS(root);

    printf("\nDFS: ");
    DFS(root);

    printf("\nChildren of 30:\n");
    findChildren(root, 30);

    printf("\nSibling of 40:\n");
    findSibling(root, 40);

    printf("\nParent of 60:\n");
    struct Node* p = findParent(root, 60);
    if (p) printf("Parent = %d\n", p->data);

    printf("\nGrandparent (GP) of 40:\n");
    findGP(root, 40);

    printf("\nUncle of 40:\n");
    findUncle(root, 40);

    printf("\nMirroring Tree...\n");
    mirror(root);

    printf("Inorder after mirror: ");
    inorder(root);

    printf("\n");

    return 0;
}

