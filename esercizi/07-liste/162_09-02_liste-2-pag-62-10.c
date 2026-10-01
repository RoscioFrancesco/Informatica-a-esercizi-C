//
//  main.c
//  liste 2 pag 62 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct N {
    int valore;
    struct N *next;
} Nodo;

typedef Nodo * Lista;


Lista f(Lista A, Lista B);

/* =========================
   UTILITY PER TEST
   ========================= */
static Lista inserisciInCoda(Lista head, int v) {
    if (head == NULL) {
        Lista n = (Lista)malloc(sizeof(Nodo));
        if (!n) { perror("malloc"); exit(1); }
        n->valore = v;
        n->next = NULL;
        return n;
    }
    head->next = inserisciInCoda(head->next, v);
    return head;
}

static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d", l->valore);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}

static void liberaLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista inserisciincoda(Lista head, int x);
int trova(int x, Lista head);

int main(void) {
    Lista A = NULL;
    Lista B = NULL;
    Lista R = NULL;

    /* ESEMPIO DEL TESTO:
       A = 1,3,2,5,3,4,5
       B = 4,2,6,6,4
       Output atteso: 1,3,5,3,5,6,6
    */
    int a_vals[] = {1,3,2,5,3,4,5};
    int b_vals[] = {4,2,6,6,4};

    for (int i = 0; i < (int)(sizeof(a_vals)/sizeof(a_vals[0])); i++)
        A = inserisciInCoda(A, a_vals[i]);

    for (int i = 0; i < (int)(sizeof(b_vals)/sizeof(b_vals[0])); i++)
        B = inserisciInCoda(B, b_vals[i]);

    printf("Lista A: ");
    stampaLista(A);

    printf("Lista B: ");
    stampaLista(B);

    /* Chiamata alla funzione richiesta */
    R = f(A, B);

    printf("Risultato f(A,B): ");
    stampaLista(R);

    

    liberaLista(A);
    liberaLista(B);
    liberaLista(R);

    return 0;
}
//• Si noti che le liste A e B possono contenere dei duplicati; di
//conseguenza anche la lista risultante può contenere duplicati.
//• Ad esempio, se A contiene gli interi 1,3,2,5,3,4,5 (in quest'ordine) e
//B contiene gli interi 4,2,6,6,4 (in quest'ordine) allora la lista
//risultante conterrà gli interi 1,3,5,3,5,6,6 (in quest'ordine).


int trova(int x, Lista head)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(head->valore==x)
            return 1;
        head=head->next;
    }
    return 0;
    }
Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                new->valore=x;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }

Lista f(Lista A, Lista B)
    {
    Lista new=NULL;
    int flag=1;
        if(A==NULL)
            flag=0;
        if(flag==1)
            {
                Lista scorriA=A;
                while (scorriA!=NULL) {
                    if(trova(scorriA->valore, B)==0)
                        {
                            new=inserisciincoda(new, scorriA->valore);
                        }
                    scorriA=scorriA->next;
                }
            }
        if(B==NULL)
            return new;
    Lista scorriB=B;
    while (scorriB!=NULL) {
        if(trova(scorriB->valore, A)==0)
            new=inserisciincoda(new, scorriB->valore);
        scorriB=scorriB->next;
    }
    return new;
    }
