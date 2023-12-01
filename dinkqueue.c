#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    return newNode;
}

void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (newNode != NULL) {
        if (queue->rear == NULL) {
            queue->front = queue->rear = newNode;
        } else {
            newNode->prev = queue->rear;
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    }
}

int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;  
    }

    int dequeuedData = queue->front->data;
    struct Node* temp = queue->front;

    queue->front = queue->front->next;
    if (queue->front != NULL) {
        queue->front->prev = NULL;
    } else {
        queue->rear = NULL;  
    }

    free(temp);

    return dequeuedData;
}

void displayQueue(struct Queue* queue) {
    printf("Queue: ");
    struct Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(struct Queue* queue) {
    while (queue->front != NULL) {
        struct Node* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
}

int main() {
    struct Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    int choice, data;

    while (1) {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to enqueue: ");
                scanf("%d", &data);
                enqueue(&queue, data);
                break;
            case 2:
                data = dequeue(&queue);
                if (data != -1) {
                    printf("Dequeued element: %d\n", data);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting the program.\n");
                freeQueue(&queue);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
