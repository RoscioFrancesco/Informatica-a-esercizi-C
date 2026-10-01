//
//  main.c
//  alberi es 10 b chat
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

/* lista di interi: un livello */
typedef struct IntList {
    int val;
    struct IntList* next;
} IntList;

/* lista di liste: livelli */
typedef struct ListOfLists {
    IntList* levelList;          // lista dei valori del livello
    struct ListOfLists* next;    // livello successivo
} ListOfLists;

typedef IntList* Lista;
typedef ListOfLists* ListaDiListe;

/* =======================
   UTILITY ALBERO
   ======================= */

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

/* =======================
   UTILITY LISTE (NO CICLI)
   ======================= */

Lista cons(int x, Lista xs)
{
    Lista n = (Lista)malloc(sizeof(*n));
    n->val = x;
    n->next = xs;
    return n;
}

Lista concatLista(Lista a, Lista b)
{
    if (a == NULL) return b;
    a->next = concatLista(a->next, b);
    return a;
}

void freeLista(Lista xs)
{
    if (!xs) return;
    freeLista(xs->next);
    free(xs);
}

void freeListaDiListe(ListaDiListe ldl)
{
    if (!ldl) return;
    freeListaDiListe(ldl->next);
    freeLista(ldl->levelList);
    free(ldl);
}

/* stampa lista (ricorsiva) */
void printLista(Lista xs)
{
    if (!xs) return;
    printf("%d", xs->val);
    if (xs->next) printf(" ");
    printLista(xs->next);
}

/* stampa lista di liste (ricorsiva) */
void printListaDiListe(ListaDiListe ldl, int livello)
{
    if (!ldl) return;
    printf("Livello %d: [ ", livello);
    printLista(ldl->levelList);
    printf(" ]\n");
    printListaDiListe(ldl->next, livello + 1);
}

//ListaDiListe listaDiLivelli(Albero t)
//{
//    
//}

/* =======================
   MAIN + ESEMPI
   ======================= */
int max(int a, int b);
Lista riemppilivello(Albero tree, int livello, int livello_exp, Lista head);
ListaDiListe concatenaLDL(ListaDiListe a, ListaDiListe b);
ListaDiListe listaDiLivelli(Albero tree);
int main(void)
{
    /*
        ESEMPIO 1:

              5
             / \
            3   8
           / \   \
          2   4   9

        Livello 0: 5
        Livello 1: 3 8
        Livello 2: 2 4 9
    */
    Albero t1 =
        newNode(5,
            newNode(3,
                newNode(2, NULL, NULL),
                newNode(4, NULL, NULL)
            ),
            newNode(8,
                NULL,
                newNode(9, NULL, NULL)
            )
        );

    printf("ESEMPIO 1 - Lista di livelli:\n");
    ListaDiListe ldl1 = listaDiLivelli(t1);
    printListaDiListe(ldl1, 0);

    freeListaDiListe(ldl1);
    freeTree(t1);

    /*
        ESEMPIO 2 (più “pieno”):

                 1
               /   \
              2     3
             / \   / \
            4  5  6  7

        Livello 0: 1
        Livello 1: 2 3
        Livello 2: 4 5 6 7
    */
    Albero t2 =
        newNode(1,
            newNode(2,
                newNode(4, NULL, NULL),
                newNode(5, NULL, NULL)
            ),
            newNode(3,
                newNode(6, NULL, NULL),
                newNode(7, NULL, NULL)
            )
        );

    printf("\nESEMPIO 2 - Lista di livelli:\n");
    ListaDiListe ldl2 = listaDiLivelli(t2);
    printListaDiListe(ldl2, 0);

    freeListaDiListe(ldl2);
    freeTree(t2);

    return 0;
}

int calcolaprofondità(Albero t)
    {
    if(t==NULL)
        return 0;
    int sx=calcolaprofondità(t->left);
    int dx=calcolaprofondità(t->right);
    return max(sx, dx)+1;
    }
int max(int a, int b)
    {
    if(a>b)
        return a;
    return b;
}
Lista f(int val, Lista head)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->val=val;
                new->next=NULL;
                return new;
            }
    head->next=f(val, head->next);
    return head;
    }
Lista copialista(Lista l)
    {
    if (l == NULL) return NULL;
    Lista new=(Lista)malloc(sizeof(*new));
    new->val=l->val;
    new->next=copialista(l->next);
    return new;
    }
ListaDiListe creaLDL(ListaDiListe head, Lista l)
    {
        if(head==NULL)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->levelList=copialista(l);
                new->next=NULL;
                return new;
            }
    head->next=creaLDL(head->next, l);
    return head;
    }
Lista riempilivello(Albero tree, int livello, int livello_exp, Lista head)
    {
        if(tree==NULL)
            return head;
        if(livello==livello_exp)
            {
                head=f(tree->val, head);
            }
    head=riempilivello(tree->left, livello+1, livello_exp, head);
    head=riempilivello(tree->right, livello+1, livello_exp, head);
    return head;
    }
ListaDiListe listaDiLivelli(Albero tree)
    {
        if(tree==NULL)
            return NULL;
        int num_livelli=calcolaprofondità(tree);
    ListaDiListe head1=NULL;
        for(int i=0; i<num_livelli; i++)
            {
                Lista l1=NULL;
                head1=creaLDL(head1, riempilivello(tree,0, i, l1));
            }
    return head1;
    }

