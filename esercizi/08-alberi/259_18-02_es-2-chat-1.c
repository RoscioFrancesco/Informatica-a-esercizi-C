//
//  main.c
//  es 2 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node *left, *right;
} node;

typedef node* tree;

/* =========================
   PROTOTIPO (DA SVOLGERE TU)
   ========================= */
int contaBuoniOnda(tree T);  // <-- NON IMPLEMENTATA QUI
int onda(float vett[], int len);
/* =========================
   UTILITY: CREA NODO
   ========================= */
tree newNode(int v, tree L, tree R) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) {
        perror("malloc");
        exit(1);
    }
    t->v = v;
    t->left = L;
    t->right = R;
    return t;
}

/* =========================
   STAMPA ALBERO (RUOTATO)
   ========================= */
void printTreeRotated(tree T, int depth) {
    if (T == NULL) return;

    printTreeRotated(T->right, depth + 1);

    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", T->v);

    printTreeRotated(T->left, depth + 1);
}

/* =========================
   FREE ALBERO
   ========================= */
void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

int depth(tree t);
int megawrapper(tree t);
int main(void) {

    /* ============================================================
       TEST 1: Albero perfetto, root “onda”, figli no, foglie sì.
       
               5
             /   \
            8     8
           / \   / \
          1  1  1  1

       Atteso: contaBuoniOnda(T1) = 5
       (radice buona + 4 foglie buone; i due 8 non sono buoni)
       ============================================================ */
    tree T1 =
        newNode(5,
            newNode(8,
                newNode(1, NULL, NULL),
                newNode(1, NULL, NULL)
            ),
            newNode(8,
                newNode(1, NULL, NULL),
                newNode(1, NULL, NULL)
            )
        );

    printf("=== TEST 1: Albero T1 ===\n");
    printTreeRotated(T1, 0);

    int r1 = contaBuoniOnda(T1);
    printf("\nRisultato contaBuoniOnda(T1) = %d\n", r1);
    printf("OUTPUT ATTESO: 5\n\n");


    /* ============================================================
       TEST 2: Quasi-perfetto su più nodi, ma onda fallisce quasi ovunque.

               4
             /   \
            6     2
           /     / \
          1     3   1
                 \
                  0

       Qui (con interpretazione standard):
       - foglie (1 sotto 6), (1 a destra di 2), (0) sono buone (altezza 0).
       - i nodi interni falliscono l'onda (spesso A0 < A1 non vale).
       
       Atteso: contaBuoniOnda(T2) = 3
       ============================================================ */
    tree T2 =
        newNode(4,
            newNode(6,
                newNode(1, NULL, NULL),
                NULL
            ),
            newNode(2,
                newNode(3,
                    NULL,
                    newNode(0, NULL, NULL)
                ),
                newNode(1, NULL, NULL)
            )
        );

    printf("=== TEST 2: Albero T2 ===\n");
    printTreeRotated(T2, 0);

    int r2 = contaBuoniOnda(T2);
    printf("\nRisultato contaBuoniOnda(T2) = %d\n", r2);
    printf("OUTPUT ATTESO: 3\n\n");


    /* Pulizia memoria */
    freeTree(T1);
    freeTree(T2);

    return 0;
}
//le foglie stanno su al massimo due profondità (quasi perfetto) definendo A[i] = media dei valori al livello i (livello 0 = u), la sequenza A deve essere una onda: A[0] < A[1] > A[2] < A[3] > ... (alternanza stretta)

void riempi(tree t,float somme[], int occ[], int livello, int foglie[])
    {
        if(t==NULL)
            return;
    if(t->left==NULL && t->right==NULL)
        {
            foglie[livello]++;
        }
    somme[livello]=somme[livello]+t->v;
    (occ[livello])++;
    livello++;
    riempi(t->left, somme, occ, livello, foglie);
    riempi(t->right, somme, occ, livello, foglie);
    }

int verifica_nodo(tree t)
    {
    int len=depth(t);
    float *media=malloc(sizeof(int)*len);
    float *somme=malloc(sizeof(float)*len);
    int *occ=malloc(sizeof(int)*len);
    int *foglie=malloc(sizeof(int)*len);
    for(int i=0; i<len; i++)
        {
            foglie[i]=0;
            media[i]=0;
            somme[i]=0;
            occ[i]=0;
        }
    riempi(t, somme, occ, 0, foglie);
    int count=0;
    for(int i=0; i<len; i++)
        {
            if(foglie[i]!=0)
                count++;
            if(occ[i]!=0)
            {
                media[i]=somme[i]/occ[i];
            }
            else
                {
                    media[i]=0;
                }
        }
    if(count>2)
        return 0;
    int ris=onda(media, len);
    free(media);
    free(foglie);
    free(somme);
    free(occ);
    return ris;
    }

int max(int a, int b)
    {
    if(a>b)return a;
    return b;
    }
int depth(tree t)
    {
        if(t==NULL)
            return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return max(sx, dx)+1;
    }
int onda(float vett[], int len)
    {
    for(int i=0; i<len-2; i++)
        {
            int a=i;
            int b=i+1;
            int c=i+2;
            if(!(vett[a]<vett[b] &&vett[b]>vett[c]))
                return 0;
        }
    return 1;
    }
void scorri_albero(tree t, int *count)
    {
        if(t==NULL)
            return;
        if(verifica_nodo(t))
            {
                (*count)++;
            }
    scorri_albero(t->left, count);
    scorri_albero(t->right, count);
    }
int contaBuoniOnda(tree t)
    {
    int count=0;
    scorri_albero(t, &count);
    return count;
    }
