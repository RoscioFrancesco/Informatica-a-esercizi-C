//  Created by Francesco Roscio Ricon on 12/02/26.
#include <stdio.h>
#include <stdlib.h>

/* ===== STRUTTURE ===== */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node *tree;


int stessiValori(tree A, tree B);   // <-- NON IMPLEMENTATA QUI


/* ===== SUPPORTO: CREAZIONE / STAMPA / DEALLOCAZIONE ===== */
tree newNode(int x) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) exit(1);
    t->dato = x;
    t->left = t->right = NULL;
    return t;
}

void printPreOrder(tree T) {
    if (!T) return;
    printf("%d ", T->dato);
    printPreOrder(T->left);
    printPreOrder(T->right);
}

void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* ===== MAIN DI TEST ===== */
void riempivett(tree albero ,int v[], tree root, int len);
int main(void) {

    /*
        A: multinsieme = {1,1,2,3}

              1
             / \
            2   1
           /
          3
    */
    tree A = newNode(1);
    A->left = newNode(2);
    A->right = newNode(1);
    A->left->left = newNode(3);

    /*
        B: stesso multinsieme {1,1,2,3} ma struttura diversa e #nodi diverso? (qui uguale)
            2
           / \
          1   3
           \
            1
    */
    tree B = newNode(2);
    B->left = newNode(1);
    B->right = newNode(3);
    B->left->right = newNode(1);

    /*
        C: multinsieme diverso (manca un 1) = {1,2,3}
            1
           / \
          2   3
    */
    tree C = newNode(1);
    C->left = newNode(2);
    C->right = newNode(3);

    printf("Albero A (preorder): ");
    printPreOrder(A);
    printf("\n");

    printf("Albero B (preorder): ");
    printPreOrder(B);
    printf("\n");

    printf("Albero C (preorder): ");
    printPreOrder(C);
    printf("\n\n");

    printf("stessiValori(A, B) = %d   (atteso: 1)\n", stessiValori(A, B));
    printf("stessiValori(A, C) = %d   (atteso: 0)\n", stessiValori(A, C));
    printf("stessiValori(B, C) = %d   (atteso: 0)\n", stessiValori(B, C));

    freeTree(A);
    freeTree(B);
    freeTree(C);

    return 0;
}
void trovamax(tree t, int *max)
    {
        if(t==NULL)
            return;
        if(t->dato>*max) *max=t->dato;
    trovamax(t->left, max);
    trovamax(t->right, max);
    }
void cercaripetiz(tree albero, int x, int *count)
    {
        if(albero==NULL)
            return;
        if(albero->dato==x)
            (*count)++;
        cercaripetiz(albero->left, x, count);
        cercaripetiz(albero->right, x, count);
    }
void riempivett(tree albero ,int v[], tree root, int len)
    {
        if(albero==NULL)
            return;
        int count=0;
        cercaripetiz(root, albero->dato, &count);
        v[albero->dato]=count;
        riempivett(albero->left, v, root, len);
        riempivett(albero->right, v, root, len);
    }
int stessiValori(tree A, tree B)
    {
        if(A==NULL && B==NULL)
            return 1;
        if(A==NULL || B==NULL)
            return 0;
        int maxA=0;
        int maxB=0;
        if(maxA!=maxB)
            return 0;
        trovamax(A, &maxA);
        trovamax(B, &maxB);
        int *vettA=malloc(sizeof(int)*(maxA+1));
        int *vettB=malloc(sizeof(int)*(maxB+1));
    for(int i=0; i<maxA; i++)
        {
            vettA[i]=0;
        }
    for(int i=0; i<maxB; i++)
        {
            vettB[i]=0;
        }
        riempivett(A, vettA, A, maxA);
        riempivett(B, vettB, B, maxB);
        for(int i=0; i<maxA; i++)
            {
                if(vettA[i]!=vettB[i])
                {
                    free(vettA);
                    free(vettB);
                    return 0;
                }
            }
    free(vettA);
    free(vettB);
    return 1;
    }
