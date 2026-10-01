//  Created by Francesco Roscio Ricon on 14/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem {
    char *parola;
    struct Elem *next;
} Nodo;
typedef Nodo *Lista;

typedef struct Elem2 {
    Lista catena;
    struct Elem2 *next;
} NodoTesta;
typedef NodoTesta *ListaDiListe;


void rimuoviCatenePalindrome(ListaDiListe *L);

/* ===== SUPPORTO COSTRUZIONE ===== */

Nodo* newNodo(char *p) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->parola = p;
    n->next = NULL;
    return n;
}

Lista pushBackLista(Lista l, char *p) {
    Nodo *n = newNodo(p);
    if (!l) return n;

    Nodo *cur = l;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return l;
}

NodoTesta* newNodoTesta(Lista catena) {
    NodoTesta *n = (NodoTesta*)malloc(sizeof(NodoTesta));
    n->catena = catena;
    n->next = NULL;
    return n;
}

ListaDiListe pushBackListaDiListe(ListaDiListe L, Lista catena) {
    NodoTesta *n = newNodoTesta(catena);
    if (!L) return n;

    NodoTesta *cur = L;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return L;
}

/* ===== STAMPA ===== */

void stampaLista(Lista l) {
    while (l) {
        printf("%s", l->parola);
        if (l->next) printf(" -> ");
        l = l->next;
    }
}

void stampaListaDiListe(ListaDiListe L) {
    int i = 1;
    printf("=== LISTA DI LISTE ===\n");
    while (L) {
        printf("Catena %d: ", i);
        stampaLista(L->catena);
        printf("\n");
        L = L->next;
        i++;
    }
    printf("\n");
}

/* ===== MAIN DI TEST ===== */

int main() {

    ListaDiListe L = NULL;

    /* Catena 1: 1 palindroma (radar) -> RESTA */
    Lista c1 = NULL;
    c1 = pushBackLista(c1, "casa");
    c1 = pushBackLista(c1, "radar");
    c1 = pushBackLista(c1, "sole");

    /* Catena 2: 2 palindrome (anna, radar) -> DA ELIMINARE */
    Lista c2 = NULL;
    c2 = pushBackLista(c2, "anna");
    c2 = pushBackLista(c2, "radar");
    c2 = pushBackLista(c2, "mare");

    /* Catena 3: 0 palindrome -> RESTA */
    Lista c3 = NULL;
    c3 = pushBackLista(c3, "uno");
    c3 = pushBackLista(c3, "due");
    c3 = pushBackLista(c3, "tre");

    /* Catena 4: 3 palindrome (otto, anna, radar) -> DA ELIMINARE */
    Lista c4 = NULL;
    c4 = pushBackLista(c4, "otto");
    c4 = pushBackLista(c4, "anna");
    c4 = pushBackLista(c4, "radar");

    L = pushBackListaDiListe(L, c1);
    L = pushBackListaDiListe(L, c2);
    L = pushBackListaDiListe(L, c3);
    L = pushBackListaDiListe(L, c4);

    printf("PRIMA della rimozione:\n");
    stampaListaDiListe(L);

    
    rimuoviCatenePalindrome(&L);

    printf("DOPO la rimozione:\n");
    stampaListaDiListe(L);

    return 0;
}
int palindroma(char parola[])
    {
    int i=0;
    int j=strlen(parola)-1;
    while(i<j)
        {
            if(parola[i]!=parola[j])
                return 0;
            i++;
            j--;
        }
    return 1;
    }
int countpalindrome(Lista head) // mi dice se eliminare o meno
    {
        int count=0;
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(palindroma(head->parola))
                    count++;
                head=head->next;
            }
        if(count>=2)
            return 1;
    return 0;
    }
void rimuoviCatenePalindrome(ListaDiListe *L)
    {
        if(*L==NULL)
            return;
    ListaDiListe *pp=L;
    while(*pp!=NULL)
        {
            if(countpalindrome((*pp)->catena))
                {
                    ListaDiListe temp=(*pp);
                    (*pp)=(*pp)->next;
                    free(temp);
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
