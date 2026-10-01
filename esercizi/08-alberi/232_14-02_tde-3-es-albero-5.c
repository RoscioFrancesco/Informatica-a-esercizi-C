//
//  main.c
//  tde 3 es albero -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURA DELL'ALBERO
   ========================= */

typedef struct nd {
    char premio[30];
    struct nd *sx, *dx;
} Nodo;

typedef Nodo* Albero;

void arrampica(Albero t, char *codice);
Albero newNodo(const char *premio) {
    Albero n = (Albero)malloc(sizeof(Nodo));
    strcpy(n->premio, premio);
    n->sx = NULL;
    n->dx = NULL;
    return n;
}

void freeTree(Albero t) {
    if(t == NULL) return;
    freeTree(t->sx);
    freeTree(t->dx);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
int f(char parola[], Albero t, int segna);
int main() {

    /*
            RADICE
           /      \
        Bambola   Macchina
        /     \        \
     Palla   Libro    Tablet
    */

    Albero T = newNodo("RADICE");

    T->sx = newNodo("Bambola");
    T->dx = newNodo("Macchina");

    T->sx->sx = newNodo("Palla");
    T->sx->dx = newNodo("Libro");

    T->dx->dx = newNodo("Tablet");

    printf("=== TEST 1 ===\n");
    printf("Codice: S\n");
    arrampica(T, "S");

    printf("\n=== TEST 2 ===\n");
    printf("Codice: SS\n");
    arrampica(T, "SS");

    printf("\n=== TEST 3 ===\n");
    printf("Codice: SD\n");
    arrampica(T, "SD");

    printf("\n=== TEST 4 ===\n");
    printf("Codice: DD\n");
    arrampica(T, "DD");

    printf("\n=== TEST 5 ===\n");
    printf("Codice: DS\n");
    arrampica(T, "DS");

    freeTree(T);
    return 0;
}



void arrampica(Albero t, char *codice) {
    int ris=f(codice, t, 0);
    if(ris==0)
        printf("Perso\n");
}

int f(char parola[], Albero t, int segna)
    {
        if(t==NULL)
            return 0;
        if(parola[segna]=='\0')
        {
            printf("premio: %s", t->premio);
            return 1;
        }
        if(parola[segna]=='S')
            {
                return f(parola, t->sx, segna+1);
            }
        if(parola[segna]=='D')
            {
                return f(parola, t->dx, segna+1);
            }
    return 0;
    }
