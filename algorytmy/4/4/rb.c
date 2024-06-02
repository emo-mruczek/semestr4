#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"

// for dynamic array
#define BLOCK_SIZE 100
int max_index_deletion = BLOCK_SIZE - 1;
int ind_deletion = 0;
int max_index_insertion = BLOCK_SIZE - 1;
int ind_insertion = 0;

int comp = 0;
int read = 0;
int repl = 0;
int *heights_deletion; // allocation needed
int *heights_insertion; // here too

void add_height_insertion(int h) {
    if (ind_insertion > max_index_insertion) {
        heights_insertion = realloc(heights_insertion, (max_index_insertion + 1 + BLOCK_SIZE) * sizeof(int));

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
        heights_deletion = realloc(heights_deletion, (max_index_deletion + 1 + BLOCK_SIZE) * sizeof(int));

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

    read++;
    if (right->left != NULL) {
        right->left->parent = n;
    }

    right->parent = n->parent;

    read++;
    if (n->parent != NULL) {
        read++;
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

    read++;
    if (left->right != NULL)
        left->right->parent = n;

    left->parent = n->parent;

    read++;
    if (n->parent != NULL) {
    read++;
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
void insert_fixup(node *n) {
    node *uncle;

    // n nie jest rootem
    // jak w cormenie zaczynamy
    while (n != root && n->parent->color == RED) {
        // czy parent n jest lewym dzieckiem?
        read++;
        if (n->parent == n->parent->parent->left) {
            // wtedy bierzemy wujka
            uncle = n->parent->parent->right;

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
            } else {
                // case 2
                read++;
                if (n == n->parent->right) {
                    n = n->parent;
                    rotate_left(n);
                }

                // case 3
                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                read++;
                rotate_right(n->parent->parent);
            }

            // to samo ale right i left sa zamienione
        } else {
            uncle = n->parent->parent->left;

            read++;
            if (uncle != NULL && uncle->color == RED) {
                n->parent->color = BLACK;
                uncle->color = BLACK;

                n->parent->parent->color = RED;

                n = n->parent->parent;
            } else {
                read++;
                if (n == n->parent->left) {
                    n = n->parent;
                    rotate_right(n);
                }

                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                read++;
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

        read++;
        if (is_less(in->element, n->element)) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    // ostateczne wstawienie
    read++;
    if (parent != NULL) {
        if (is_less(in->element, parent->element)) {
            parent->left = in;
        } else {
            parent->right = in;
        }
    } else {
        // drzewo bylo puste
        root = in;
    }

    // przypinam rzeczy do nowego node
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
        read++;
        if (key == n->element) {
            *result = n;
            return true;
        }

        if (is_less(key, n->element)) {
            n = n->left;
        } else {
            *result = n;
            n = n->right;
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
        read++;
        // czy child jest lewym dzieckiem
        read++;
        if (child == child_parent->left) {
            node *sibling = child_parent->right;

            // case 1 tj brat jest czerwony
            read++;
            if (sibling != NULL && sibling->color == RED) {
                sibling->color = BLACK;
                child_parent->color = RED;
                rotate_left(child_parent);
                sibling = child_parent->right;
            }

            // case 2 tj brat ma czerwone dzieci
            read++;
            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                    (sibling->right == NULL || sibling->right->color == BLACK)) {
                read++;
                if (sibling != NULL) {
                    sibling->color = RED;
                }

                child = child_parent;
                child_parent = child_parent->parent;
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
            }

            read++;
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
                }

                sibling->color = child_parent->color;
                child_parent->color = BLACK;

                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }

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
        }

        return;
    }

    if (parent->left == old) {
        parent->left = new;
    }

    if (parent->right == old) {
        parent->right = new;
    }
}

static void swap_child(node *child, node *old, node *new) {
    if (child == NULL) {
        return;
    }

    if (child->parent == old) {
        child->parent = new;
    }
}

static void swap_nodes(node **x, node **y) {
    node *t = *x;
    *x = *y;
    *y = t;
}
node *delete (int element) {
    node *to_delete = search(element); //szukam gdzie jest element do usuniecia

    // nie ma co usuwac, bo taki element nie istnieje
    if (to_delete == NULL) {
        return NULL;
    }

    node *child;

    // ma oboje synow
    if (to_delete->left != NULL && to_delete->right != NULL) {

        // szukam nastepnika
        node *root_right = to_delete->right;

        while (root_right->left != NULL) {
            root_right = root_right->left;
        }

        swap_colors(&to_delete->color, &root_right->color);
        swap_parents(to_delete->parent, to_delete, root_right);

        if (to_delete->right != root_right) {
            swap_parents(root_right->parent, root_right, to_delete);
        }

        swap_child(root_right->left, root_right, to_delete);
        swap_child(root_right->left, root_right, to_delete);
        swap_child(root_right->right, root_right, to_delete);
        swap_child(root_right->right, root_right, to_delete);
        swap_child(to_delete->left, to_delete, root_right);

        if (to_delete->right != root_right) {
            swap_child(to_delete->right, to_delete, root_right);
        }

        if (to_delete->right == root_right) {
            to_delete->right = to_delete;
            root_right->parent = root_right;
        }

        swap_nodes(&to_delete->parent, &root_right->parent);
        swap_nodes(&to_delete->left, &root_right->left);
        swap_nodes(&to_delete->right, &root_right->right);
    }

    if (to_delete->left != NULL) {
        child = to_delete->left;
    } else {
        child = to_delete->right;
    }

    swap_parents(to_delete->parent, to_delete, child);
    swap_child(child, to_delete, to_delete->parent);

    if (child != NULL && child->color == RED) {
        child->color = BLACK;
    } else if (to_delete->color != RED) {
        delete_fixup(child, to_delete->parent);
    }

    // usuwanie node
    to_delete->parent = NULL;
    to_delete->left = NULL;
    to_delete->right = NULL;
    to_delete->color = BLACK;
    return to_delete;
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

    if (root->color == RED) {
        printf(ANSI_RED "[%d]" ANSI_RESET "\n", root->element);
    } else {
        printf("[%d]\n", root->element);
    }

    left_trace[depth] = ' ';

    if (root->right != NULL) {
        right_trace[depth] = '|';
        print_BST(root->right, depth + 1, '\\');
    }
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
    node *node_ptr = newnode(element);
    insert(node_ptr);

    printf("INSERT: [%d]\n\n", element);
    tree_size++;
}

void delete_from_command(int element) {
    if (root != NULL) {
        printf("DELETE: [%d]\n\n", element);
        node *n = delete (element);

        if (n != NULL) {
            tree_size--;
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

            int h_avg = 0;

            for (int i = 0; i < ind; i++) {
                h_avg += heights[i];
            }

            h_avg /= ind;

            printf("%d %d %d %d", comp, read, repl, h_avg);

            free(heights);
            return 0;

        default:
            printf("Nieistniejaca komenda\n");
            break;
        }
    }
}
