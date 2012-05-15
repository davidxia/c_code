#include <stdio.h>
#include <stdlib.h>

typedef struct aNode
{
    int data;
    struct aNode* left;
    struct aNode* right;
} node;


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
    root->left = leftNode;
    root->right = rightNode;

    leftNode->data = 3;
    leftNode->left = leaf1;
    leftNode->right = leaf2;

    rightNode->data = 9;
    rightNode->left = leaf3;
    rightNode->right = leaf4;

    leaf1->data = 1;
    leaf1->left = NULL;
    leaf1->right = NULL;

    leaf2->data = 4;
    leaf2->left = NULL;
    leaf2->right = NULL;

    leaf3->data = 6;
    leaf3->left = NULL;
    leaf3->right = NULL;

    leaf4->data = 11;
    leaf4->left = NULL;
    leaf4->right = NULL;

    return root;
}


node* buildUnbalancedTree()
{
    node* root = malloc( sizeof( node ) );
    node* leftNode = malloc( sizeof( node ) );
    node* rightNode = malloc( sizeof ( node ) );
    node* leaf1 = malloc( sizeof ( node ) );
    node* leaf2 = malloc( sizeof ( node ) );
    node* leaf3 = malloc( sizeof ( node ) );
    node* leaf4 = malloc( sizeof ( node ) );

    root->data = 5;
    root->left = leftNode;
    root->right = rightNode;

    leftNode->data = 3;
    leftNode->left = leaf1;
    leftNode->right = leaf2;

    rightNode->data = 9;
    rightNode->left = NULL;
    rightNode->right = NULL;

    leaf1->data = 1;
    leaf1->left = leaf3;
    leaf1->right = leaf4;

    leaf2->data = 4;
    leaf2->left = NULL;
    leaf2->right = NULL;

    leaf3->data = 6;
    leaf3->left = NULL;
    leaf3->right = NULL;

    leaf4->data = 11;
    leaf4->left = NULL;
    leaf4->right = NULL;

    return root;
}



/* Helper function that allocates a new node with the given data and NULL
 * left and right pointers.
 */
node* newNode( int data )
{
    node* newNode = malloc( sizeof( node ) );
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


int maxDepth( node* root )
{
    if (!root)
        return 0;

    int ldepth = maxDepth( root->left );
    int rdepth = maxDepth( root->right );

    if (ldepth > rdepth) return ldepth + 1;
    else return rdepth + 1;
}


int minDepth( node* root )
{
    if (!root)
        return 0;

    int ldepth = minDepth( root->left );
    int rdepth = minDepth( root->right );

    if (ldepth < rdepth) return ldepth + 1;
    else return rdepth + 1;
}


main()
{
    puts( "We build a binary search tree" );
    node* root = buildBinarySearchTree();

    if (maxDepth( root ) - minDepth( root ) <= 1)
        puts( "This tree is balanced" );
    else
        puts( "This tree is not balanced" );


    puts( "We build an unbalanced tree" );
    root = buildUnbalancedTree();

    if (maxDepth( root ) - minDepth( root ) <= 1)
        puts( "This tree is balanced" );
    else
        puts( "This tree is not balanced" );

    printf( "\n\n" );
}

