//  Created by Francesco Roscio Ricon on 09/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

/* =====================
   STRUTTURE DATI (da testo)
   ===================== */
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

/* =====================
   UTILITY DI SUPPORTO PER I TEST
   ===================== */
static ListaLibri aggiungiLibroInTesta(ListaLibri l, const char *titolo, const char *argomento, float prezzo) {
    ListaLibri newL = (ListaLibri)malloc(sizeof(Libro));
    if (!newL) { perror("malloc"); exit(1); }
    strncpy(newL->titolo, titolo, N-1); newL->titolo[N-1] = '\0';
    strncpy(newL->argomento, argomento, N-1); newL->argomento[N-1] = '\0';
    newL->prezzo = prezzo;
    newL->next = l;
    return newL;
}

static ListaAutori aggiungiAutoreInTesta(ListaAutori a, const char *cognome, const char *nome) {
    ListaAutori newA = (ListaAutori)malloc(sizeof(Autore));
    if (!newA) { perror("malloc"); exit(1); }
    strncpy(newA->cognome, cognome, N-1); newA->cognome[N-1] = '\0';
    strncpy(newA->nome, nome, N-1); newA->nome[N-1] = '\0';
    newA->libri = NULL;
    newA->next = a;
    return newA;
}

static void stampaLibri(ListaLibri l) {
    while (l != NULL) {
        printf("    - \"%s\" (%s) %.2f\n", l->titolo, l->argomento, l->prezzo);
        l = l->next;
    }
}

static void stampaAutori(ListaAutori a) {
    while (a != NULL) {
        printf("Autore: %s %s\n", a->nome, a->cognome);
        if (a->libri == NULL) printf("    (nessun libro)\n");
        else stampaLibri(a->libri);
        a = a->next;
    }
}

static void liberaLibri(ListaLibri l) {
    while (l != NULL) {
        ListaLibri tmp = l;
        l = l->next;
        free(tmp);
    }
}

static void liberaAutori(ListaAutori a) {
    while (a != NULL) {
        ListaAutori tmp = a;
        a = a->next;
        liberaLibri(tmp->libri);
        free(tmp);
    }
}
int verificalibri(ListaLibri libri, float P);
/* =====================
   MAIN DI TEST
   ===================== */
int main() {
    ListaAutori autori = NULL;

    /* Creo 3 autori */
    autori = aggiungiAutoreInTesta(autori, "Rossi", "Mario");
    autori = aggiungiAutoreInTesta(autori, "Bianchi", "Luca");
    autori = aggiungiAutoreInTesta(autori, "Verdi", "Anna");

    /* Attacco libri (esempi) */
    autori->libri = aggiungiLibroInTesta(autori->libri, "Algoritmi", "CS", 35.50f);
    autori->libri = aggiungiLibroInTesta(autori->libri, "C per tutti", "Programmazione", 22.00f);

    autori->next->libri = aggiungiLibroInTesta(autori->next->libri, "Database", "SQL", 45.00f);
    autori->next->libri = aggiungiLibroInTesta(autori->next->libri, "Reti", "Sistemi", 30.00f);

    autori->next->next->libri = aggiungiLibroInTesta(autori->next->next->libri, "Analisi 1", "Matematica", 18.00f);
    autori->next->next->libri = aggiungiLibroInTesta(autori->next->next->libri, "Algoritmi", "CS", 50.00f); /* titolo ripetuto su autore diverso */

    printf("=== ARCHIVIO INIZIALE ===\n");
    stampaAutori(autori);

    
    float P = 25.0f;
    int quanti = f(autori, P);
    printf("\nRisultato f(autori, %.2f) = %d\n", P, quanti);

    
    char titoloDaEliminare[N] = "Algoritmi";
    int rimossi = eliminaLibro(autori, titoloDaEliminare);

    printf("\nRisultato eliminaLibro(autori, \"%s\") = %d\n", titoloDaEliminare, rimossi);

    printf("\n=== ARCHIVIO DOPO eliminaLibro ===\n");
    stampaAutori(autori);

    liberaAutori(autori);
    return 0;
}

/* =====================
   STUB FUNZIONI (NON SVOLTE)
   ===================== */
int f(ListaAutori autori, float P) {
    int count=0;
    if(autori==NULL)
        return 0;
    ListaAutori scorri=autori;
    while (scorri!=NULL) {
        if(verificalibri(scorri->libri, P))
            count++;
        scorri=scorri->next;
    }
    return count;
}
int verificalibri(ListaLibri libri, float P)
    {
    int flag=1;
    if(libri==NULL)
        return 0;
    while (libri!=NULL) {
        if(libri->prezzo<P)
            flag=0;
        libri=libri->next;
    }
    return flag;
    }
ListaLibri eliminadalistalibri(ListaLibri head, char titolo[], int *count)
    {
        if(head==NULL)
            return head;
        if(strcmp(head->titolo, titolo)==0)
            {
                ListaLibri temp=head->next;
                *count=1;
                free(head);
                return eliminadalistalibri(temp, titolo, count);
            }
    head->next=eliminadalistalibri(head->next, titolo, count);
    return head;
    }

int eliminaLibro(ListaAutori autori, char * titolo)
    {
        if(autori==NULL)
            return 0;
        int flag=0;
        autori->libri=eliminadalistalibri(autori->libri, titolo, &flag);
        return flag+eliminaLibro(autori->next, titolo);
    }
