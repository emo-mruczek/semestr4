#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"

// for dynamic array
#define BLOCK_SIZE 100
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

typedef enum color_type { RED, BLACK } color_type;

typedef struct node {
    color_type color;
    struct node *parent;
    struct node *left;
    struct node *right;
    int element;
} node;

node *root = NULL;

node *newnode(int element) {
    node *tmp = (node *)malloc(sizeof(node));

    tmp->element = element;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    tmp->color = RED;
    return tmp;
}

void rotate_left(node *n) {
    node *right = n->right;
    n->right = right->left;
    repl++;
    read += 2;

    read++;

    if (right->left != NULL) {
        right->left->parent = n;
        read += 2;
        repl++;
    }

    right->parent = n->parent;
    repl++;
    read++;

    read++;

    if (n->parent != NULL) {
        read += 2;

        if (n == n->parent->left) {
            n->parent->left = right;
            read += 2;
            repl++;
        } else  {
            n->parent->right = right;
            read += 2;
            repl++;
        }
    } else {
        root = right;
        repl++;
    }

    right->left = n;
    n->parent = right;
    repl += 2;
    read += 2;
}

void rotate_right(node *n) {

    node *left = n->left;
    n->left = left->right;
    repl++;
    read += 2;

    read++;

    if (left->right != NULL) {
        left->right->parent = n;
        read += 2;
        repl++;
    }

    read ++;
    repl++;

    left->parent = n->parent;

    read++;

    if (n->parent != NULL) {
        read += 2;

        if (n == n->parent->right) {
            n->parent->right = left;
            read += 2;
            repl++;

        } else  {
            n->parent->left = left;
            read += 2;
            repl++;

        }
    } else {
        root = left;
        repl++;
    }

    left->right = n;
    n->parent = left;
    read += 2;
    repl++;

}
void insert_fixup(node *n) {
    node *uncle;

    // n nie jest rootem
    // jak w cormenie zaczynamy
    read += 2;

    while (n != root && n->parent->color == RED) {
        read += 2;

        // czy parent n jest lewym dzieckiem?
        read += 4;

        if (n->parent == n->parent->parent->left) {
            // wtedy bierzemy wujka
            uncle = n->parent->parent->right;
            read += 3;

            // jezeli oboje - wujek i parent - sa czerwoni
            // case 1 z cormena
            read++;

            if (uncle != NULL && uncle->color == RED) {
                // pokoloruj
                n->parent->color = BLACK;
                uncle->color = BLACK;

                // dziadek musi byc czerwonny,
                n->parent->parent->color = RED;

                // przepinamy na dziadka i robimy dalej fixup w razie potrzeby
                n = n->parent->parent;
                repl++;

            } else {
                // case 2
                read += 2;

                if (n == n->parent->right) {
                    n = n->parent;
                    repl++;
                    rotate_left(n);
                }

                // case 3
                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                read += 2;
                rotate_right(n->parent->parent);
            }

            // to samo ale right i left sa zamienione
        } else {
            uncle = n->parent->parent->left;
            read += 3;

            read++;

            if (uncle != NULL && uncle->color == RED) {
                n->parent->color = BLACK;
                uncle->color = BLACK;

                n->parent->parent->color = RED;

                n = n->parent->parent;
                repl++;
            } else {
                read += 2;

                if (n == n->parent->left) {
                    n = n->parent;
                    repl++;
                    rotate_right(n);
                }

                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                read += 2;
                rotate_left(n->parent->parent);
            }
        }
    }

    //zeby miec pewnosc, ze zachowana zostaje wlasnosc
    root->color = BLACK;
}

node *insert(node *in) {
    node *n = root; // node ktory bedziemy porownywac z in
    node *parent = NULL; // przyszly parent in

    // szukam miejsca do wstawienia

    while (n != NULL) {
        parent = n;
        repl++;

        read++;

        if (is_less(in->element, n->element)) {
            n = n->left;
            repl++;
        } else {
            n = n->right;
            repl++;
        }
    }

    // ostateczne wstawienie
    read++;

    if (parent != NULL) {
        if (is_less(in->element, parent->element)) {
            parent->left = in;
            repl++;
        } else {
            parent->right = in;
            repl++;
        }
    } else {
        // drzewo bylo puste
        root = in;
        repl++;
    }

    // przypinam rzeczy do nowego node
    repl++;
    in->parent = parent;
    in->left = in->right = NULL;
    in->color = RED;

    // na koniec fixup
    insert_fixup(in);

    return in;
}

bool find(int key, node **result) {

    node *n;

    // szukam od roota
    n = root;

    *result = NULL;

    while (n != NULL) {
        if (key == n->element) {
            *result = n;
            return true;
        }

        if (is_less(key, n->element)) {
            n = n->left;
            repl++;
        } else {
            *result = n;
            n = n->right;
            repl++;
        }
    }

    return false;
}

node *search (int key) {
    node *n;

    if (find(key, &n)) {
        return n;
    } else {
        return NULL;
    }
}

