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

node *newnode(int element, node *parent) {
    node *tmp = (node *)malloc(sizeof(node));

    tmp->element = element;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = parent;
    tmp->color = RED;

    return tmp;
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
            grandparent->left != NULL && (grandparent->left)->color == RED) {
        // dziadek zostaje czerwonym a jego dzieci czarne
        (grandparent->right)->color = BLACK;
        (grandparent->left)->color = BLACK;
        grandparent->color = RED;
        return;
    } else {
        // rotacja

        node *greatgrandparent = grandparent->parent;

        // przypadek ze ojciec to prawy syn
        if (grandparent->right == par) {
            // node jest prawym synem
            if (par->right == n) {
                grandparent->right = par->left;

                if (par->left != NULL) {
                    (par->left)->parent = grandparent;
                }

                par->left = grandparent;
                grandparent->parent = par;

                // dodaj do drzewa
                par->parent = greatgrandparent;

                if (greatgrandparent != NULL) {
                    if (greatgrandparent->left != NULL &&
                            greatgrandparent->left == grandparent) {
                        greatgrandparent->left = par;
                    } else {
                        greatgrandparent->right = par;
                    }
                }

                // cyk kolory
                par->color = BLACK;
                grandparent->color = RED;
            } else {
                // przypadek ze ojcec jest lewym synem
                // rotacja parent z child
                par->left = child->right;

                if (child->right != NULL) {
                    (child->right)->parent = par;
                }

                child->right = par;
                par->parent = child;

                // rotacja dziecka z dziadkiem
                grandparent->right = child->left;

                if (child->left != NULL) {
                    (child->left)->parent = grandparent;
                }

                child->left = grandparent;
                grandparent->parent = child;

                // dodaj do drzewa
                child->parent = greatgrandparent;

                if (greatgrandparent != NULL) {
                    if (greatgrandparent->left != NULL &&
                            greatgrandparent->left == grandparent) {
                        greatgrandparent->left = child;
                    } else {
                        greatgrandparent->right = child;
                    }
                }

                // kolorki
                child->color = BLACK;
                grandparent->color = RED;
            }
        } else {
            // to co powyzej analogicznie dla lewego przypadku
            if (par->left == n) {
                grandparent->left = par->right;

                if (par->right != NULL) {
                    (par->right)->parent = grandparent;
                }

                par->right = grandparent;
                grandparent->parent = par;

                par->parent = greatgrandparent;

                if (greatgrandparent != NULL) {
                    if (greatgrandparent->left != NULL &&
                            greatgrandparent->left == grandparent) {
                        greatgrandparent->left = par;
                    } else {
                        greatgrandparent->right = par;
                    }
                }

                par->color = BLACK;
                grandparent->color = RED;
            } else {

                par->right = child->left;

                if (child->left != NULL) {
                    (child->left)->parent = par;
                }

                child->left = par;
                par->parent = child;

                grandparent->left = child->right;

                if (child->right != NULL) {
                    (child->right)->parent = grandparent;
                }

                child->right = grandparent;
                grandparent->parent = child;

                child->parent = greatgrandparent;

                if (greatgrandparent != NULL) {
                    if (greatgrandparent->left != NULL &&
                            greatgrandparent->left == grandparent) {
                        greatgrandparent->left = child;
                    } else {
                        greatgrandparent->right = child;
                    }
                }

                // Change The Colors
                child->color = BLACK;
                grandparent->color = RED;
            }
        }

    }

}

