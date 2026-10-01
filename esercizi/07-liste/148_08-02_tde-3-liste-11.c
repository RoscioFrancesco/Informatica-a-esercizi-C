//
//  main.c
//  tde 3 liste -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
    char *nome;
    char categoria;
    int prezzoAlKg;
    struct Product *next;
} Prodotto;

typedef Prodotto *ListaProdotti;

typedef struct Peasant {
    char *cognome;
    char *nome;
    ListaProdotti prodotti;
    struct Peasant *next;
} Contadino;

typedef Contadino *ListaContadini;

/* =========================
   PROTOTIPI FUNZIONI ESERCIZIO (DA FARE)
   ========================= */
float mediaPrezziProdotto(ListaContadini contadini, char *prodotto);
int eliminaProdotto(ListaContadini *contadini, char * prodotto);




/* =========================
   UTILITY
   ========================= */
static char *dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char *)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static ListaProdotti nuovoProdotto(const char *nome, char categoria, int prezzoAlKg) {
    ListaProdotti p = (ListaProdotti)malloc(sizeof(*p));
    if (!p) { perror("malloc"); exit(1); }
    p->nome = dupstr(nome);
    p->categoria = categoria;
    p->prezzoAlKg = prezzoAlKg;
    p->next = NULL;
    return p;
}

static ListaContadini nuovoContadino(const char *cognome, const char *nome) {
    ListaContadini c = (ListaContadini)malloc(sizeof(*c));
    if (!c) { perror("malloc"); exit(1); }
    c->cognome = dupstr(cognome);
    c->nome = dupstr(nome);
    c->prodotti = NULL;
    c->next = NULL;
    return c;
}

/* inserimenti in testa (semplici per test) */
static ListaProdotti pushProdotto(ListaProdotti head, ListaProdotti x) {
    x->next = head;
    return x;
}

static ListaContadini pushContadino(ListaContadini head, ListaContadini x) {
    x->next = head;
    return x;
}

/* stampa */
static void stampaProdotti(ListaProdotti p) {
    while (p) {
        printf("    - %-10s | cat=%c | %d €/Kg\n", p->nome, p->categoria, p->prezzoAlKg);
        p = p->next;
    }
}

static void stampaContadini(ListaContadini c) {
    printf("=== LISTA CONTADINI ===\n");
    while (c) {
        printf("Contadino: %s %s\n", c->cognome, c->nome);
        if (c->prodotti == NULL) {
            printf("    (nessun prodotto)\n");
        } else {
            stampaProdotti(c->prodotti);
        }
        c = c->next;
        printf("\n");
    }
}

/* free */
static void freeProdotti(ListaProdotti p) {
    while (p) {
        ListaProdotti nx = p->next;
        free(p->nome);
        free(p);
        p = nx;
    }
}

static void freeContadini(ListaContadini c) {
    while (c) {
        ListaContadini nx = c->next;
        freeProdotti(c->prodotti);
        free(c->cognome);
        free(c->nome);
        free(c);
        c = nx;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    ListaContadini contadini = NULL;

    /* Creo 3 contadini con liste prodotto */
    ListaContadini c1 = nuovoContadino("Rossi", "Mario");
    c1->prodotti = pushProdotto(c1->prodotti, nuovoProdotto("mele",   'F', 3));
    c1->prodotti = pushProdotto(c1->prodotti, nuovoProdotto("pere",   'F', 4));
    c1->prodotti = pushProdotto(c1->prodotti, nuovoProdotto("patate", 'V', 2));

    ListaContadini c2 = nuovoContadino("Bianchi", "Luca");
    c2->prodotti = pushProdotto(c2->prodotti, nuovoProdotto("mele",   'F', 2));
    c2->prodotti = pushProdotto(c2->prodotti, nuovoProdotto("carote", 'V', 3));

    ListaContadini c3 = nuovoContadino("Verdi", "Anna");
    c3->prodotti = pushProdotto(c3->prodotti, nuovoProdotto("mele", 'F', 5)); /* solo mele */

    /* Inserisco i contadini nella lista (testa) */
    contadini = pushContadino(contadini, c1);
    contadini = pushContadino(contadini, c2);
    contadini = pushContadino(contadini, c3);

    /* STAMPA INIZIALE */
    stampaContadini(contadini);

    /* TEST mediaPrezziProdotto */
    {
        char prodotto[] = "mele";
        float m = mediaPrezziProdotto(contadini, prodotto);
        printf("mediaPrezziProdotto(\"%s\") = %.2f\n", prodotto, m);
    }

    /* TEST eliminaProdotto */
    {
        char prodotto[] = "mele";
        int rimossiDa = eliminaProdotto(&contadini, prodotto);
        printf("eliminaProdotto(\"%s\") -> eliminato da %d contadini\n", prodotto, rimossiDa);
        printf("\nDopo eliminazione:\n");
        stampaContadini(contadini);
    }

    /* cleanup */
    freeContadini(contadini);
    return 0;
}



void datiprodotto(ListaContadini contadini, char prodotto[], float *somma, float *count)
    {
        if(contadini==NULL)
            return;
    ListaContadini scorri=contadini;
    while (scorri!=NULL) {
        ListaProdotti scorri_prodotti=scorri->prodotti;
        while (scorri_prodotti!=NULL) {
            if(strcmp(scorri_prodotti->nome, prodotto))
                {
                    *somma=*somma+scorri_prodotti->prezzoAlKg;
                    (*count)++;
                }
            scorri_prodotti=scorri_prodotti->next;
        }
        scorri=scorri->next;
    }
    }
float mediaPrezziProdotto(ListaContadini contadini, char * prodotto)
    {
    float somma=0;
    float count=0;
    datiprodotto(contadini, prodotto, &somma, &count);
    return somma/count;
    }
//Si codifichi in C la seguente funzione:

ListaProdotti eliminadaprod(ListaProdotti lista, char prodotto[], int *num)
    {
        if(lista==NULL)
            return lista;
    if(strcmp((lista->nome), prodotto)==0)
            {
                *num=1;
                ListaProdotti succ=lista->next;
                free(lista->nome);
                free(lista);
                return eliminadaprod(succ, prodotto, num);
            }
        lista->next=eliminadaprod(lista->next, prodotto, num);
        return lista;
    }
int eliminaProdotto(ListaContadini *contadini, char * prodotto)
    {
        if(*contadini==NULL)
            return 0;
    ListaContadini prec=NULL;
    int somma=0;
    ListaContadini scorri=*contadini;
    while(scorri!=NULL)
        {
            ListaContadini succ=scorri->next;
            int num=0;
            scorri->prodotti=eliminadaprod(scorri->prodotti, prodotto, &num);
            somma=somma+num;
            if(scorri->prodotti==NULL)
                {
                    if(prec==NULL)
                        {
                            *contadini=succ;
                            free(scorri->cognome);
                            free(scorri->nome);
                            free(scorri);
                            scorri=*contadini;
                        }
                    else
                        {
                            prec->next=succ;
                            free(scorri->cognome);
                            free(scorri->nome);
                            free(scorri);
                            scorri=succ;
                        }
            
                }
            else
                {
                    prec=scorri;
                    scorri=succ;
                }
        }
    return somma;
    }
