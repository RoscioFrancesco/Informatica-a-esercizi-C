//  Created by Francesco Roscio Ricon on 08/02/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct ET {
    int dato;
    struct ET *left;
    struct ET *center;
    struct ET *right;
} treeNode;

typedef treeNode *tree;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO
   ========================= */
int cerca(tree t, int totale);

/* =========================
   STUB (solo per compilare)
   === DA TOGLIERE QUANDO SVOLGI ===
   ========================= */
int cerca(tree t, int totale);

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */
static tree nuovoNodo(int valore) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = valore;
    n->left = NULL;
    n->center = NULL;
    n->right = NULL;
    return n;
}

static int èFoglia(tree t) {
    return (t != NULL &&
            t->left == NULL &&
            t->center == NULL &&
            t->right == NULL);
}

static void stampaCammini(tree t, int somma, int livello) {
    if (t == NULL)
        return;

    somma += t->dato;

    if (èFoglia(t)) {
        printf("Foglia raggiunta (livello %d) → somma cammino = %d\n",
               livello, somma);
        return;
    }

    stampaCammini(t->left, somma, livello + 1);
    stampaCammini(t->center, somma, livello + 1);
    stampaCammini(t->right, somma, livello + 1);
}

static void freeTree(tree t) {
    if (t == NULL)
        return;
    freeTree(t->left);
    freeTree(t->center);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
void contafoglie(tree albero, int *count);
void riempivettore(int v[], tree albero, int somma, int *segna);
int main(void) {
    /*
        Costruzione albero ternario:

                 5
           /      |      \
          3       2       4
        /   \              \
       1     4              6

    Cammini:
    5-3-1   → somma 9
    5-3-4   → somma 12
    5-2     → somma 7
    5-4-6   → somma 15
    */

    tree t = nuovoNodo(5);
    t->left = nuovoNodo(3);
    t->center = nuovoNodo(2);
    t->right = nuovoNodo(4);

    t->left->left = nuovoNodo(1);
    t->left->right = nuovoNodo(4);

    t->right->right = nuovoNodo(6);

    printf("=== Cammini radice → foglie ===\n");
    stampaCammini(t, 0, 0);

    int totale = 12;
    int esito = cerca(t, totale);

    printf("\nRisultato cerca(t, %d) = %d\n", totale, esito);

    freeTree(t);
    return 0;
}
int *inizializza(int k)
    {
    int *v=malloc(sizeof(int)*k);
    for(int i=0; i<k; i++)
        v[i]=0;
    return v;
    }
void contafoglie(tree albero, int *count)
    {
        if(albero==NULL)
            return;
        if(albero->left==NULL && albero->right==NULL && albero->center==NULL)
            (*count)++;
    contafoglie(albero->center, count);
    contafoglie(albero->left, count);
    contafoglie(albero->right, count);
    }
void riempivettore(int v[], tree albero, int somma, int *segna)
    {
        if(albero==NULL)
            return;
        somma=somma+albero->dato;
    if(albero->left==NULL && albero->right==NULL && albero->center==NULL)
        {
            v[*segna]=somma;
            (*segna)++;
        }
    riempivettore(v, albero->left, somma, segna);
    riempivettore(v, albero->right, somma, segna);
    riempivettore(v, albero->center, somma, segna);
    }
int cerca(tree t, int totale)
    {
    if(t==NULL)
        return 0;
    int len=0;
    contafoglie(t, &len);
    int *vett=inizializza(len);
    int segna=0;
    riempivettore(vett, t, 0, &segna);
    int contatore=0;
    for(int i=0; i<len; i++)
        {
            if(vett[i]==totale)
                contatore++;
        }
    free(vett);
    if(contatore>=2)
        return 1;
    return 0;
    }
