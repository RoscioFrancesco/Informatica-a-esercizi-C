//
//  main.c
//  albero chat albero 4B  -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* Albero;

typedef struct List {
    int val;
    struct List *next;
} List;

typedef List* Lista;

/* =======================
   UTILITY
   ======================= */

static Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

static List* newListNode(int v, List* next) {
    List* n = (List*)malloc(sizeof(List));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = next;
    return n;
}

static void stampaPreorder(Albero t) {
    if (!t) return;
    printf("%d ", t->val);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void stampaLista(Lista l) {
    while (l) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("\n");
}

static void freeTree(Albero t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void freeLista(Lista l) {
    while (l) {
        Lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =======================
   PROTOTIPI ESERCIZIO
   ======================= */

/*
  Struttura risultato consigliata:
  - len   : lunghezza del cammino
  - sum   : somma dei valori
  - path  : lista dei valori del cammino
*/
typedef struct {
    int len;
    int sum;
    Lista path;
} Risultato;
//Risultato f(Albero t, int somma, int len);
Lista camminoMigliore(Albero t);
Lista copialista(Lista head);
/* =======================
   MAIN DI TEST
   ======================= */
void copiarisultato(Lista head, int somma, int len, Risultato *ris);
Lista inserisciincoda(Lista head, int x);
Lista inseriscifront(Lista head, int x);
void f(Albero t, int somma, Risultato *ris, Lista prova, int len, int *lenmax, int *summax);
int main(void) {
    /*
            5
           / \
          7   6
         / \   \
        9   8   10
       /
      12

      Cammini validi:
      5-7-8     (len=3, somma=20 pari)
      5-7-9-12  (len=4, somma=33 dispari -> NO)
      5-6-10    (len=3, somma=21 dispari -> NO)

      Cammino migliore atteso:
      5 -> 7 -> 8
    */

    Albero t =
        newNode(5,
            newNode(7,
                newNode(9,
                    newNode(12, NULL, NULL),
                    NULL
                ),
                newNode(8, NULL, NULL)
            ),
            newNode(6,
                NULL,
                newNode(10, NULL, NULL)
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    Risultato best;
    best.path=NULL;
    best.len=0;
    best.sum=0;
    int lenmax=0;
    int summax=0;
    f(t, 0, &best, NULL, 0, &lenmax, &summax);

    printf("Cammino migliore (len max, somma max, sinistra): ");
    if (best.path)
        stampaLista(best.path);
    else
        printf("NESSUNO\n");

    freeLista(best.path);
    freeTree(t);
    return 0;
}

/* =======================
   FUNZIONI DA SVOLGERE
   ======================= */

void f(Albero t, int somma, Risultato *ris, Lista prova, int len, int *lenmax, int *summax)
    {
        if(t==NULL)
            return;
        prova=inseriscifront(prova, t->val);
        Lista nodocreato=prova;
        len++;
        somma=somma+t->val;
        if(t->left==NULL && t->right==NULL)
            {
                if (somma%2==0) {
                    if(len==*lenmax)
                        {
                            if(somma==*summax)
                                {
                                    return;
                                }
                            if(somma>*summax)
                                {
                                    freeLista(ris->path);
                                    copiarisultato(prova, somma, len, ris);
                                    free(prova);
                                    return;
                                }
                            
                        }
                    if(len>*lenmax)
                        {
                            *lenmax=len;
                            *summax=somma;
                            if(*summax<somma)
                                *summax=somma;
                            freeLista(ris->path);
                            copiarisultato(prova, somma, len, ris);
                            free(prova);
                            return;
                        }
                    if (len == *lenmax && somma == *summax)
                        {
                            free(prova);
                            return;
                        }
                }
            }
        if(t->left!=NULL && t->left->val>t->val)
            f(t->left, somma, ris, prova, len, lenmax, summax);
        if(t->right!=NULL && t->right->val>t->val)
            f(t->right, somma, ris, prova, len, lenmax, summax);
    free(nodocreato);
    }
void copiarisultato(Lista head, int somma, int len, Risultato *ris)
    {
    Lista scorri=head;
    ris->len=len;
    ris->sum=somma;
    ris->path=copialista(head);
    }
Lista copialista(Lista head)
    {
        if(head==NULL)
            return NULL;
        Lista new=(Lista)malloc(sizeof(*new));
        new->val=head->val;
    new->next=copialista(head->next);
    return new;
    }
Lista inseriscifront(Lista head, int x)
    {
    Lista new=(Lista)malloc(sizeof(*new));
    new->val=x;
    new->next=head;
    return new;
    }
