//  Created by Francesco Roscio Ricon on 09/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Node {
    int partitaIVA;
    char *nome;
    int numSingole;
    int numDoppie;
    struct Node *next;
} Nodo;

typedef Nodo * Lista;


Lista estraiInOrdine(Lista lis);

/* =========================
   FUNZIONI DI SUPPORTO
   (per creare e stampare)
   ========================= */
Lista inserisciInTesta(Lista head, int piva, char *nome, int singole, int doppie)
{
    Lista n = (Lista)malloc(sizeof(Nodo));
    n->partitaIVA = piva;
    n->nome = strdup(nome);   // solo per test
    n->numSingole = singole;
    n->numDoppie = doppie;
    n->next = head;
    return n;
}

void stampaLista(Lista l)
{
    while (l != NULL) {
        printf("P.IVA: %d | Nome: %s | Singole: %d | Doppie: %d\n",
               l->partitaIVA, l->nome, l->numSingole, l->numDoppie);
        l = l->next;
    }
    printf("----\n");
}

void liberaLista(Lista l)
{
    while (l != NULL) {
        Lista tmp = l;
        l = l->next;
        free(tmp->nome);
        free(tmp);
    }
}

int main()
{
    Lista alberghi = NULL;
    Lista risultato = NULL;

    /* Lista NON ordinata */
    alberghi = inserisciInTesta(alberghi, 345678, "Hotel Luna", 10, 15);
    alberghi = inserisciInTesta(alberghi, 123456, "Hotel Sole", 20, 5);
    alberghi = inserisciInTesta(alberghi, 987654, "Hotel Mare", 8, 12);
    alberghi = inserisciInTesta(alberghi, 555555, "Hotel Stella", 7, 7);

    printf("Lista originale:\n");
    stampaLista(alberghi);

    /* Chiamata funzione richiesta */
    risultato = estraiInOrdine(alberghi);

    printf("Lista estratta (più doppie che singole, ordinata per partitaIVA):\n");
    stampaLista(risultato);

    liberaLista(alberghi);
    liberaLista(risultato);

    return 0;
}
//solo gli alberghi con più doppie
//che singole ordinati per partitaIVA.
int ver(Nodo albergo)
    {
        if(albergo.numDoppie>albergo.numSingole)
            return 1;
    return 0;
    }
Lista inserimentoord(Lista head, Nodo x)
    {
        if(head==NULL || x.partitaIVA < head->partitaIVA)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                *new=x;
                new->nome=malloc(sizeof(char)*(strlen(x.nome)+1));
                strcpy(new->nome, x.nome);
                new->next=head;
                return new;
            }
        head->next=inserimentoord(head->next, x);
        return head;
    }
Lista estraiInOrdine(Lista lis)
    {
        if(lis==NULL)
            return NULL;
        Lista new=NULL;
        while (lis!=NULL) {
            if(ver(*lis))
                {
                    new=inserimentoord(new, *lis);
                }
            lis=lis->next;
        }
        return new;
    }
