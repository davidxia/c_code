#include <stdio.h>
#include <stdlib.h>


typedef struct aNode
{
    int data;
    struct aNode* left;
    struct aNode* right;
    struct aNode* parent;
} node;


node* findMin( node* root );


/* A node and reference implementation. */
node* buildBinarySearchTree()
{
    node* root = malloc( sizeof( node ) );
    node* leftNode = malloc( sizeof( node ) );
    node* rightNode = malloc( sizeof ( node ) );
    node* leaf1 = malloc( sizeof ( node ) );
    node* leaf2 = malloc( sizeof ( node ) );
    node* leaf3 = malloc( sizeof ( node ) );
    node* leaf4 = malloc( sizeof ( node ) );

    root->data = 5;
    root->parent = NULL;
    root->left = leftNode;
    root->right = rightNode;

    leftNode->data = 3;
    leftNode->parent = root;
    leftNode->left = leaf1;
    leftNode->right = leaf2;

    rightNode->data = 9;
    rightNode->parent = root;
    rightNode->left = leaf3;
    rightNode->right = leaf4;

    leaf1->data = 1;
    leaf1->parent = leftNode;
    leaf1->left = NULL;
    leaf1->right = NULL;

    leaf2->data = 4;
    leaf2->parent = leftNode;
    leaf2->left = NULL;
    leaf2->right = NULL;

    leaf3->data = 6;
    leaf3->parent = rightNode;
    leaf3->left = NULL;
    leaf3->right = NULL;

    leaf4->data = 11;
    leaf4->parent = rightNode;
    leaf4->left = NULL;
    leaf4->right = NULL;

    return root;
}


int countNodes( node* tree )
{
    if (!tree->right && !tree->left)
        return 1;

    int numRightNodes = 0;
    int numLeftNodes = 0;

    if (tree->right)
        numRightNodes = countNodes( tree->right );
    else
        numRightNodes = 0;
    if (tree->left)
        numLeftNodes = countNodes( tree->left );
    else
        numLeftNodes = 0;

    return numRightNodes + numLeftNodes + 1;
}


void printTree( node* tree )
{
    if (tree->right) {
        printf( " " );
        printTree( tree->right );
    }
    printf( "%d\n", tree->data );
    if (tree->left) {
        printf( " " );
        printTree( tree->left );
    }
}

/* Given a binary search tree, return true if a node with the target data is found in the tree.
 * Recurs down the tree, chooses the left or right branch by comparing the target to each node.
 */
node* lookup( node* treeNode, int target )
{
    if (treeNode) {
        if (target == treeNode->data)
            return treeNode;
        else {
            if (target < treeNode->data)
                return lookup( treeNode->left, target );
            else
                return lookup( treeNode->right, target );
        }
    }
    else
        return NULL;
}


/* Helper function that allocates a new node with the given data and NULL left and right pointers. */
node* newNode( node* parent, int data )
{
    node* newNode = malloc( sizeof( node ) );
    newNode->data = data;
    newNode->parent = parent;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* Given a binary search tree and a number, inserts a new node with the given number
 * into the correct place in the tree.
 */
void insert( node** nodeRef, node* parent, int data )
{
    node* current = *nodeRef;
    if (current) {
        if (data <= current->data)
            insert( &(current->left), current, data );
        else
            insert( &(current->right), current, data );
    } else
        *nodeRef = newNode( current, data );
}


void replaceNodeInParent( node* item, node* newNode )
{
    if (item->parent) {
        if (item == item->parent->left)
            item->parent->left = newNode;
        else
            item->parent->right = newNode;
    }

    if (newNode)
        newNode->parent = item->parent;

    free( item );
}



void delete( node** nodeRef, int data )
{
    node* target = lookup( *nodeRef, data );

    if (target) {
        if (target->left && target->right) {
            node* successor = findMin( target->right );
            target->data = successor->data;
            replaceNodeInParent( successor, successor->right );
        } else if (target->left) {
            replaceNodeInParent( target->left, NULL );
        } else if (target->right) {
            replaceNodeInParent( target->right, NULL );
        } else {
            free( target );
        }
    }
}


int size( node* root )
{
    if (root)
        return 1 + size( root->left ) + size( root->right );
    else return 0;
}


int maxDepth( node* root )
{
    if (root) {
        int ldepth = maxDepth( root->left );
        int rdepth = maxDepth( root->right );

        if (ldepth > rdepth) return ldepth + 1;
        else return rdepth + 1;
    }
    else return 0;
}


/* Given a non-empty binary search tree, return minimum data value. */
int minValue( node* root )
{
    node* current = root;
    while (current->left)
        current = current->left;
    return current->data;
}


node* findMin( node* root )
{
    node* current = root;
    while (current->left)
        current = current->left;
    return current;
}


/* Given a non-empty binary search tree, return maximum data value. */
int maxValue( node* root )
{
    node* current = root;
    while (current->right)
        current = current->right;
    return current->data;
}


/* Given binary search tree, print nodes in increasing order. */
void printTreeInOrder( node* root )
{
    if (root->left) printTreeInOrder( root->left );
    printf( "%d, ", root->data );
    if (root->right) printTreeInOrder( root->right );
}


/* Given a binary tree, print out the nodes of the tree according to a bottom-up "postorder" traversal */
void printTreePostOrder( node* root )
{
    if (root == NULL) return;
    printTreePostOrder( root->left );
    printTreePostOrder( root->right );
    printf( "%d, ", root->data );
}

/* Given a tree and a sum, return true if there is a path from the root down to a leaf,
 * such that adding up all the values along the path equals the given sum.
 * Strategy: subtract the node value from the sum when recurring down,
 * and check to see if the sum is 0 when you run out of tree.
 */
int hasPathSum( node* root, int sum )
{
    if (root == NULL)
        return (sum == 0);
    else {
        int subSum = sum - root->data;
        return (hasPathSum( root->left, subSum) || hasPathSum( root->right, subSum ) );
    }
}


int* nodesToArray( node* root )
{
    int numNodes = countNodes( root );
    int arr[ numNodes ];
}


main()
{
    node* root = buildBinarySearchTree();
    printf( "# nodes in tree: %d\n\n", countNodes( root ) );
    printTree( root );

    printf( "\n\nType in a number to search for in the binary search tree:\n" );
    int target;
    scanf( "%d", &target );
    if (lookup( root, target ))
        puts( "Found it!" );
    else
        puts( "Could not find it." );

    printf( "\n\nType in a number to insert into the binary search tree:\n" );
    scanf( "%d", &target );
    insert( &root, NULL, target );
    printf( "# nodes in tree: %d\n\n", countNodes( root ) );
    printTree( root );

    printf( "\n\nThe size of this tree is: %d", size( root ) );
    printf( "\n\nThe max depth of this tree is: %d", maxDepth( root ) );
    printf( "\n\nThe min value of this tree is: %d", minValue( root ) );
    printf( "\n\nThe max value of this tree is: %d", maxValue( root ) );

    printf( "\n\nPrinting binary search tree in order:\n" );
    printTreeInOrder( root );

    printf( "\n\nPrinting binary search tree in bottom-up postorder traversal:\n" );
    printTreePostOrder( root );

    printf( "\n\nIs there a path that sums to (enter sum):\n" );
    scanf( "%d", &target );
    if (hasPathSum( root, target ))
        printf( "Yes" );
    else
        printf( "No" );

    printf( "\n\n" );
}

