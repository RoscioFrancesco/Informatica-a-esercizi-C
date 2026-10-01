//  Created by Francesco Roscio Ricon on 11/02/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int v;
    struct node *left, *right;
} Node;

typedef Node *Tree;
void percorsofromhere(Tree t, int count_cambi, int dir_prec, int sommavalori, int *max);
int percorsoMigliore(Tree t);

static Tree newNode(int v) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = v;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void stampaPreorder(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%d ", t->v);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* stampa valore + indirizzo nodo (debug) */
static void stampaPreorderAddr(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("(%d@%p) ", t->v, (void*)t);
    stampaPreorderAddr(t->left);
    stampaPreorderAddr(t->right);
}
void wrapper(Tree t, int *max);

int main(void) {
    /*
            10
           /  \
          5    8
         / \    \
        2   7    4
           /    / \
          6    1   3

    (Esempio fatto apposta per avere più percorsi con cambi direzione diversi)
    */
    Tree t = newNode(10);
    t->left = newNode(5);
    t->right = newNode(8);

    t->left->left = newNode(2);
    t->left->right = newNode(7);
    t->left->right->left = newNode(6);

    t->right->right = newNode(4);
    t->right->right->left = newNode(1);
    t->right->right->right = newNode(3);

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    printf("Albero (preorder con indirizzi): ");
    stampaPreorderAddr(t);
    printf("\n\n");
    
    int best = percorsoMigliore(t);
    printf("percorsoMigliore(t) = %d\n", best);

    freeTree(t);
    return 0;
}


int percorsoMigliore(Tree t) {
    int max=0;
    wrapper(t, &max);
    return max;
}
void percorsofromhere(Tree t, int count_cambi, int dir_prec, int sommavalori, int *max) // dirprec=1 viene da sx, -1 viene da dx
    {
        if(t==NULL)
            return;
        sommavalori=sommavalori+t->v;
        int val=sommavalori-(count_cambi)*count_cambi;
        if(*max<val)
            *max=val;
        int cambisx=count_cambi;
        int cambidx=count_cambi;
        if(t->left!=NULL)
            {
                if(dir_prec==-1)
                    cambisx++;
                percorsofromhere(t->left, cambisx, 1, sommavalori, max);
            }
        if(t->right!=NULL)
            {
                if(dir_prec==1)
                    cambidx++;
                percorsofromhere(t->right, cambidx, -1, sommavalori, max);
            }
    }
void wrapper(Tree t, int *max)
    {
    if(t==NULL)
        return;
    int ris=0;
    percorsofromhere(t, 0, 0, 0, &ris);
    if(*max<ris)
        *max=ris;
    wrapper(t->left, max);
    wrapper(t->right, max);
    }
