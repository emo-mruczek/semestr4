#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// for dynamic array
#define BLOCK_SIZE 100
int max_index = BLOCK_SIZE - 1;
int ind = 0;

int comp = 0;
int read = 0;
int repl = 0;
int *heights; // allocation needed

void add_height(int h) {
    if (ind > max_index) {
        heights = realloc(heights, (max_index + 1 + BLOCK_SIZE) * sizeof(int));

        if (heights == NULL) {
            perror("brak pamieci");
        }

        //printf("realock\n");
        max_index += BLOCK_SIZE;
    }

    heights[ind] = h;
    ind++;
}

bool is_less(int a, int b) {
    comp++;

    if (a < b) {
        return true;
    } else {
        return false;
    }
}

bool is_equal(int a, int b) {
    comp++;

    if (a == b) {
        return true;
    } else {
        return false;
    }
}

///////////

typedef struct node {
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
    } else if (is_less(node_ptr->element, (*root)->element)) {
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

///////////////////////////

node *newNode(int element) {
    node *tmp = (node *)malloc(sizeof(node));

    tmp->element = element;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

node *getMax(node *root) {
    // jesli nie ma lisci po prawej, to ten node jest maksymalny
    if (root->right != NULL) {
        return getMax(root->right);
    }

    return root;
}

node *delete (node *root, int element) {
    if (root == NULL) {
        return root;
    } else if (is_less( root->element, element)) {
        root->right = delete (root->right, element);
    } else if (is_less(element, root->element)) {
        root->left = delete (root->left, element);
    } else if (is_equal(element, root->element)) {
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

void insert_from_command(int element) {
    node *node_ptr = newNode(element);
    insert(&root, node_ptr);
}

void delete_from_command(int element) {
    if (root != NULL) {
        root = delete (root, element);
    } else {
        printf("Drzewo nie ma elementow\n");
    }
}

int main() {
    heights = (int *)malloc(sizeof(int) * BLOCK_SIZE);

    if (heights == NULL) {
        perror("some error");
        return 1;
    }

    // cli
    char command;
    int value;

    while (1) {
        scanf("%s", &command);

        switch (command) {
        case 'i':
            scanf("%d", &value);
            insert_from_command(value);
            add_height(height(root));
            break;

        case 'd':
            scanf("%d", &value);
            delete_from_command(value);
            add_height(height(root));
            break;

        case 'e':
            free_subtree(&root);

            for (int i = 0; i < ind; i++) {
                printf("%d ", heights[i]);
            }

            free(heights);
            return 1;

        default:
            printf("Nieistniejaca komenda\n");
            break;
        }
    }
}
