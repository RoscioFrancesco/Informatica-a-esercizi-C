//
//  main.c
//  albero tde3
//
//  Created by Francesco Roscio Ricon on 23/01/26.
//  Si codifichi in C la seguente funzione:
//  ListaSpettacoli eliminaSpettacoliVecchi(ListaSpettacoli spettacoli, Data oggi)
//  che elimina gli spettacoli precedenti rispetto alla data passata nel parametro oggi [4 punti].

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct d {
    int giorno, mese, anno;
} Data;

typedef struct spe {
    char codice[N], titolo[N], descrizione[N];
    int costoBiglietto;
    Data data;
    struct spe *next;
} spettacolo;

typedef spettacolo* ListaSpettacoli;
ListaSpettacoli eliminaSpettacoliVecchi (ListaSpettacoli head, Data data_oggi);
/* ---- Funzioni di utilità ---- */


spettacolo* newSpettacolo(const char *cod, const char *tit, const char *desc, int costo, Data d) {
    spettacolo *s = (spettacolo*)malloc(sizeof(spettacolo));
    if (!s) { printf("Errore malloc\n"); exit(1); }

    strncpy(s->codice, cod, N);
    strncpy(s->titolo, tit, N);
    strncpy(s->descrizione, desc, N);
    s->costoBiglietto = costo;
    s->data = d;
    s->next = NULL;
    return s;
}

/* inserimento in lista ordinata per codice */
ListaSpettacoli insertOrdinatoCodice(ListaSpettacoli L, spettacolo *nuovo) {
    if (L == NULL || strcmp(nuovo->codice, L->codice) < 0) {
        nuovo->next = L;
        return nuovo;
    }
    spettacolo *cur = L;
    while (cur->next != NULL && strcmp(nuovo->codice, cur->next->codice) > 0) {
        cur = cur->next;
    }
    nuovo->next = cur->next;
    cur->next = nuovo;
    return L;
}

void stampaLista(ListaSpettacoli L) {
    printf("Lista spettacoli:\n");
    while (L != NULL) {
        printf("  [%s] %s - %02d/%02d/%04d - costo=%d\n",
               L->codice, L->titolo,
               L->data.giorno, L->data.mese, L->data.anno,
               L->costoBiglietto);
        L = L->next;
    }
    printf("\n");
}

void freeLista(ListaSpettacoli L) {
    while (L != NULL) {
        spettacolo *tmp = L;
        L = L->next;
        free(tmp);
    }
}

int verificadata(Data oggi, Data spettacolo);

/* ---------------- MAIN DI TEST ---------------- */

int main() {
    ListaSpettacoli L = NULL;

    /* creo qualche spettacolo con date diverse */
    L = insertOrdinatoCodice(L, newSpettacolo("A010", "Concerto", "Musica live", 30, (Data){10, 1, 2024}));
    L = insertOrdinatoCodice(L, newSpettacolo("A005", "Teatro", "Commedia", 25, (Data){20, 12, 2023}));
    L = insertOrdinatoCodice(L, newSpettacolo("A020", "Opera", "Classica", 60, (Data){5,  3, 2024}));
    L = insertOrdinatoCodice(L, newSpettacolo("A015", "Teatro", "Dramma", 35, (Data){1,  1, 2024}));

    printf("PRIMA dell'eliminazione:\n");
    stampaLista(L);

    Data oggi = {1, 2, 2024};  // 01/02/2024

    L = eliminaSpettacoliVecchi(L, oggi);

    printf("DOPO l'eliminazione (tolti quelli con data < %02d/%02d/%04d):\n",
           oggi.giorno, oggi.mese, oggi.anno);
    stampaLista(L);

    freeLista(L);
    return 0;
}

int verificadata(Data oggi, Data spettacolo)
    {
        if(oggi.anno>spettacolo.anno)
            return 1;
        if(oggi.anno==spettacolo.anno)
            {
                if(oggi.mese>spettacolo.mese)
                    return 1;
                if(oggi.mese==spettacolo.mese)
                    {
                        if(oggi.giorno>spettacolo.giorno)
                            return 1;
                    }
            }
        return 0;
    }

ListaSpettacoli eliminaSpettacoliVecchi (ListaSpettacoli head, Data data_oggi)
    {
        if(head==NULL)
            return head;
    ListaSpettacoli scorri_spettacoli=head;
    ListaSpettacoli prec=NULL;
    while(scorri_spettacoli!=NULL)
        {
            ListaSpettacoli succ=scorri_spettacoli->next;
            if(verificadata(data_oggi, scorri_spettacoli->data))
                {
                    if(prec==NULL)
                        {
                            head=succ;
                            free(scorri_spettacoli);
                            scorri_spettacoli=succ;
                        }
                    else
                        {
                            prec->next=succ;
                            free(scorri_spettacoli);
                            scorri_spettacoli=succ;
                        }
                }
            else
            {
                prec=scorri_spettacoli;
                scorri_spettacoli=scorri_spettacoli->next;
            }
        }
    return head;
    }
