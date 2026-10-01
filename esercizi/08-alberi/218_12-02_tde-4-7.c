//
//  main.c
//  tde 4 -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   Strutture dati (date)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node *tree;

int foglieInterneIncrociate(tree TA, tree TB);

/* --- Utility per test --- */
tree newNode(int v, tree L, tree R);
void freeTree(tree T);
void printPreorder(tree T);

/* =========================
   MAIN di test
   ========================= */
int main(void) {
    /*
      Costruisci due alberi di esempio (puoi cambiare i valori/forma).
      Nota: qui i valori NON contano per l'esercizio, conta la posizione foglia/interno.
    */

    /* TA */
    tree TA =
        newNode(10,
            newNode(5,
                newNode(2, NULL, NULL),   /* foglia */
                NULL
            ),
            newNode(20,
                NULL,
                newNode(30, NULL, NULL)   /* foglia */
            )
        );

    /* TB */
    tree TB =
        newNode(100,
            newNode(50,
                NULL,
                newNode(60, NULL, NULL)   /* foglia */
            ),
            newNode(200,
                newNode(150, NULL, NULL), /* foglia */
                NULL
            )
        );

    printf("TA (preorder): ");
    printPreorder(TA);
    printf("\n");

    printf("TB (preorder): ");
    printPreorder(TB);
    printf("\n\n");

    int ok = foglieInterneIncrociate(TA, TB);
    printf("Risultato foglieInterneIncrociate(TA, TB) = %d\n", ok);

    freeTree(TA);
    freeTree(TB);
    return 0;
}

/* =========================
   Utility
   ========================= */
tree newNode(int v, tree L, tree R) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = v;
    n->left = L;
    n->right = R;
    return n;
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

void printPreorder(tree T) {
    if (T == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", T->dato);
    printPreorder(T->left);
    printPreorder(T->right);
}


int foglieInterneIncrociate(tree TA, tree TB) {
    
    (void)TA;
    (void)TB;
    return -1; /* placeholder: cambia con 0/1 */
}
int èfoglia(tree albero)
    {
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    return 0;
    }
