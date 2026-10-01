//
//  main.c
//  tde 3 alberi -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct ET {
    int *dato;              /* valore dinamico */
    struct ET *left;
    struct ET *right;
} treeNode;

typedef treeNode *tree;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO
   ========================= */
int ksimilare(tree t1, tree t2, int k);

static tree nuovoNodo(int valore) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = (int *)malloc(sizeof(int));
    if (!n->dato) {
        perror("malloc");
        exit(1);
    }
    *(n->dato) = valore;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaPerLivelli(tree t, int livello) {
    if (t == NULL)
        return;
    printf("Livello %d -> valore %d\n", livello, *(t->dato));
    stampaPerLivelli(t->left, livello + 1);
    stampaPerLivelli(t->right, livello + 1);
}

static void freeTree(tree t) {
    if (t == NULL)
        return;
    freeTree(t->left);
    freeTree(t->right);
    free(t->dato);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /* Costruzione primo albero */
    tree t1 = nuovoNodo(5);
    t1->left = nuovoNodo(3);
    t1->right = nuovoNodo(7);
    t1->left->left = nuovoNodo(2);
    t1->left->right = nuovoNodo(1);

    /* Costruzione secondo albero */
    tree t2 = nuovoNodo(4);
    t2->left = nuovoNodo(6);
    t2->right = nuovoNodo(2);
    t2->right->right = nuovoNodo(3);

    printf("=== Albero t1 ===\n");
    stampaPerLivelli(t1, 0);

    printf("\n=== Albero t2 ===\n");
    stampaPerLivelli(t2, 0);

    int k = 2;
    int esito = ksimilare(t1, t2, k);

    printf("\nksimilare(t1, t2, %d) = %d\n", k, esito);

    /* Deallocazione */
    freeTree(t1);
    freeTree(t2);

    return 0;
}

int max(int a, int b)
    {
    if(a>b)
        return a;
    return b;
}
int depth(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=depth(albero->right);
    int dx=depth(albero->left);
    return max(sx, dx)+1;
    }
int *vett(int k)
    {
    int *v=malloc(sizeof(int)*k);
    for(int i=0; i<k; i++)
        {
            v[i]=0;
        }
    return v;
    }
void riempialbero(int vett[], tree albero, int livello)
    {
        if(albero==NULL)
            return;
    vett[livello]=vett[livello]+(*albero->dato);
    riempialbero(vett, albero->left, livello+1);
    riempialbero(vett, albero->right, livello+1);
    }
int ksimilare(tree a1, tree a2, int K)
    {
    int len1=depth(a1);
    int len2=depth(a2);
    int*v1=vett(len1);
    int *v2=vett(len2);
    riempialbero(v1, a1, 0);
    riempialbero(v2, a2, 0);
    int count=0;
    for(int i=0; i<len1; i++)
        {
            for(int j=0; j<len2; j++)
                {
                    if(v1[i]==v2[j])
                        count++;
                }
        }
        if(K>count)
            return 1;
    return 0;
    }
