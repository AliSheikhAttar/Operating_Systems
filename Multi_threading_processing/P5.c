#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

struct Node {
    int id;
    int value;
    struct Node* children[2];
};

struct Node* createNode(int id, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->id = id;
    newNode->value = value;
    newNode->children[0] = NULL;
    newNode->children[1] = NULL;
    return newNode;
}

void buildTree(struct Node* root) {
    struct Node* nodes[20];
    for (int i = 0; i < 20; ++i) {
        nodes[i] = createNode(i + 1, (i + 1) * 10);
    }

    root->children[0] = nodes[0];
    root->children[1] = nodes[1];
    nodes[0]->children[0] = nodes[2];
    nodes[0]->children[1] = nodes[3];
    nodes[1]->children[0] = nodes[4];
    nodes[1]->children[1] = nodes[5];
    nodes[2]->children[0] = nodes[6];
    nodes[2]->children[1] = nodes[7];
    nodes[3]->children[0] = nodes[8];
    nodes[3]->children[1] = nodes[9];
    nodes[4]->children[0] = nodes[10];
    nodes[4]->children[1] = nodes[11];
    nodes[5]->children[0] = nodes[12];
    nodes[5]->children[1] = nodes[13];
    nodes[6]->children[0] = nodes[14];
    nodes[6]->children[1] = nodes[15];
    nodes[7]->children[0] = nodes[16];
    nodes[7]->children[1] = nodes[17];
    nodes[8]->children[0] = nodes[18];
    nodes[8]->children[1] = nodes[19];
}

struct Node* dfsSearch(struct Node* root, int target) {
    if (root == NULL) {
        return NULL;
    }

    if (root->value == target) {
        return root;
    }
    
    struct Node* found = NULL;
    int i = 0;
    int ids[2];
    int j = 0;
    while (root->children[i] != NULL && i < 2) {

        found = dfsSearch(root->children[i], target);
        if (found != NULL)
        {
            return found;
        }
        
        ++i;
    }
    

    return found;
}

int main() {
    clock_t startTime = clock();
    struct Node* root = createNode(0, 0);
    buildTree(root);
    int targetValue = 150;
    struct Node* result = dfsSearch(root, targetValue);
    clock_t endTime = clock();
    double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    if (result != NULL) {
        printf("Found node with value %d\n", targetValue);
        printf("Node id: %d\n", result->id);
    } else {
        printf("Value %d not found in the tree\n", targetValue);
    }

    printf("Execution time: %f seconds\n", executionTime);

    return 0;
}