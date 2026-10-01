//
//  main.c
//  tde 5 es 2 liste -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct Item {
    int matricola;
    char *cognome;
    char *nome;
    char *ruolo;
    int bonus;
    struct Item *next;
} Cartellino;

typedef Cartellino *ListaDiCartellini;

typedef struct Node {
    int matricola;
    Data data;
    struct Node *next;
} Assenza;

typedef Assenza *ListaDiAssenze;


int distanza(Data d1, Data d2);  // distanza in giorni tra d1 e d2


void aggiornaBonus(ListaDiCartellini lc, ListaDiAssenze la, Data oggi);

/* ===== SUPPORTO TEST ===== */
static Data makeData(int g,int m,int a){ Data d={g,m,a}; return d; }

ListaDiCartellini pushCart(ListaDiCartellini l, int mat, char *cog, char *nom, char *ruolo, int bonus) {
    Cartellino *n = (Cartellino*)malloc(sizeof(Cartellino));
    n->matricola = mat;
    n->cognome = cog;
    n->nome = nom;
    n->ruolo = ruolo;
    n->bonus = bonus;
    n->next = NULL;
    if (!l) return n;
    Cartellino *cur = l;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return l;
}

ListaDiAssenze pushAssenza(ListaDiAssenze l, int mat, Data d) {
    Assenza *n = (Assenza*)malloc(sizeof(Assenza));
    n->matricola = mat;
    n->data = d;
    n->next = NULL;
    if (!l) return n;
    Assenza *cur = l;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return l;
}

void stampaData(Data d) { printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno); }

void stampaCartellini(ListaDiCartellini l) {
    printf("=== CARTELLINI ===\n");
    for (Cartellino *c=l; c; c=c->next) {
        printf("Mat:%d  %s %s  Ruolo:%s  Bonus:%d\n",
               c->matricola, c->cognome, c->nome, c->ruolo, c->bonus);
    }
    printf("\n");
}

void stampaAssenze(ListaDiAssenze l) {
    printf("=== ASSENZE (ordinate per data) ===\n");
    for (Assenza *a=l; a; a=a->next) {
        printf("Mat:%d  Data:", a->matricola);
        stampaData(a->data);
        printf("\n");
    }
    printf("\n");
}

void liberaCartellini(ListaDiCartellini l){
    while(l){ Cartellino *t=l; l=l->next; free(t); }
}
void liberaAssenze(ListaDiAssenze l){
    while(l){ Assenza *t=l; l=l->next; free(t); }
}

int main(void) {
    /* Data di riferimento per “ultimi 30 giorni” */
    Data oggi = makeData(14, 2, 2026);

    /* Cartellini (bonus iniziali) */
    ListaDiCartellini lc = NULL;
    lc = pushCart(lc, 101, "Rossi",  "Mario", "Impiegato",  500);
    lc = pushCart(lc, 102, "Bianchi","Luca",  "Tecnico",    800);
    lc = pushCart(lc, 103, "Verdi",  "Anna",  "Dirigente",  300);
    lc = pushCart(lc, 104, "Neri",   "Sara",  "Impiegato",  200);

    /* Assenze ordinate per data (attenzione: già in ordine crescente) */
    ListaDiAssenze la = NULL;

    /* Dip. 101: 0 assenze negli ultimi 30 giorni (solo una vecchia) */
    la = pushAssenza(la, 101, makeData( 1,  1, 2026));  // vecchia (>30)

    /* Dip. 102: 1 assenza negli ultimi 30 giorni */
    la = pushAssenza(la, 102, makeData(25,  1, 2026));  // dentro 30

    /* Dip. 103: 3 assenze negli ultimi 30 giorni -> -1000 ma non sotto 0 */
    la = pushAssenza(la, 103, makeData(20,  1, 2026));  // dentro 30
    la = pushAssenza(la, 103, makeData(30,  1, 2026));  // dentro 30
    la = pushAssenza(la, 103, makeData(10,  2, 2026));  // dentro 30

    /* Dip. 104: 2 assenze negli ultimi 30 giorni -> nessuna variazione */
    la = pushAssenza(la, 104, makeData(18,  1, 2026));  // dentro 30
    la = pushAssenza(la, 104, makeData( 5,  2, 2026));  // dentro 30

    printf("Oggi = "); stampaData(oggi); printf("\n\n");

    printf("PRIMA dell'aggiornamento:\n");
    stampaCartellini(lc);
    stampaAssenze(la);

    
    aggiornaBonus(lc, la, oggi);

    printf("DOPO l'aggiornamento:\n");
    stampaCartellini(lc);

    liberaCartellini(lc);
    liberaAssenze(la);
    return 0;
}

int bisestile(int anno) {
    if ((anno % 400 == 0) || (anno % 4 == 0 && anno % 100 != 0))
        return 1;
    return 0;
}

int giorniMese(int mese, int anno) {
    int giorni[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (mese == 2 && bisestile(anno))
        return 29;

    return giorni[mese - 1];
}

/* Converte una data nel numero totale di giorni
   trascorsi dal 01/01/0001 */
long giorniTotali(Data d) {
    long totale = 0;

    // anni precedenti
    for (int a = 1; a < d.anno; a++) {
        totale += 365 + bisestile(a);
    }

    // mesi precedenti nell'anno corrente
    for (int m = 1; m < d.mese; m++) {
        totale += giorniMese(m, d.anno);
    }

    // giorni del mese
    totale += d.giorno;

    return totale;
}

/* ===== FUNZIONE RICHIESTA ===== */

int distanza(Data d1, Data d2) {
    long g1 = giorniTotali(d1);
    long g2 = giorniTotali(d2);

    long diff = g1 - g2;
    if (diff < 0) diff = -diff;

    return (int)diff;
}
int contassenza(ListaDiAssenze lista, int cartellino)
    {
        if(lista==NULL)
            return 0;
    ListaDiAssenze scorri=lista;
    Data oggi;
    oggi.anno=2026;
    oggi.mese=2;
    oggi.giorno=14;
    int count=0;
    while(scorri!=NULL)
        {
            if(cartellino==scorri->matricola && distanza(oggi, scorri->data)<30)
                count++;
            scorri=scorri->next;
        }
    return count;
    }
void aggiornaBonus(ListaDiCartellini lc, ListaDiAssenze la, Data oggi)
    {
        if(la==NULL || lc==NULL)
            return;
        while(lc!=NULL)
            {
                int count=contassenza(la, lc->matricola);
                if(count==0)
                    lc->bonus=lc->bonus+1000;
                if(count==2)
                    lc->bonus=lc->bonus-1000;
                if(lc->bonus<0)
                    lc->bonus=0;
                lc=lc->next;
            }
    }
