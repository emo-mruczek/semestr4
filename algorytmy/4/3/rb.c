#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum color_type {
    RED,
    BLACK
} color_type;

typedef struct node {
    color_type color;
    struct node *parent;
    struct node *left;
    struct node *right;
    int element;
} node;

node *root = NULL;

void insert(node **root, node *node_ptr) {
    if (node_ptr == NULL) {
        return;
    }

    if (*root == NULL) {
        *root = node_ptr;
    } else if (node_ptr->element < (*root)->element) {
        insert(&(*root)->left, node_ptr);
    } else {
        insert(&(*root)->right, node_ptr);
    }
}

void free_subtree(node **root) {
    if (*root == NULL) {
        return;
    }

    if ((*root)->left != NULL) {
        free_subtree(&(*root)->left);
    }

    if ((*root)->right != NULL) {
        free_subtree(&(*root)->right);
    }

    free(*root);
    *root = NULL;
}

// global variables used in `print_BST`
char *left_trace;  // needs to be allocaded with size
char *right_trace; // needs to be allocaded with size

void print_BST(node *root, int depth, char prefix) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        print_BST(root->left, depth + 1, '/');
    }

    if (prefix == '/')
        left_trace[depth - 1] = '|';

    if (prefix == '\\')
        right_trace[depth - 1] = ' ';

    if (depth == 0)
        printf("-");

    if (depth > 0)
        printf(" ");

    for (int i = 0; i < depth - 1; i++)
        if (left_trace[i] == '|' || right_trace[i] == '|') {
            printf("| ");
        } else {
            printf("  ");
        }

    if (depth > 0)
        printf("%c-", prefix);

    printf("[%d]\n", root->element);
    left_trace[depth] = ' ';

    if (root->right != NULL) {
        right_trace[depth] = '|';
        print_BST(root->right, depth + 1, '\\');
    }
}

///////////////////////////

node *newNode(int element, node *parent) {
    node *tmp = (node *)malloc(sizeof(node));

    tmp->element = element;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = parent;
    tmp->color = RED;

    return tmp;
}

bool is_leaf(node *node) {
    if (node->left == NULL && node->right == NULL) {
        return true;
    } 
    return false;
}

node *getMax(node *root) {
    // jesli nie ma lisci po prawej, to ten node jest maksymalny
    if (root->right != NULL) {
        return getMax(root->right);
    }

    return root;
}

node *left_rotate(node *n) {
    node *par = n->parent;
    node *grandparent = par->parent;

    par->right = n->left;
    if (n->left != NULL)
    {
        n->left->parent = par;
    }
    n->parent = grandparent;
    par->parent = n;
    n->left = par;
    if (grandparent != NULL)
    {
        if (grandparent->right == par)
        {
            grandparent->right = n;
        }
        else
        {
            grandparent->left = n;
        }
    }
    return n;
}

node *right_rotate(node *n)
{
    node *par = n->parent;
    node *grandparent = par->parent;

    par->left = n->right;
    if (n->right != NULL)
    {
        n->right->parent = par;
    }
    n->parent = grandparent;
    par->parent = n;
    n->right = par;
    if (grandparent != NULL)
    {
        if (grandparent->right == par)
        {
            grandparent->right = n;
        }
        else
        {
            grandparent->left = n;
        }
    }
    return n;
}

