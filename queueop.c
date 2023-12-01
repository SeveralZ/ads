#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Queue {
    int front1, rear1;
    int front2, rear2;
    int array[MAX_SIZE];
};

void initializeQueues(struct Queue *queues) {
    queues->front1 = queues->rear1 = -1;
    queues->front2 = queues->rear2 = MAX_SIZE;
}

int isFull(struct Queue *queues) {
    return (queues->rear1 == queues->rear2 - 1);
}

int isEmpty1(struct Queue *queues) {
    return (queues->front1 == -1);
}

int isEmpty2(struct Queue *queues) {
    return (queues->front2 == MAX_SIZE);
}

void enqueue1(struct Queue *queues, int item) {
    if (isFull(queues)) {
        printf("Queue 1 is full. Cannot enqueue.\n");
    } else {
        if (isEmpty1(queues)) {
            queues->front1 = queues->rear1 = 0;
        } else {
            queues->rear1++;
        }
        queues->array[queues->rear1] = item;
        printf("%d enqueued in Queue 1.\n", item);
    }
}

void enqueue2(struct Queue *queues, int item) {
    if (isFull(queues)) {
        printf("Queue 2 is full. Cannot enqueue.\n");
    } else {
        if (isEmpty2(queues)) {
            queues->front2 = queues->rear2 = MAX_SIZE - 1;
        } else {
            queues->rear2--;
        }
        queues->array[queues->rear2] = item;
        printf("%d enqueued in Queue 2.\n", item);
    }
}

int dequeue1(struct Queue *queues) {
    if (isEmpty1(queues)) {
        printf("Queue 1 is empty. Cannot dequeue.\n");
        return -1;
    } else {
        int item = queues->array[queues->front1];
        if (queues->front1 == queues->rear1) {
            initializeQueues(queues);
        } else {
            queues->front1++;
        }
        printf("%d dequeued from Queue 1.\n", item);
        return item;
    }
}

int dequeue2(struct Queue *queues) {
    if (isEmpty2(queues)) {
        printf("Queue 2 is empty. Cannot dequeue.\n");
        return -1;
    } else {
        int item = queues->array[queues->front2];
        if (queues->front2 == queues->rear2) {
            initializeQueues(queues);
        } else {
            queues->front2--;
        }
        printf("%d dequeued from Queue 2.\n", item);
        return item;
    }
}

void displayQueue(struct Queue *queues) {
    if (isEmpty1(queues) && isEmpty2(queues)) {
        printf("Both queues are empty.\n");
    } else {
        printf("Queue 1 elements: ");
        for (int i = queues->front1; i <= queues->rear1; i++) {
            printf("%d ", queues->array[i]);
        }
        printf("\n");

        printf("Queue 2 elements: ");
        for (int i = queues->front2; i >= queues->rear2; i--) {
            printf("%d ", queues->array[i]);
        }
        printf("\n");
    }
}

int main() {
    struct Queue queues;
    initializeQueues(&queues);

    int choice, item;

    while (1) {
        printf("\nMultiple Queues Menu:\n");
        printf("1. Enqueue in Queue 1\n");
        printf("2. Enqueue in Queue 2\n");
        printf("3. Dequeue from Queue 1\n");
        printf("4. Dequeue from Queue 2\n");
        printf("5. Display Queues\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue in Queue 1: ");
                scanf("%d", &item);
                enqueue1(&queues, item);
                break;
            case 2:
                printf("Enter the element to enqueue in Queue 2: ");
                scanf("%d", &item);
                enqueue2(&queues, item);
                break;
            case 3:
                dequeue1(&queues);
                break;
            case 4:
                dequeue2(&queues);
                break;
            case 5:
                displayQueue(&queues);
                break;
            case 6:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
