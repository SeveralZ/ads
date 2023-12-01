#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void displayList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void reverse(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;  
        current->next = prev;     
        prev = current;           
        current = nextNode;        
    }

    *head = prev;  
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
    struct Node* temp;
    int n, data;

    printf("Enter the number of nodes in the linked list: ");
    scanf("%d", &n);

    printf("Enter the data for each node:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data);
        temp = createNode(data);
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        temp->next = head;
        head = temp;
    }

    printf("\nOriginal List: ");
    displayList(head);

    reverse(&head);

    printf("Reversed List: ");
    displayList(head);

    freeList(head);

    return 0;
}
