#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
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

struct StackNode* createStackNode(struct TreeNode* data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
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

void push(struct Stack* stack, struct TreeNode* data) {
    struct StackNode* newNode = createStackNode(data);
    if (newNode != NULL) {
        newNode->next = stack->top;
        stack->top = newNode;
    }
}

struct TreeNode* pop(struct Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }

    struct TreeNode* poppedData = stack->top->data;
    struct StackNode* temp = stack->top;

    stack->top = stack->top->next;
    free(temp);

    return poppedData;
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

void mirrorImage(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Stack stack;
    stack.top = NULL;

    push(&stack, root);

    while (stack.top != NULL) {
        root = pop(&stack);

        // Swap left and right children
        struct TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        if (root->left != NULL) {
            push(&stack, root->left);
        }

        if (root->right != NULL) {
            push(&stack, root->right);
        }
    }
}

void displayTree(struct TreeNode* root) {
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

int calculateHeight(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    struct Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    int height = 0;

    enqueue(&queue, root);

    while (queue.front != NULL) {
        int levelSize = queue.rear - queue.front + 1;

        while (levelSize > 0) {
            struct TreeNode* current = dequeue(&queue);

            if (current->left != NULL) {
                enqueue(&queue, current->left);
            }

            if (current->right != NULL) {
                enqueue(&queue, current->right);
            }

            levelSize--;
        }

        height++;
    }

    return height;
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
        printf("2. Display Tree\n");
        printf("3. Display Mirror Image\n");
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
                displayTree(root);
                break;
            case 3:
                mirrorImage(root);
                printf("Mirror Image (without disturbing original):\n");
                displayTree(root);
                break;
            case 4:
                printf("Height of the Tree: %d\n", calculateHeight(root));
                break;
            case 5:
                printf("Exiting the program.\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
