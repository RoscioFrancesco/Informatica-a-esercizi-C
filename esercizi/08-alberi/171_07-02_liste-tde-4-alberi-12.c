//
//  main.c
//  liste tde 4 alberi -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node* tree;


int completo(tree t);

/* =========================
   UTILITY PER TEST
   ========================= */
static tree nuovoNodo(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->dato);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN (runnabile)
   ========================= */
int completo1(tree albero);
int profonditàfoglia(tree albero, int profondita, int *prof_prec, int *hasprec);
int main(void) {

    /* Caso 1: albero "perfetto" (dovrebbe essere completo) */
    tree T1 = nuovoNodo(1);
    T1->left = nuovoNodo(2);
    T1->right = nuovoNodo(3);
    T1->left->left = nuovoNodo(4);
    T1->left->right = nuovoNodo(5);
    T1->right->left = nuovoNodo(6);
    T1->right->right = nuovoNodo(7);

    /* Caso 2: albero NON completo (una foglia a profondità diversa / un nodo con un solo figlio) */
    tree T2 = nuovoNodo(10);
    T2->left = nuovoNodo(20);
    T2->right = nuovoNodo(30);
    T2->left->left = nuovoNodo(40);   /* manca left->right => nodo con 1 figlio */

    printf("Albero T1 (preorder): ");
    stampaPreorder(T1);
    printf("\n");

    printf("Albero T2 (preorder): ");
    stampaPreorder(T2);
    printf("\n\n");

    
    printf("T1 completo? %d (ATTESO: 1 se la funzione e' corretta)\n", completo(T1));
    printf("T2 completo? %d (ATTESO: 0 se la funzione e' corretta)\n", completo(T2));

    freeTree(T1);
    freeTree(T2);

    return 0;
}

/* =========================
   STUB: NON SVOLGE L'ESERCIZIO
   ========================= */

int completo1(tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        if(albero->left==NULL || albero->right==NULL)
            return 0;
    return completo1(albero->left) &&completo1(albero->right);
    }
int profonditàfoglia(tree albero, int profondita, int *prof_prec, int *hasprec)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(*hasprec==0)
                    {
                        *prof_prec=profondita;
                        *hasprec=1;
                        return 1;
                    }
                else
                    {
                        if(profondita!=*prof_prec)
                            return  0;
                        return 1;
                    }
            }
        return profonditàfoglia(albero->left, profondita+1, prof_prec, hasprec)&&profonditàfoglia(albero->right, profondita+1, prof_prec, hasprec);
    
    }

int completo(tree t)
    {
    int cond1=completo1(t);
    int prof_prec=0;
    int hasprec=0;
    int ris2=profonditàfoglia(t, 0, &prof_prec, &hasprec);
    return cond1&&ris2;
    }
