#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the node structure
struct node {
    int id;
    int value;
    struct node* children;
};

// Define a function to create a new node
struct node* create_node(int id, int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->id = id;
    new_node->value = value;
    new_node->children = NULL;
    return new_node;
}

// Define a function to add a child node
void add_child(struct node* parent, struct node* child) {
    child->children = parent->children;
    parent->children = child;
}



// Define a function for DFS search
struct node* dfs_search(struct node* root, int target) {
    if (root == NULL) {
        return NULL;
    }

    if (root->value == target) {
        return root;
    }

    struct node* found = NULL;
    struct node* current_child = root->children;
    while (current_child != NULL && found == NULL) {
        found = dfs_search(current_child, target);
        current_child = current_child->children;
    }

    return found;
}



// Example usage
int main() {
    // Create a tree with 20 nodes
    clock_t startTime = clock();
    struct node* root = create_node(0, 0);
    for (int i = 1; i < 20; i++) {
        struct node* new_node = create_node(i, i * 10);
        if(i % 5 == 0)
        {
            root = new_node;
            continue;
        }
        add_child(root, new_node);
    }

    // Search for a value using DFS
    int target_value = 60;
    struct node* result = dfs_search(root, target_value);
    clock_t endTime = clock();
    double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    if (result != NULL) {
        printf("Found node with value %d\n", target_value);
        printf("Node id: %d\n", result->id);
    } else {
        printf("Value %d not found in the tree\n", target_value);
    }
    printf("Execution time: %f seconds\n", executionTime);

    // Free allocated memory
    // Implement a function to free the entire tree if needed

    return 0;
}
