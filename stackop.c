#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int size;
    int top1, top2;
} twoStacks;

void initialize(twoStacks* ts, int n) {
    ts->size = n;
    ts->arr = (int*)malloc(sizeof(int) * n);
    ts->top1 = n / 2 + 1;
    ts->top2 = n / 2;
}

int stackFull(twoStacks* ts) {
    return ts->top1 == ts->top2 + 1;
}

int stackEmpty(twoStacks* ts, int stackNumber) {
    return (stackNumber == 1) ? (ts->top1 > ts->size / 2) : (ts->top2 <= ts->size / 2);
}

void displayStack(twoStacks* ts, int stackNumber) {
    printf("Stack %d: ", stackNumber);
    if (stackNumber == 1) {
        for (int i = ts->top1; i <= ts->size / 2; ++i) {
            printf("%d ", ts->arr[i]);
        }
    } else {
        for (int i = ts->top2; i > ts->size / 2; --i) {
            printf("%d ", ts->arr[i]);
        }
    }
    printf("\n");
}

void push1(twoStacks* ts, int x) {
    if (stackFull(ts)) {
        printf("Stack Overflow By element: %d\n", x);
    } else {
        ts->top1--;
        ts->arr[ts->top1] = x;
        printf("Pushed %d to Stack 1\n", x);
    }
}

void push2(twoStacks* ts, int x) {
    if (stackFull(ts)) {
        printf("Stack Overflow By element: %d\n", x);
    } else {
        ts->top2++;
        ts->arr[ts->top2] = x;
        printf("Pushed %d to Stack 2\n", x);
    }
}

int pop1(twoStacks* ts) {
    if (stackEmpty(ts, 1)) {
        printf("Stack UnderFlow\n");
        exit(1);
    } else {
        int x = ts->arr[ts->top1];
        ts->top1++;
        printf("Popped element from Stack 1: %d\n", x);
        return x;
    }
}

int pop2(twoStacks* ts) {
    if (stackEmpty(ts, 2)) {
        printf("Stack UnderFlow\n");
        exit(1);
    } else {
        int x = ts->arr[ts->top2];
        ts->top2--;
        printf("Popped element from Stack 2: %d\n", x);
        return x;
    }
}

int main() {
    int choice, x;
    twoStacks ts;
    int n;

    printf("Enter the size of the stacks: ");
    scanf("%d", &n);

    initialize(&ts, n);

    do {
        printf("\n--- Menu ---\n");
        printf("1. Push to Stack 1\n");
        printf("2. Push to Stack 2\n");
        printf("3. Pop from Stack 1\n");
        printf("4. Pop from Stack 2\n");
        printf("5. Display Stacks\n");
        printf("6. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to push to Stack 1: ");
                scanf("%d", &x);
                push1(&ts, x);
                break;

            case 2:
                printf("Enter element to push to Stack 2: ");
                scanf("%d", &x);
                push2(&ts, x);
                break;

            case 3:
                pop1(&ts);
                break;

            case 4:
                pop2(&ts);
                break;

            case 5:
                displayStack(&ts, 1);
                displayStack(&ts, 2);
                break;

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 6);

    free(ts.arr);

    return 0;
}
