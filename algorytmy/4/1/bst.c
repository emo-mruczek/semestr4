
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *left;
    struct node * right;
    int element;
} node ;

node* root=NULL;

void insert (node** root, node* node_ptr) {
    if (node_ptr==NULL) {
        return;
    }

    if (*root == NULL) {
        *root= node_ptr;
    } else if (node_ptr->element < (*root)->element) {
        insert(&(*root)->left, node_ptr);
    } else {
        insert(&(*root)->right, node_ptr);
    }
}

void free_subtree(node** root) {
    if (*root == NULL) {
        return;
    }

    if((*root)->left != NULL) {
        free_subtree( &(*root)->left );
    }

    if((*root)->right != NULL) {
        free_subtree( &(*root)->right );
    }

    free(*root);
    *root=NULL;
}

// global variables used in `print_BST`
char* left_trace; // needs to be allocaded with size
char* right_trace; // needs to be allocaded with size

void print_BST (node * root, int depth,char prefix) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        print_BST(root->left, depth+1, '/');
    }
    if(prefix == '/') left_trace[depth-1]='|';
    if(prefix == '\\') right_trace[depth-1]=' ';
    if( depth==0) printf("-");
    if( depth>0) printf(" ");
    for(int i=0; i<depth-1; i++)
        if( left_trace[i]== '|' || right_trace[i]=='|' ) {
            printf("| ");
        } else {
            printf("  ");
        }
    if( depth>0 ) printf("%c-", prefix);
    printf("[%d]\n", root->element);
    left_trace[depth]=' ';
    if( root->right != NULL ){
        right_trace[depth]='|';
        print_BST(root->right, depth+1, '\\');
    }
}

///////////////////////////

node *newNode(int element) {
    node *tmp = (node *)malloc(sizeof(node));

    tmp->element = element;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;  
}

node *getMax(node *root)
{
    // If there's no leaf to the right, then this is the maximum key value
    if (root->right != NULL)
    {
        return getMax(root->right);
    }
    return root;
}

node *delete (node *root, int element)
{
    // If the root is null, nothing to be done
    if (root == NULL)
    {
        return root;
    }
    else if (element > root->element)
    {  // If the input key is greater than the root's, search in the right
        // subtree
        root->right = delete (root->right, element);
    }
    else if (element < root->element)
    {  // If the input key is lower than the root's, search in the left subtree
        root->left = delete (root->left, element);
    }
    else if (element == root->element)
    {
        // If the input key matches the root's, check the following cases
        // termination condition
        if ((root->left == NULL) && (root->right == NULL))
        {  // Case 1: the root has no leaves, remove the node
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {  // Case 2: the root has one leaf, make the leaf the new root and
            // remove
            // the old root
            node *tmp = root;
            root = root->right;
            free(tmp);
            return root;
        }
        else if (root->right == NULL)
        {
            node *tmp = root;
            root = root->left;
            free(tmp);
            return root;
        }
        else
        {  // Case 3: the root has 2 leaves, find the greatest key in the left
            // subtree and switch with the root's

            // finds the biggest node in the left branch.
            node *tmp = getMax(root->left);

            // sets the element of this node equal to the element of the biggest node
            // (lefts)
            root->element = tmp->element;
            root->left = delete (root->left, tmp->element);
        }
    }
    return root;
}

int height(node *root)
{
    // If the root is null, this is the bottom of the tree (height 0)
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        // Get the height from both left and right subtrees to check which is
        // the greatest
        int right_h = height(root->right);
        int left_h = height(root->left);

        // The final height is the height of the greatest subtree(left or right)
        // plus 1(which is the root's level)
        if (right_h > left_h)
        {
            return (right_h + 1);
        }
        else
        {
            return (left_h + 1);
        }
    }
}

int find(node *root, int element)
{
    // If the root is null, the key's not present
    if (root == NULL)
    {
        return 0;
    }
    else if (element > root->element)
    {
        // If the input key is greater than the root's, search in the right
        // subtree
        return find(root->right, element);
    }
    else if (element < root->element)
    {
        // If the input key is lower than the root's, search in the left subtree
        return find(root->left, element);
    }
    else if (element == root->element)
    {
        // If the input and the root key match, return 1
        return 1;
    }
    else
    {  // unknown result!!
        return 0;
    }
}

void purge(node *root)
{
    if (root != NULL)
    {
        if (root->left != NULL)
        {
            purge(root->left);
        }
        if (root->right != NULL)
        {
            purge(root->right);
        }
        free(root);
        root = NULL;  // reset pointer
    }
}

int tree_size = 0;

void print_init() {
    left_trace= malloc( tree_size*sizeof(char) );
    right_trace= malloc( tree_size*sizeof(char) );
    for(int i=0; i<=tree_size; i++){
        left_trace[i]=' ';
        left_trace[i]=' ';
    }

    printf("TREE:\n");
    print_BST(root, 0, '-');
    printf("\n\n");

    free(left_trace);
    free(right_trace);
}
void insert_from_command(int element) {
    node *node_ptr = newNode(element);
    printf("INSERT: [%d]\n\n", node_ptr->element);
    insert(&root, node_ptr );
    tree_size++;
    print_init();
}

void delete_from_command(int element) {

}

void height_from_command() {

}




int main(){

    // cli 
    char command;
    int value;
    while (1) {
        printf("Podaj komende: i - insert, d - delete, h - height, e - exit\n");
        scanf("%s", &command);
        switch (command) {
            case 'i':
                printf("Podaj wartosc:\n");
                scanf("%d", &value);
                insert_from_command(value);
                break;
            case 'd':
                printf("Podaj wartosc:\n");
                scanf("%d", &value);
                delete_from_command(value);
                break;
            case 'h':
                height_from_command();
                break;
            case 'e':
                free_subtree(&root);
                return 1;
            default:
                printf("Nieistniejaca komenda\n");
                break;
        }
    }
}
