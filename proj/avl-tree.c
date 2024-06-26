#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ALLOWED_IMBALANCE 1
#define MAX_NODE_NUM 100

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

AVLNode* createNode(int data);
AVLNode* findNode(int data, AVLNode* tree);
void insertNode(int data, AVLNode** treePointer);
void removeNode(int data, AVLNode** treePointer);

int max(int a, int b);
int getHeight(AVLNode* tree);
AVLNode* findMinNode(AVLNode* tree);
AVLNode* findMaxNode(AVLNode* tree);

void balanceTree(AVLNode** treePointer);
void rotateWithLeftChild(AVLNode** k2Pointer);
void rotateWithRightChild(AVLNode** k1Poinnter);
void doubleWithLeftChild(AVLNode** k3Pointer);
void doubleWithRightChild(AVLNode** k3Pointer);

void splitAVLTree(AVLNode* tree, int flag);

void printAVLTreeRecur(AVLNode* tree, int layer);
void printAVLTree(AVLNode* tree);
void printHints();
void printAVLTreeArr(AVLNode* tree);

int main() {
    AVLNode* tree = NULL;
    int tempData;
    char command;

    printf("Which operation do you want to perform on the AVL Tree?\n");
    printHints();
    while (1) {
        while ((command = getchar()) == '\n');

        switch(command) {
            case 'F':
                printf("Please enter the data that you want to find: ");
                scanf("%d", &tempData);
                AVLNode* result = findNode(tempData, tree);
                printf("\n---------------------------------------------------------------\n");
                if (result == NULL) printf("The data you entered is not in the AVL Tree.\n");
                else {
                    printf("Find data: %d\n", tempData);
                    printf("The address of the node: %p\n", result);
                    printf("The height of the node: %d\n", result->height);
                    printf("To know exactly where the node is, you can use command 'P' to print the tree.");
                }
                printf("\n---------------------------------------------------------------\n");
                break;
            case 'H':
                printHints();
                break;
            case 'I':
                printf("Please enter the data that you want to insert to the AVL Tree: ");
                scanf("%d", &tempData);
                insertNode(tempData, &tree);
                printf("\nAfter Insertion: \n");
                printAVLTree(tree);
                break;
            case 'P':
                printAVLTree(tree);
                break;
            case 'Q':
                return 0;
            case 'R':
                printf("Please enter the data that you want to remove from the AVL Tree: ");
                scanf("%d", &tempData);
                removeNode(tempData, &tree);
                printf("\nAfter removal:\n");
                printAVLTree(tree);
                break;
            case 'S':
                printf("Please enter the flag data: ");
                scanf("%d", &tempData);
                splitAVLTree(tree, tempData);
                break;
            default:
                printf("Unknown command. Please try again.\n");
        }
        printf("Which operation do you want to perform on the AVL Tree('H' for hints): ");
    }
    return 0;
}

AVLNode* createNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->height = 0;
    node->left = NULL, node->right = NULL;
    return node;
}

AVLNode* findNode(int data, AVLNode* tree) {
    if (tree == NULL) return NULL;

    if (data < tree->data) return findNode(data, tree->left);
    else if (data > tree->data) return findNode(data, tree->right);
    else return tree;
}

void insertNode(int data, AVLNode** treePointer) {
    AVLNode* tree = *treePointer;
    if (tree == NULL) *treePointer = createNode(data);
    else if (data < tree->data) insertNode(data, &tree->left);
    else if (data > tree->data) insertNode(data, &tree->right);

    balanceTree(treePointer);
}