void insert(int elem, node **root) {
    node *temp_root = *root;

    while (temp_root) {
        if (temp_root->element > elem) {

            if (temp_root->left != NULL) {
                temp_root = temp_root->left;
            } else {
                node *to_in = newnode(elem, temp_root);
                temp_root->left = to_in;
                temp_root = to_in;

                break;
            }
        } else {
            if (temp_root->right != NULL) {
                temp_root = temp_root->right;
            } else {
                // Insert The node
                node *to_in = newnode(elem, temp_root);
                temp_root->right = to_in;
                temp_root = to_in;
                break;
            }
        }
    }

    // fixup
    while (temp_root != *root) {
        insert_fixup(temp_root);

        if (temp_root->parent == NULL) {
            *root = temp_root;
            break;
        }

        temp_root = temp_root->parent;

        if (temp_root == *root) {
            temp_root->color = BLACK;
        }
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

node *left_rotate(node *n) {
    node *par = n->parent;
    node *grandparent = par->parent;

    par->right = n->left;

    if (n->left != NULL) {
        n->left->parent = par;
    }

    n->parent = grandparent;
    par->parent = n;
    n->left = par;

    if (grandparent != NULL) {
        if (grandparent->right == par) {
            grandparent->right = n;
        } else {
            grandparent->left = n;
        }
    }

    return n;
}

node *right_rotate(node *n) {
    node *par = n->parent;
    node *grandparent = par->parent;

    par->left = n->right;

    if (n->right != NULL) {
        n->right->parent = par;
    }

    n->parent = grandparent;
    par->parent = n;
    n->right = par;

    if (grandparent != NULL) {
        if (grandparent->right == par) {
            grandparent->right = n;
        } else {
            grandparent->left = n;
        }
    }

    return n;
}
void delete_fixup(node *for_deletion, int delete, int dir, node **root) {
    // usuwany jest rootem
    if (for_deletion == (*root)) {
        (*root)->color = BLACK;
        return;
    }

    // usuwany jest czarny
    if (!delete && for_deletion->color == RED) {
        if (!dir) {
            if (for_deletion->right != NULL) {
                for_deletion->right->color = RED;
            }
        } else {
            if (for_deletion->left != NULL) {
                for_deletion->left->color = RED;
            }
        }

        for_deletion->color = BLACK;
        return;
    }

    // sprawdzamy braci
    node *sibling;
    node *par = for_deletion->parent;
    int locateChild = 0;  // 0 jest do usuniecia jest lewym synem

    if (par->right == for_deletion) {
        sibling = par->left;
        locateChild = 1;
    } else {
        sibling = par->right;
    }

    // ktorys z braci jest czerwony
    if ((sibling->right != NULL && sibling->right->color == RED) ||
            (sibling->left != NULL && sibling->left->color == RED)) {
        if (sibling->right != NULL && sibling->right->color == RED) {
            // brat jest lewy a dziecko prawe -> rotacja w lewo
            if (locateChild == 1) {
                int parColor = par->color;

                sibling = left_rotate(sibling->right);
                // Step 2: Right rotate updated sibling
                par = right_rotate(sibling);

                // czy root byl obracany
                if (par->parent == NULL) {
                    *root = par;
                }

                // kolorkiiii
                par->color = parColor;
                par->left->color = BLACK;
                par->right->color = BLACK;

                // usun
                if (delete) {
                    if (for_deletion->left != NULL) {
                        for_deletion->left->parent = par->right;
                    }

                    par->right->right = for_deletion->left;
                    free(for_deletion);
                }
            } else {
                // ananlogiczny przypadek

                int parColor = par->color;

                par = left_rotate(sibling);

                if (par->parent == NULL) {
                    *root = par;
                }

                par->color = parColor;
                par->left->color = BLACK;
                par->right->color = BLACK;

                if (delete) {
                    if (for_deletion->right != NULL) {
                        for_deletion->right->parent = par->left;
                    }

                    par->left->left = for_deletion->left;
                    free(for_deletion);
                }
            }
        } else {
            if (locateChild == 0) {
                int parColor = par->color;

                sibling = right_rotate(sibling->left);

                par = left_rotate(sibling);

                if (par->parent == NULL) {
                    *root = par;
                }

                par->color = parColor;
                par->left->color = BLACK;
                par->right->color = BLACK;

                if (delete) {
                    if (for_deletion->right != NULL) {
                        for_deletion->right->parent = par->left;
                    }

                    par->left->left = for_deletion->right;
                    free(for_deletion);
                }
            } else {

                int parColor = par->color;

                par = right_rotate(sibling);

                if (par->parent == NULL) {
                    *root = par;
                }

                par->color = parColor;
                par->left->color = BLACK;
                par->right->color = BLACK;

                if (delete) {
                    if (for_deletion->left != NULL) {
                        for_deletion->left->parent = par->right;
                    }

                    par->right->right = for_deletion->left;
                    free(for_deletion);
                }
            }
        }
    } else if (sibling->color == BLACK) {
        // zrob brata czerwonym

        sibling->color = RED;

        // Delete if necessary
        if (delete) {
            if (locateChild) {
                for_deletion->parent->right = for_deletion->left;

                if (for_deletion->left != NULL) {
                    for_deletion->left->parent = for_deletion->parent;
                }
            } else {
                for_deletion->parent->left = for_deletion->right;

                if (for_deletion->right != NULL) {
                    for_deletion->right->parent = for_deletion->parent;
                }
            }
        }

        delete_fixup(par, 0, locateChild, root);
    } else {
        // przenies brata wyzej
        if (locateChild) {

            for_deletion->parent->right = for_deletion->left;

            if (for_deletion->left != NULL) {
                for_deletion->left->parent = for_deletion->parent;
            }

            par = right_rotate(sibling);

            if (par->parent == NULL) {
                *root = par;
            }

            par->color = BLACK;
            par->right->color = RED;
            delete_fixup(par->right, 0, 1, root);
        } else {

            for_deletion->parent->left = for_deletion->right;

            if (for_deletion->right != NULL) {
                for_deletion->right->parent = for_deletion->parent;
            }

            par = left_rotate(sibling);

            if (par->parent == NULL) {
                *root = par;
            }

            // printf("\nroot - %d - %d\n", parent->val, parent->left->val);

            par->color = 0;
            par->left->color = 1;
            delete_fixup(par->left, 0, 0, root);
        }
    }

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

void delete (int element, node **root) {
    node *temp_root = *root;

    // szukaj elementu
    while (1) {
        if (element == temp_root->element) {
            // znalezniono
            break;
        }

        if (element > temp_root->element) {
            if (temp_root->right != NULL) {
                temp_root = temp_root->right;
            } else {
                printf("Node nie istnieje");
                return;
            }
        } else {
            if (temp_root->left != NULL) {
                temp_root = temp_root->left;
            } else {
                printf("Node nie istnieje");
                return;
            }
        }
    }

    node *for_deletion = temp_root;

    if (for_deletion->left != NULL) {
        for_deletion = for_deletion->left;

        while (for_deletion->right != NULL) {
            for_deletion = for_deletion->right;
        }
    } else if (for_deletion->right != NULL) {
        for_deletion = for_deletion->right;

        while (for_deletion->left != NULL) {
            for_deletion = for_deletion->left;
        }
    }

    if (for_deletion == *root) {
        *root = NULL;
        return;
    }

    temp_root->element = for_deletion->element;
    for_deletion->element = element;

    // case 1 z cormena
    if (for_deletion->color == RED ||
            (for_deletion->left != NULL && for_deletion->left->color == RED) ||
            (for_deletion->right != NULL && for_deletion->right->color == RED)) {
        // jest lisciem
        if (for_deletion->left == NULL && for_deletion->right == NULL) {
            // po prostu usun
            if (for_deletion->parent->left == for_deletion) {
                for_deletion->parent->left = NULL;
            } else {
                for_deletion->parent->right = NULL;
            }
        } else {

            // czy ma lewego syna
            if (for_deletion->left != NULL) {
                for_deletion->parent->right = for_deletion->left;
                for_deletion->left->parent = for_deletion->parent;
                for_deletion->left->color = RED;
            } else {
                for_deletion->parent->left = for_deletion->right;
                for_deletion->right->parent = for_deletion->parent;
                for_deletion->right->color = RED;
            }
        }

        free(for_deletion);
    } else {
        // przypadek 2 z cormena
        delete_fixup(for_deletion, 1, ((for_deletion->parent->right == for_deletion)), root);
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

    if (root == NULL) {
        root = newnode(element, NULL);
        root->color = BLACK;
    } else {
        insert(element, &root);

    }

    printf("INSERT: [%d]\n\n", element);
    tree_size++;
    print_init();
}

void delete_from_command(int element) {
    if (root != NULL) {
        printf("DELETE: [%d]\n\n", element);
        delete (element, &root);
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
