#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
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

struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        newNode->key = key;
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

struct TreeNode* insertNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    }

    return root;
}

struct TreeNode* findNode(struct TreeNode* root, int key) {
    while (root != NULL && root->key != key) {
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
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

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Stack stack1, stack2;
    stack1.top = NULL;
    stack2.top = NULL;

    push(&stack1, root);

    while (stack1.top != NULL) {
        root = pop(&stack1);
        push(&stack2, root);

        if (root->left != NULL) {
            push(&stack1, root->left);
        }

        if (root->right != NULL) {
            push(&stack1, root->right);
        }
    }

    printf("Postorder Traversal: ");
    while (stack2.top != NULL) {
        root = pop(&stack2);
        printf("%d ", root->key);
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
    int choice, key;

    while (1) {
        printf("\nBST Operations Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Mirror Image\n");
        printf("3. Find Node\n");
        printf("4. Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insertNode(root, key);
                break;
            case 2:
                mirrorImage(root);
                printf("Mirror image created.\n");
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (findNode(root, key) != NULL) {
                    printf("Key %d found in the BST.\n", key);
                } else {
                    printf("Key %d not found in the BST.\n", key);
                }
                break;
            case 4:
                postorderTraversal(root);
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
