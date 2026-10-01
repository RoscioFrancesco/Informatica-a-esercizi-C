//
//  main.c
//  tde alberi 2  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *left, *right;   /* fix del typo */
} node;

typedef node *tree;

typedef struct ELLista {
    tree foglia;
    struct ELLista *next;
} nodeLista;

typedef nodeLista *Lista;

/* =========================
   PROTOTIPO ESERCIZIO
   ========================= */

Lista listaFoglie(tree T);

/* =========================
   SUPPORTO PER TEST
   ========================= */
static tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    n->dato = x;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

static void freeList(Lista L) {
    while (L) {
        nodeLista *tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* stampa struttura: dato(left,right) */
static void printShape(tree T) {
    if (!T) { printf("NULL"); return; }
    printf("%d(", T->dato);
    printShape(T->left);
    printf(",");
    printShape(T->right);
    printf(")");
}

static int isLeaf(tree T) {
    return (T != NULL && T->left == NULL && T->right == NULL);
}

/* stampa le foglie dell'albero in ordine left-to-right (solo per controllo visivo) */
static void printLeaves(tree T) {
    if (!T) return;
    if (isLeaf(T)) {
        printf("%d ", T->dato);
        return;
    }
    printLeaves(T->left);
    printLeaves(T->right);
}

/* stampa la lista di foglie: valore + indirizzo foglia */
static void printLeafList(Lista L) {
    if (!L) {
        printf("(lista vuota)\n");
        return;
    }
    int k = 0;
    while (L) {
        printf("  [%d] foglia->dato=%d  (addr foglia=%p)\n",
               k, L->foglia->dato, (void*)L->foglia);
        L = L->next;
        k++;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* Albero di test con 4 foglie */
    /*
              10
            /    \
           5      20
          / \       \
         2   7       30
            / \
           6   8

       Foglie: 2, 6, 8, 30
       La lista risultante dipende dal tipo di visita scelto nella tua soluzione.
    */
    tree T = newNode(10);
    T->left = newNode(5);
    T->right = newNode(20);
    T->left->left = newNode(2);
    T->left->right = newNode(7);
    T->left->right->left = newNode(6);
    T->left->right->right = newNode(8);
    T->right->right = newNode(30);

    printf("===== ALBERO =====\n");
    printf("Struttura: ");
    printShape(T);
    printf("\nFoglie (left->right): ");
    printLeaves(T);
    printf("\n\n");

    printf("===== LISTA FOGLIE (puntatori a foglie) =====\n");
    Lista L = listaFoglie(T);
    printLeafList(L);

    /* cleanup (NON liberare le foglie dall'albero tramite la lista!) */
    freeList(L);
    freeTree(T);

    return 0;
}


/*

*/
Lista inseriscincoda(Lista head, tree foglia)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->foglia=foglia;
                return new;
            }
        head->next=inseriscincoda(head->next, foglia);
        return head;
    }
Lista f(tree T, Lista new) {
    if(T==NULL)
        return new;
    if(T->left==NULL && T->right==NULL)
    {
        new=inseriscincoda(new, T);
    }
    new=f(T->left, new);
    new=f(T->right, new);
    return new;
}
Lista listaFoglie(tree T)
    {
    Lista new=NULL;
    new=f(T, new);
    return new;
    }
