#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int arr[MAX];
int top1 = -1;
int top2 = MAX;

// push into stack 1
void push1(int x) {
    if (top1 + 1 == top2) {
        printf("Stack Overflow!\n");
        return;
    }
    arr[++top1] = x;
}

// push into stack 2
void push2(int x) {
    if (top2 - 1 == top1) {
        printf("Stack Overflow!\n");
        return;
    }
    arr[--top2] = x;
}

// pop from stack 1
int pop1() {
    if (top1 == -1) {
        printf("Stack1 Underflow!\n");
        return -1;
    }
    return arr[top1--];
}

// pop from stack 2
int pop2() {
    if (top2 == MAX) {
        printf("Stack2 Underflow!\n");
        return -1;
    }
    return arr[top2++];
}

int main() {
    push1(10);
    push1(20);
    push2(30);
    push2(40);

    printf("Popped from stack1: %d\n", pop1());
    printf("Popped from stack2: %d\n", pop2());

    return 0;
}
