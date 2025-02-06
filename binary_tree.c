#include <stdio.h>
#include <stdlib.h>

#define PRINT_FORMAT "%c " // Tree node print format

typedef char ElementType; // Assume elements are char's
typedef struct TreeNode *TreePtr;

struct TreeNode {
    ElementType element;
    TreePtr left;
    TreePtr right;
};

// Create a new tree node
TreePtr create_node(ElementType element) {
    TreePtr new_node = (TreePtr)malloc(sizeof(struct TreeNode));
    new_node->element = element;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Free a tree node and its descendants
void destroy_node(TreePtr node) {
    if (node != NULL) {
        destroy_node(node->left); // L
        destroy_node(node->right); // R
        free(node); // V
    }
}

// Print a tree node
void print_node(TreePtr tree) {
    printf(PRINT_FORMAT, tree->element);
}

// Insert a node (child) to a tree (parent)
TreePtr insert_node(ElementType element, TreePtr parent, int isRight) {
    TreePtr child = create_node(element);
    if (parent != NULL) {
        if (isRight) {
            parent->right = child;
        } else {
            parent->left = child;
        }
    }
    return child;
}

// Preorder traversal
void preorder(TreePtr root) {
    if (root != NULL) {
        print_node(root); // V
        preorder(root->left); // L
        preorder(root->right); // R
    }
}

// Inorder traversal
void inorder(TreePtr root) {
    if (root != NULL) {
        inorder(root->left); // L
        print_node(root); // V
        inorder(root->right); // R
    }
}

// Postorder traversal
void postorder(TreePtr root) {
    if (root != NULL) {
        postorder(root->left); // L
        postorder(root->right); // R
        print_node(root); // V
    }
}

// Delete a subtree (child) of a tree
void delete_node(TreePtr parent, int isRight) {
    if (parent->left != NULL || parent->right != NULL) {
        if (isRight) {
            destroy_node(parent->right);
            parent->right = NULL;
        } else {
            destroy_node(parent->left);
            parent->left = NULL;
        }
    } else {
        destroy_node(parent);
        parent = NULL;
    }
}

int main() {
    // Insertion
    TreePtr binary_tree = insert_node('A', NULL, 0);
    TreePtr subtree_l = insert_node('B', binary_tree, 0);
    TreePtr subtree_r = insert_node('C', binary_tree, 1);
    insert_node('D', subtree_l, 0);
    insert_node('E', subtree_l, 1);
    insert_node('F', subtree_r, 0);
    insert_node('G', subtree_r, 1);

    // Traversal
    printf("After insertion:\n");
    printf("Preorder: ");
    preorder(binary_tree);
    putchar('\n');

    printf("Inorder: ");
    inorder(binary_tree);
    putchar('\n');
    
    printf("Postorder: ");
    postorder(binary_tree);
    putchar('\n');

    // Deletion
    printf("\nAfter deletion:\n");
    delete_node(binary_tree, 1);

    printf("Preorder: ");
    preorder(binary_tree);
    putchar('\n');

    printf("Inorder: ");
    inorder(binary_tree);
    putchar('\n');
    
    printf("Postorder: ");
    postorder(binary_tree);
    putchar('\n');
    return 0;
}