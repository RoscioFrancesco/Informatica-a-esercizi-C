//
//  main.c
//  alberi es 12
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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

static void tree_free(Node *root) {
    if (!root) return;
    tree_free(root->left);
    tree_free(root->right);
    free(root);
}


int wrappermin(Tree t);
void trovamin(Tree t, int *min);
int f(Tree t, int k, int flag);
int check_paths_contain_min(Tree t, int m);
int minimo_obbligatorio(Tree t);

int main(void) {
    /*
      Test 1:  minimo = 1 presente in ogni cammino
            2
           / \
          1   3
             /
            1
      Cammini:
        2-1 (contiene 1) OK
        2-3-1 (contiene 1) OK
      => 1
    */
    Node *t1 = node_new(2,
                    node_new(1, NULL, NULL),
                    node_new(3,
                             node_new(1, NULL, NULL),
                             NULL));
    assert(minimo_obbligatorio(t1) == 1);
    tree_free(t1);

    /*
      Test 2: minimo = 1 NON presente in un cammino
            2
           / \
          1   3
               \
                4
      Cammini:
        2-1 (contiene 1) OK
        2-3-4 (NON contiene 1) FAIL
      => 0
    */
    Node *t2 = node_new(2,
                    node_new(1, NULL, NULL),
                    node_new(3,
                             NULL,
                             node_new(4, NULL, NULL)));
    assert(minimo_obbligatorio(t2) == 0);
    tree_free(t2);

    /*
      Test 3: minimo = 5 (tutti i nodi sono 5) => ovviamente presente
            5
           / \
          5   5
      => 1
    */
    Node *t3 = node_new(5,
                    node_new(5, NULL, NULL),
                    node_new(5, NULL, NULL));
    assert(minimo_obbligatorio(t3) == 1);
    tree_free(t3);

    /*
      Test 4: albero a catena, minimo in fondo -> unico cammino lo contiene
        10
          \
           7
            \
             3
              \
               1
      => 1
    */
    Node *t4 = node_new(10, NULL,
                    node_new(7, NULL,
                        node_new(3, NULL,
                            node_new(1, NULL, NULL))));
    assert(minimo_obbligatorio(t4) == 1);
    tree_free(t4);

    /*
      Test 5: radice è il minimo, quindi presente in ogni cammino
            0
           / \
          2   3
             / \
            4   5
      => 1
    */
    Node *t5 = node_new(0,
                    node_new(2, NULL, NULL),
                    node_new(3,
                             node_new(4, NULL, NULL),
                             node_new(5, NULL, NULL)));
    assert(minimo_obbligatorio(t5) == 1);
    tree_free(t5);

    /*
      Test 6: albero vuoto (scelta: vero) => 1
    */
    Node *t6 = NULL;
    assert(minimo_obbligatorio(t6) == 1);

    printf("Tutti i test passati.\n");
    return 0;
}
int minimo_obbligatorio(Tree t) {
    if (!t) return 1;
    int m = wrappermin(t);
    return check_paths_contain_min(t,m);
}
void trovamin(Tree t, int *min)
    {
        if(t==NULL)
            return;
        if(*min>=t->value)
            *min=t->value;
    trovamin(t->left, min);
    trovamin(t->right, min);
    }
int wrappermin(Tree t)
    {
    int min=t->value;
    trovamin(t, &min);
    return min;
    }
int f(Tree t, int k, int flag)
    {
        if(t==NULL)
            return 1;
        if(k==t->value)
            flag=1;
        if(t->left==NULL && t->right==NULL)
        {
            if(flag==1)
                return 1;
            return 0;
        }
    return f(t->left, k, flag) && f(t->right, k, flag);
    }
int check_paths_contain_min(Tree t, int m)
    {
    return f(t, m, 0);
    }
