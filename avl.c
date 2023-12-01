#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};


int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}


int getBalanceFactor(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


void updateHeight(struct Node* node) {
    if (node == NULL) {
        return;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}


struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}


struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode != NULL) {
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->height = 1;
            return newNode;
        }
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    } else {
        
        return root;
    }

   
    updateHeight(root);

   
    int balance = getBalanceFactor(root);

    
    if (balance > 1 && data < root->left->data) {
        return rightRotate(root);
    }
    
    if (balance < -1 && data > root->right->data) {
        return leftRotate(root);
    }
    
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
   
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void printLevelOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * 1000);
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];

        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }

    free(queue);
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
    int choice, data;

    while (1) {
        printf("\nAVL Tree Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Display Levelwise\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                printf("Level Order Traversal: ");
                printLevelOrder(root);
                printf("\n");
                break;
            case 3:
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice. \n");
        }
    }

    return 0;
}
