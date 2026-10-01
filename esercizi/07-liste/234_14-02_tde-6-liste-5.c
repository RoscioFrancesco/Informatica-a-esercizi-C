//
//  main.c
//  tde 6 liste -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

typedef struct Book {
    char titolo[N], argomento[N];
    float prezzo;
    struct Book *next;
} Libro;
typedef Libro *ListaLibri;

typedef struct Author {
    char cognome[N], nome[N];
    ListaLibri libri;
    struct Author *next;
} Autore;
typedef Autore *ListaAutori;


int f(ListaAutori autori, float P);
int eliminaLibro(ListaAutori autori, char *titolo);

/* ===== SUPPORTO TEST ===== */
Libro* newLibro(const char *tit, const char *arg, float prezzo) {
    Libro *l = (Libro*)malloc(sizeof(Libro));
    strcpy(l->titolo, tit);
    strcpy(l->argomento, arg);
    l->prezzo = prezzo;
    l->next = NULL;
    return l;
}

Autore* newAutore(const char *cog, const char *nom) {
    Autore *a = (Autore*)malloc(sizeof(Autore));
    strcpy(a->cognome, cog);
    strcpy(a->nome, nom);
    a->libri = NULL;
    a->next = NULL;
    return a;
}

ListaLibri pushLibro(ListaLibri head, Libro *x) {
    if (!head) return x;
    Libro *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = x;
    return head;
}

ListaAutori pushAutore(ListaAutori head, Autore *x) {
    if (!head) return x;
    Autore *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = x;
    return head;
}

void stampaLibri(ListaLibri l) {
    for (Libro *cur = l; cur; cur = cur->next) {
        printf("   - Titolo: %-18s | Argomento: %-10s | Prezzo: %.2f\n",
               cur->titolo, cur->argomento, cur->prezzo);
    }
}

void stampaAutori(ListaAutori a) {
    printf("=== LISTA AUTORI ===\n");
    for (Autore *cur = a; cur; cur = cur->next) {
        printf("Autore: %s %s\n", cur->cognome, cur->nome);
        if (!cur->libri) printf("   (nessun libro)\n");
        else stampaLibri(cur->libri);
    }
    printf("\n");
}

void liberaLibri(ListaLibri l) {
    while (l) { Libro *t = l; l = l->next; free(t); }
}

void liberaAutori(ListaAutori a) {
    while (a) {
        Autore *t = a;
        a = a->next;
        liberaLibri(t->libri);
        free(t);
    }
}
ListaLibri eliminalibro(ListaLibri head, char titolo[], int *flag);
int main(void) {
    /* Costruzione dati di test */

    ListaAutori autori = NULL;

    Autore *a1 = newAutore("Rossi", "Mario");
    a1->libri = pushLibro(a1->libri, newLibro("C_base",     "prog",   19.90f));
    a1->libri = pushLibro(a1->libri, newLibro("Algoritmi",  "cs",     24.50f));
    a1->libri = pushLibro(a1->libri, newLibro("Reti",       "reti",   35.00f));

    Autore *a2 = newAutore("Bianchi", "Luca");
    a2->libri = pushLibro(a2->libri, newLibro("C_base",     "prog",   18.00f));  // stesso titolo di a1
    a2->libri = pushLibro(a2->libri, newLibro("Database",   "db",     22.00f));

    Autore *a3 = newAutore("Verdi", "Anna");
    a3->libri = pushLibro(a3->libri, newLibro("Poesie",     "arte",   9.99f));
    a3->libri = pushLibro(a3->libri, newLibro("Romanzo",    "arte",   12.00f));

    autori = pushAutore(autori, a1);
    autori = pushAutore(autori, a2);
    autori = pushAutore(autori, a3);

    printf("STATO INIZIALE:\n");
    stampaAutori(autori);

    /* ===== TEST f(autori, P) ===== */
    float P = 25.0f;
    int count = f(autori, P);
    printf("Chiamata: f(autori, %.2f)\n", P);
    printf("Risultato f = %d\n\n", count);

    /* ===== TEST eliminaLibro(autori, titolo) ===== */
    char titoloDaEliminare[] = "C_base";
    int rimossi = eliminaLibro(autori, titoloDaEliminare);
    printf("Chiamata: eliminaLibro(autori, \"%s\")\n", titoloDaEliminare);
    printf("Numero autori da cui e' stato eliminato = %d\n\n", rimossi);

    printf("STATO DOPO eliminaLibro:\n");
    stampaAutori(autori);

    liberaAutori(autori);
    return 0;
}
int verificaautore(ListaLibri head, float prezzo) // autore verifica la proprità
    {
        if(head==NULL)
            return 1;
        ListaLibri scorri=head;
        while(scorri!=NULL)
            {
                if(scorri->prezzo>prezzo)
                    return 0;
                scorri=scorri->next;
            }
        return 1;
    }
int f(ListaAutori autori, float P)
    {
        if(autori==NULL)
            return 0;
    int count=0;
        while(autori!=NULL)
            {
                if(verificaautore(autori->libri, P))
                    count++;
                autori=autori->next;
            }
    return count;
    }


int eliminaLibro(ListaAutori autori, char * titolo)
    {
        if(autori==NULL)
            return 0;
    int count=0;
        while(autori!=NULL)
            {
                int flag=0;
                autori->libri=eliminalibro(autori->libri, titolo, &flag);
                count=count+flag;
                autori=autori->next;
            }
    return count;
    }

ListaLibri eliminalibro(ListaLibri head, char titolo[], int *flag)
    {
        if(head==NULL)
            return head;
        if(strcmp(head->titolo, titolo)==0)
            {
                ListaLibri succ=head->next;
                free(head);
                (*flag)=1;
                return eliminalibro(succ, titolo, flag);
            }
    head->next=eliminalibro(head->next, titolo, flag);
    return head;
    }
