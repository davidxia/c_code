#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct tree_el {
    int val;
    struct tree_el* left;
    struct tree_el* right;
} node;


node * new_node(int val) {
    node* new_node = malloc(sizeof(node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void print_tree(node* tree) {
    if (tree != NULL) {
        printf("%d\n ", tree->val);
        print_tree(tree->left);
        print_tree(tree->right);
    }
}

void ordered_print_tree(node* tree) {
    if (tree == NULL) return;
    ordered_print_tree(tree->left);
    printf("%d ", tree->val);
    ordered_print_tree(tree->right);
}

/*
 Given a binary tree, print its
 nodes according to the "bottom-up"
 postorder traversal.
*/
void print_post_order(node* tree) {
    if (tree == NULL) return;
    print_post_order(tree->left);
    print_post_order(tree->right);
    printf("%d ", tree->val);
}

/*
 Given a binary tree, print its
 nodes according to the "top-down"
 postorder traversal.
*/
void print_pre_order(node* tree) {
    if (tree == NULL) return;
    printf("%d ", tree->val);
    print_pre_order(tree->left);
    print_pre_order(tree->right);
}

node* insert(node* anode, int val) {
    // 1. If the tree is empty
    // return a new, single node
    if (anode == NULL) {
        return new_node(val);
    } else {
        // 2. Otherwise, recur down the tree.
        if (val <= anode->val) anode->left = insert(anode->left, val);
        else anode->right = insert(anode->right, val);
        return anode; // return the (unchanged) node pointer
    }
}

int size(node* tree) {
    if (tree == NULL) {
        return 0;
    } else {
        return(size(tree->left) + 1 + size(tree->right));
    }
}

int max_depth(node* tree) {
    if (tree == NULL) {
        return 0;
    } else {
        // computer depth of each subtree
        int l_depth = max_depth(tree->left);
        int r_depth = max_depth(tree->right);
        printf("val: %d; left depth: %d; right depth: %d\n", tree->val, l_depth, r_depth);
        // use larger one
        if (l_depth > r_depth) return(l_depth + 1);
        else return (r_depth + 1);
    }
}

int min_value(node* tree) {
    if (tree->left == NULL) return tree->val;
    else return min_value(tree->left);
}


/*
 Given a tree and a sum, return true if there is a path from the root
 down to a leaf, such that adding up all the values along the path
 equals the given sum.
 Strategy: subtract the node value from the sum when recurring down,
 and check to see if the sum is 0 when you run out of tree.
*/
int has_path_sum(node* tree, int sum) {
    // return true 1 if we run out of tree and sum == 0
    if (tree == NULL) {
        return(sum == 0);
    } else {
        // otherwise check both subtrees
        int sub_sum = sum - tree->val;
        return (has_path_sum(tree->left, sub_sum) ||
                has_path_sum(tree->right, sub_sum));
    }
}

/*
 Given a binary tree, return true if a node
 with the target data is found in the tree. Recurs
 down the tree, chooses the left or right
 branch by comparing the target to each node.
*/
static int lookup(node* node, int target) {
    // 1. Base case == empty tree
    // in that case, the target is not found so return false
    if (node == NULL) {
        return 0;
    } else {
        // 2. see if found here
        if (target == node->val) return 1;
        else {
            // 3. otherwise recur down the correct subtree
            if (target < node->val) return (lookup(node->left, target));
            else return (lookup(node->right, target));
        }
    }
}

// Utility that prints out an array on a line.
void print_array(int ints[], int len) {
    int i;
    for (i = 0; i<len; i++) {
        printf("%d ", ints[i]);
    }
    printf("\n");
}

/*
 Recursive helper function -- given a node, and an array containing
 the path from the root node up to but not including this node,
 print out all the root-leaf paths.
*/
void print_paths_recur(node* tree, int path[], int path_len) {
    if (tree == NULL) return;
    
    // append this node to the path array
    path[path_len] = tree->val;
    path_len++;
    
    // it's a leaf, so print the path that led here
    if (tree->left == NULL && tree->right == NULL) {
        print_array(path, path_len);
    } else {
        // otherwise try both subtrees
        print_paths_recur(tree->left, path, path_len);
        print_paths_recur(tree->right, path, path_len);
    }
}

/*
 Given a binary tree, print out all of its root-to-leaf
 paths, one per line. Uses a recursive helper to do the work.
*/
void print_paths(node* tree) {
    int path[1000];
    print_paths_recur(tree, path, 0);
}

void mirror(node* tree) {
    if (tree == NULL) {
        return;
    } else {
        node* temp;
        mirror(tree->left);
        mirror(tree->right);
        temp = tree->left;
        tree->left = tree->right;
        tree->right = temp;
    }
}

void double_tree(node* tree) {
    if (tree == NULL) {
        return;
    } else {
        node* temp;
        double_tree(tree->left);
        double_tree(tree->right);
        temp = tree->left;
        node* new_node = malloc(sizeof(node));
        new_node->val = tree->val;
        new_node->left = temp;
        new_node->right = NULL;
        tree->left = new_node;
    }
}

/*
 Given two trees, return true if they are
 structurally identical.
*/
int same_tree(node* a, node* b) {
    // 1. both empty -> true
    if (a == NULL && b == NULL) return 1;
    // 2. both non-empty -> compare them
    else if (a != NULL && b != NULL) {
        return (
            a->val == b->val &&
            same_tree(a->left, b->left) &&
            same_tree(a->right, b->right)
        );
    }
    // 3. one empty, one not -> false
    else {
        return 0;
    }
}

/*
 For the key values 1...numKeys, how many structurally unique
 binary search trees are possible that store those keys.
 Strategy: consider that each value could be the root.
 Recursively find the size of the left and right subtrees.
*/
int count_trees(int num_keys) {
    if (num_keys <= 1) {
        return 1;
    } else {
        // there will be one value at the root, with whatever remains
        // on the left and right each forming their own subtrees.
        // Iterate through all the values that could be the root...
        int sum = 0;
        int left, right, root;
        
        for (root=1; root<=num_keys; root++) {
            left = count_trees(root - 1);
            right = count_trees(num_keys - root);
            
            // number of possible trees with this root == left * right
            sum += left * right;
        }
        return sum;
    }
}

void main() {
    node* root = NULL;
    root = insert(root, 4);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, -1);
    root = insert(root, 2);
    print_tree(root);
    
    printf("\nSize of tree: %d\n", size(root));
    printf("\nMax depth of tree: %d\n", max_depth(root));
    printf("Min value of tree: %d\n", min_value(root));
    ordered_print_tree(root);
    
    printf("\nPrint post order\n");
    print_post_order(root);
    printf("\nPrint pre order\n");
    print_pre_order(root);

    printf("\nhas path sum 4: %d\n", has_path_sum(root, 3));
    print_paths(root);
    
    printf("We mirror the tree.\n");
    mirror(root);
    print_paths(root);
    
    print_tree(root);
    printf("Double the left nodes of the tree.\n");
    double_tree(root);
    print_tree(root);
    
    printf("\nWe create 2 new trees\n");
    node* root2 = NULL;
    root2 = insert(root2, 5);
    root2 = insert(root2, 4);
    root2 = insert(root2, 9);
    root2 = insert(root2, 3);
    print_tree(root2);
    node* root3 = NULL;
    root3 = insert(root3, 5);
    root3 = insert(root3, 4);
    root3 = insert(root3, 8);
    root3 = insert(root3, 3);
    print_tree(root3);
    printf("Are they the same? %d\n", same_tree(root2, root3));
    
    printf("# unique binary search trees for %d nodes: %d\n", 5, count_trees(5));
}

