//
//  main.c
//  es 6 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;
int collassaInstabili(Lista *head);

/* Utility tipiche (se ti servono) */
Nodo *newNode(int v);
void pushBack(Lista *l, int v);
void stampaLista(Lista l);
void freeLista(Lista *l);

/* Helper per verificare instabilità su una finestra (opzionale) */
int isInstabile(long long somma, int k, int minimo);


Nodo *newNode(int v) {
    /* TODO */
    return NULL;
}

void pushBack(Lista *l, int v) {
    /* TODO */
}

void stampaLista(Lista l) {
    /* TODO */
}

void freeLista(Lista *l) {
    /* TODO */
}

int isInstabile(long long somma, int k, int minimo) {
    /* TODO: return (somma < (long long)k * minimo); */
    return 0;
}

/* ===================== MAIN (TEST) ===================== */
int min(Lista head, int k);
int somma(Lista head, int k);
int èinstabile(Lista head, int k, Lista *finish);
int main(void) {
    Lista l = NULL;

    /* Esempio di input: cambia come vuoi */
    int a[] = {5, 1, 4, 2, 7, 3};
    int n = (int)(sizeof(a) / sizeof(a[0]));

    for (int i = 0; i < n; i++) {
        pushBack(&l, a[i]);
    }

    printf("Lista iniziale: ");
    stampaLista(l);

    int c = collassaInstabili(&l);

    printf("Collassi effettuati: %d\n", c);
    printf("Lista finale: ");
    stampaLista(l);

    freeLista(&l);
    return 0;
}
int distanzadafine(Lista head)
    {
        if(head==NULL)
            return 0;
    int count=0;
        while (head!=NULL)
        {
            count++;
            head=head->next;
        }
    return count;
    }
int èinstabile(Lista head, int k, Lista *finish)
    {
    for(int i=0; i<k; i++)
    {
        *finish=(*finish)->next;
    }
        if(somma(head, k)<k*min(head, k))
            return 1;
        return 0;
    }
int somma(Lista head, int k)
    {
    int ris=0;
    for(int i=0; i<k && head!=NULL; i++) {
        ris=ris+head->valore;
        head=head->next;
        }
        return ris;
    }
int min(Lista head, int k)
    {
    Lista scorri=head;
    int min=head->valore;
    for(int i=0; i<k && scorri!=NULL; i++)
        {
            if(scorri->valore<min)
                min=scorri->valore;
            scorri=scorri->next;
        }
    return min;
    }
void distruggiK(Lista head, int K)
    {
        if(head==NULL || K==0)
            return;
        Lista temp=head->next;
        free(head);
    distruggiK(temp, K-1);
    }
Lista f(Lista head, int *count)
    {
        if(head==NULL)
            return head;
        Lista scorrilista=head;
        while (scorrilista!=NULL) {
            int possibiliK=distanzadafine(scorrilista);
            for(int i=1; i<=possibiliK; i++)
                {
                    Lista finish=scorrilista;
                    if(èinstabile(scorrilista, i, &finish))
                        {
                            scorrilista->valore=somma(scorrilista, i)/i;
                            distruggiK(scorrilista->next, i-1);
                            scorrilista->next=finish;
                            (*count)++;
                        }
                }
        scorrilista=scorrilista->next;
        }
        return head;
    }
int collassaInstabili(Lista *head)
    {
    int count=0;
    Lista l=*head;
    l=f(l, &count);
    *head=l;
    return count;
    }
