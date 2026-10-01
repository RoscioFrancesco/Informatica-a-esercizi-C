//  Created by Francesco Roscio Ricon on 08/02/26.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct t {
    char parola[1000];
    struct t *left, *right;
} Nodo;

typedef Nodo *Tree;

/* =========================
   FUNZIONE DATA DAL TESTO (NON CODIFICARE)
   ========================= */
int simili(char *s1, char *s2);

/* Stub per compilare (DA TOGLIERE quando hai la simili vera) */
int simili(char *s1, char *s2)
{
    int i = 0, j = 0;
    int diff = 0;

    while (s1[i] != '\0' && s2[j] != '\0') {
        if (s1[i] == s2[j]) {
            i++;
            j++;
        } else {
            diff++;
            if (diff > 2) return 0;

            /* prova a saltare un carattere */
            if (s1[i+1] == s2[j]) {
                i++;            // carattere in più in s1
            } else if (s1[i] == s2[j+1]) {
                j++;            // carattere in più in s2
            } else {
                i++;            // caratteri diversi
                j++;
            }
        }
    }

    /* caratteri rimasti */
    while (s1[i] != '\0') {
        diff++;
        i++;
    }
    while (s2[j] != '\0') {
        diff++;
        j++;
    }

    return diff <= 2;
}

/* =========================
   FUNZIONE RICHIESTA (DA FARE)
   ========================= */
int f(Tree t);

/* =========================
   UTILITY: crea nodo, stampa, free
   ========================= */
static Tree nuovoNodo(const char *parola) {
    Tree n = (Tree)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    strncpy(n->parola, parola, sizeof(n->parola) - 1);
    n->parola[sizeof(n->parola) - 1] = '\0';
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaPreorder(Tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("\"%s\" ", t->parola);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /*
        Esempio albero (parole a piacere):

                 "casa"
                /      \
            "cassa"    "cava"
             /           \
         "cassa!"        "cave"

        L'idea dell'esercizio: lungo ogni cammino radice->foglia,
        ogni parola deve essere simile alla successiva.
        Qui NON possiamo sapere il risultato vero senza la simili(),
        quindi il main serve solo a costruire, stampare e chiamare f().
    */

    Tree t = nuovoNodo("casa");
    t->left = nuovoNodo("cassa");
    t->right = nuovoNodo("cava");
    t->left->left = nuovoNodo("cassa!");
    t->right->right = nuovoNodo("cave");

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n\n");

    int ris = f(t);
    printf("f(t) = %d\n", ris);
    printf("(atteso: 1 se TUTTI i cammini radice->foglia sono cctsf, 0 altrimenti)\n");

    freeTree(t);
    return 0;
}

int f(Tree albero)
    {
        if(albero==NULL)
            return 1;
        int sx=1;
        int dx=1;
        if(albero->left!=NULL)
            {
                if(simili(albero->parola, albero->left->parola)==0)
                    return 0;
                sx=f(albero->left);
            }
        if(albero->right!=NULL)
        {
            if(simili(albero->parola, albero->right->parola)==0)
                return 0;
            dx=f(albero->right);
        }
    return sx&&dx;
    }
