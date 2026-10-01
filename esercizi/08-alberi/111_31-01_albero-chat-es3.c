//
//  main.c
//  albero chat es3
//
//  Created by Francesco Roscio Ricon on 31/01/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* Tree;

typedef struct EL{
    int val;
    int occ;
    struct EL * next;
}Vagone;
typedef Vagone * Lista;

Tree newNode(int val, Tree left, Tree right) {
    Tree t = (Tree)malloc(sizeof(Node));
    if (!t) { perror("malloc"); exit(1); }
    t->val = val;
    t->left = left;
    t->right = right;
    return t;
}

void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   ESERCIZIO (DA FARE TU)
   ======================= */

int multisetUguali(Tree TA, Tree TB);
int wrapper(Tree albero, int x);
void contaalbero(Tree albero, int x, int* somma);
void riempilista(Tree albero, Tree root, Lista *head);
int f(Tree albero1, Tree albero2);
/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)
       Stessi valori con stesse molteplicità, ma struttura diversa.

       TA1 contiene: {5, 5, 3, 7, 7, 7}
                5
               / \
              3   7
                 / \
                5   7
                   /
                  7

       TB1 contiene: {5, 5, 3, 7, 7, 7}
                7
               / \
              5   7
             /   /
            3   7
                 \
                  5
       ============================================================ */

    Tree TA1 = newNode(5,
                newNode(3, NULL, NULL),
                newNode(7,
                    newNode(5, NULL, NULL),
                    newNode(7,
                        newNode(7, NULL, NULL),
                        NULL)));

    Tree TB1 = newNode(7,
                newNode(5,
                    newNode(3, NULL, NULL),
                    NULL),
                newNode(7,
                    newNode(7,
                        NULL,
                        newNode(5, NULL, NULL)),
                    NULL));

    /* ============================================================
       CASO 2: FALSO (atteso 0)
       Stessi valori "presenti", ma molteplicità diversa:
       TA2: {1,2,2,3}
       TB2: {1,2,3,3}
       ============================================================ */

    Tree TA2 = newNode(2,
                newNode(1, NULL, NULL),
                newNode(2,
                    newNode(3, NULL, NULL),
                    NULL));

    Tree TB2 = newNode(3,
                newNode(1, NULL, NULL),
                newNode(2,
                    newNode(3, NULL, NULL),
                    NULL));

    /* ============================================================
       CASO 3: FALSO (atteso 0)
       Stessa quantità di nodi ma un valore diverso:
       TA3: {4,4,4}
       TB3: {4,4,5}
       ============================================================ */

    Tree TA3 = newNode(4,
                newNode(4, NULL, NULL),
                newNode(4, NULL, NULL));

    Tree TB3 = newNode(4,
                newNode(4, NULL, NULL),
                newNode(5, NULL, NULL));

    /* ============================================================
       CASO 4: VERO (atteso 1)
       Entrambi vuoti: multiset uguali (insieme vuoto)
       ============================================================ */
    Tree TA4 = NULL;
    Tree TB4 = NULL;

    /* ============================================================
       CASO 5: FALSO (atteso 0)
       Uno vuoto e uno no
       ============================================================ */
    Tree TA5 = NULL;
    Tree TB5 = newNode(1, NULL, NULL);

    /* =======================
       PRINTF
       ======================= */

    printf("Caso 1 (atteso 1): %d\n", multisetUguali(TA1, TB1));
    printf("Caso 2 (atteso 0): %d\n", multisetUguali(TA2, TB2));
    printf("Caso 3 (atteso 0): %d\n", multisetUguali(TA3, TB3));
    printf("Caso 4 (atteso 1): %d\n", multisetUguali(TA4, TB4));
    printf("Caso 5 (atteso 0): %d\n", multisetUguali(TA5, TB5));

    /* libero memoria (TA4/TA5 sono NULL, ok) */
    freeTree(TA1); freeTree(TB1);
    freeTree(TA2); freeTree(TB2);
    freeTree(TA3); freeTree(TB3);
    freeTree(TB5);

    return 0;
}


Lista inserisciincodaordinato(int x, int occ, Lista head)
    {
        if(head==NULL || x>head->val)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                new->val=x;
                new->occ=occ;
                return new;
            }
        head->next=inserisciincodaordinato(x, occ, head->next);
        return head;
    }
int trova(int x, Lista head)
    {
    if(head==NULL)
        return 0;
        while(head!=NULL)
            {
                if(head->val==x)return 1;
                head=head->next;
            }
    return 0;
    }
void riempilista(Tree albero, Tree root, Lista *head)
    {
    if (albero == NULL) return;
    int occ=wrapper(root, albero->val);
    if(trova(albero->val, *head)==0)
        {
            *head=inserisciincodaordinato(albero->val, occ, *head);
        }
    riempilista(albero->left, root, head);
    riempilista(albero->right, root, head);
    }
void contaalbero(Tree albero, int x, int* somma)
    {
        if(albero==NULL)
            return;
        if(albero->val==x)
            (*somma)++;
    contaalbero(albero->left, x, somma);
    contaalbero(albero->right, x, somma);
    }
int wrapper(Tree albero, int x)
    {
    int somma=0;
    contaalbero(albero, x, &somma);
    return somma;
    }
int multisetUguali(Tree albero1, Tree albero2)
    {
    Lista head1=NULL;
    Lista head2=NULL;
    riempilista(albero1, albero1, &head1);
    riempilista(albero2, albero2, &head2);
    while(head1!=NULL && head2!=NULL)
        {
            if(head1->val!=head2->val || head1->occ!=head2->occ)
                return 0;
            head1=head1->next;
            head2=head2->next;
        }
    return (head1 == NULL && head2 == NULL);

    }
