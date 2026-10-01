//
//  main.c
//  alberi es 13
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    if (!n) {
        perror("malloc");
        exit(1);
    }
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
int foglie_stessa_profondita(Tree t);

/* =========================
   MAIN + TEST
   ========================= */
int foglie_stessa_profondita(Tree t);
int f(Tree t, int livello, int *profondità, int *flag);
int main(void) {
    /*
      Test 1: albero vuoto
      Scelta tipica: vero (1), perché non ci sono foglie che violano la proprietà.
    */
    Tree t0 = NULL;
    assert(foglie_stessa_profondita(t0) == 1);

    /*
      Test 2: singolo nodo (radice = foglia) -> tutte le foglie (una sola) stessa profondità
          7
      Profondità foglia: 0 (se la radice è a profondità 0)
      => 1
    */
    Tree t1 = node_new(7, NULL, NULL);
    assert(foglie_stessa_profondita(t1) == 1);
    tree_free(t1);

    /*
      Test 3: albero perfetto, foglie tutte a profondità 2 -> OK
              1
            /   \
           2     3
          / \   / \
         4  5  6  7
      => 1
    */
    Tree t2 = node_new(1,
                node_new(2,
                    node_new(4, NULL, NULL),
                    node_new(5, NULL, NULL)),
                node_new(3,
                    node_new(6, NULL, NULL),
                    node_new(7, NULL, NULL)));
    assert(foglie_stessa_profondita(t2) == 1);
    tree_free(t2);

    /*
      Test 4: NON tutte le foglie alla stessa profondità -> FAIL
              1
            /   \
           2     3
          /
         4
      Foglie: 4 a profondità 2, 3 a profondità 1
      => 0
    */
    Tree t3 = node_new(1,
                node_new(2,
                    node_new(4, NULL, NULL),
                    NULL),
                node_new(3, NULL, NULL));
    assert(foglie_stessa_profondita(t3) == 0);
    tree_free(t3);

    /*
      Test 5: catena (solo un cammino) -> c'è una sola foglia -> OK
          1
           \
            2
             \
              3
               \
                4
      => 1
    */
    Tree t4 = node_new(1, NULL,
                node_new(2, NULL,
                    node_new(3, NULL,
                        node_new(4, NULL, NULL))));
    assert(foglie_stessa_profondita(t4) == 1);
    tree_free(t4);

    /*
      Test 6: due foglie a profondità diversa -> FAIL
              10
             /  \
            5    20
                 /
                15
      Foglie: 5 a profondità 1, 15 a profondità 2
      => 0
    */
    Tree t5 = node_new(10,
                node_new(5, NULL, NULL),
                node_new(20,
                    node_new(15, NULL, NULL),
                    NULL));
    assert(foglie_stessa_profondita(t5) == 0);
    tree_free(t5);

    /*
      Test 7: tutte le foglie alla stessa profondità, ma albero non perfetto (nodi mancanti interni)
              1
            /   \
           2     3
            \   /
             5 6
      Foglie: 5 e 6 a profondità 2
      => 1
    */
    Tree t6 = node_new(1,
                node_new(2,
                    NULL,
                    node_new(5, NULL, NULL)),
                node_new(3,
                    node_new(6, NULL, NULL),
                    NULL));
    assert(foglie_stessa_profondita(t6) == 1);
    tree_free(t6);

    /*
      Test 8: tre foglie, una a profondità diversa -> FAIL
              1
            /   \
           2     3
          /     / \
         4     6   7
              /
             8
      Foglie: 4 a prof 2, 7 a prof 2, 8 a prof 3
      => 0
    */
    Tree t7 = node_new(1,
                node_new(2,
                    node_new(4, NULL, NULL),
                    NULL),
                node_new(3,
                    node_new(6,
                        node_new(8, NULL, NULL),
                        NULL),
                    node_new(7, NULL, NULL)));
    assert(foglie_stessa_profondita(t7) == 0);
    tree_free(t7);

    printf("Tutti i test passati.\n");
    return 0;
}

int f(Tree t, int livello, int *profondità, int *flag)
    {
        if(t==NULL)
            return 1;
        if(t->left==NULL && t->right==NULL)
            {
                if(*flag==0)
                {
                    *profondità=livello;
                    *flag=1;
                    return 1;
                }
                else
                    {
                        if(*profondità==livello)
                            return 1;
                        return 0;
                    }
            }
    return f(t->left, livello+1, profondità, flag) && f(t->right, livello+1, profondità, flag);
    }

int foglie_stessa_profondita(Tree t)
    {
    if(t==NULL)
        return 1;
    if(t->left==NULL && t->right==NULL)
        return 1;
    int flag=0;
    int profondità=0;
    return f(t, 0, &profondità, &flag);
    }
