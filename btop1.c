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

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct TreeNode* stack[100];  
    int top = -1;

    printf("Preorder Traversal: ");

    while (1) {
        while (root != NULL) {
            printf("%d ", root->data);
            stack[++top] = root;
            root = root->left;
        }

        if (top == -1) {
            break;
        }

        root = stack[top--]->right;
    }

    printf("\n");
}

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct TreeNode* stack1[100];  
    struct TreeNode* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 != -1) {
        root = stack1[top1--];
        stack2[++top2] = root;

        if (root->left != NULL) {
            stack1[++top1] = root->left;
        }

        if (root->right != NULL) {
            stack1[++top1] = root->right;
        }
    }

    printf("Postorder Traversal: ");
    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }

    printf("\n");
}

int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    struct TreeNode* stack[100];  
    int top = -1;
    int count = 0;

    while (1) {
        while (root != NULL) {
            stack[++top] = root;
            root = root->left;
        }

        if (top == -1) {
            break;
        }

        root = stack[top--];
        count++;

        root = root->right;
    }

    return count;
}

int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    struct TreeNode* stack[100];  
    int top = -1;
    int maxDepth = 0;

    while (1) {
        while (root != NULL) {
            stack[++top] = root;
            root = root->left;
            maxDepth = (top + 1 > maxDepth) ? top + 1 : maxDepth;
        }

        if (top == -1) {
            break;
        }

        root = stack[top--];
        root = root->right;
    }

    return maxDepth;
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
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Count Total Number of Nodes\n");
        printf("5. Display Height of Tree\n");
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
                preorderTraversal(root);
                break;
            case 3:
                postorderTraversal(root);
                break;
            case 4:
                printf("Total number of nodes: %d\n", countNodes(root));
                break;
            case 5:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 6:
                printf("Exiting the program.\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
