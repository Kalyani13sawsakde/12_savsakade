#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int arr[MAX];

// queue 1 pointers
int front1 = -1, rear1 = -1;

// queue 2 pointers
int front2 = MAX, rear2 = MAX;

// enqueue in queue 1 (left side)
void enqueue1(int x) {
    if (rear1 + 1 == rear2) {
        printf("Queue Overflow!\n");
        return;
    }

    if (front1 == -1) front1 = 0;
    arr[++rear1] = x;
    printf("Inserted %d in Queue1\n", x);
}

// enqueue in queue 2 (right side)
void enqueue2(int x) {
    if (rear2 - 1 == rear1) {
        printf("Queue Overflow!\n");
        return;
    }

    if (front2 == MAX) front2 = MAX - 1;
    arr[--rear2] = x;
    printf("Inserted %d in Queue2\n", x);
}

// dequeue from queue 1
int dequeue1() {
    if (front1 == -1) {
        printf("Queue1 Underflow!\n");
        return -1;
    }

    int val = arr[front1++];

    if (front1 > rear1) front1 = rear1 = -1;

    return val;
}

// dequeue from queue 2
int dequeue2() {
    if (front2 == MAX) {
        printf("Queue2 Underflow!\n");
        return -1;
    }

    int val = arr[front2--];

    if (front2 < rear2) front2 = rear2 = MAX;

    return val;
}

void display1() {
    if (front1 == -1) {
        printf("Queue1 EMPTY\n");
        return;
    }
    printf("Queue1: ");
    for (int i = front1; i <= rear1; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void display2() {
    if (front2 == MAX) {
        printf("Queue2 EMPTY\n");
        return;
    }
    printf("Queue2: ");
    for (int i = front2; i >= rear2; i--)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    enqueue1(10);
    enqueue1(20);
    enqueue1(30);

    enqueue2(40);
    enqueue2(50);
    enqueue2(60);

    display1();
    display2();

    printf("Dequeued from Queue1: %d\n", dequeue1());
    printf("Dequeued from Queue2: %d\n", dequeue2());

    display1();
    display2();

    return 0;
}

