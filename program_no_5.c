#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// push
void push(char c) {
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top] = c;
}

// pop
char pop() {
    if (top == -1) {
        return '\0';     // stack empty
    }
    return stack[top--];
}

// check matching pair
int isMatching(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

// function to check expression
int checkParenthesis(char exp[]) {
    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        // if opening bracket, push to stack
        if (c == '(' || c == '{' || c == '[') {
            push(c);
        }

        // if closing bracket, check match
        else if (c == ')' || c == '}' || c == ']') {
            char open = pop();
            if (!isMatching(open, c)) {
                return 0; // mismatch found
            }
        }
    }

    // stack must be empty at the end
    return (top == -1);
}

int main() {
    char exp[100];

    printf("Enter an expression: ");
    scanf("%s", exp);

    if (checkParenthesis(exp))
        printf("Parenthesis MATCHED\n");
    else
        printf("Parenthesis NOT MATCHED\n");

    return 0;
}

