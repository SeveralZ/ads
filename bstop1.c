#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
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

struct TreeNode* findMin(struct TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
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
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

struct TreeNode* findNode(struct TreeNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return findNode(root->left, key);
    } else {
        return findNode(root->right, key);
    }
}

void iterativeInorderTraversal(struct TreeNode* root) {
    struct StackNode* stack = NULL;
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            printf("%d ", current->key);
            struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
            newNode->treeNode = current;
            newNode->next = stack;
            stack = newNode;
            current = current->left;
        }

        struct StackNode* temp = stack;
        current = temp->treeNode;
        stack = temp->next;
        current = current->right;
    }
}

void iterativePreorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (stack != NULL) {
        struct TreeNode* current = pop(&stack);
        printf("%d ", current->key);

        if (current->right != NULL) {
            push(&stack, current->right);
        }

        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
}

void push(struct StackNode** stack, struct TreeNode* treeNode) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode != NULL) {
        newNode->treeNode = treeNode;
        newNode->next = *stack;
        *stack = newNode;
    }
}

struct TreeNode* pop(struct StackNode** stack) {
    if (*stack == NULL) {
        return NULL;
    }

    struct TreeNode* treeNode = (*stack)->treeNode;
    struct StackNode* temp = *stack;
    *stack = (*stack)->next;
    free(temp);
    return treeNode;
}

void showTree(struct TreeNode* root) {
    printf("BST: ");
    iterativeInorderTraversal(root);
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
        printf("2. Delete Node\n");
        printf("3. Find Node\n");
        printf("4. Show BST\n");
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
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
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
                printf("Inorder Traversal: ");
                iterativeInorderTraversal(root);
                printf("\n");
                printf("Preorder Traversal: ");
                iterativePreorderTraversal(root);
                printf("\n");
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
