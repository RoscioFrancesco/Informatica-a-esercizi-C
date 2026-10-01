//
//  main.c
//  alberi es 13b
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* =========================
   STRUTTURE NECESSARIE
   ========================= */
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* Tree;

/* =========================
   UTILITY: CREAZIONE / FREE
   ========================= */
static Node* node_new(int value, Node *left, Node *right) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->value = value;
    n->left = left;
    n->right = right;
    return n;
}

static void tree_free(Tree t) {
    if (!t) return;
    tree_free(t->left);
    tree_free(t->right);
    free(t);
}

/* Debug: inorder (ricorsiva) */
static void print_inorder(Tree t) {
    if (!t) return;
    print_inorder(t->left);
    printf("%d ", t->value);
    print_inorder(t->right);
}

/* Stampa pattern (ricorsiva, no cicli) */
static void print_pattern_rec(const int *p, int n, int i) {
    if (i >= n) return;
    printf("%d", p[i]);
    if (i + 1 < n) {
        printf(", ");
        print_pattern_rec(p, n, i + 1);
    }
}
static void print_pattern(const int *p, int n) {
    printf("[");
    print_pattern_rec(p, n, 0);
    printf("]");
}

/* =========================
   PROTOTIPI (come vuoi tu)
   ========================= */
int pattern_cammino(Tree t, int pattern[], int n);
int f(Tree t, int v[], int segna, int len);



/* =========================
   RUN TEST: stampa atteso + ottenuto
   ========================= */
static void run_test(const char *name, Tree t, int pattern[], int n, int expected) {
    int got = pattern_cammino(t, pattern, n);

    printf("=== %s ===\n", name);
    printf("Inorder albero (debug): ");
    print_inorder(t);
    printf("\nPattern               : ");
    print_pattern(pattern, n);
    printf("\nAtteso                : %d\n", expected);
    printf("Ottenuto              : %d\n", got);
    printf("Esito                 : %s\n\n", (got == expected) ? "OK" : "FAIL");

    assert(got == expected);
}

/* =========================
   MAIN con ESEMPI
   ========================= */
int main(void) {
    /*
     Albero base:
     1
     /   \
     2     3
     / \     \
     4   5     6
     \
     7
     
     Cammini radice->foglia:
     [1,2,4]
     [1,2,5,7]
     [1,3,6]
     */
    Tree t = node_new(1,
                      node_new(2,
                               node_new(4, NULL, NULL),
                               node_new(5, NULL,
                                        node_new(7, NULL, NULL))),
                      node_new(3,
                               NULL,
                               node_new(6, NULL, NULL)));
    
    int p1[] = {1,2,4};
    run_test("Test1 (match 1-2-4)", t, p1, 3, 1);
    
    int p2[] = {1,2,5,7};
    run_test("Test2 (match 1-2-5-7)", t, p2, 4, 1);
    
    int p3[] = {1,3,6};
    run_test("Test3 (match 1-3-6)", t, p3, 3, 1);
}

int pattern_cammino(Tree t, int pattern[], int n)
    {
    int segna=0;
    int len = n;
    return f(t, pattern, segna, len);
    }

int f(Tree t, int v[], int segna, int len)
    {
        if(t==NULL)
            return 0;
        if(v[segna]!=t->value)
            return 0;
        (segna)++;
        if(t->left==NULL &&t->right==NULL)
            {
                if(segna==len)
                    return 1;
                return 0;
            }
    return f(t->left, v, segna, len)|| f(t->right, v, segna, len);
    }

