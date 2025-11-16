#include <stdio.h>
#include <ctype.h>
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
    if (top == -1) return '\0';
    return stack[top--];
}

// check precedence
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// reverse a string
void reverse(char str[]) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// swap '(' and ')'
void swapParenthesis(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

// infix → postfix
void infixToPostfix(char infix[], char postfix[]) {
    int j = 0;
    top = -1; // reset stack

    for (int i = 0; infix[i]; i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(c) &&
                   !(c == '^' && stack[top] == '^')) {
                postfix[j++] = pop();
            }
            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

// infix → prefix
void infixToPrefix(char infix[], char prefix[]) {
    char rev[MAX], post[MAX];
    strcpy(rev, infix);

    reverse(rev);
    swapParenthesis(rev);

    infixToPostfix(rev, post);
    reverse(post);

    strcpy(prefix, post);
}

int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix: %s\n", prefix);

    return 0;
}

