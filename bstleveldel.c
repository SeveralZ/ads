#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct QueueNode {
    struct TreeNode* data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
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
        if (queue->front == NULL) {
            queue->front = newNode;
            queue->rear = newNode;
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
    free(temp);

    return dequeuedData;
}

struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

struct TreeNode* findMin(struct TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct TreeNode* deleteNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void levelOrderTraversal(struct TreeNode* root) {
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
        printf("\nBinary Search Tree Operations Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Level-wise\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                levelOrderTraversal(root);
                break;
            case 4:
                printf("Exiting the program.\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice. P\n");
        }
    }

    return 0;
}
