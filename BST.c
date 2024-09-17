#include "BST.h"

typedef struct node
{
    int data;
    struct node * right;
    struct node * left;
}Node;


struct BST
{
    int size;
    struct node * root;
};

//BST init function initializes a BST struct
BST * initBST()
{
    BST * tree=malloc(sizeof(BST));
    if(tree)
    {
        tree->size=0;
        tree->root=NULL;
        return tree;
    }
    return NULL;
}

//This insertHelper fucntion helps when the BST already has at least one node
int insertHelper(Node * p, Node * root, BST * tree)
{
    if(root==NULL)
    {
        root=p;
        tree->size++;
        return 0;
    }
    // if statements to compare and put the data in the right spot, uses recursion to make more comparisons
    if(p->data > root->data)
    {
        insertHelper(p,root->right,tree);
    }
    if(p->data < root->data)
    {
        insertHelper(p,root->left,tree);
    }
    return 1;
}

//This insert function will insert a data into the right of a BST that is passed
int insertBST(BST *tree, int data)
{
    //a node for this data is created
    Node * p=malloc(sizeof(Node));
    if(p)
    {
        p->data=data;
        p->right=NULL;
        p->left=NULL;
    }
    //checks to see if the BST is empt
    if(tree->size==0)
    {
        tree->root=p;
        tree->size++;        
        return 0;
    }
    return insertHelper(p,tree->root, tree);
}

//getSizeBST function returns the size of the tree that it is passed
int getSizeBST(BST *tree)
{
    return tree->size;
}

//this getMinHelper function rides the left side of the BST to get the smallest element
int getMinHelper(Node * root)
{
    //smallest element will be stored and returned by this min variable
    int min;
    if(root->left==NULL)
    {
        min=root->data;
    }
    else
    {
        getMinHelper(root->left);
    }
    return min;
}

//the getMinBST will return the smallest element in the passed BST
int getMinBST(BST *tree)
{
    return getMinHelper(tree->root);
}

//This flatten function helps the postOrderPrintBST function by flattening the BST into an array so that it can be printed
//it is passed the root of the BST, the array and its index
int flatten(Node * root, int array[], int index)
{
    //checks to see if the root is null
    if(root!=NULL)
    {
        //uses recursion to get each and every element
        index=flatten(root->left, array,index);
        array[index]=root->data;
        index=flatten(root->right, array,index);
    }
    return index;
}

//The postOrderPrintBST function is passed a BST and prints all of the elements in the BST
void postOrderPrintBST(BST *tree)
{
    int array[getSizeBST(tree)];
    flatten(tree->root, array,0);
    //for loop that prints all of the elements
    int i;
    for(i=0;i<getSizeBST(tree);i++)
    {
        printf("%d\n", array[i]);
    }
}

//freeHelper function goes through all the root nodes of the BST and frees them
void freeHelper(Node* root)
{
    if(root==NULL)
    {
        return;
    }
    freeHelper(root->right);
    freeHelper(root->left);
    free(root);
}
//freeBST function frees the BST that it is passed
void freeBST(BST *tree)
{
    if(tree->root==NULL)
    {
        return;
    }
    freeHelper(tree->root);//calling the helper
    //making the size back to 0 and the root null
    tree->size=0;
    tree->root=NULL;
}
