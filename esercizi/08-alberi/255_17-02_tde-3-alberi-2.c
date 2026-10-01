//
//  main.c
//  tde 3 alberi  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TN {
    int valore;
    struct TN *left, *right;
} Node;

typedef Node *Tree;

int ridondato(Tree T);

static Node *newNode(int v) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->valore = v;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(Tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* stampa in-order (solo per vedere i valori) */
static void printInOrder(Tree T) {
    if (!T) return;
    printInOrder(T->left);
    printf("%d ", T->valore);
    printInOrder(T->right);
}

/* stampa struttura (preorder con parentesi) */
static void printShape(Tree T) {
    if (!T) { printf("NULL"); return; }
    printf("%d(", T->valore);
    printShape(T->left);
    printf(",");
    printShape(T->right);
    printf(")");
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* =========================================================
       TEST 1: Albero RIDONDATO (atteso: 1)
       Proprietà: ogni nodo interno ha almeno una foglia nel suo sottoalbero
       che contiene lo stesso valore del nodo interno.
       ========================================================= */

    /*
              5
            /   \
           3     5
          / \     \
         3   2     5

       Nodi interni: 5(root), 3, 5(destro)
       - per 5(root): nel suo sottoalbero c'è una foglia 5 (in basso a destra)
       - per 3: nel suo sottoalbero c'è una foglia 3 (a sinistra)
       - per 5(destro): nel suo sottoalbero c'è una foglia 5 (figlio destro)
    */
    Tree T1 = newNode(5);
    T1->left = newNode(3);
    T1->right = newNode(5);
    T1->left->left = newNode(3);
    T1->left->right = newNode(2);
    T1->right->right = newNode(5);

    printf("===== TEST 1 (RIDONDATO atteso = 1) =====\n");
    printf("Struttura: ");
    printShape(T1);
    printf("\nInOrder: ");
    printInOrder(T1);
    printf("\n");
    printf("ridondato(T1) = %d\n\n", ridondato(T1));

    /* =========================================================
       TEST 2: Albero NON ridondato (atteso: 0)
       ========================================================= */

    /*
              7
            /   \
           4     9
          / \   / \
         1   2 8  10

       Nodi interni: 7,4,9
       - per 4: foglie nel suo sottoalbero sono 1 e 2, nessuna vale 4 => FAIL
       quindi albero NON ridondato
    */
    Tree T2 = newNode(7);
    T2->left = newNode(4);
    T2->right = newNode(9);
    T2->left->left = newNode(1);
    T2->left->right = newNode(2);
    T2->right->left = newNode(8);
    T2->right->right = newNode(10);

    printf("===== TEST 2 (NON ridondato atteso = 0) =====\n");
    printf("Struttura: ");
    printShape(T2);
    printf("\nInOrder: ");
    printInOrder(T2);
    printf("\n");
    printf("ridondato(T2) = %d\n\n", ridondato(T2));

    freeTree(T1);
    freeTree(T2);
    return 0;
}

/*
int ridondato(Tree T) {
    // TODO: tua soluzione
}
*/
//un albero si dice ridondato se ogni valore vi presente
//su un nodo interno ni è anche presente in un nodo foglia nf dell’albero che
//ha ni come radice.

int èfoglia(Tree t)
    {
    if(t==NULL)
        return 0;
        if(t->left==NULL && t->right==NULL)
            return 1;
    return 0;
    }
void cerca(Tree root, Tree nodo_mio, Tree *punt)
    {
        if(root==NULL)
            return;
        if(root->valore==nodo_mio->valore && root!=nodo_mio && !èfoglia(*punt))
            *punt=root;
    cerca(root->left, nodo_mio, punt);
    cerca(root->right, nodo_mio, punt);
    }

int verificanodo(Tree t)
    {
        if(t==NULL)
            return 1;
        if(!èfoglia(t))
            {
                Tree punt=NULL;
                cerca(t, t, &punt);
                if(punt==NULL)// non l'ha trovato
                    {return 0;}
                if(!èfoglia(punt))
                    return 0;
            }
    return verificanodo(t->left) && verificanodo(t->right);
    }
int ridondato(Tree T) {
    return verificanodo(T);
}
