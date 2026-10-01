//
//  main.c
//  albero chat albero 5A  -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
   STRUTTURE DATI
   ======================= */
typedef struct Node {
    char c;
    int n;
    struct Node *left, *right;
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
static Node* newNode(char c, int n, Node* l, Node* r) {
    Node* x = (Node*)malloc(sizeof(Node));
    if (!x) { perror("malloc"); exit(1); }
    x->c = c; x->n = n; x->left = l; x->right = r;
    return x;
}

static Lista cons(int v, Lista next) {
    List* x = (List*)malloc(sizeof(List));
    if (!x) { perror("malloc"); exit(1); }
    x->val = v; x->next = next;
    return x;
}

static void freeLista(Lista l) {
    while (l) { Lista t = l; l = l->next; free(t); }
}

static void freeTree(Albero t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void stampaLista(Lista l) {
    while (l) { printf("%d ", l->val); l = l->next; }
    printf("\n");
}

/* =======================
   ESERCIZIO (pattern scelto)
   ======================= */

/*
  dir: direzione attesa al prossimo passo
       -1 = sinistra
        1 = destra
  idx: posizione corrente nella parola (word[idx] deve matchare t->c)
*/


/* Wrapper: direzione iniziale libera, provo entrambe.
   Preferenza: se esiste in entrambe, prendo quella che parte a sinistra. */
//Lista numeriCheVerificanoParolaZigZag(Albero t, const char *word) {
//  // altrimenti provo iniziando a destra
//}
Lista copialista(Lista head);
/* =======================
   MAIN DI TEST
   ======================= */
Lista numeriCheVerificanoParolaZigZag(Albero t, char parola[]);
int main(void) {
    /*
            (c,10)
            /    \
        (a,7)   (a,99)
           \        \
          (s,8)     (s,3)
          /            \
       (a,2)           (a,4)

      parola = "casa"

      Zig-zag possibile: sx, dx, sx
      c(10) -> a(7) -> s(8) -> a(2)
      output: 10 7 8 2
    */

    Albero t =
        newNode('c', 10,
            newNode('a', 7,
                NULL,
                newNode('s', 8,
                    newNode('a', 2, NULL, NULL),
                    NULL
                )
            ),
            newNode('a', 99,
                NULL,
                newNode('s', 3,
                    NULL,
                    newNode('a', 4, NULL, NULL)
                )
            )
        );

    const char *word = "casa";
    Lista res = numeriCheVerificanoParolaZigZag(t, "casa");

    printf("Parola: %s\n", word);
    printf("Lista numeri (cammino zig-zag che matcha la parola): ");
    if (res) stampaLista(res);
    else printf("NESSUNO\n");

    freeLista(res);
    freeTree(t);
    return 0;
}
Lista invertiLista(Lista l)
{
    if (l == NULL || l->next == NULL)
        return l;
    Lista rest = invertiLista(l->next);
    l->next->next = l;
    l->next = NULL;
    return rest;
}
Lista inserisciintesta(Lista head, int x)
    {
    Lista new=(Lista)malloc(sizeof(*new));
    new->next=head;
    new->val=x;
    return new;
    }
void f(Albero t, Lista *real, Lista prova, int dir, char parola[], int segna) // dir=1 vado a dx, dir=-1 vado a sx
    {
        if(t==NULL)
            return;
        if(parola[segna]!=t->c)
            return;
        segna++;
        prova=inserisciintesta(prova, t->n);
        Lista newnode=prova;
        if(dir==1)
            {
                if(t->right!=NULL)
                {
                    f(t->right, real, prova, -dir, parola, segna);
                    free(newnode);
                    return;
                }
            }
        if(dir==-1)
            {
                if(t->left!=NULL)
                {
                    f(t->left, real, prova, -dir, parola, segna);
                    free(newnode);
                    return;
                }
            }
        if(t->right==NULL && t->left==NULL)
            {
                if(parola[segna]=='\0')
                    {
                        *real=copialista(prova);
                        free(newnode);
                        return;
                    }
            }
        free(newnode);
    }
Lista copialista(Lista head)
    {
    if(head==NULL)
        return head;
    Lista new=(Lista)malloc(sizeof(*new));
    new->val=head->val;
    new->next=copialista(head->next);
    return new;
    }
Lista numeriCheVerificanoParolaZigZag(Albero t, char parola[])
    {
    Lista real=NULL;
    f(t, &real, NULL, -1, parola, 0);
    f(t, &real, NULL, 1, parola, 0);
    real=invertiLista(real);
    return real;
    }
