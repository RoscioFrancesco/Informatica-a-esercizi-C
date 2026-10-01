//  Created by Francesco Roscio Ricon on 07/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Node {
    int    codice;
    char * cognome;
    char * nome;
    struct Node * next;
} Nodo;

typedef Nodo * Lista;


Lista generaListaOrdinata(Lista lis);
Lista inserisciordinata(Lista head, Nodo dacopiare);
/* =========================
   FUNZIONI DI SUPPORTO (TEST)
   ========================= */
static char *dupstr(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static Lista nuovoNodo(int codice, const char *cognome, const char *nome) {
    Lista n = malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->codice = codice;
    n->cognome = dupstr(cognome);
    n->nome = dupstr(nome);
    n->next = NULL;
    return n;
}

static Lista pushFront(Lista head, Lista n) {
    n->next = head;
    return n;
}

static void stampaLista(Lista l) {
    printf("[\n");
    while (l != NULL) {
        printf("  Codice: %d | Cognome: %-10s | Nome: %s\n",
               l->codice, l->cognome, l->nome);
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Lista next = l->next;
        free(l->cognome);
        free(l->nome);
        free(l);
        l = next;
    }
}

/* =========================
   MAIN (runnabile)
   ========================= */
int main(void) {

    Lista lis = NULL;

    /* Lista NON ordinata */
    lis = pushFront(lis, nuovoNodo(103, "Rossi",   "Luca"));
    lis = pushFront(lis, nuovoNodo(101, "Bianchi", "Marco"));
    lis = pushFront(lis, nuovoNodo(105, "Rossi",   "Anna"));
    lis = pushFront(lis, nuovoNodo(102, "Verdi",   "Giulia"));
    lis = pushFront(lis, nuovoNodo(104, "Bianchi", "Andrea"));

    printf("Lista originale (non ordinata):\n");
    stampaLista(lis);

    
    printf("\nLista ordinata per cognome e nome (ATTESO se implementata):\n");
    Lista ordinata = generaListaOrdinata(lis);
    stampaLista(ordinata);

    /* cleanup */
    freeLista(lis);
    freeLista(ordinata);

    return 0;
}

/* =========================
   STUB: NON SVOLGE L'ESERCIZIO
   ========================= */
Lista generaListaOrdinata(Lista lis) {
    Lista new=NULL;
    if(lis==NULL)
        return new;
    while (lis!=NULL) {
        new=inserisciordinata(new, *lis);
        lis=lis->next;
    }
    return new;
}
Lista inserisciordinata(Lista head, Nodo dacopiare)
    {
        if(head==NULL || strcmp(dacopiare.cognome, head->cognome)<0|| (strcmp(dacopiare.cognome, head->cognome)==0 && strcmp(dacopiare.nome, head->nome)<0))
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                char *nome=malloc(sizeof(char)*(strlen(dacopiare.nome)+1));
                strcpy(nome, dacopiare.nome);
                new->nome=nome;
                char *cognome=malloc(sizeof(char)*(strlen(dacopiare.cognome)+1));
                strcpy(cognome, dacopiare.cognome);
                new->cognome=cognome;
                new->codice=dacopiare.codice;
                return new;
            }
        head->next=inserisciordinata(head->next, dacopiare);
        return head;
    
    }
