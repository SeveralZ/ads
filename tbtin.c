#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded;  
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->isThreaded = 0; 
    }
    return newNode;
}


struct Node* insertNode(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            if (current->isThreaded) {
                break;  
            }
            current = current->right;
        } else {
            free(newNode); 
            return root;
        }
    }

   
    if (data < parent->data) {
        parent->left = newNode;
        newNode->right = parent;
        newNode->isThreaded = 1;  
    } else {
        newNode->right = parent->right;
        parent->right = newNode;
        parent->isThreaded = 0; 
    }

    return root;
}


void inorderTraversal(struct Node* root) {
    while (root != NULL) {
        
        while (root->left != NULL) {
            root = root->left;
        }

        printf("%d ", root->data);

        if (root->isThreaded) {
            root = root->right;
        } else {
            root = root->right;
        }
    }
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int n, data;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");
    freeTree(root);

    return 0;
}
