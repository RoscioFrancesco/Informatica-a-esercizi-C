//
//  main.c
//  tde liste 2 -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA DI FLOAT
   ========================= */
typedef struct Node {
    float val;
    struct Node *next;
} Node;

typedef Node* Lista;

/* =========================
   PROTOTIPO (DA SVOLGERE)
   ========================= */
/*
   Stampa i valori che costituiscono gli X massimi valori contenuti in L
   in ordine decrescente.
   Vincoli/Scelte: puoi stampare anche se X > lunghezza (stampi ciò che c'è).
*/
void stampaXMassimiDec(Lista L, int X); /* TODO */

/* =========================
   UTILITY PER TEST (QUI I CICLI SONO OK)
   ========================= */
static Node* newNode(float v, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if(!n){ perror("malloc"); exit(1); }
    n->val = v;
    n->next = next;
    return n;
}

static Lista fromArray(const float a[], int n) {
    Lista L = NULL;
    for(int i = n-1; i >= 0; --i)
        L = newNode(a[i], L);
    return L;
}

static void printLista(Lista L) {
    printf("Lista: ");
    while(L) {
        printf("%.2f ", L->val);
        L = L->next;
    }
    printf("\n");
}

static void freeLista(Lista L) {
    while(L) {
        Node *tmp = L->next;
        free(L);
        L = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista merge(Lista head);
void stampaXMassimiDec(Lista L, int X);
int main(void) {
    /* esempio del testo: 10 2 3 23 101, X=3 => 101 23 10 */
    float dati[] = {10, 2, 3, 23, 101};
    int n = (int)(sizeof(dati)/sizeof(dati[0]));
    int X = 3;
    Lista L = fromArray(dati, n);
    
    printf("Input:\n");
    printLista(L);
    printf("X = %d\n\n", X);

    printf("Output atteso (per questo input): 101 23 10\n");
    printf("Output prodotto dalla tua funzione: ");
    stampaXMassimiDec(L, X);   
    printf("\n");

    freeLista(L);
    return 0;
}

/*
   Stampa i valori che costituiscono gli X massimi valori contenuti in L
   in ordine decrescente.
   Vincoli/Scelte: puoi stampare anche se X > lunghezza (stampi ciò che c'è).
*/

Lista merge(Lista head)
    {
        if(head==NULL)
            return head;
        for(Lista scorri=head; scorri!=NULL; scorri=scorri->next)
            {
                for(Lista succ=scorri->next; succ!=NULL; succ=succ->next)
                    {
                        if(scorri->val>succ->val)
                            {
                                int temp=succ->val;
                                succ->val=scorri->val;
                                scorri->val=temp;
                            }
                    }
            }
        return head;
    }

void stampaXMassimiDec(Lista L, int X)
    {
    L=merge(L);
    printf("\n");
    Lista scorri=L;
    for(int i=0; i<X; i++)
        {
            printf("%f-->", scorri->val);
            scorri=scorri->next;
        }
    }
