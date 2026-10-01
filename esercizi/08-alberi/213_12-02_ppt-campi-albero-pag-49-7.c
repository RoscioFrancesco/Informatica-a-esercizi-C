//  Created by Francesco Roscio Ricon on 12/02/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;
typedef node *tree;


tree newNode(int dato, tree left, tree right) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = dato;
    n->left = left;
    n->right = right;
    return n;
}

/* Utility: libera l'albero */
void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* ====== TODO: QUI METTI LE TUE FUNZIONI ====== */
/* Esempio firme (puoi cambiarle come vuoi) */
int verificadiscendenti(int val, tree t);
int scorrialbero(tree t);
int checkProperty(tree t) {
    return scorrialbero(t);
}
/* ============================================ */

int main(void) {
    /*
      Costruzione di un albero di esempio (puoi cambiarlo):
              7
            /   \
           3     5
          / \     \
         6  10     8
    */
    tree t =
        newNode(7,
            newNode(3,
                newNode(6, NULL, NULL),
                newNode(10, NULL, NULL)
            ),
            newNode(5,
                NULL,
                newNode(8, NULL, NULL)
            )
        );

    printf("Albero creato.\n");
    printf("Ora chiamo la funzione da implementare...\n");

    int res = checkProperty(t);

    printf("Risultato checkProperty(t) = %d\n", res);
    printf("(Atteso: 0 oppure 1, quando implementi la logica)\n");

    freeTree(t);
    printf("Memoria liberata. Fine.\n");
    return 0;
}
int verificadiscendenti(int val, tree t)
    {
        if(t==NULL)
            return 0;
        if(t->dato%val==0)
            return 1;
    return verificadiscendenti(val, t->left) || verificadiscendenti(val, t->right);
    }
int scorrialbero(tree t)
    {
        if(t==NULL)
            return 1;
        if(t->left==NULL && t->right==NULL)
            return 1;
        if((verificadiscendenti(t->dato, t->left)||verificadiscendenti(t->dato, t->right))==0)
            return 0;
    return scorrialbero(t->right)&&scorrialbero(t->left);
    }
