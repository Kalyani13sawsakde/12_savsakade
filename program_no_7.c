#include <stdio.h>
#include <ctype.h>   // for isalnum()
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// push
void push(char c) {
    stack[++top] = c;
}

// pop
char pop() {
    return stack[top--];
}

// check precedence
int precedence(char c) {
    if (c == '^') return 3;      // highest precedence
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// function to convert infix → postfix
void infixToPostfix(char infix[], char postfix[]) {
    int j = 0;  // index for postfix

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        // Operand → directly add to output
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        // Opening parenthesis → push
        else if (c == '(') {
            push(c);
        }
        // Closing parenthesis → pop until '('
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();
            pop();  // remove '('
        }
        // Operator
        else {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(c) &&
                   !(c == '^' && stack[top] == '^'))  // right-associativity of ^
            {
                postfix[j++] = pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';  // null-terminate
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix: %s\n", postfix);

    return 0;
}
