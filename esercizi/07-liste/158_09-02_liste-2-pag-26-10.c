//
//  main.c
//  liste 2 pag 26 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
/*
 * ESERCIZIO: Pulizia di una Lista di Liste (Filtro Catene CCTSF)
 * 
 * Sono date le seguenti strutture dati:
 * - 'Lista' (Nodo): una lista concatenata in cui ogni nodo contiene una stringa 
 *   allocata dinamicamente ('parola').
 * - 'ListaDiListe' (NodoTesta): una lista concatenata in cui ogni nodo contiene 
 *   a sua volta una 'Lista' (chiamata 'catena').
 * 
 * DEFINIZIONI:
 * 1. Due stringhe si dicono "simili" se hanno la stessa esatta lunghezza e 
 *    differiscono per al massimo 2 caratteri nello stesso indice.
 * 2. Una catena (Lista) si definisce "CCTSF" se, per ogni coppia di nodi 
 *    adiacenti al suo interno, le due parole contenute sono "simili". 
 *    (Nota: una catena vuota o composta da un solo nodo è sempre considerata CCTSF).
 * 
 * RICHIESTA:
 * Scrivere una funzione in C con la seguente firma:
 * 
 *      ListaDiListe pulisciNonCCTSF(ListaDiListe L);
 * 
 * La funzione riceve in input il puntatore alla testa di una ListaDiListe.
 * Deve esplorare la struttura e RIMUOVERE dalla lista principale tutti i nodi 
 * la cui 'catena' interna NON rispetta la proprietà CCTSF.
 * 
 * Gestione della memoria:
 * Per ogni elemento rimosso, la funzione deve deallocare correttamente e 
 * completamente la memoria ad esso associata (utilizzando la funzione free()).
 * Questo include:
 * - Le stringhe ('parola') allocate dinamicamente.
 * - I nodi ('Nodo') della sotto-lista.
 * - Il nodo ('NodoTesta') della lista principale.
 * 
 * La funzione deve restituire il puntatore alla testa della ListaDiListe 
 * aggiornata, mantenendo intatto l'ordine delle catene valide superstiti.
 * È consentito (e consigliato) l'uso di funzioni ausiliarie (es. per verificare 
 * la similarità, per testare la proprietà CCTSF e per la distruzione delle liste).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Elem {
    char *parola;
    struct Elem *next;
} Nodo;
typedef Nodo *Lista;

typedef struct Elem2 {
    Lista catena;           /* da ogni NodoTesta inizia una Lista */
    struct Elem2 *next;
} NodoTesta;
typedef NodoTesta *ListaDiListe;

/* =========================
   PROTOTIPI (simili e f già noti)
   ========================= */
int simili(char s1[], char s2[]);   /* nel compito può essere data */
int f(Lista l);                     /* 1 se catena cctsf, 0 altrimenti */


ListaDiListe pulisciNonCCTSF(ListaDiListe L);  

/* =========================
   SUPPORTO: gestione Lista di parole
   ========================= */
static Lista push_back_parola(Lista l, const char *s) {
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }

    n->parola = (char *)malloc(strlen(s) + 1);
    if (!n->parola) { perror("malloc"); exit(1); }
    strcpy(n->parola, s);

    n->next = NULL;

    if (l == NULL) return n;
    Nodo *cur = l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return l;
}

static void stampaCatena(Lista l) {
    printf("[");
    while (l != NULL) {
        printf("\"%s\"", l->parola);
        if (l->next != NULL) printf(" -> ");
        l = l->next;
    }
    printf("]");
}

static void freeCatena(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l->next;
        free(l->parola);
        free(l);
        l = tmp;
    }
}

/* =========================
   SUPPORTO: gestione ListaDiListe
   ========================= */
static ListaDiListe push_back_catena(ListaDiListe L, Lista catena) {
    NodoTesta *n = (NodoTesta *)malloc(sizeof(NodoTesta));
    if (!n) { perror("malloc"); exit(1); }
    n->catena = catena;
    n->next = NULL;

    if (L == NULL) return n;
    NodoTesta *cur = L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return L;
}

static void stampaListaDiListe(ListaDiListe L) {
    int i = 1;
    while (L != NULL) {
        printf("Catena %d: ", i);
        stampaCatena(L->catena);
        /* utile per debug: vedi se è cctsf secondo la tua f(...) */
        printf("   (f=%d)\n", f(L->catena));
        L = L->next;
        i++;
    }
    if (i == 1) printf("(ListaDiListe vuota)\n");
}

static void freeListaDiListe(ListaDiListe L) {
    while (L != NULL) {
        NodoTesta *tmp = L->next;
        freeCatena(L->catena);
        free(L);
        L = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void distruggilista(Lista head);
int main(void) {
    ListaDiListe LL = NULL;

    /* Catena 1 */
    Lista c1 = NULL;
    c1 = push_back_parola(c1, "cane");
    c1 = push_back_parola(c1, "pane");
    c1 = push_back_parola(c1, "pale");
    LL = push_back_catena(LL, c1);

    /* Catena 2 */
    Lista c2 = NULL;
    c2 = push_back_parola(c2, "casa");
    c2 = push_back_parola(c2, "mare");
    LL = push_back_catena(LL, c2);

    /* Catena 3 */
    Lista c3 = NULL;
    c3 = push_back_parola(c3, "polo");
    c3 = push_back_parola(c3, "pollo");
    c3 = push_back_parola(c3, "palla");
    LL = push_back_catena(LL, c3);

    printf("=== PRIMA PULIZIA ===\n");
    stampaListaDiListe(LL);

    
    LL = pulisciNonCCTSF(LL);

    printf("\n=== DOPO PULIZIA (rimangono solo cctsf) ===\n");
    stampaListaDiListe(LL);

    /* Alla fine libera tutto quel che resta */
    freeListaDiListe(LL);

    return 0;
}

int simili(char s1[], char s2[]) {
    int len1 = strlen(s1), len2 = strlen(s2);
    if (len1 != len2) return 0;

    int diff = 0;
    for (int i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) diff++;
        if (diff > 2) return 0;
    }
    return 1;
}
int f(Lista l)
    {
        if(l==NULL || l->next==NULL)
            return 1;
        Lista succ=l->next;
    return simili(l->parola, succ->parola)&&f(succ);
    }


void distruggilista(Lista head)
    {
        if(head==NULL)
            return;
        Lista temp=head->next;
        free(head->parola);
        free(head);
    distruggilista(temp);
    }
ListaDiListe pulisciNonCCTSF(ListaDiListe L)
    {
        if(L==NULL)
            return L;
        if(f(L->catena)==0)
            {
                ListaDiListe temp=L->next;
                distruggilista(L->catena);
                free(L);
                return pulisciNonCCTSF(temp);
            }
    L->next=pulisciNonCCTSF(L->next);
    return L;
    }
