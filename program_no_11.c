#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

int stack[MAX];
int top = -1;

// push
void push(int x) {
    stack[++top] = x;
}

// pop
int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

// evaluate postfix expression
int evaluatePostfix(char exp[]) {
    int i;
    for (i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        // if operand, push to stack
        if (isdigit(c)) {
            push(c - '0'); // convert char to int
        } else { // operator
            int val2 = pop();
            int val1 = pop();
            switch (c) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
                case '%': push(val1 % val2); break;
                case '^': push(pow(val1, val2)); break;
                default:
                    printf("Unknown operator: %c\n", c);
                    return -1;
            }
        }
    }
    return pop();
}

int main() {
    char exp[MAX];

    printf("Enter postfix expression (single digit operands): ");
    scanf("%s", exp);

    int result = evaluatePostfix(exp);
    printf("Result: %d\n", result);

    return 0;
}

