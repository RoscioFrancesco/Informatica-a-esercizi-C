//
//  main.c
//  es 1 chat alberi -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE DATI
   ========================= */
typedef struct node {
    int dato;
    struct node *left;
    struct node *right;
} node;

typedef node* tree;

/* =========================
   PROTOTIPI
   ========================= */
void eliminaSottoalberiDispari(tree *T);   // <-- DA IMPLEMENTARE (non risolto qui)

tree newNode(int x);
void freeTree(tree T);

void printInOrder(tree T);
void printPreOrder(tree T);

/* =========================
   HELPERS
   ========================= */
tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    if(!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(tree T) {
    if(T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

void printInOrder(tree T) {
    if(T == NULL) return;
    printInOrder(T->left);
    printf("%d ", T->dato);
    printInOrder(T->right);
}

void printPreOrder(tree T) {
    if(T == NULL) return;
    printf("%d ", T->dato);
    printPreOrder(T->left);
    printPreOrder(T->right);
}

void distriggi(tree t);
int main(void) {
    
    tree T = newNode(10);
    T->left = newNode(5);
    T->right = newNode(8);
    T->left->left = newNode(2);
    T->left->right = newNode(1);
    T->right->right = newNode(7);

    printf("ALBERO INIZIALE\n");
    printf("PreOrder : "); printPreOrder(T); printf("\n");
    printf("InOrder  : "); printInOrder(T);  printf("\n");

    printf("\nChiamo eliminaSottoalberiDispari(&T)...\n");
    eliminaSottoalberiDispari(&T);

    printf("\nALBERO DOPO\n");
    if(T == NULL) {
        printf("T = NULL (albero vuoto)\n");
    } else {
        printf("PreOrder : "); printPreOrder(T); printf("\n");
        printf("InOrder  : "); printInOrder(T);  printf("\n");
    }

    /* Pulizia finale (se non hai già eliminato tutto nella funzione) */
    freeTree(T);
    return 0;
}
int sommasottoalbero(tree t)
    {
        if(t==NULL)
            return 0;
    return t->dato+sommasottoalbero(t->left)+sommasottoalbero(t->right);
    }


void eliminaSottoalberiDispari(tree *T)
    {
        if(*T==NULL)
            {
                return;
            }
        if(sommasottoalbero(*T)%2==1)
            {
                distriggi((*T)->left);
                distriggi((*T)->right);
                *T=NULL;
                return;
            }
    eliminaSottoalberiDispari(&(*T)->left);
    eliminaSottoalberiDispari(&(*T)->right);
    }
void distriggi(tree t)
    {
        if(t==NULL)
            return;
    distriggi(t->left);
    distriggi(t->right);
    free(t);
    }
