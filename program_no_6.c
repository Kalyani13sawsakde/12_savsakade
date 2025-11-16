#include <stdio.h>

#define MAX 100

int stack[MAX];
int top = -1;

// push
void push(int x) {
    stack[++top] = x;
}

// pop
int pop() {
    return stack[top--];
}

int main() {
    int num, temp;

    printf("Enter a decimal number: ");
    scanf("%d", &num);

    temp = num;

    if (num == 0) {
        printf("Binary: 0\n");
        return 0;
    }

    // store remainders in stack
    while (temp > 0) {
        push(temp % 2);
        temp = temp / 2;
    }

    printf("Binary: ");
    // pop to print in reverse order
    while (top != -1) {
        printf("%d", pop());
    }

    printf("\n");
    return 0;
}

