//  Created by Francesco Roscio Ricon on 09/02/26.
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node *tree;
int *merge(int vett[], int len);

/* =========================
   FUNZIONI AUSILIARIE
   ========================= */
tree nuovoNodo(int val) {
    tree n = (tree)malloc(sizeof(node));
    n->dato = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}
/* =========================
   MAIN DI TEST
   ========================= */
int f(tree albero);
int contanodi(tree albero);
void riempivettore(tree albero, int vett[], int *segna);
int *merge(int vett[], int len);

int main() {
    /*
            5
           / \
          3   5
         / \   \
        3   7   7
    */

    tree t = nuovoNodo(5);
    t->left = nuovoNodo(3);
    t->right = nuovoNodo(5);
    t->left->left = nuovoNodo(3);
    t->left->right = nuovoNodo(7);
    t->right->right = nuovoNodo(7);

    int risultato = f(t);

    printf("Numero di valori distinti nell'albero: %d\n", risultato);

    return 0;
}
int contanodi(tree albero)
    {
        if(albero==NULL)
            return 0;
    return 1+contanodi(albero->left)+contanodi(albero->right);
    }
void riempivettore(tree albero, int vett[], int *segna)
    {
        if(albero==NULL)
            return;
        vett[*segna]=albero->dato;
        (*segna)++;
    riempivettore(albero->left, vett, segna);
    riempivettore(albero->right, vett, segna);
    }
int f(tree albero)
    {
    int len=contanodi(albero);
    int *vett=malloc(sizeof(int)*len);
    int segna=0;
    riempivettore(albero, vett, &segna);
    int count=1;
    vett=merge(vett, len);
    for(int i=0; i<len-1; i++)
        {
            if(vett[i]!=vett[i+1])
                count++;
        }
    return count;
    }
int *merge(int vett[], int len)
    {
    for(int i=0; i<len-1; i++)
        {
            for(int j=i+1; j<len; j++)
                {
                    if(vett[i]>vett[j])
                        {
                            int temp=vett[i];
                            vett[i]=vett[j];
                            vett[j]=temp;
                        }
                }
        }
        return vett;
    }
