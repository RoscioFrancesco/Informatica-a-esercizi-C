//
//  main.c
//  alberi es 12 b chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* Albero;

typedef struct IntList {
    int val;
    struct IntList* next;
} IntList;

typedef IntList* Lista;

/* =======================
   PROTOTIPI
   ======================= */

/* utility per costruire gli esempi */
Node* newNode(int v, Node* l, Node* r);
void freeTree(Albero t);

/* stampa ricorsiva (no cicli) */
void printLista(Lista l);
void freeLista(Lista l);




bool isPari(int x);



Node* newNode(int v, Node* l, Node* r)
{
    Node* n = (Node*)malloc(sizeof(*n));
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

void freeTree(Albero t)
{
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

void printLista(Lista l)
{
    if (!l) return;
    printf("%d", l->val);
    if (l->next) printf(" -> ");
    printLista(l->next);
}

void freeLista(Lista l)
{
    if (!l) return;
    freeLista(l->next);
    free(l);
}

Lista listaFiltrataInorder(Albero t);

int main(void)
{
    /*
      ESEMPIO 1
               5
             /   \
            3     8
           / \   / \
          2  4  7   10

      Inorder (tutti): 2,3,4,5,7,8,10
      Filtrati pari:   2,4,8,10
    */
    Albero t1 =
        newNode(5,
            newNode(3,
                newNode(2, NULL, NULL),
                newNode(4, NULL, NULL)
            ),
            newNode(8,
                newNode(7, NULL, NULL),
                newNode(10, NULL, NULL)
            )
        );

    printf("ESEMPIO 1 - atteso (pari in inorder): 2 -> 4 -> 8 -> 10\n");
    Lista l1 = listaFiltrataInorder(t1);
    printf("Risultato: ");
    if (!l1) printf("(lista vuota)");
    else printLista(l1);
    printf("\n\n");

    freeLista(l1);
    freeTree(t1);

    /*
      ESEMPIO 2 (tutti dispari => lista vuota)
            9
           / \
          5  11
         /
        3

      Inorder: 3,5,9,11
      Pari: nessuno
    */
    Albero t2 =
        newNode(9,
            newNode(5,
                newNode(3, NULL, NULL),
                NULL
            ),
            newNode(11, NULL, NULL)
        );

    printf("ESEMPIO 2 - atteso: (lista vuota)\n");
    Lista l2 = listaFiltrataInorder(t2);
    printf("Risultato: ");
    if (!l2) printf("(lista vuota)");
    else printLista(l2);
    printf("\n\n");

    freeLista(l2);
    freeTree(t2);

    /*
      ESEMPIO 3 (albero con un solo nodo)
          6

      Inorder: 6
      Pari: 6
    */
    Albero t3 = newNode(6, NULL, NULL);

    printf("ESEMPIO 3 - atteso: 6\n");
    Lista l3 = listaFiltrataInorder(t3);
    printf("Risultato: ");
    if (!l3) printf("(lista vuota)");
    else printLista(l3);
    printf("\n\n");

    freeLista(l3);
    freeTree(t3);

    return 0;
}


Lista inserisciincoda(Lista head, int x)
{
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->val=x;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
Lista scorrialbero(Albero tree, Lista head)
    {
        if(tree==NULL)
            return head;
        if(tree->val%2==0)
            {
                head=inserisciincoda(head, tree->val);
            }
    head=scorrialbero(tree->left, head);
    head=scorrialbero(tree->right, head);
    return head;
    }



Lista listaFiltrataInorder(Albero t)
{
    Lista head=NULL;
    head=scorrialbero(t, head);
    return head;
}
