//  Created by Francesco Roscio Ricon on 05/02/26.

#include <stdio.h>
#include <stdlib.h>

/* Strutture richieste */
typedef struct nd {
    int n1, n2;
    struct nd *prox;
} Node;

typedef Node *List;

void stampaLista(List l);
void liberaLista(List l);
List inserisciincoda(int piccolo, int grande, List head);
/* Main di test */
List scomponi(int val);
int cons_uguauli(List head, int K);
int Wrapperugauli(List head, int k);
int Wrapperdiverse(List head, int k);
int cons_diverse(List head, int K);
int funz(List head, int k);
int noripetiz(List head, int k);

int main(void) {
    int n;

    printf("Inserisci un intero positivo n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Input non valido.\n");
        return 1;
    }

    List ris = scomponi(n);    // chiamata alla tua funzione

    printf("\nScomposizioni di %d (a>0, b>0, a<b, a+b=n):\n", n);
    if (ris == NULL) {
        printf("(nessuna scomposizione)\n");
    } else {
        stampaLista(ris);
    }
    printf("\n%d", funz(ris, 3));
}

/* Stampa lista: una coppia per riga */
void stampaLista(List l) {
    for (Node *p = l; p != NULL; p = p->prox) {
        printf("<%d,%d>\n", p->n1, p->n2);
    }
}

/* Deallocazione lista */
void liberaLista(List l) {
    while (l != NULL) {
        Node *tmp = l;
        l = l->prox;
        free(tmp);
    }
}


List inserisciincoda(int piccolo, int grande, List head)
    {
        if(head==NULL)
            {
                List new=(List)malloc(sizeof(*new));
                new->prox=NULL;
                new->n1=piccolo;
                new->n2=grande;
                return new;
            }
    head->prox=inserisciincoda(piccolo, grande, head->prox);
    return head;
    }
List scomponi(int val)
    {
    List new=NULL;
    int stop=val/2;
    for(int i=1; i<=stop; i++)
        {
            int piccolo=i;
            int grande=val-i;
            if(piccolo==grande)
                break;
            new=inserisciincoda(piccolo, grande, new);
        }
    return new;
    }

int cons_uguauli(List head, int K)
    {
        if(K==0)
            return 1;
        if(head==NULL || head->prox==NULL)
            return 0;
        if(head->prox->n1!=head->n1 || head->prox->n2!=head->n2)
            return 0;
        return cons_uguauli(head->prox, K-1);
    }
int Wrapperugauli(List head, int k)
    {
        if(head==NULL)
            return 0;
    List scorri=head;
    while (scorri!=NULL) {
        if(cons_uguauli(scorri, k))
            return 1;
        scorri=scorri->prox;
        }
    return 0;
    }

int Wrapperdiverse(List head, int k)
    {
        if(head==NULL)
            return 0;
    List scorri=head;
    while (scorri!=NULL) {
        if(noripetiz(scorri, k))
            return 1;
        scorri=scorri->prox;
        }
    return 0;
    }
int funz(List head, int k)
    {
    return Wrapperugauli(head, k) || Wrapperdiverse(head, k);
    }
int coppieuguali(Node a, Node b)
    {
        if(a.n1==b.n1 && a.n2==b.n2)
            return 1;
        return 0;
    }
int noripetiz(List head, int k)
    {
        if(k==0)
            return 1;
        if(head==NULL)
            return 0;
        List scorri=head->prox;
    int temp=k;
        while (scorri!=NULL && temp>0) {
            if(coppieuguali(*head, *scorri))
                return 0;
            scorri=scorri->prox;
            temp--;
        }
    return noripetiz(head->prox, k-1);
    }
