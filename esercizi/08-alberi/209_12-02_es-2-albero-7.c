//
//  main.c
//  es 2 albero  -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXH 256
typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} Node;

typedef Node* tree;

int camminoAlternatoMigliore(tree T, int K, int out[], int *lenOut);

tree newNode(int v) {
    tree t = (tree)malloc(sizeof(Node));
    if (!t) {
        printf("Errore malloc\n");
        exit(1);
    }
    t->val = v;
    t->left = t->right = NULL;
    return t;
}

void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

void printPath(int v[], int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(", ");
        printf("%d", v[i]);
    }
    printf("]");
}


/* ===================== MAIN DI TEST ===================== */
int èpari(int a);
void f(tree albero, tree *foglia, int len_cammino, int prec, int sommatotale, int *hasprec, int *lenmax, int *maxsomme, int *maxcambi, int cambidiparità);
int trovavettore(tree albero, tree foglia, int vett[], int scorri);
tree wrapper(tree albero);
int depth(tree albero);
int *totale(tree albero);
int main() {

    /*
               5
             /   \
            2     7
           / \   / \
          9   4 6  11
         /
        8
    */

    tree T = newNode(5);
    T->left = newNode(2);
    T->right = newNode(7);

    T->left->left = newNode(9);
    T->left->right = newNode(4);

    T->right->left = newNode(6);
    T->right->right = newNode(11);

    T->left->left->left = newNode(8);

    int len=depth(T);
    int *array=malloc(sizeof(int)*(len+1));
    array=totale(T);
    
}


/* ===================== SKELETON FUNZIONE ===================== */


int camminoAlternatoMigliore(tree T, int K, int out[], int *lenOut) {

    (void)T;
    (void)K;
    (void)out;
    (void)lenOut;

    

    return 0;
}
int èpari(int a)
    {
        if(a%2==0)
            return 1;
    return 0;
    }
void f(tree albero, tree *foglia, int len_cammino, int prec, int sommatotale, int *hasprec, int *lenmax, int *maxsomme, int *maxcambi, int cambidiparità)
    {
        if(albero==NULL)
            return;
        sommatotale=sommatotale+albero->val;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(*hasprec==0)
                    {
                        (*hasprec)=1;
                        *lenmax=len_cammino;
                        *maxsomme=sommatotale;
                        *maxcambi=cambidiparità;
                    }
                else
                    {
                        if(cambidiparità>*maxcambi)
                            *foglia=albero;
                        else if (*maxsomme>sommatotale)
                            *foglia=albero;
                        else if (sommatotale<*maxsomme)
                            *foglia=albero;
                        
                    }
            }
        if(èpari(prec)!=èpari(albero->val))
            cambidiparità++;
    f(albero->right, foglia, len_cammino+1, albero->val, sommatotale, hasprec, lenmax, maxsomme, maxcambi, cambidiparità);
    f(albero->left, foglia, len_cammino+1, albero->val, sommatotale, hasprec, lenmax, maxsomme, maxcambi, cambidiparità);
    }
tree wrapper(tree albero)
    {
    tree foglia=NULL;
    int maxcambi=0;
    int hasprec=0;
    int lenmax=0;
    int maxsomme=0;
    f(albero, &foglia, 0, 0, 0, &hasprec, &lenmax, &maxsomme, &maxcambi, 0);
    return foglia;
    }
int trovavettore(tree albero, tree foglia, int vett[], int scorri)
    {
        if(albero==NULL)
            return 0;
        if(albero==foglia)
        {
            vett[scorri]=albero->val;
            return 1;
        }
        if(trovavettore(albero->left, foglia, vett, scorri+1))
        {
            vett[scorri]=albero->val;
            return 1;
        }
        if(trovavettore(albero->right, foglia, vett, scorri+1))
        {
            vett[scorri]=albero->val;
            return 1;
        }
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
    int sx=depth(albero->left);
    int dx=depth(albero->right);
    return 1+max(sx, dx);
    }
int *totale(tree albero)
    {
    int len=depth(albero);
    int *vett=malloc(sizeof(int)*len);
    tree foglia=wrapper(albero);
    trovavettore(albero, foglia, vett, 0);
    for(int i=0; i<len; i++)
        printf("%d-->", vett[i]);
    return vett;
    }
