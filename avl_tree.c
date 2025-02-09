#include <stdio.h>
#include <stdlib.h>

#define PRINT_FORMAT "%d " // Tree node print format

typedef int ElementType; // Assume elements are integers
typedef struct AVLNode *TreePtr;

struct AVLNode {
    ElementType element;
    int height;
    TreePtr left;
    TreePtr right;
};

// Create a new tree node
TreePtr create_node(ElementType element) {
    TreePtr new_node = (TreePtr)malloc(sizeof(struct AVLNode));
    new_node->element = element;
    new_node->height = 0; // Leaf node
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Print a tree node
void print_node(TreePtr tree) {
    printf(PRINT_FORMAT, tree->element);
}

// Find the height of a node
int height(TreePtr tree) {
    if (tree != NULL) {
        return tree->height;
    } else {
        return -1; // Empty tree
    }
}

// Small function to find the larger value among 2 values
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Perform left rotation
TreePtr left_rotation(TreePtr x) {
    // Swap pointers
    TreePtr y = x->right;
    x->right = y->left; // T2
    y->left = x;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(x->height, height(y->right)) + 1;

    return y;
}

// Perform right rotation
TreePtr right_rotation(TreePtr x) {
    // Swap pointers
    TreePtr y = x->left;
    x->left = y->right; // T2
    y->right = x;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), x->height) + 1;

    return y;
}

// Perform left-right rotation
TreePtr left_right_rotation(TreePtr x) {
    x->left = left_rotation(x->left); // Left rotation of left child
    return right_rotation(x); // Right rotation
}

// Perform right-left rotation
TreePtr right_left_rotation(TreePtr x) {
    x->right = right_rotation(x->right); // Right rotation of right child
    return left_rotation(x); // Left rotation
}

// Insert a node to a tree
TreePtr insert_node(ElementType element, TreePtr tree) {
    if (tree == NULL) {
        tree = create_node(element);
    } else if (element < tree->element) {
        tree->left = insert_node(element, tree->left);
        if (height(tree->left) - height(tree->right) == 2) {
            if (element < tree->left->element) { // Right rotation (LL case)
                tree = right_rotation(tree);
            } else { // Left-right rotation (LR case)
                tree = left_right_rotation(tree);
            }
        }
    } else if (element > tree->element) {
        tree->right = insert_node(element, tree->right);
        if (height(tree->right) - height(tree->left) == 2) {
            if (element > tree->right->element) { // Left rotation (RR case)
                tree = left_rotation(tree);
            } else { // Right-left rotation (RL case)
                tree = right_left_rotation(tree);
            }
        }
    }
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

// Find the subtree with root node == target in a tree
TreePtr search_node(ElementType target, TreePtr tree) {
    if (tree != NULL) {
        if (target < tree->element) {
            return search_node(target, tree->left);
        } else if (target > tree->element) {
            return search_node(target, tree->right);
        } else {
            return tree;
        }
    } else {
        return NULL;
    }
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

int main() {
    // Example
    TreePtr avl_tree = insert_node(22, NULL);
    avl_tree = insert_node(1, avl_tree);
    avl_tree = insert_node(14, avl_tree);
    avl_tree = insert_node(19, avl_tree);
    avl_tree = insert_node(3, avl_tree);
    avl_tree = insert_node(27, avl_tree);
    preorder(avl_tree);
    putchar('\n');
    inorder(avl_tree);
    putchar('\n');
    postorder(avl_tree);
    putchar('\n');

    // Exercise
    avl_tree = insert_node(26, avl_tree);
    avl_tree = insert_node(25, avl_tree);
    avl_tree = insert_node(5, avl_tree);
    preorder(avl_tree);
    putchar('\n');
    inorder(avl_tree);
    putchar('\n');
    postorder(avl_tree);
    putchar('\n');

    return 0;
}