//
//  main.c
//  albero alterna_pari_dispari
//
//  Created by Francesco Roscio Ricon on 23/01/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodeS {
    int val;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* Funzione per creare un nuovo nodo */
tree newNode(int val) {
    tree n = (tree)malloc(sizeof(node));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}


/* Funzione per liberare la memoria */
void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}


int èpari(int val);

int esistePercorsoAlternato(tree albero);
int main() {
    /*
        Costruiamo questo albero:

               2
             /   \
            7     4
           / \     \
          6   9     5
         /
        3

      Percorso alternato esempio:
      2 (pari) -> 7 (dispari) -> 6 (pari) -> 3 (dispari)  ✅ valido (foglia)
    */

    tree T = newNode(2);
    T->left = newNode(7);
    T->right = newNode(4);

    T->left->left = newNode(6);
    T->left->right = newNode(9);

    T->left->left->left = newNode(3);

    T->right->right = newNode(5);

    int res = esistePercorsoAlternato(T);

    if (res)
        printf("Esiste almeno un percorso radice-foglia con alternanza pari/dispari ✅\n");
    else
        printf("NON esiste alcun percorso radice-foglia con alternanza pari/dispari ❌\n");

    freeTree(T);
    return 0;
}
int esistePercorsoAlternato(tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        if(èpari(albero->val))
            {
                if(albero->left==NULL && albero->right==NULL)
                    return 1;
                if(albero->left!=NULL && !èpari(albero->left->val) && albero->right== NULL)
                    return esistePercorsoAlternato(albero->left);
                if(albero->right!=NULL && !èpari(albero->right->val)&& albero->left==NULL)
                    return esistePercorsoAlternato(albero->right);
                if(!èpari(albero->right->val)&&!èpari(albero->left->val))
                    return esistePercorsoAlternato(albero->left)|| esistePercorsoAlternato(albero->right);
                return 0;
            }
        if(!èpari(albero->val))
            {
                if(albero->left==NULL && albero->right==NULL)
                    return 1;
                if( albero->left!=NULL && èpari(albero->left->val) && albero->right== NULL)
                    return esistePercorsoAlternato(albero->left);
                if( albero->right!=NULL && èpari(albero->right->val)&& albero->left==NULL)
                    return esistePercorsoAlternato(albero->right);
                if(èpari(albero->right->val)&&èpari(albero->left->val))
                    return esistePercorsoAlternato(albero->left)|| esistePercorsoAlternato(albero->right);
                return 0;
            }
    return esistePercorsoAlternato(albero->left)||esistePercorsoAlternato(albero->right);
    }


int èpari(int val)
    {
    if(val%2==0)
        return 1;
    return 0;
}
