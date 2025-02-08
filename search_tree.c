#include <stdio.h>
#include <stdlib.h>

#define PRINT_FORMAT "%d " // Tree node print format

typedef int ElementType; // Assume elements are integers
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

// Print a tree node
void print_node(TreePtr tree) {
    printf(PRINT_FORMAT, tree->element);
}

// Insert a node to a tree
TreePtr insert_node(ElementType element, TreePtr tree) {
    if (tree == NULL) {
        tree = create_node(element);
    } else if (element < tree->element) {
        tree->left = insert_node(element, tree->left);
    } else if (element > tree->element) {
        tree->right = insert_node(element, tree->right);
    }
    return tree;
}

// Delete a node of a tree
TreePtr delete_node(ElementType target, TreePtr tree) {
    TreePtr tmp;
    if (tree != NULL) {
        if (target < tree->element) {
            tree->left = delete_node(target, tree->left);
        } else if (target > tree->element) {
            tree->right = delete_node(target, tree->right);
        } else {
            // Deletion
            if (tree->left != NULL && tree->right != NULL) {
                // 2 children
                tmp = tree->right; // Right sub-tree
                while (tmp->left != NULL) {
                    tmp = tmp->left;
                } // Find smallest
                tree->element = tmp->element;
                tree->right = delete_node(tree->element, tree->right);
            } else {
                // 0-1 child
                tmp = tree; // Node to be deleted
                if (tree->left != NULL) {
                    tree = tree->left; // Only left child
                } else if (tree->right != NULL) {
                    tree = tree->right; // Only right child
                } else {
                    tree = NULL; // No children
                }
                free(tmp);
            }
        }
    }
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

// Find the height of a node
int height(TreePtr tree) {
    if (tree != NULL) {
        int left_height = height(tree->left);
        int right_height = height(tree->right);
        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    } else {
        return -1; // Empty tree
    }
}

int main() {
    // Build the tree
    TreePtr search_tree = insert_node(14, NULL);
    insert_node(1, search_tree);
    insert_node(22, search_tree);
    insert_node(3, search_tree);
    insert_node(19, search_tree);
    insert_node(27, search_tree);
    insert_node(26, search_tree);
    postorder(search_tree);
    putchar('\n');

    // Searching
    postorder(search_node(22, search_tree));
    putchar('\n');

    // Height
    printf("%d\n", height(search_tree));
    printf("%d\n", height(search_tree->left));
    printf("%d\n", height(search_tree->right));

    // Deletion 22
    delete_node(22, search_tree);
    postorder(search_tree);
    putchar('\n');

    // Insert 22
    insert_node(22, search_tree);
    preorder(search_tree);
    putchar('\n');
    inorder(search_tree);
    putchar('\n');
    postorder(search_tree);
    putchar('\n');

    return 0;
}