#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert at beginning
void insertBeg(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL)
        (*head)->prev = newNode;
    *head = newNode;
}

// Insert at end
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert at position
void insertPos(struct Node** head, int data, int pos) {
    if (pos == 1) {
        insertBeg(head, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* temp = *head;

    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }

    newNode->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = newNode;
    newNode->prev = temp;
    temp->next = newNode;
}

// Delete at beginning
void deleteBeg(struct Node** head) {
    if (*head == NULL) return;
    struct Node* temp = *head;
    *head = temp->next;
    if (*head != NULL)
        (*head)->prev = NULL;
    free(temp);
}

// Delete at end
void deleteEnd(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    if (temp->next == NULL) {
        free(temp);
        *head = NULL;
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->prev->next = NULL;
    free(temp);
}

// Delete at position
void deletePos(struct Node** head, int pos) {
    if (*head == NULL) return;

    if (pos == 1) {
        deleteBeg(head);
        return;
    }

    struct Node* temp = *head;

    for (int i = 1; temp != NULL && i < pos; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
}

// Reverse DLL
struct Node* reverse(struct Node* head) {
    struct Node* temp = NULL;
    struct Node* curr = head;

    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp != NULL)
        head = temp->prev;

    return head;
}

// Merge two sorted DLLs
struct Node* mergeDLL(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        a->next = mergeDLL(a->next, b);
        if (a->next)
            a->next->prev = a;
        return a;
    } else {
        b->next = mergeDLL(a, b->next);
        if (b->next)
            b->next->prev = b;
        return b;
    }
}

// Find middle
struct Node* findMiddle(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Sorting (bubble sort)
void sortDLL(struct Node* head) {
    struct Node *i, *j;
    int temp;

    for (i = head; i != NULL; i = i->next)
        for (j = i->next; j != NULL; j = j->next)
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
}

// Loop detection (rare but possible by bad pointer use)
int detectLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

// Sum of data
int sumDLL(struct Node* head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

// Print odd and even numbers
void printOddEven(struct Node* head) {
    struct Node* temp = head;

    printf("Odd values: ");
    while (temp) {
        if (temp->data % 2 != 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }

    temp = head;
    printf("\nEven values: ");
    while (temp) {
        if (temp->data % 2 == 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Print DLL
void printDLL(struct Node* head) {
    struct Node* temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 4);
    insertEnd(&head, 25);
    insertBeg(&head, 2);

    printf("Original DLL:\n");
    printDLL(head);

    printf("\nSorted DLL:\n");
    sortDLL(head);
    printDLL(head);

    printf("\nMiddle Node = %d\n", findMiddle(head)->data);

    printf("Sum of nodes = %d\n", sumDLL(head));

    printf("\nOdd & Even values:\n");
    printOddEven(head);

    head = reverse(head);
    printf("\nReversed DLL:\n");
    printDLL(head);

    return 0;
}

