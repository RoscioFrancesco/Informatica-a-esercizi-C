//
//  main.c
//  es chat 2 -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ====== TIPO ALBERO ====== */
typedef struct node {
    int v;
    struct node *left, *right;
} node;

typedef node *tree;


int camminoBudget(tree T, int B);
int f(int B, tree albero, int negativi, int pari, char passo_prec, int count);
/* ====== UTILS: crea nodo ====== */
static tree newNode(int v, tree L, tree R) {
    tree t = (tree)malloc(sizeof(node));
    if (t == NULL) {
        perror("malloc");
        exit(1);
    }
    t->v = v;
    t->left = L;
    t->right = R;
    return t;
}

/* ====== UTILS: stampa (preorder) ====== */
static void printPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->v);
    printPreorder(t->left);
    printPreorder(t->right);
}

/* ====== UTILS: libera albero ====== */
static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* ====== ESEMPIO DI ALBERO PER TEST ======
           5
         /   \
       -2     4
      / \    / \
     7  -6  8  -1
*/
static tree buildExampleTree(void) {
    tree n7  = newNode(7, NULL, NULL);
    tree n_6 = newNode(-6, NULL, NULL);
    tree n8  = newNode(8, NULL, NULL);
    tree n_1 = newNode(-1, NULL, NULL);

    tree n_2 = newNode(-2, n7, n_6);
    tree n4  = newNode(4, n8, n_1);

    tree n5  = newNode(5, n_2, n4);
    return n5;
}

/* ====== MAIN ====== */
int main(void) {
    tree T = buildExampleTree();

    printf("Albero (preorder con NULL): ");
    printPreorder(T);
    printf("\n\n");

    int Bvals[] = {0, 1, 2, 3};
    int nB = (int)(sizeof(Bvals) / sizeof(Bvals[0]));

    for (int i = 0; i < nB; i++) {
        int B = Bvals[i];
        int ok = camminoBudget(T, B);  
        printf("B=%d -> camminoBudget = %d\n", B, ok);
    }

    freeTree(T);
    return 0;
}
int f(int B, tree albero, int negativi, int pari, char passo_prec, int count)
    {
        if(albero==NULL)
            return 0;
        if(albero->v%2==0)
            pari++;
        if(albero->v<0)
            negativi++;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(B>=count && pari==negativi)
                    return 1;
                return 0;
            }
    int sx=0;
    int dx=0;
    int countdx=count;
    int countsx=count;
        if(albero->left!=NULL)
            {
                if(passo_prec=='d')
                    countsx++;
                sx=f(B, albero->left, negativi, pari, 's', countsx);
            }
        if(albero->right!=NULL)
            {
                if(passo_prec=='s')
                    countdx++;
                dx=f(B, albero->right, negativi, pari, 'd', countdx);
            }
    return sx||dx;
    }

int camminoBudget(tree T, int B)
    {
    if(T==NULL)
        return 0;
    return f(B, T, 0, 0, 'a', 0);
    }
