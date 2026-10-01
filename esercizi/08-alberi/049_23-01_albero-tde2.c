//  Created by Francesco Roscio Ricon on 23/01/26.
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node* tree;

/* ---------- Funzioni di supporto ---------- */

tree newNode(int val) {
    tree n = (tree)malloc(sizeof(node));
    if (n == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->dato = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* ---------- MAIN DI TEST ---------- */

int wrapper_nodiinterni(tree albero);
void calcolaalbero_interni(tree albero, int *somma);
int wrapper_nodifoglia(tree albero);
void calcolaalbero_nodifoglia(tree albero, int *somma);
int cercavalore(tree albero, int valore);
int verifica(tree alberoA, tree alberoB);

int main() {

    /*
        Costruiamo TA:

              10
             /  \
            3    7
           / \
          1   2

        Nodi interni TA = 10 + 3 = 13
        (foglie: 1,2,7 non contano)

        Quindi sommaInterniTA = 13
    */

    tree TA = newNode(10);
    TA->left = newNode(3);
    TA->right = newNode(7);
    TA->left->left = newNode(1);
    TA->left->right = newNode(2);

    /*
        Costruiamo TB:

              5
             / \
            4   6
               / \
              2   3

        Foglie TB = 4 + 2 + 3 = 9
        Quindi sommaFoglieTB = 9

        Per far tornare la condizione, mettiamo in TA un nodo con valore 9
        (esempio: aggiungiamo un figlio a destra del 7)
    */

    TA->right->right = newNode(9);  // così TA contiene 9 ✅

    /*
        Ora dobbiamo far sì che TB contenga 13 (somma nodi interni di TA)

        Aggiungiamo un nodo 13 in TB:
    */
    tree TB = newNode(5);
    TB->left = newNode(4);
    TB->right = newNode(6);
    TB->right->left = newNode(2);
    TB->right->right = newNode(3);

    TB->left->left = newNode(13);   // così TB contiene 13 ✅



    if (verifica(TA, TB))
        printf("RISULTATO: 1 ✅ (condizioni verificate)\n");
    else
        printf("RISULTATO: 0 ❌ (condizioni NON verificate)\n");

    freeTree(TA);
    freeTree(TB);

    return 0;
}

void calcolaalbero_nodifoglia(tree albero, int *somma)
    {
    if(albero==NULL)
        return;
    if(albero->left==NULL && albero->right==NULL)
        *somma=*somma+albero->dato;
    calcolaalbero_nodifoglia(albero->left, somma);
    calcolaalbero_nodifoglia(albero->right, somma);
}

int wrapper_nodifoglia(tree albero)
    {
    int somma=0;
    calcolaalbero_nodifoglia(albero, &somma);
    return somma;
    }

void calcolaalbero_interni(tree albero, int *somma)
    {
        if(albero==NULL)
            return;
        if(albero->left!=NULL || albero->right!=NULL)
            *somma=*somma+albero->dato;
    calcolaalbero_interni(albero->left, somma);
    calcolaalbero_interni(albero->right, somma);
    }
int wrapper_nodiinterni(tree albero)
    {
    int somma=0;
    calcolaalbero_interni(albero, &somma);
    return somma;
    }

int cercavalore(tree albero, int valore)
    {
        if(albero==NULL)
            return 0;
        if(albero->dato==valore)
            return 1;
    return cercavalore(albero->left, valore)&& cercavalore(albero->right, valore);
    }

int verifica(tree alberoA, tree alberoB)
    {
    int sommanodifogliaTB=wrapper_nodifoglia(alberoB);
    int sommanodiinterniTA=wrapper_nodiinterni(alberoA);
    return cercavalore(alberoA, sommanodifogliaTB) && cercavalore(alberoB, sommanodiinterniTA);
    }
