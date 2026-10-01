//  Created by Francesco Roscio Ricon on 05/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* =========================
   STRUTTURE DATI
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

/* =========================
   PROTOTIPO FUNZIONE RICHIESTA
   ========================= */
int numeroValoriDistinti(tree t);


/* =========================
   FUNZIONI DI SUPPORTO (solo per test)
   ========================= */
node* newNode(int valore) {
    node *n = (node*)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = valore;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void stampaInOrder(tree t) {
    if (t == NULL)
        return;
    stampaInOrder(t->left);
    printf("%d ", t->dato);
    stampaInOrder(t->right);
}

void freeTree(tree t) {
    if (t == NULL)
        return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
void trovaval(tree albero, tree nodo_mio, int *count);
void scorrialbero(tree albero, int *distinti, tree root);
int f(tree albero);
int main(void) {

    /*
        Albero di esempio:

                5
              /   \
             3     7
            / \     \
           3   4     5

        Valori presenti: {3,4,5,7}
        Valori distinti = 4
    */

    tree t = newNode(5);
    t->left = newNode(3);
    t->right = newNode(7);
    t->left->left = newNode(3);
    t->left->right = newNode(4);
    t->right->right = newNode(5);

    printf("Visita inorder dell'albero:\n");
    stampaInOrder(t);
    printf("\n");

    printf("\nChiamata a numeroValoriDistinti(t)...\n");
    int risultato = f(t);

    printf("Numero di valori distinti: %d\n", risultato);

    freeTree(t);
    return 0;
}

/* =========================
   STUB (NON SVOLGO L'ESERCIZIO)
   ========================= */
int nodi(tree albero)
    {
        if(albero==NULL)
            return 0;
    return 1+nodi(albero->left)+nodi(albero->right);
    }

int *vett(int k)
    {
    int *v=malloc(sizeof(int)*k);
    for(int i=0; i<k; i++)
    {v[i]=0;
    }
    return v;
}
void riempivettore(tree albero, int v[], int *contatore)
    {
        if(albero==NULL)
            return;;
        v[*contatore]=albero->dato;
        (*contatore)++;
    riempivettore(albero->left, v,contatore);
    riempivettore(albero->right, v, contatore);
    }

void merge(int v[], int prof)
    {
    for(int i=0; i<prof; i++)
        {
            for(int j=i+1; j<prof; j++)
                {
                    if(v[i]>v[j])
                        {
                            int temp=v[i];
                            v[i]=v[j];
                            v[j]=temp;
                        }
                }
        }
    }

int f(tree albero)
    {
    if(albero==NULL)
        return 0;
    if(albero->left==NULL && albero->right==NULL)
        return 1;
        int depth=nodi(albero);
        int *v=vett(depth);
        int contatore=0;
        riempivettore(albero, v, &contatore);
        merge(v, depth);
        int ris=0;
        for(int i=0; i<depth-1; i++)
            {
                if(v[i]!=v[i+1])
                    ris++;
            }
    free(v);
    return ris+1;
    }