void delete_fixup(node *child, node *child_parent) {
    while (child != root && (child == NULL || child->color == BLACK)) {

        // czy child jest lewym dzieckiem
        read++;

        if (child == child_parent->left) {
            node *sibling = child_parent->right;
            read++;

            // case 1 tj brat jest czerwony
            read++;

            if (sibling != NULL && sibling->color == RED) {
                sibling->color = BLACK;
                child_parent->color = RED;
                rotate_left(child_parent);
                sibling = child_parent->right;
                repl++;
            }

            // case 2 tj brat ma czerwone dzieci
            read += 2;

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                    (sibling->right == NULL || sibling->right->color == BLACK)) {
                read++;

                if (sibling != NULL) {
                    sibling->color = RED;
                }

                child = child_parent;
                child_parent = child_parent->parent;
                read++;
                repl += 2;
            } else {
                // case 3
                read++;

                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    read++;

                    if (sibling->left != NULL) {
                        sibling->left->color = BLACK;
                    }

                    sibling->color = RED;
                    rotate_right(sibling);
                    sibling = child_parent->right;
                    read++;
                    repl++;
                }

                // case 4
                sibling->color = child_parent->color;
                child_parent->color = BLACK;

                read++;

                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }

                rotate_left(child_parent);
                child = root;
                repl++;
            }
        } else {
            // doslownie to samo ale right i left zamienione
            node *sibling = child_parent->left;

            read++;

            if (sibling != NULL && sibling->color == RED) {
                sibling->color = BLACK;
                child_parent->color = RED;
                rotate_right(child_parent);
                sibling = child_parent->left;
                repl++;
            }

            read += 2;

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                    (sibling->right == NULL || sibling->right->color == BLACK)) {
                read++;

                if (sibling != NULL) {
                    sibling->color = RED;
                }

                child = child_parent;
                child_parent = child_parent->parent;
            } else {
                read++;

                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    read++;

                    if (sibling->right != NULL) {
                        sibling->right->color = BLACK;
                    }

                    sibling->color = RED;
                    rotate_left(sibling);
                    sibling = child_parent->left;
                    read++;
                    repl++;
                }

                sibling->color = child_parent->color;
                child_parent->color = BLACK;

                read++;

                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }

                repl++;
                rotate_right(child_parent);
                child = root;
            }
        }
    }

    if (child != NULL) {
        child->color = BLACK;
    }
}

static void swap_colors(color_type *x, color_type *y) {

    color_type t = *x;
    *x = *y;
    *y = t;
}

static void swap_parents(node *parent, node *old, node *new) {
    if (parent == NULL) {
        if (root == old) {
            root = new;
            repl++;
        }

        return;
    }

    read++;

    if (parent->left == old) {
        parent->left = new;
        repl++;
    }

    read++;

    if (parent->right == old) {
        parent->right = new;
        repl++;
    }
}

static void swap_child(node *child, node *old, node *new) {
    if (child == NULL) {
        return;
    }

    read++;

    if (child->parent == old) {
        child->parent = new;
        repl++;
    }
}

static void swap_nodes(node **x, node **y) {
    node *t = *x;
    *x = *y;
    *y = t;
    repl += 2;
}
node *delete (int element) {
    node *to_delete = search(element); //szukam gdzie jest element do usuniecia

    // nie ma co usuwac, bo taki element nie istnieje
    if (to_delete == NULL) {
        return NULL;
    }

    node *child;

    // ma oboje synow
    read += 2;

    if (to_delete->left != NULL && to_delete->right != NULL) {

        // szukam nastepnika
        node *root_right = to_delete->right;
        repl++;

        read++;

        while (root_right->left != NULL) {
            root_right = root_right->left;
            repl++;
        }

        swap_colors(&to_delete->color, &root_right->color);
        swap_parents(to_delete->parent, to_delete, root_right);

        read++;

        if (to_delete->right != root_right) {
            swap_parents(root_right->parent, root_right, to_delete);
        }

        swap_child(root_right->left, root_right, to_delete);
        swap_child(root_right->left, root_right, to_delete);
        swap_child(root_right->right, root_right, to_delete);
        swap_child(root_right->right, root_right, to_delete);
        swap_child(to_delete->left, to_delete, root_right);

        read++;

        if (to_delete->right != root_right) {
            swap_child(to_delete->right, to_delete, root_right);
        }

        read++;

        if (to_delete->right == root_right) {
            to_delete->right = to_delete;
            root_right->parent = root_right;
            read += 2;
        }

        swap_nodes(&to_delete->parent, &root_right->parent);
        swap_nodes(&to_delete->left, &root_right->left);
        swap_nodes(&to_delete->right, &root_right->right);
    }

    read++;

    if (to_delete->left != NULL) {
        child = to_delete->left;
        repl++;
    } else {
        child = to_delete->right;
        repl++;
    }

    swap_parents(to_delete->parent, to_delete, child);
    swap_child(child, to_delete, to_delete->parent);

    if (child != NULL && child->color == RED) {
        child->color = BLACK;
    } else if (to_delete->color != RED) {
        read++;
        delete_fixup(child, to_delete->parent);
    }

    // usuwanie node
    to_delete->parent = NULL;
    to_delete->left = NULL;
    to_delete->right = NULL;
    to_delete->color = BLACK;
    return to_delete;
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

void insert_from_command(int element) {
    node *node_ptr = newnode(element);
    insert(node_ptr);
}

void delete_from_command(int element) {
    if (root != NULL) {
        node *n = delete (element);

        if (n != NULL) {
        } else {
            printf("Brak elementu w drzewie\n");
        }
    } else {
        printf("Drzewo nie ma elementow\n");
    }
}

void height_from_command() {
    int h = height(root);
    printf("HEIGHT: [%d]\n\n", h);
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
