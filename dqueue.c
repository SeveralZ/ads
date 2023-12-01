#include <stdio.h>

#define MAX_CAPACITY 10

struct CircularDeque {
    int deque[MAX_CAPACITY];
    int front, rear;
};

void initializeDeque(struct CircularDeque *deque) {
    deque->front = deque->rear = -1;
}

int is_empty(struct CircularDeque *deque) {
    return (deque->front == -1);
}

int is_full(struct CircularDeque *deque) {
    return ((deque->rear + 1) % MAX_CAPACITY == deque->front);
}

void insert_front(struct CircularDeque *deque, int item) {
    if (is_full(deque)) {
        printf("Deque is full. Cannot insert at the front.\n");
    } else {
        if (is_empty(deque)) {
            deque->front = deque->rear = 0;
        } else {
            deque->front = (deque->front - 1 + MAX_CAPACITY) % MAX_CAPACITY;
        }
        deque->deque[deque->front] = item;
        printf("%d inserted at the front.\n", item);
    }
}

void insert_rear(struct CircularDeque *deque, int item) {
    if (is_full(deque)) {
        printf("Deque is full. Cannot insert at the rear.\n");
    } else {
        if (is_empty(deque)) {
            deque->front = deque->rear = 0;
        } else {
            deque->rear = (deque->rear + 1) % MAX_CAPACITY;
        }
        deque->deque[deque->rear] = item;
        printf("%d inserted at the rear.\n", item);
    }
}

int delete_front(struct CircularDeque *deque) {
    if (is_empty(deque)) {
        printf("Deque is empty. Cannot delete from the front.\n");
        return -1;
    } else {
        int item = deque->deque[deque->front];
        if (deque->front == deque->rear) {
            initializeDeque(deque);
        } else {
            deque->front = (deque->front + 1) % MAX_CAPACITY;
        }
        printf("%d deleted from the front.\n", item);
        return item;
    }
}

int delete_rear(struct CircularDeque *deque) {
    if (is_empty(deque)) {
        printf("Deque is empty. Cannot delete from the rear.\n");
        return -1;
    } else {
        int item = deque->deque[deque->rear];
        if (deque->front == deque->rear) {
            initializeDeque(deque);
        } else {
            deque->rear = (deque->rear - 1 + MAX_CAPACITY) % MAX_CAPACITY;
        }
        printf("%d deleted from the rear.\n", item);
        return item;
    }
}

void display(struct CircularDeque *deque) {
    if (is_empty(deque)) {
        printf("Deque is empty.\n");
    } else {
        printf("Deque elements: ");
        int i = deque->front;
        do {
            printf("%d ", deque->deque[i]);
            i = (i + 1) % MAX_CAPACITY;
        } while (i != (deque->rear + 1) % MAX_CAPACITY);
        printf("\n");
    }
}

int main() {
    struct CircularDeque deque;
    initializeDeque(&deque);

    int choice, item;

    while (1) {
        printf("\nCircular Deque Menu:\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display Deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert at the front: ");
                scanf("%d", &item);
                insert_front(&deque, item);
                break;
            case 2:
                printf("Enter the element to insert at the rear: ");
                scanf("%d", &item);
                insert_rear(&deque, item);
                break;
            case 3:
                delete_front(&deque);
                break;
            case 4:
                delete_rear(&deque);
                break;
            case 5:
                display(&deque);
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