void removeNode(int data, AVLNode** treePointer) {
    AVLNode* tree = *treePointer;
    if (tree == NULL) return;

    if (data < tree->data) removeNode(data, &tree->left);
    else if (data > tree->data) removeNode(data, &tree->right);
    else if (tree->left != NULL && tree->right != NULL) {
        tree->data = findMinNode(tree->right)->data;
        removeNode(tree->data, &tree->right);
    } else {
        AVLNode* oldNode = tree;
        (*treePointer) = (tree->left != NULL) ? tree->left : tree->right;
        free(oldNode);
    }

    balanceTree(treePointer);
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int getHeight(AVLNode* tree) {
    if (tree == NULL) return -1;
    return tree->height;
}

AVLNode* findMinNode(AVLNode* tree) {
    while (tree->left != NULL) tree = tree->left;
    return tree;
}

AVLNode* findMaxNode(AVLNode* tree) {
    while (tree->right != NULL) tree = tree->right;
    return tree;
}

void balanceTree(AVLNode** treePointer) {
    if (treePointer == NULL | *treePointer == NULL) return;
    AVLNode* tree = *treePointer;
    if (getHeight(tree->left) - getHeight(tree->right) > ALLOWED_IMBALANCE) {
        if (getHeight(tree->left->left) >= getHeight(tree->left->right)) {
            rotateWithLeftChild(treePointer);
        } else {
            doubleWithLeftChild(treePointer);
        }
    } else if (getHeight(tree->right) - getHeight(tree->left) > ALLOWED_IMBALANCE) {
        if (getHeight(tree->right->right) >= getHeight(tree->right->left)) {
            rotateWithRightChild(treePointer);
        } else {
            doubleWithRightChild(treePointer);
        }
    }

    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}

void rotateWithLeftChild(AVLNode** k2Pointer) {
    AVLNode* k2 = *k2Pointer;
    AVLNode* k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;

    *k2Pointer = k1;
}

void rotateWithRightChild(AVLNode** k1Pointer) {
    AVLNode* k1 = *k1Pointer;
    AVLNode* k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;

    *k1Pointer = k2;
}

void doubleWithLeftChild(AVLNode** k3Pointer) {
    AVLNode* k3 = *k3Pointer;
    rotateWithRightChild(&(k3->left));
    rotateWithLeftChild(k3Pointer);
}

void doubleWithRightChild(AVLNode** k1Pointer) {
    AVLNode* k1 = *k1Pointer;
    rotateWithLeftChild(&(k1->right));
    rotateWithRightChild(k1Pointer);
}

void splitAVLTree(AVLNode* tree, int flag) {
    AVLNode* smallTree = NULL;
    AVLNode* largeTree = NULL;

    int stackPointer = -1;
    AVLNode** stack = (AVLNode**)malloc(MAX_NODE_NUM * sizeof(AVLNode*));
    AVLNode* p = tree;

    while (stackPointer != -1 || p != NULL) {
        while (p != NULL) {
            stack[++stackPointer] = p;
            p = p->left;
        }

        if (stackPointer != -1) {
            p = stack[stackPointer--];
            if (p->data < flag) insertNode(p->data, &smallTree);
            else if (p->data > flag) insertNode(p->data, &largeTree);

            p = p->right;
        }
    }

    printf("The current two AVL trees are:\n");
    printf("---------------------------------------------------------------\n");
    printAVLTreeArr(smallTree);
    printf("\n");
    printAVLTreeArr(largeTree);
    printf("---------------------------------------------------------------\n\n");
}

void printToArr(AVLNode* tree, int layer, int left, int right, char** arr) {
    if (tree == NULL || left > right) return;

    int data = tree->data, begin = (left + right) / 2, len = 0;
    while (data) { data /= 10; len++; }
    data = tree->data;

    // write digits
    for (int i = len - 1; i >= 0; i--) {
        arr[2 * layer][begin + i] = data % 10 + '0';
        data /= 10;
    }

    // write slashes
    if (tree->left != NULL) {
        int slashLeftPos = (3 * begin / 2 + left / 2 - 1) / 2;
        arr[2 * layer + 1][slashLeftPos] = '/';
    }
    if (tree->right != NULL) {
        int slashRightPos = (3 * begin / 2 + right / 2 + 1) / 2;
        arr[2 * layer + 1][slashRightPos] = '\\';
    }

    printToArr(tree->left, layer + 1, left, begin - 2, arr);
    printToArr(tree->right, layer + 1, begin + 2, right, arr);
}

void printAVLTreeArr(AVLNode* tree) {
    int treeHeight = getHeight(tree);
    int height = 2 * treeHeight + 1;
    int width = pow(2, treeHeight + 2) - 3;

    char** arr = (char**)malloc(sizeof(char*) * height);
    for (int i = 0; i < height; i++) {
        arr[i] = (char*)malloc(sizeof(char) * (width + 3));
        arr[i][width + 2] = '\0';
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            arr[i][j] = ' ';
        }
    }

    printToArr(tree, 0, 0, width - 1, arr);
    for (int i = 0; i < height; i++) printf("%s\n", arr[i]);
    free(arr);
}

void printAVLTree(AVLNode* tree) {
    printf("The current AVL tree is:\n");
    printf("---------------------------------------------------------------\n");
    printAVLTreeArr(tree);
    printf("---------------------------------------------------------------\n\n");
}

void printHints() {
    printf("---------------------------------------------------------------\n");
    printf("Hints:\n");
    printf("'F' to find whether the data is already in this AVL Tree.\n");
    printf("'I' to insert a node with data you entered.\n");
    printf("'P' to print the current AVL Tree.\n");
    printf("'Q' to quit the program.\n");
    printf("'R' to remove a node with data you entered.\n");
    printf("'S' to split this AVL Tree.\n");
    printf("IMPORTANT: You can only enter ONE character at one time!!!\n");
    printf("---------------------------------------------------------------\n");
}
