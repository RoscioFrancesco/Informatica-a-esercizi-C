//
//  main.c
//  tde 1 liste -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Studente {
    int matricola;
    char nome[30];
    char cognome[30];
    int voto;
    struct Studente *next;
} Studente;

typedef Studente* ListaStudenti;


/* =========================
   STRUTTURA LISTA DI LISTE
   ========================= */

typedef struct NodoLista {
    int voto;                       // voto della sottolista
    ListaStudenti lista;            // lista studenti con quel voto
    struct NodoLista *next;
} NodoLista;

typedef NodoLista* ListaDiListe;




void eliminaStudente(ListaStudenti *L);
ListaDiListe listaDiStudentiPerVoto(ListaStudenti L);


/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

ListaStudenti creaStudente(int m, char *nome, char *cognome, int voto) {
    ListaStudenti s = malloc(sizeof(Studente));
    if (!s) exit(1);
    s->matricola = m;
    strcpy(s->nome, nome);
    strcpy(s->cognome, cognome);
    s->voto = voto;
    s->next = NULL;
    return s;
}

void inserisciTesta(ListaStudenti *L, ListaStudenti s) {
    s->next = *L;
    *L = s;
}

void stampaListaStudenti(ListaStudenti L) {
    while (L != NULL) {
        printf("[%d] %s %s - voto: %d\n",
               L->matricola, L->nome, L->cognome, L->voto);
        L = L->next;
    }
}

void stampaListaDiListe(ListaDiListe LL) {
    while (LL != NULL) {
        printf("\n=== VOTO %d ===\n", LL->voto);
        stampaListaStudenti(LL->lista);
        LL = LL->next;
    }
}

void liberaListaStudenti(ListaStudenti L) {
    while (L) {
        ListaStudenti tmp = L;
        L = L->next;
        free(tmp);
    }
}

void liberaListaDiListe(ListaDiListe LL) {
    while (LL) {
        NodoLista *tmp = LL;
        liberaListaStudenti(LL->lista);
        LL = LL->next;
        free(tmp);
    }
}


/* =========================
   MAIN DI TEST
   ========================= */
ListaStudenti inserisciincoda(ListaStudenti head, Studente x);
void eliminaStudente(ListaStudenti *L);
ListaDiListe creanuovalista(ListaDiListe head, ListaStudenti nuovo, int voto);

int main() {

    ListaStudenti L = NULL;

    inserisciTesta(&L, creaStudente(1,"Mario","Rossi",30));
    inserisciTesta(&L, creaStudente(2,"Luca","Bianchi",17));
    inserisciTesta(&L, creaStudente(3,"Anna","Verdi",28));
    inserisciTesta(&L, creaStudente(4,"Paolo","Neri",18));
    inserisciTesta(&L, creaStudente(5,"Sara","Blu",17));
    inserisciTesta(&L, creaStudente(6,"Elena","Gialli",30));

    printf("=== LISTA INIZIALE ===\n");
    stampaListaStudenti(L);

    /* ===== TEST eliminaStudente ===== */
    eliminaStudente(&L);

    printf("\n=== DOPO ELIMINAZIONE (<18) ===\n");
    stampaListaStudenti(L);

    ListaDiListe LL = listaDiStudentiPerVoto(L);

    printf("\n=== LISTA DI LISTE PER VOTO ===\n");
    stampaListaDiListe(LL);

    liberaListaDiListe(LL);

    return 0;
}
void eliminaStudente(ListaStudenti *L)
    {
        if(*L==NULL)
            return;
        if((*L)->voto<18)
            {
                ListaStudenti succ=*L;
                *L=(*L)->next;
                free(succ);
                eliminaStudente(L);
            }
    eliminaStudente(&(*L)->next);
    }
ListaStudenti inserisciincoda(ListaStudenti head, Studente x)
    {
        if(head==NULL)
            {
                ListaStudenti new=(ListaStudenti)malloc(sizeof(Studente));
                *new=x;
                new->next=NULL;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
ListaDiListe trova(ListaDiListe head, int x)
    {
        if(head==NULL)
            return 0;
        while (head!=NULL) {
            if(x==head->voto)
                return head;
            head=head->next;
            }
        return NULL;
    }
ListaDiListe creanuovalista(ListaDiListe head, ListaStudenti nuovo, int voto)
    {
        if(head==NULL|| voto<head->voto)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->next=head;
                new->voto=voto;
                new->lista=inserisciincoda(new->lista, *nuovo);
                return new;
            }
        head->next=creanuovalista(head->next, nuovo, voto);
        return head;
    }

ListaDiListe listaDiStudentiPerVoto(ListaStudenti L)
    {
        if(L==NULL)
            return NULL;
    ListaDiListe new=NULL;
    ListaStudenti scorristud=L;
    while (scorristud!=NULL) {
        ListaDiListe punt=trova(new, scorristud->voto);
        if(punt==NULL)
            {
                new=creanuovalista(new, scorristud, scorristud->voto);
            }
        else
            {
                punt->lista=inserisciincoda(punt->lista, *scorristud);
            }
        scorristud=scorristud->next;
        }
    return new;
    }
