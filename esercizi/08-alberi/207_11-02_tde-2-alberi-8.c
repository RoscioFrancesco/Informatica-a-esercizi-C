//
//  main.c
//  tde 2 alberi -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* ===== DEFINIZIONE ALBERO ===== */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node *tree;


int verifica(tree T);   // <-- DA IMPLEMENTARE TU


/* ===== FUNZIONI DI SUPPORTO ===== */

tree newNode(int x) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) exit(1);
    t->dato = x;
    t->left = t->right = NULL;
    return t;
}

void stampaInOrder(tree T) {
    if (T == NULL) return;
    stampaInOrder(T->left);
    printf("%d ", T->dato);
    stampaInOrder(T->right);
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}
void trovamin(tree albero, int *min);
int main() {

    /*
        ALBERO 1 (dovrebbe essere valido)

                10
               /  \
              5    20
             / \     \
            2   7     30
    */

    tree T1 = newNode(10);
    T1->left = newNode(5);
    T1->right = newNode(20);
    T1->left->left = newNode(2);
    T1->left->right = newNode(7);
    T1->right->right = newNode(30);


    /*
        ALBERO 2 (NON valido)

                10
               /  \
              5    20
                   /
                  3    <-- ERRORE
    */

    tree T2 = newNode(10);
    T2->left = newNode(5);
    T2->right = newNode(20);
    T2->right->left = newNode(3);   // viola la proprietà


    printf("Albero 1 (inorder): ");
    stampaInOrder(T1);
    printf("\nRisultato verifica(T1) = %d\n\n", verifica(T1));

    printf("Albero 2 (inorder): ");
    stampaInOrder(T2);
    printf("\nRisultato verifica(T2) = %d\n", verifica(T2));

    freeTree(T1);
    freeTree(T2);

    return 0;
}
int f(tree albero, int max, int min)
    {
        if(albero==NULL)
            return 1;
        if(albero->dato>max || albero->dato<min)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    return f(albero->left,albero->dato, min) && f(albero->right, max, albero->dato);
    }
void trovamax(tree albero, int*max)
    {
        if(albero==NULL)
            return;
        if(albero->dato>*max)
            *max=albero->dato;
    trovamax(albero->left, max);
    trovamax(albero->right, max);
    }
int wrappermax(tree albero)
    {
    int max=albero->dato;
    trovamax(albero, &max);
    return max;
    }
int wrappermin(tree albero)
    {
    int min=wrappermax(albero);
    trovamin(albero, &min);
    return min;
    }
void trovamin(tree albero, int *min)
    {
        if(albero==NULL)
            return;
        if(*min>albero->dato)
            *min=albero->dato;
    trovamin(albero->left, min);
    trovamin(albero->right, min);
    }
int verifica(tree T)
    {
    int max=wrappermax(T);
    int min=wrappermin(T);
    return f(T, max, min);
    }
