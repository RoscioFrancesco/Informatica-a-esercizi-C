//
//  main.c
//  es 5 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
//
//
//Che:
//
//elimina il minimo numero di nodi possibile
//in modo che la lista finale sia valida
//se esistono più soluzioni, va scelta quella che:
//preserva il maggior numero di nodi iniziali consecutivi
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char *parola;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;

/* =========================
   PROTOTIPO FUNZIONE (DA SVOLGERE)
   ========================= */
int correggiBersaglioAvanzato(Lista *l);

/* =========================
   UTILITY PER TEST
   ========================= */
static char *dupstr(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n);
    return p;
}

static Nodo *nuovoNodo(const char *parola) {
    Nodo *n = (Nodo *)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    n->parola = dupstr(parola);
    n->next = NULL;
    return n;
}

static void pushBack(Lista *l, const char *parola) {
    Nodo *n = nuovoNodo(parola);
    if (*l == NULL) {
        *l = n;
        return;
    }
    Nodo *c = *l;
    while (c->next) c = c->next;
    c->next = n;
}

static void stampaLista(const char *label, Lista l) {
    printf("%s: ", label);
    while (l) {
        printf("\"%s\"", l->parola);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}

static void freeLista(Lista l) {
    while (l) {
        Nodo *nx = l->next;
        free(l->parola);
        free(l);
        l = nx;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista f(Lista head, int *count, int wait);

int compatibili(char parola1[], char parola2[]);
int maxnuminizialicompatibili(Lista head, Lista *inizio);
int main(void) {
    Lista l = NULL;

    /*
      Lista di test: scegli parole con sovrapposizioni di sottostringhe (>=2)
      e alcune “rompi-catena” per verificare che la tua funzione elimini nodi.
      (Qui NON stiamo risolvendo: solo setup e stampa.)
    */
    pushBack(&l, "casa");
    pushBack(&l, "salone");
    pushBack(&l, "alone");
    pushBack(&l, "pasta");
    pushBack(&l, "stella");
    pushBack(&l, "xyz");
    pushBack(&l, "zebra");
    pushBack(&l, "abra");
    pushBack(&l, "bravo");

    stampaLista("Lista iniziale", l);

    int esito = correggiBersaglioAvanzato(&l);

    printf("correggiBersaglioAvanzato(...) ha restituito: %d\n", esito);
    stampaLista("Lista dopo correzione", l);

    freeLista(l);
    return 0;
}

int compatibili(char parola1[], char parola2[])
    {
    int i=0;
    while (parola1[i]!='\0') {
        if(parola1[i]==parola2[0])
            {
                int j=0;
                int count=0;
                while(parola1[i+j]==parola2[j] && parola1[i+j]!='\0' && parola2[j]!='\0')
                {
                    j++;
                    count++;
                }
                if(count>=2)
                    return 1;
            }
        i++;
        }
    return 0;
    }
//elimina il minimo numero di nodi possibile
//in modo che la lista finale sia valida
//se esistono più soluzioni, va scelta quella che:
//preserva il maggior numero di nodi iniziali consecutivi

int maxnuminizialicompatibili(Lista head, Lista *inizio)
    {
    int count=0;
    Lista scorrilista=head;
    while (scorrilista!=NULL && compatibili(scorrilista->parola, scorrilista->next->parola)==1) {
        scorrilista=scorrilista->next;
        count++;
    }
    *inizio=scorrilista;
    return count;
    }
int correggiBersaglioAvanzato(Lista *l)
    {
    int counteliminati=0;
    Lista head=*l;
    Lista new=NULL;
    int wait=maxnuminizialicompatibili(head, &new);
    head=f(head, &counteliminati, wait);
    *l=head;
    return counteliminati;
    }
Lista f(Lista head, int *count, int wait)
    {
        if(head==NULL || head->next==NULL)
            return head;
    Lista scorri=head->next;
    Lista prec=head;
    int incr=0;
        while(prec!=NULL && scorri!=NULL)
            {
                Lista succ=scorri->next;
                if(compatibili(prec->parola, prec->next->parola)==0 && incr>=wait)
                    {
                        prec->next=succ;
                        free(scorri->parola);
                        free(scorri);
                        scorri=succ;
                        (*count)++;
                    }
                else
                    {
                        prec=scorri;
                        scorri=succ;
                    }
                incr++;
            }
        return head;
    }
