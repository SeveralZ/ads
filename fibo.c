#include <stdio.h>

int stack[50];
int ptr = -1;

void push(int val) {
    stack[++ptr] = val;
}

void pop() {
    ptr--;
}

int top() {
    if (ptr < 0) {
        return -1;
    } else {
        return stack[ptr];
    }
}

void factorial() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    push(1);
    for (int i = 2; i <= n; i++) {
        push(top() * i);
    }

    printf("Factorial of %d is %d\n", n, top());
}

void fibonacci();

void fib(int n) {
    int a = 0, b = 1, nextTerm;

    for (int i = 3; i <= n; i++) {
        nextTerm = a + b;
        printf("%d ", nextTerm);
        a = b;
        b = nextTerm;
    }
}

void fibonacci() {
    int n;
    printf("Enter the number of terms for Fibonacci series: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Invalid number of terms\n");
        return;
    } else if (n == 1) {
        printf("%d\n", 0);
        return;
    } else if (n == 2) {
        printf("0 1\n");
        return;
    } else {
        printf("0 1 ");
        fib(n - 2);
        printf("\n");
    }
}

int main() {
    int choice;

    do {
        printf("Menu:\n");
        printf("1. Factorial Calculation\n");
        printf("2. Fibonacci Series\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                factorial();
                break;

            case 2:
                fibonacci();
                break;

            case 3:
                printf("Exiting.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 3);

    return 0;
}
