//
//  main.c
//  es chat 5  -2
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

int contaParityStabili(tree T);
int depth(tree t);
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

int main(void) {

    /* =====================================================
       TEST 1

           2
          / \
         4   6

       - Nodo 2: livelli ok, ma profondità max = 1 (dispari) => NON parity-stabile
       - Nodi 4 e 6: foglie, profondità max = 0 (pari), livello0 pari>=dispari => SI

       Atteso: 2
       ===================================================== */
    tree T1 = newNode(2);
    T1->left = newNode(4);
    T1->right = newNode(6);

    printf("=== TEST 1 ===\n");
    printf("Preorder: ");
    printPreorder(T1);
    printf("\n");
    printf("contaParityStabili(T1) = %d\n\n", contaParityStabili(T1));


    /* =====================================================
       TEST 2

             5
            / \
           2   8
          /
         4

       - Nodo 5: livello0 ha 1 dispari e 0 pari => viola subito => NO
       - Nodo 2: livelli ok, ma profondità max = 1 (dispari) => NO
       - Nodo 8: foglia => SI
       - Nodo 4: foglia => SI

       Atteso: 2
       ===================================================== */
    tree T2 = newNode(5);
    T2->left = newNode(2);
    T2->right = newNode(8);
    T2->left->left = newNode(4);

    printf("=== TEST 2 ===\n");
    printf("Preorder: ");
    printPreorder(T2);
    printf("\n");
    printf("contaParityStabili(T2) = %d\n\n", contaParityStabili(T2));


    /* =====================================================
       TEST 3 (esempio con nodo interno valido)

              2
             / \
            3   4
           / \
          6   8

       - Nodo 2:
         profondità max = 2 (pari)
         livello0: {2} pari1>=dispari0 ok
         livello1: {3,4} pari1>=dispari1 ok
         livello2: {6,8} pari2>=dispari0 ok
         => SI

       - Nodo 3: livello0 dispari1>pari0 => NO (e profondità max=1 dispari)
       - Foglie 4,6,8: SI

       Atteso: 4
       ===================================================== */
    tree T3 = newNode(2);
    T3->left = newNode(3);
    T3->right = newNode(4);
    T3->left->left = newNode(6);
    T3->left->right = newNode(8);

    printf("=== TEST 3 ===\n");
    printf("Preorder: ");
    printPreorder(T3);
    printf("\n");
    printf("contaParityStabili(T3) = %d\n\n", contaParityStabili(T3));

    
    printf("\n\n%d", depth(T3));

    /* cleanup */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);

    return 0;
}

int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree t)
    {
        if(t==NULL)
            return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return 1+max(sx, dx);
    }
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return 0;
    }

void riempivettoresottoalbero(tree t, int vett[], int depth)
    {
        if(t==NULL)
            {
                return;
            }
        if(èpari(t->v))
            vett[depth]++;
        else
            {
                vett[depth]--;
            }
    riempivettoresottoalbero(t->left, vett, depth+1);
    riempivettoresottoalbero(t->right, vett, depth+1);
    }
int verificanodo(tree t)
    {
    int len=depth(t);
    int *vett=malloc(sizeof(int)*len);
    for(int i=0; i<len; i++)
        {
            vett[i]=0;
        }
    riempivettoresottoalbero(t, vett, 0);
    if(len%2==0)
        return 0;
    for(int i=0; i<len; i++)
        {
            if(vett[i]<0)
            {
                free(vett);
                return 0;
            }
        }
    free(vett);
    return 1;
    }
void wrapper(tree t, int *count)
    {
        if(t==NULL)
            return;
        if(verificanodo(t))
            (*count)++;
    wrapper(t->left, count);
    wrapper(t->right, count);
    }
int contaParityStabili(tree T)
    {
    int count=0;
    wrapper(T, &count);
    return count;
    }
