#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
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

void insertFront(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (newNode != NULL) {
        newNode->next = *head;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
    }
}

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (newNode != NULL) {
        if (*head == NULL) {
            *head = newNode;
        } else {
            struct Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }
}

void deleteNode(struct Node** head, int data) {
    struct Node* current = *head;

    while (current != NULL && current->data != data) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Node with data %d not found.\n", data);
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    printf("Node with data %d deleted successfully.\n", data);
}

void displayList(struct Node* head) {
    printf("Doubly Linked List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int choice, data;

    while (1) {
        printf("\nDoubly Linked List Menu:\n");
        printf("1. Insert at the Front\n");
        printf("2. Insert at the End\n");
        printf("3. Delete a Node\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert at the front: ");
                scanf("%d", &data);
                insertFront(&head, data);
                break;
            case 2:
                printf("Enter the data to insert at the end: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                break;
            case 3:
                printf("Enter the data to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 4:
                displayList(head);
                break;
            case 5:
                printf("Exiting the program.\n");
                freeList(head);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
