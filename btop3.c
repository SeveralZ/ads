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

void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Stack stack;
    stack.top = NULL;

    printf("Inorder Traversal: ");

    while (1) {
        while (root != NULL) {
            push(&stack, root);
            root = root->left;
        }

        if (stack.top == NULL) {
            break;
        }

        root = pop(&stack);
        printf("%d ", root->data);

        root = root->right;
    }

    printf("\n");
}

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Stack stack;
    stack.top = NULL;

    printf("Preorder Traversal: ");

    push(&stack, root);

    while (stack.top != NULL) {
        root = pop(&stack);
        printf("%d ", root->data);

        if (root->right != NULL) {
            push(&stack, root->right);
        }

        if (root->left != NULL) {
            push(&stack, root->left);
        }
    }

    printf("\n");
}

int countLeafNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    struct Stack stack;
    stack.top = NULL;

    int count = 0;

    push(&stack, root);

    while (stack.top != NULL) {
        root = pop(&stack);

        if (root->left == NULL && root->right == NULL) {
            count++;
        }

        if (root->right != NULL) {
            push(&stack, root->right);
        }

        if (root->left != NULL) {
            push(&stack, root->left);
        }
    }

    return count;
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
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Display Number of Leaf Nodes\n");
        printf("5. Mirror Image\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                inorderTraversal(root);
                break;
            case 3:
                preorderTraversal(root);
                break;
            case 4:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                mirrorImage(root);
                printf("Mirror image created.\n");
                break;
            case 6:
                printf("Exiting the program.\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