void insert_fixup(node *n) {
    //czy node jest rootem?
    if (n == NULL || n->parent == NULL) {
    return;
    }

    node *child = n;
    // jesli jest czarny albo jego rodzic jest czarny
    if (n->color == BLACK || (n->parent)->color == BLACK) {
    return;
    }

    // rodzic i dziecko sa czerwoni, wtedy sprawdz wujka
    node *par = n->parent;
    node *grandparent = par->parent;

    // jesli dziadek to null, wtedy rodzic to root -> pokoloruj root
    if (grandparent == NULL) {
        par->color = BLACK;
        return;
    }

    // oba dzieci dziadka sa czerwone
if (grandparent->right != NULL && (grandparent->right)->color == RED &&
        grandparent->left != NULL && (grandparent->left)->color == RED)
    {
        // dziadek zostaje czerwonym a jego dzieci czarne
        (grandparent->right)->color = BLACK;
        (grandparent->left)->color = BLACK;
        grandparent->color = RED;
        return;
    } else {
        // rotacja

    node *greatgrandparent = grandparent->parent;
        // przypadek ze ojciec to prawy syn
        if (grandparent->right == par)
        {
            // node jest prawym synem
            if (par->right == n)
            {
                grandParent->right = par->left;
                if (par->left != NULL)
                {
                    (par->left)->parent = grandParent;
                }
                par->left = grandParent;
                grandParent->par = par;

                // dodaj do drzewa
                par->par = greatGrandParent;
                if (greatGrandParent != NULL)
                {
                    if (greatGrandParent->left != NULL &&
                        greatGrandParent->left == grandParent)
                    {
                        greatGrandParent->left = par;
                    }
                    else
                    {
                        greatGrandParent->right = par;
                    }
                }

                // cyk kolory
                par->color = BLACK;
                grandParent->color = RED;
            }
            else
            {  // przypadek ze ojcec jest lewym synem
                // rotacja parent z child
                par->left = child->right;
                if (child->right != NULL)
                {
                    (child->right)->parent = par;
                }
                child->right = par;
                par->par = child;

                // rotacja dziecka z dziadkiem
                grandParent->right = child->left;
                if (child->left != NULL)
                {
                    (child->left)->parent = grandParent;
                }
                child->left = grandParent;
                grandParent->parent = child;

                // dodaj do drzewa
                child->parent = greatGrandParent;
                if (greatGrandParent != NULL)
                {
                    if (greatGrandParent->left != NULL &&
                        greatGrandParent->left == grandParent)
                    {
                        greatGrandParent->left = child;
                    }
                    else
                    {
                        greatGrandParent->right = child;
                    }
                }

                // kolorki
                child->color = BLACK;
                grandParent->color = RED;
            }
        }
        else
        {  // to co powyzej analogicznie dla lewego przypadku
            if (par->left == n)
            {
                grandParent->left = par->right;
                if (par->right != NULL)
                {
                    (par->right)->parent = grandParent;
                }
                par->right = grandParent;
                grandParent->parent = par;

                par->parent = greatGrandParent;
                if (greatGrandParent != NULL)
                {
                    if (greatGrandParent->left != NULL &&
                        greatGrandParent->left == grandParent)
                    {
                        greatGrandParent->left = par;
                    }
                    else
                    {
                        greatGrandParent->right = par;
                    }
                }

    
                parent->color = BLACK;
                grandParent->color = RED;
            }
            else
            {  

                par->right = child->left;
                if (child->left != NULL)
                {
                    (child->left)->parent = par;
                }
                child->left = par;
                par->parent = child;

                grandParent->left = child->right;
                if (child->right != NULL)
                {
                    (child->right)->parent = grandParent;
                }
                child->right = grandParent;
                grandParent->parent = child;

                child->parent = greatGrandParent;
                if (greatGrandParent != NULL)
                {
                    if (greatGrandParent->left != NULL &&
                        greatGrandParent->left == grandParent)
                    {
                        greatGrandParent->left = child;
                    }
                    else
                    {
                        greatGrandParent->right = child;
                    }
                }

                // Change The Colors
                child->color = BLACK;
                grandParent->color = RED;
            }
        }


    }

}

node *delete (node *root, int element) {
    if (root == NULL) {
        return root;
    } else if (element > root->element) {
        root->right = delete (root->right, element);
    } else if (element < root->element) {
        root->left = delete (root->left, element);
    } else if (element == root->element) {
        if ((root->left == NULL) && (root->right == NULL)) {
            // bez lisci
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // jeden lisc
            node *tmp = root;
            root = root->right;
            free(tmp);
            return root;
        } else if (root->right == NULL) {
            node *tmp = root;
            root = root->left;
            free(tmp);
            return root;
        } else {
            //dwa liscie
            node *tmp = getMax(root->left);
            root->element = tmp->element;
            root->left = delete (root->left, tmp->element);
        }
    }

    return root;
}

int height(node *root) {
    if (root == NULL) {
        return 0;
    } else {
        // ktory wyzszy
        int right_h = height(root->right);
        int left_h = height(root->left);

        if (right_h > left_h) {
            return (right_h + 1);
        } else {
            return (left_h + 1);
        }
    }
}

void purge(node *root) {
    if (root != NULL) {
        if (root->left != NULL) {
            purge(root->left);
        }

        if (root->right != NULL) {
            purge(root->right);
        }

        free(root);
        root = NULL;
    }
}

int tree_size = 0;

void print_init() {
    left_trace = malloc((tree_size + 1) * sizeof(char));
    right_trace = malloc((tree_size + 1) * sizeof(char));

    for (int i = 0; i <= tree_size; i++) {
        left_trace[i] = ' ';
        left_trace[i] = ' ';
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
    insert(&root, node_ptr);
    tree_size++;
    print_init();
}

void delete_from_command(int element) {
    if (root != NULL) {
        printf("DELETE: [%d]\n\n", element);
        root = delete (root, element);
        tree_size--;
        print_init();
    } else {
        printf("Drzewo nie ma elementow\n");
    }
}

void height_from_command() {
    int h = height(root);
    printf("HEIGHT: [%d]\n\n", h);
}

int main() {

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
