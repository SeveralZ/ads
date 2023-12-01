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

void insertSorted(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL || (*head)->data >= data) {
        newNode->next = *head;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
    } else {
        struct Node* current = *head;

        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }

        newNode->next = current->next;
        newNode->prev = current;
        
        if (current->next != NULL) {
            current->next->prev = newNode;
        }

        current->next = newNode;
    }
}

void displayList(struct Node* head) {
    printf("Doubly Linked List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            insertSorted(&result, list1->data);
            list1 = list1->next;
        } else {
            insertSorted(&result, list2->data);
            list2 = list2->next;
        }
    }

    while (list1 != NULL) {
        insertSorted(&result, list1->data);
        list1 = list1->next;
    }

    while (list2 != NULL) {
        insertSorted(&result, list2->data);
        list2 = list2->next;
    }

    return result;
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
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    int n1, n2, data;

    printf("Enter the number of nodes for the first sorted list: ");
    scanf("%d", &n1);
    printf("Enter the sorted data for each node:\n");
    for (int i = 0; i < n1; ++i) {
        scanf("%d", &data);
        insertSorted(&list1, data);
    }

    printf("Enter the number of nodes for the second sorted list: ");
    scanf("%d", &n2);
    printf("Enter the sorted data for each node:\n");
    for (int i = 0; i < n2; ++i) {
        scanf("%d", &data);
        insertSorted(&list2, data);
    }

    printf("\nOriginal List 1: ");
    displayList(list1);
    printf("Original List 2: ");
    displayList(list2);

    struct Node* result = mergeSortedLists(list1, list2);
    printf("\nMerged Sorted List: ");
    displayList(result);

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}
