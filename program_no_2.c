#include <stdio.h>
#include <stdlib.h>

#define MAX 5   // maximum size of queue

int queue[MAX];
int front = -1;
int rear = -1;

// Check if queue is empty
int isEmpty() {
    return (front == -1);
}

// Check if queue is full
int isFull() {
    return (rear == MAX - 1);
}

// Insert element into queue
void enqueue(int x) {
    if (isFull()) {
        printf("Queue is FULL!\n");
        return;
    }
    if (front == -1)
        front = 0;   // first element
    queue[++rear] = x;
    printf("Inserted %d\n", x);
}

// Remove element from queue
int dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    int val = queue[front];

    // If only one element left, reset queue
    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }

    return val;
}

// Get front element
int peek() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    return queue[front];
}

// Display queue
void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Queue Menu ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                value = dequeue();
                if (value != -1)
                    printf("Removed: %d\n", value);
                break;

            case 3:
                value = peek();
                if (value != -1)
                    printf("Front: %d\n", value);
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

