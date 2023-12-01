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

    printf("Non-recursive Postorder Traversal: ");
    while (stack2.top != NULL) {
        root = pop(&stack2);
        printf("%d ", root->data);
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
        printf("\n Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Postorder Traversal\n");
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
                postorderTraversal(root);
                break;
            case 4:
                printf("Exiting the program.\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
