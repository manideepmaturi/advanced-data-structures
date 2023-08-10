#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the Splay Tree
struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Right Rotate
struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left Rotate
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation to bring the key to the root
struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key) {
        // Key is in the left subtree
        if (root->left == NULL) return root;

        if (key < root->left->key) {
            // Zig-Zig (Left Left)
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (key > root->left->key) {
            // Zig-Zag (Left Right)
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    } else {
        // Key is in the right subtree
        if (root->right == NULL) return root;

        if (key < root->right->key) {
            // Zag-Zig (Right Left)
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        } else if (key > root->right->key) {
            // Zag-Zag (Right Right)
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insertion operation
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) return createNode(key);

    root = splay(root, key);

    if (key < root->key) {
        struct Node* newNode = createNode(key);
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
        return newNode;
    } else if (key > root->key) {
        struct Node* newNode = createNode(key);
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
        return newNode;
    }

    // Key is already present, no duplicates allowed
    return root;
}

// Function to print the tree in inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
// Function to delete a key from the tree
struct Node* deletenode(struct Node* root, int key) {
    if (root == NULL) return root;

    root = splay(root, key);

    if (key != root->key) {
        printf("Key not found!\n");
        return root;
    }

    struct Node* leftSubtree = root->left;
    struct Node* rightSubtree = root->right;
    free(root);

    if (leftSubtree == NULL) return rightSubtree;

    leftSubtree = splay(leftSubtree, key);
    leftSubtree->right = rightSubtree;
    return leftSubtree;
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    do {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print Inorder\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deletenode(root, key);
                break;
            case 3:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
