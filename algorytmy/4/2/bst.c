#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// for dynamic array
#define BLOCK_SIZE 1000
long long max_index_deletion = BLOCK_SIZE - 1;
long long ind_deletion = 0;
long long max_index_insertion = BLOCK_SIZE - 1;
long long ind_insertion = 0;

long long comp = 0;
long long read = 0;
long long repl = 0;
long long *heights_deletion; // allocation needed
long long *heights_insertion; // here too

void add_height_insertion(int h) {
    if (ind_insertion > max_index_insertion) {
        heights_insertion = realloc(heights_insertion, (max_index_insertion + 1 + BLOCK_SIZE) * sizeof(long long));

        if (heights_insertion == NULL) {
            perror("brak pamieci");
        }

        //printf("realock\n");
        max_index_insertion += BLOCK_SIZE;
    }

    heights_insertion[ind_insertion] = h;
    ind_insertion++;
}
void add_height_deletion(int h) {
    if (ind_deletion > max_index_deletion) {
        heights_deletion = realloc(heights_deletion, (max_index_deletion + 1 + BLOCK_SIZE) * sizeof(long long));

        if (heights_deletion == NULL) {
            perror("brak pamieci");
        }

        //printf("realock\n");
        max_index_deletion += BLOCK_SIZE;
    }

    heights_deletion[ind_deletion] = h;
    ind_deletion++;
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
    struct node *parent;
    int element;
} node;

node *root = NULL;

// counts
void insert(node **root, node *node_ptr, node *parent) {
    if (node_ptr == NULL) {
        return;
    }

    if (*root == NULL) {
        *root = node_ptr;
        node_ptr->parent = parent;
        repl += 2;
    } else if (is_less(node_ptr->element, (*root)->element)) {
        read++;
        insert(&(*root)->left, node_ptr, *root);
    } else {
        read++;
        insert(&(*root)->right, node_ptr, *root);
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
    tmp->parent = NULL;

    return tmp;
}

// counts
node *getMax(node *root) {
    // jesli nie ma lisci po prawej, to ten node jest maksymalny
    read++;

    if (root->right != NULL) {
        return getMax(root->right);
    }

    return root;
}

void transplant(node **root, node **to_trans) {
    node *tmp = *root;
    *root = *to_trans;
    free(tmp);
    repl++;
}
// counts
node *delete (node *root, int element) {
    if (root == NULL) {
        return root;
    }

    read++;

    if (is_less( root->element, element)) {
        read++;
        repl++;
        root->right = delete (root->right, element);
    } else if (is_less(element, root->element)) {
        read++;
        repl++;
        root->left = delete (root->left, element);
    } else if (is_equal(element, root->element)) {
        read += 2;

        if ((root->left == NULL) && (root->right == NULL)) {
            // bez lisci
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // jeden lisc
            transplant(&root, &root->right);
            return root;
        } else if (root->right == NULL) {
            transplant(&root, &root->left);
            return root;
        } else {
            //dwa liscie
            //transplant
            node *tmp = getMax(root->left);
            root->element = tmp->element;
            repl++;
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
    insert(&root, node_ptr, NULL);
}

void delete_from_command(int element) {
    if (root != NULL) {
        root = delete (root, element);
    } else {
        printf("Drzewo nie ma elementow\n");
    }
}

long long find_max(long long tab[], long long ind) {
    long long max_val = -1;

    for (long long i = 0; i < ind; i++) {
        if (tab[i] > max_val) {
            max_val = tab[i];
        }
    }

    return max_val;
}

int main() {
    heights_deletion = (long long *)malloc(sizeof(long long) * BLOCK_SIZE);
    heights_insertion = (long long *)malloc(sizeof(long long) * BLOCK_SIZE);

    if (heights_deletion == NULL) {
        perror("some error");
        return 1;
    }

    if (heights_insertion == NULL) {
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
            add_height_insertion(height(root));
            break;

        case 'd':
            scanf("%d", &value);
            delete_from_command(value);
            add_height_deletion(height(root));
            break;

        case 'e':
            free_subtree(&root);

            long long h_avg_deletion = 0;
            long long h_avg_insertion = 0;

            for (long long i = 0; i < ind_deletion; i++) {
                h_avg_deletion += heights_deletion[i];
            }

            for (long long i = 0; i < ind_insertion; i++) {
                h_avg_insertion += heights_insertion[i];
            }

            h_avg_deletion /= ind_deletion;
            h_avg_insertion /= ind_insertion;

            long long h_max_del = find_max(heights_deletion, ind_deletion);
            long long h_max_ins = find_max(heights_insertion, ind_insertion);

            printf("%lld %lld %lld %lld %lld %lld %lld ", comp, read, repl, h_avg_deletion, h_avg_insertion,  h_max_del, h_max_ins);

            //printf("%lld %lld %lld ", comp, read, repl);
            free(heights_deletion);
            free(heights_insertion);
            return 0;

        default:
            printf("Nieistniejaca komenda\n");
            break;
        }
    }
}
