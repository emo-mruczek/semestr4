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

void rotate_left(node *n) {
    node *right = n->right;
    n->right = right->left;

    if (right->left != NULL)
        right->left->parent = n;

    right->parent = n->parent;

    if (n->parent != NULL) {
        if (n == n->parent->left) {
            n->parent->left = right;
        } else  {
            n->parent->right = right;
        }
    } else {
        root = right;
    }

    right->left = n;
    n->parent = right;
}

void rotate_right(node *n) {

    node *left = n->left;
    n->left = left->right;

    if (left->right != NULL)
        left->right->parent = n;

    left->parent = n->parent;

    if (n->parent != NULL) {
        if (n == n->parent->right) {
            n->parent->right = left;
        } else  {
            n->parent->left = left;
        }
    } else {
        root = left;
    }

    left->right = n;
    n->parent = left;
}

void splay(node *n) {
    // dopoki node nie jest rootem
    while (n->parent != NULL) {
        // node jest dzieckiem roota i wystarczy jedna rotacja
        if (n->parent == root) {
            if (n == n->parent->left) {
                rotate_right(n->parent);
            } else {
                rotate_left(n->parent);
            }
        } else {
            node *par = n->parent;
            node *grandparent = par->parent; //grandparent

            // node jest lewym dzieckiem i parent jest lewym dzieckiem
            // zig zig rotation
            if (n->parent->left == n && par->parent->left == par) {
                rotate_right(grandparent);
                rotate_right(par);
                // node jest prawym dzieckiem i parent jest prawym dzieckiem
                // zag zag roation
            } else if (n->parent->right == n && par->parent->right == par) {
                rotate_left(grandparent);
                rotate_left(par);
                // zag zig rotation
            } else if (n->parent->right == n && par->parent->left == par) {
                rotate_left(par);
                rotate_right(grandparent);
                // zig zag rotation
            } else if (n->parent->left == n && par->parent->right == par) {
                rotate_right(par);
                rotate_left(grandparent);
            }
        }
    }

}

void insert(node *n) {
    node *new = NULL;
    node *temp = root;

    while (temp != NULL) {
        new = temp;

        if (n->element < temp->element) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }

        n->parent = new;
    }

    // jesli jest rootem
    if (new == NULL) {
        root = n;
    } else if (n->element < new->element) {
        new->left = n;
    } else {
        new->right = n;
    }

    splay(n);
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

node *minimum(node *n) {
    while (n->left != NULL) {
        n = n->left;
    }

    return n;

}

void replace(node *n, node *m) {
    if (n->parent == NULL) {
        root = m;
    } else if (n == n->parent->left) {
        n->parent->left = m;
    } else {
        n->parent->right = m;
    }

    if (m != NULL) {
        m->parent = n->parent;
    }

}

node *find(int key) {

    node *n = root;

    while (n != NULL) {
        if (n->element < key) {
            n = n->right;
        } else if (key < n->element) {

            n = n->left;
        } else return n;
    }

    return NULL;
}

void delete (int key) {
    node *n = find(key);

    if (n == NULL) {
        return;
    }

    splay(n);

    if (n->left == NULL) {
        replace(n, n->right);
    } else if (n->right == NULL) {
        replace(n, n ->left);
    } else {
        node *temp = minimum(n->right);

        if (temp->parent != n) {
            replace(temp, temp->right);
            temp->right = n->right;
            temp->right->parent = temp;
        }

        replace(n, temp);
        temp->left = n->left;
        temp->left->parent = temp;
    }

    free(n);
}



node *newNode(int element) {
    node *tmp = (node *)malloc(sizeof(node));

    tmp->element = element;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;

    return tmp;
}

node *getMax(node *root) {
    // jesli nie ma lisci po prawej, to ten node jest maksymalny
    if (root->right != NULL) {
        return getMax(root->right);
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
    insert(node_ptr);
}

void delete_from_command(int element) {
    if (root != NULL) {
        delete (element);
    } else {
        printf("Drzewo nie ma elementow\n");
    }
}

void height_from_command() {
    int h = height(root);
    printf("HEIGHT: [%d]\n\n", h);
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
        printf("Podaj komende: i - insert, d - delete, h - height, e - exit\n");
        scanf("%s", &command);

        switch (command) {
        case 'i':
            printf("Podaj wartosc:\n");
            scanf("%d", &value);
            insert_from_command(value);
                add_height_insertion(height(root));
            break;

        case 'd':
            printf("Podaj wartosc:\n");
            scanf("%d", &value);
            delete_from_command(value);
add_height_deletion(height(root));
            break;

        case 'h':
            height_from_command();
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

            printf("%lld %lld %lld %lld %lld ", comp, read, repl, h_avg_deletion, h_avg_insertion);

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
