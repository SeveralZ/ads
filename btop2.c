#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

struct QueueNode {
    struct TreeNode* data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct QueueNode* createQueueNode(struct TreeNode* data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void enqueue(struct Queue* queue, struct TreeNode* data) {
    struct QueueNode* newNode = createQueueNode(data);
    if (newNode != NULL) {
        if (queue->rear == NULL) {
            queue->front = queue->rear = newNode;
        } else {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    }
}

struct TreeNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    struct TreeNode* dequeuedData = queue->front->data;
    struct QueueNode* temp = queue->front;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;  
    }

    free(temp);

    return dequeuedData;
}

void levelWiseDisplay(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    printf("Level-wise Display: ");

    enqueue(&queue, root);

    while (queue.front != NULL) {
        struct TreeNode* current = dequeue(&queue);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }

        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }

    printf("\n");
}

void mirrorImage(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    enqueue(&queue, root);

    while (queue.front != NULL) {
        struct TreeNode* current = dequeue(&queue);

        struct TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }

        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
}

int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    struct Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    enqueue(&queue, root);
    enqueue(&queue, NULL);  

    int h = 0;

    while (queue.front != NULL) {
        struct TreeNode* current = dequeue(&queue);

        if (current == NULL) {
            if (queue.front != NULL) {
                enqueue(&queue, NULL);  
            }
            h++;
        } else {
            if (current->left != NULL) {
                enqueue(&queue, current->left);
            }
            if (current->right != NULL) {
                enqueue(&queue, current->right);
            }
        }
    }

    return h;
}

void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode* root = NULL;
    int choice, data;

    while (1) {
        printf("\nBinary Tree Operations Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Level-wise Display\n");
        printf("3. Mirror Image\n");
        printf("4. Display Height of Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                levelWiseDisplay(root);
                break;
            case 3:
                mirrorImage(root);
                printf("Mirror image created.\n");
                break;
            case 4:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 5:
                printf("Exiting the program.\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
