//
//  main.c
//  liste 2 pag 85 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo, con refusi corretti)
   ========================= */
typedef struct canz {
    char titolo[100], album[100], artista[200], compositore[100];
    int anno;
} Canzone;

typedef struct ncanz {
    Canzone c;
    struct ncanz *next;
} NodoCanzone;

typedef NodoCanzone *Libreria;

/* =========================
   PROTOTIPI FUNZIONI (ESERCIZIO)
   ========================= */
Libreria aggiungi(Canzone c, Libreria lib);          
Libreria QueenAscoltabili(Libreria lib);             

/* =========================
   UTILITY: STAMPA
   ========================= */
static void stampaCanzone(const Canzone *c) {
    printf("Titolo: %-20s | Album: %-15s | Artista: %-10s | Compositore: %-12s | Anno: %d\n",
           c->titolo, c->album, c->artista, c->compositore, c->anno);
}

static void stampaLibreria(Libreria lib) {
    int i = 1;
    while (lib != NULL) {
        printf("%2d) ", i);
        stampaCanzone(&lib->c);
        lib = lib->next;
        i++;
    }
    if (i == 1) printf("(libreria vuota)\n");
}

/* =========================
   UTILITY: FREE
   ========================= */
static void freeLibreria(Libreria lib) {
    while (lib != NULL) {
        Libreria tmp = lib->next;
        free(lib);
        lib = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int ver(Libreria head);
int main(void) {
    Libreria lib = NULL;

    /* Dati di test (Queen + altri) */
    Canzone c1 = {"Don't Stop Me Now", "Jazz", "Queen", "Freddie Mercury", 1978};
    Canzone c2 = {"Radio Ga Ga", "The Works", "Queen", "Roger Taylor", 1984};  /* fuori range anno */
    Canzone c3 = {"Another One Bites The Dust", "The Game", "Queen", "John Deacon", 1980}; /* compositore diverso */
    Canzone c4 = {"A Kind of Magic", "A Kind of Magic", "Queen", "Roger Taylor", 1986}; /* fuori range */
    Canzone c5 = {"Rock It (Prime Jive)", "The Game", "Queen", "Roger Taylor", 1980}; /* DENTRO range */
    Canzone c6 = {"Under Pressure", "Hot Space", "Queen", "Roger Taylor", 1981}; /* DENTRO range (anche se nella realtà è più complesso, qui solo test) */
    Canzone c7 = {"Money", "The Dark Side", "Pink Floyd", "Roger Waters", 1973}; /* artista diverso */

    lib = aggiungi(c1, lib);
    lib = aggiungi(c2, lib);
    lib = aggiungi(c3, lib);
    lib = aggiungi(c4, lib);
    lib = aggiungi(c5, lib);
    lib = aggiungi(c6, lib);
    lib = aggiungi(c7, lib);

    printf("Libreria (input):\n");
    stampaLibreria(lib);
    
    Libreria q = QueenAscoltabili(lib);
    printf("Risultato QueenAscoltabili (nuova lista):\n");
    stampaLibreria(q);

    freeLibreria(q);

    freeLibreria(lib);
    return 0;
}

Libreria aggiungi(Canzone c, Libreria lib)
{
        if(lib==NULL)
            {
                Libreria new=(Libreria)malloc(sizeof(*new));
                new->c=c;
                new->next=NULL;
                return new;
            }
    lib->next=aggiungi(c, lib->next);
    return lib;
}

Libreria QueenAscoltabili(Libreria lib) {
    Libreria new=NULL;
    Libreria scorri=lib;
    while (scorri!=NULL) {
        if(ver(scorri))
            {
                new=aggiungi(scorri->c, new);
            }
        scorri=scorri->next;
    }
    return new;
}


int ver(Libreria head)
{
    if(head==NULL)
        return 0;
    if(head->c.anno>=1978 && head->c.anno<=1982 && strcmp(head->c.compositore, "Roger Taylor")==0 && strcmp(head->c.artista, "Queen")==0)
        return 1;
    return 0;
}

