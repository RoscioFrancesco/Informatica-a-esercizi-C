//
//  main.c
//  es 1 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ====== STRUTTURE (come da testo) ====== */
typedef struct nodo {
    char *parola;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;

/* ====== PROTOTIPI ====== */
int verificaCoerenza(Lista l);
int correggiCoerenza(Lista *l);

/* ====== FUNZIONI DI SUPPORTO (per test) ====== */
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

static void stampaLista(Lista l) {
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

/* ====== LOGICA ESERCIZIO ====== */
static int fortementeCompatibili(const char *p, const char *q) {
    if (!p || !q) return 0;
    size_t lp = strlen(p), lq = strlen(q);
    if (lp == 0 || lq == 0) return 0;
    return (p[lp - 1] == q[0]) && (lp != lq);
}
/* ====== MAIN DI TEST ====== */
int verificacoppia(char parola1[], char parola2[]);
int verificaCoerenza(Lista l);
Lista f(Lista head);
void distruggi(Lista a, Lista b);
int main(void) {
    Lista l1 = NULL;
    /* Esempio coerente: a->a e lunghezze diverse */
    pushBack(&l1, "casa");     /* a */
    pushBack(&l1, "amore");    /* a... (len diversa da "casa") */
    pushBack(&l1, "estate");   /* e... (len diversa da "amore") */
    pushBack(&l1, "ele");      /* e... (len diversa da "estate") */

    printf("Lista l1:\n");
    stampaLista(l1);
    printf("verificaCoerenza(l1) = %d\n", verificaCoerenza(l1));
    printf("correggiCoerenza(l1) = %d\n", correggiCoerenza(&l1));
    printf("Dopo correzione l1:\n");
    stampaLista(l1);
    printf("\n");

    Lista l2 = NULL;
    /* Esempio con blocchi non coerenti:
       anchor="casa" (a)
       "amore" ok (a->a, len diversa)
       poi blocco non coerente: "muro"(e? no), "orso"(e? no), "eco"(e? sì con anchor="amore"?)
       Attenzione: il blocco qui è “rispetto all'anchor corrente”.
    */
    pushBack(&l2, "casa");
    pushBack(&l2, "amore");
    pushBack(&l2, "muro");   /* NON compatibile con "amore" (e vs m) -> inizia blocco da eliminare */
    pushBack(&l2, "orso");   /* continua blocco */
    pushBack(&l2, "estate"); /* torna compatibile con "amore" (e->e, len diversa) -> fine blocco */
    pushBack(&l2, "ele");    /* compatibile con "estate" */

    printf("Lista l2 (prima):\n");
    stampaLista(l2);
    printf("verificaCoerenza(l2) = %d\n", verificaCoerenza(l2));
    printf("correggiCoerenza(l2) = %d\n", correggiCoerenza(&l2));
    printf("Lista l2 (dopo):\n");
    stampaLista(l2);

    freeLista(l1);
    freeLista(l2);
    return 0;
}

int verificacoppia(char parola1[], char parola2[])
    {
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    if(len1!=len2 && parola1[len1-1]==parola2[0])
        return 1;
    return 0;
    }
int verificaCoerenza(Lista l)
    {
        if(l==NULL || l->next==NULL)
            return 1;
        if(verificacoppia(l->parola, l->next->parola)==0)
            return 0;
        return verificaCoerenza(l->next);
    }

int correggiCoerenza(Lista *l)
    {
    Lista head=*l;
    if(verificaCoerenza(head)==1)
        return 1;
    head=f(head);
    return 0;
    }
Lista f(Lista head)
    {
        if(head==NULL)
            return head;
    Lista scorri=head;
    Lista prec=NULL;
    while (scorri!=NULL) {
        Lista succ=scorri->next;
        if(succ!=NULL && verificacoppia(scorri->parola, succ->parola)==0)
            {
                Lista ancora=scorri;
                Lista arpione=succ;
                int count=0;
                while (arpione!=NULL && verificacoppia(ancora->parola, arpione->parola)==0) {
                    arpione=arpione->next;
                    count++;
                }
                Lista precedente=ancora;
                while (precedente->next!=arpione) {
                    precedente=precedente->next;
                }
                Lista dopoancora=ancora->next;
                ancora->next=arpione;
                distruggi(dopoancora, precedente);
                scorri=ancora->next;
            }
        else
        {
            prec=scorri;
            scorri=succ;
        }
        }
    return head;
    }
void distruggi(Lista a, Lista b)
    {
    while (a!=NULL && a!=b) {
        Lista temp=a->next;
        free(a->parola);
        free(a);
        a=temp;
        }
    free(b);
    }
