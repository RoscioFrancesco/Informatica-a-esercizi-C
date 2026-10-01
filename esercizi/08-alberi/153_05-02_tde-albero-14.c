//
//  main.c
//  tde albero-14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA ALBERO BINARIO
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* Tree;

/* =========================
   PROTOTIPO FUNZIONE
   ========================= */
int larghezza(Tree t);   

/* =========================
   FUNZIONE DI SUPPORTO
   ========================= */
Tree newNode(int val, Tree left, Tree right) {
    Tree n = (Tree)malloc(sizeof(node));
    if (n == NULL) {
        perror("malloc");
        exit(1);
    }
    n->dato = val;
    n->left = left;
    n->right = right;
    return n;
}

/* =========================
   MAIN
   ========================= */
int profmax(Tree albero);
int max(int a, int b);
int *vettore(int k);
int larghezza(Tree t);
int *riempivettore(Tree albero);
void f(Tree albero, int v[], int profondità);

int main() {

    /*
              1
             / \
            2   3
           / \   \
          4   5   6
    */

    Tree t =
        newNode(1,
            newNode(2,
                newNode(4, NULL, NULL),
                newNode(5, NULL, NULL)
            ),
            newNode(3,
                NULL,
                newNode(6, NULL, NULL)
            )
        );

    printf("Larghezza dell'albero: %d\n", larghezza(t));

    return 0;
}

/* =========================
   STUB DELLA FUNZIONE
   ========================= */


int *vettore(int k)
    {
    int*vettore=malloc(sizeof(int)*k);
    for(int i=0; i<k; i++)
        {
            vettore[i]=0;
        }
    return vettore;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int profmax(Tree albero)
    {
        if(albero==NULL)
            return 0;
        int sx=profmax(albero->left);
        int dx=profmax(albero->right);
    return max(sx, dx)+1;
    }
void f(Tree albero, int v[], int profondità)
    {
    if (albero==NULL) {
        return;
        }
    v[profondità]++;
    f(albero->left, v, profondità+1);
    f(albero->right, v, profondità+1);
    }
int *riempivettore(Tree albero)
    {
        int depth=profmax(albero);
        int *v=vettore(depth);
        f(albero, v, 0);
    return v;
    }
int larghezza(Tree t)
    {
    if(t==NULL)
        return 0;
    int len=profmax(t);
    int *v=riempivettore(t);
    int max=0;
    for(int i=0; i<len; i++)
        {
            if(v[i]>max)
                max=v[i];
        }
    free(v);
    return max;
    }
