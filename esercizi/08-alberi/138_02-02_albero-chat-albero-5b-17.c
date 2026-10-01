//
//  main.c
//  albero chat albero 5B  -17
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

static Node* newNode(char c, int n, Node* l, Node* r) {
    Node* x = (Node*)malloc(sizeof(Node));
    if (!x) { perror("malloc"); exit(1); }
    x->c = c;
    x->n = n;
    x->left = l;
    x->right = r;
    return x;
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

static void stampaLista(Lista l) {
    while (l) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("\n");
}

static void stampaPreorder(Albero t) {
    if (!t) return;
    printf("(%c,%d) ", t->c, t->n);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* =======================
   PROTOTIPI ESERCIZIO 5B
   ======================= */
Lista inserisciincoda(Lista head, int x);
Lista esercizio5B(Albero t, const char *pattern, int k);
Lista copialista(Lista head);
///* helper ricorsivo (DA SVOLGERE) */
//void f(Albero t,
//       const char *pattern, int k,
//       int idx, int dir,
//       int prevN, int hasPrev,
//       int err, int sum,
//       Lista prova,
//       /* struttura best da definire */ void *best);

/* =======================
   MAIN DI TEST
   ======================= */
void f(Albero t, int dir, int wildcard, int K, int numerrori, char parola[], int segna, Lista *real, Lista prova, int depth, int prev, int hasprev, int m);
Lista invertiLista(Lista l);
int main(void) {
    /*
        Albero di test (con scelte “trappola”):

                    (a,10)
                   /      \
              (b,7)       (a,12)
               /  \          \
           (a,6) (c,9)      (b,8)
              \     \        /   \
            (d,5)  (d,4)  (c,11) (c,1)
                   /
                (x,3)

        Proponiamo:
          pattern = "a?cd"
          k = 1

        - lunghezza cammino = 4 nodi
        - zig-zag obbligatorio (due possibili start: sx o dx)
        - alternanza numerica (>/<) può creare errori
        - mismatch lettera può creare errori

        Questo main serve per debug e stress dei casi:
        - rami mancanti (se dir impone un figlio NULL)
        - wildcard
        - mismatch
        - confronto numerico alternato
    */

    Albero t =
        newNode('a', 10,
            newNode('b', 7,
                newNode('a', 6,
                    NULL,
                    newNode('d', 5, NULL, NULL)
                ),
                newNode('c', 9,
                    NULL,
                    newNode('d', 4,
                        newNode('x', 3, NULL, NULL),
                        NULL
                    )
                )
            ),
            newNode('a', 12,
                NULL,
                newNode('b', 8,
                    newNode('c', 11, NULL, NULL),
                    newNode('c', 1, NULL, NULL)
                )
            )
        );

    const char *pattern = "a?cd";
    int k = 1;

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    printf("Pattern: \"%s\" (lunghezza=%d)\n", pattern, (int)strlen(pattern));
    printf("k (errori massimi ammessi): %d\n", k);

    Lista res = esercizio5B(t, pattern, k);

    printf("Cammino scelto (lista di n in ordine): ");
    if (res) stampaLista(res);
    else printf("NESSUN CAMMINO VALIDO\n");

    freeLista(res);
    freeTree(t);
    return 0;
}

/* =======================
   FUNZIONE DA SVOLGERE
   ======================= */

Lista esercizio5B(Albero t, const char *pattern, int k)
{
    Lista head=NULL;
    int m=strlen(pattern);
    f(t, 1, 0, k, 0, pattern, 0, &head, NULL, 0, 0, 0, m);
    if(head==NULL)
    {
        f(t, -1, 0, k, 0, pattern, 0, &head, NULL, 0, 0, 0, m);
    }
    head=invertiLista(head);
    return head;
}


// dir=1 vado a sx, dir=-1 vado a dx
void f(Albero t, int dir, int wildcard, int K, int numerrori, char parola[], int segna, Lista *real, Lista prova, int depth, int prev, int hasprev, int m)
    {
        if(t==NULL)
            return;
        if(parola[segna]!='?')
            {
                if (parola[segna]!=t->c)
                    {
                        return;
                    }
                
            }
        else
            {
                if(wildcard>1)
                    return;
                wildcard++;
            }
        if(hasprev==1)
            {
                if(depth%2==0)
                    {
                        if(t->n<=prev)
                            numerrori++;
                    }
                if(depth%2==1)
                    {
                        if(t->n>=prev)
                            numerrori++;
                    }
            }
    segna++;
    depth++;
    hasprev=1;
    prova=inserisciincoda(prova, t->n);
    if(m==segna)
        {
            if(numerrori>K)
                return;
            *real=copialista(prova);
            freeLista(prova);
            return;
        }
        if(dir==1)
            {
                if(t->left!=NULL)
                    f(t->left, -dir, wildcard, K, numerrori, parola, segna, real, prova, depth, t->n, hasprev, m);
                return;
            }
        if(dir==-1)
            {
                if(t->right!=NULL)
                    f(t->right, -dir, wildcard, K, numerrori, parola, segna, real, prova, depth, t->n, hasprev, m);
                return;
            }
    freeLista(prova);
    }
Lista inserisciincoda(Lista head, int x)
    {
    Lista new=(Lista)malloc(sizeof(*new));
    new->val=x;
    new->next=head;
    return new;
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
Lista invertiLista(Lista l)
{
    if (l == NULL || l->next == NULL)
        return l;
    Lista rest=invertiLista(l->next);
    l->next->next=l;
    l->next=NULL;
    return rest;
}
