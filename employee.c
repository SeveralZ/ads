#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
};

struct TreeNode {
    struct Employee data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(struct Employee empData) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        newNode->data = empData;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

struct TreeNode* insertNode(struct TreeNode* root, struct Employee empData) {
    if (root == NULL) {
        return createNode(empData);
    }

    if (empData.empId < root->data.empId) {
        root->left = insertNode(root->left, empData);
    } else if (empData.empId > root->data.empId) {
        root->right = insertNode(root->right, empData);
    }

    return root;
}

struct TreeNode* searchEmployee(struct TreeNode* root, int empId) {
    while (root != NULL && root->data.empId != empId) {
        if (empId < root->data.empId) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Employee ID: %d\n", root->data.empId);
        inOrderTraversal(root->right);
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
    struct Employee empData;
    int choice, searchId;

    while (1) {
        printf("\nEmployee Database Menu:\n");
        printf("1. Insert Employee Record\n");
        printf("2. Search Employee Record\n");
        printf("3. Display Employee Records\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &empData.empId);
                root = insertNode(root, empData);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &searchId);
                struct TreeNode* result = searchEmployee(root, searchId);
                if (result != NULL) {
                    printf("Employee Record Found:\n");
                    printf("Employee ID: %d\n", result->data.empId);
                } else {
                    printf("Record not found for ID %d\n", searchId);
                }
                break;
            case 3:
                printf("In-Order Traversal:\n");
                inOrderTraversal(root);
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
