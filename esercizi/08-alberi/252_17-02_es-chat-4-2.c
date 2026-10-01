//
//  main.c
//  es chat 4  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node *left, *right;
} node;

typedef node* tree;

int contaNodiConCammino(tree T, int K);

tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->v = x;
    n->left = n->right = NULL;
    return n;
}

void printPreorder(tree T) {
    if (T == NULL) return;
    printf("%d ", T->v);
    printPreorder(T->left);
    printPreorder(T->right);
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================
   MAIN DI TEST
   ========================= */
void scorrialbero(tree t, int *count, int K);
int f(tree t, int somma, int K, int stato_expected);
int stato(int x);


int main(void) {

    /* =========================================================
       TEST 1 (K = 10)

                 5
               /   \
             -2     -3
            /  \      \
           4   -1      6
               /      / \
              2     -4  -5

       Nodi che hanno almeno un cammino u->foglia con:
       - alternanza segno
       - somma assoluta >= 10

       Verifica rapida:
       - da 5:  5->-2->4  (|.|=11) valido  => conta
       - da -3: -3->6->-4 (|.|=13) valido  => conta
       - da 6:  6->-4     (|.|=10) valido  => conta
       Tutti gli altri hanno solo cammini con |somma| < 10 o non alternanti.

       Atteso: 3
       ========================================================= */
    tree T1 = newNode(5);
    T1->left = newNode(-2);
    T1->right = newNode(-3);
    T1->left->left = newNode(4);
    T1->left->right = newNode(-1);
    T1->left->right->left = newNode(2);
    T1->right->right = newNode(6);
    T1->right->right->left = newNode(-4);
    T1->right->right->right = newNode(-5);

    int K1 = 10;
    printf("=== TEST 1 (K=%d) ===\n", K1);
    printf("Preorder: ");
    printPreorder(T1);
    printf("\n");
    printf("contaNodiConCammino(T1, %d) = %d\n\n", K1, contaNodiConCammino(T1, K1));


    /* =========================================================
       TEST 2 (K = 10)

       Catena a destra:
           -7
             \
              3
               \
               -2
                 \
                  9

       Cammini validi e |somma|:
       - da -7: -7->3->-2->9  alterna, |.|=21  => conta
       - da  3:  3->-2->9     alterna, |.|=14  => conta
       - da -2: -2->9         alterna, |.|=11  => conta
       - da  9: solo 9, |.|=9 < 10 => non conta

       Atteso: 3
       ========================================================= */
    tree T2 = newNode(-7);
    T2->right = newNode(3);
    T2->right->right = newNode(-2);
    T2->right->right->right = newNode(9);

    int K2 = 10;
    printf("=== TEST 2 (K=%d) ===\n", K2);
    printf("Preorder: ");
    printPreorder(T2);
    printf("\n");
    printf("contaNodiConCammino(T2, %d) = %d\n\n", K2, contaNodiConCammino(T2, K2));


    /* cleanup */
    freeTree(T1);
    freeTree(T2);

    return 0;
}
//Un cammino è valido se: i valori alternano segno (+, -, +, -, … oppure -, +, -, +, …) e la somma assoluta dei valori nel cammino è ≥ K

int stato(int x)
    {
        if(x>0) return 1;
    return -1;
    }
int f(tree t, int somma, int K, int stato_expected)
    {
        if(t==NULL)
            return 0;
    int val=t->v;
    if(t->v<0)
        val=-t->v;
        somma=somma+val;
        int stato_now=stato(t->v);
        if(stato_now!=stato_expected)
            return 0;
        if(t->left==NULL && t->right==NULL)
            {
                if(somma>=K)
                    return 1;
                return 0;
            }
        int new_expected=-stato_now;
    return f(t->left, somma, K, new_expected) || f(t->right, somma, K, new_expected);
    }
void scorrialbero(tree t, int *count, int K)
    {
        if(t==NULL)
            return;
        if(f(t, 0, K, stato(t->v)))
            (*count)++;
    scorrialbero(t->left, count, K);
    scorrialbero(t->right, count, K);
    }

int contaNodiConCammino(tree T, int K)
{
    int count=0;
    scorrialbero(T, &count, K);
    return count;
}
