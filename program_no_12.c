#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertBeg(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
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
}

// Insert at position
void insertPos(struct Node** head, int data, int pos) {
    if (pos == 1) {
        insertBeg(head, data);
        return;
    }
    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    for (int i = 1; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete beginning
void deleteBeg(struct Node** head) {
    if (*head == NULL) return;
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Delete end
void deleteEnd(struct Node** head) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    struct Node* temp = *head;
    while (temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

// Delete at position
void deletePos(struct Node** head, int pos) {
    if (*head == NULL) return;
    if (pos == 1) {
        deleteBeg(head);
        return;
    }
    struct Node* temp = *head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range!\n");
        return;
    }

    struct Node* del = temp->next;
    temp->next = temp->next->next;
    free(del);
}

// Reverse list
struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* cur = head;
    struct Node* next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

// Merge two sorted lists
struct Node* mergeLists(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    struct Node* result = NULL;

    if (a->data <= b->data) {
        result = a;
        result->next = mergeLists(a->next, b);
    } else {
        result = b;
        result->next = mergeLists(a, b->next);
    }
    return result;
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

// Sort using bubble sort
void sortList(struct Node* head) {
    struct Node *i, *j;
    int temp;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Detect loop
int detectLoop(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return 1;
    }
    return 0;
}

// Sum of data
int sumList(struct Node* head) {
    int sum = 0;
    while (head != NULL) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

// Print odd and even data separately
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

// Print list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 5);
    insertEnd(&head, 30);
    insertBeg(&head, 2);

    printf("Original list:\n");
    printList(head);

    printf("\nAfter sorting:\n");
    sortList(head);
    printList(head);

    printf("\nMiddle node = %d\n", findMiddle(head)->data);

    printf("\nSum of all nodes = %d\n", sumList(head));

    printf("\nOdd/Even values:\n");
    printOddEven(head);

    head = reverse(head);
    printf("\nReversed list:\n");
    printList(head);

    return 0;
}

