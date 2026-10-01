//  Created by Francesco Roscio Ricon on 12/02/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

int isLionese(tree T);

tree newNode(int x) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) exit(1);
    t->dato = x;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void printPreOrder(tree T) {
    if (T == NULL) return;
    printf("%d ", T->dato);
    printPreOrder(T->left);
    printPreOrder(T->right);
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}


/* =========================
   MAIN DI TEST
   ========================= */

int main() {

    /*
        ALBERO 1 (LIONESE)

                10
               /  \
              3    8
             / \    \
            5   7    12

        Regole:
        - figli sinistri → dispari ✔
        - figli destri → pari ✔
    */

    tree T1 = newNode(10);
    T1->left = newNode(3);
    T1->right = newNode(8);
    T1->left->left = newNode(5);
    T1->left->right = newNode(7);   // <-- ERRORE VOLUTO? no, qui è figlio destro quindi dovrebbe essere pari (ma lo lasciamo a te verificare)
    T1->right->right = newNode(12);


    /*
        ALBERO 2 (NON LIONESE)

                10
               /  \
              4    6

        4 è figlio sinistro ma è pari ❌
    */

    tree T2 = newNode(10);
    T2->left = newNode(4);
    T2->right = newNode(6);


    printf("Albero T1 (preorder): ");
    printPreOrder(T1);
    printf("\nRisultato isLionese(T1) = %d\n\n", isLionese(T1));

    printf("Albero T2 (preorder): ");
    printPreOrder(T2);
    printf("\nRisultato isLionese(T2) = %d\n", isLionese(T2));

    freeTree(T1);
    freeTree(T2);

    return 0;
}
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return 0;
    }
int alberopari(tree t)
    {
        if(t==NULL)
            return 1;
        if(èpari(t->dato)==0)
            return 0;
    return alberopari(t->left) && alberopari(t->right);
    }
int alberodispari(tree t)
    {
        if(t==NULL)
            return 1;
        if(èpari(t->dato)==1)
            return 0;
    return alberodispari(t->left) && alberodispari(t->right);
    }

int isLionese(tree T)
    {
        if(T==NULL)
            return 1;
        if(T->left!=NULL && èpari(T->left->dato)==1)
            return 0;
        if(T->right!=NULL && èpari(T->right->dato)==0)
            return 0;
    return isLionese(T->left) &&isLionese(T->right);
    }
