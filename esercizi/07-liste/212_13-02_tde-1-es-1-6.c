//  Created by Francesco Roscio Ricon on 13/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int partitaIVA;
    char *nome;
    int numSingole;
    int numDoppie;
    struct Node *next;
} Nodo;

typedef Nodo* Lista;

Lista estraiInOrdine(Lista lis);   // TODO: da implementare

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

Nodo* newHotel(int piva, const char* nome, int sing, int dopp) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->partitaIVA = piva;
    n->nome = strdup(nome);
    n->numSingole = sing;
    n->numDoppie = dopp;
    n->next = NULL;
    return n;
}

Lista inserisciInCoda(Lista head, Nodo* nuovo) {
    if(head == NULL)
        return nuovo;

    Nodo* tmp = head;
    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nuovo;
    return head;
}

void printLista(Lista L) {
    if(L == NULL) {
        printf("NULL\n");
        return;
    }

    while(L != NULL) {
        printf("[PIVA:%d | %s | Sing:%d | Dopp:%d]",
               L->partitaIVA,
               L->nome,
               L->numSingole,
               L->numDoppie);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeLista(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp->nome);
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int ver(Nodo hotel);
Lista inserisciinordien(Lista head, Nodo hotel);
int main() {

    Lista L = NULL;

    L = inserisciInCoda(L, newHotel(300, "HotelRoma", 10, 15));
    L = inserisciInCoda(L, newHotel(120, "HotelMilano", 20, 5));
    L = inserisciInCoda(L, newHotel(450, "HotelVenezia", 8, 12));
    L = inserisciInCoda(L, newHotel(210, "HotelNapoli", 7, 7));
    L = inserisciInCoda(L, newHotel(150, "HotelTorino", 3, 9));

    printf("=== LISTA ORIGINALE ===\n");
    printLista(L);

    Lista R = estraiInOrdine(L);

    printf("\n=== LISTA ESTRATTA (piu doppie che singole, ordinata per PIVA) ===\n");
    printLista(R);

    freeLista(L);
    freeLista(R);

    return 0;
}



Lista estraiInOrdine(Lista lis) {
    if(lis==NULL)
        return lis;
    Lista new=NULL;
    while(lis!=NULL)
        {
            if(ver(*lis))
                {
                    new=inserisciinordien(new, *lis);
                }
            lis=lis->next;
        }
    return new;
}
int ver(Nodo hotel)
    {
        if(hotel.numDoppie>hotel.numSingole)
            return 1;
    return 0;
    }
Lista inserisciinordien(Lista head, Nodo hotel)
    {
        if(head==NULL || hotel.partitaIVA<head->partitaIVA)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                *new=hotel;
                new->nome=malloc(sizeof(char)*(strlen(hotel.nome)+1));
                strcpy(new->nome, hotel.nome);
                new->next=head;
                return new;
            }
        head->next=inserisciinordien(head->next, hotel);
        return head;
    }
