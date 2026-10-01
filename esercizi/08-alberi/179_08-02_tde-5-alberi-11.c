//  Created by Francesco Roscio Ricon on 08/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (corrette)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node * tree;

typedef struct ES {
    int num;
    struct ES *next;
}Vagone;
typedef Vagone* Lista;


int sommaPari(tree t);
void f(tree t, int *somma);
Lista inserisciincoda(Lista head, int x);
void riempilista(tree albero, Lista *head);
Lista inserisciincoda(Lista head, int x);
/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */
tree nuovoNodo(int val) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->dato);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

void freeTree(tree t) {
    if (t == NULL)
        return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   FUNZIONE RICHIESTA (STUB)
   ========================= */
int sommaPari(tree t) {
    if(t==NULL)
        return 0;
    int somma=0;
    f(t, &somma);
    return somma;
}
void riempilista(tree albero, Lista *head);
Lista wrapper(tree albero);
void stampalista(Lista head);
/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /*
            10
           /  \
          5    8
         / \
        2   7
    */

    tree root = nuovoNodo(10);
    root->left = nuovoNodo(5);
    root->right = nuovoNodo(8);
    root->left->left = nuovoNodo(2);
    root->left->right = nuovoNodo(7);

    printf("Albero (preorder): ");
    stampaPreorder(root);
    printf("\n");

    int risultato = sommaPari(root);
    printf("Somma dei valori pari: %d\n", risultato);
    
    Lista new=NULL;
    new=wrapper(root);
    stampalista(new);
}
void f(tree t, int *somma)
    {
        if(t==NULL)
            return;
        if(t->dato%2==0)
            {
                *somma=*somma+t->dato;
            }
    f(t->left, somma);
    f(t->right, somma);
    }

Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                new->num=x;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
void riempilista(tree albero, Lista *head)
    {
        if(albero==NULL)
            return;
    if(albero->dato%2==0)
        *head=inserisciincoda(*head, albero->dato);
    riempilista(albero->left, head);
    riempilista(albero->right, head);
    }
Lista wrapper(tree albero)
    {
    Lista new=NULL;
    if(albero==NULL)
        return new;
    riempilista(albero, &new);
    return new;
    }
void stampalista(Lista head)
    {
    if(head==NULL)
        while(head!=NULL)
        {
            printf("%d-->", head->num);
            head=head->next;
        }
    }
