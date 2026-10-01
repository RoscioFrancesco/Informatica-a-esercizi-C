//
//  main.c
//  albero chat es2 liste da capo -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================
   STRUTTURE DATI
   ========================= */

typedef struct Node {
    char *word;            // allocata dinamicamente
    struct Node *next;
} Node;

typedef Node* Lista;

/* =========================
   PROTOTIPI UTILITY (no cicli)
   ========================= */

static char* str_dup(const char *s);
static Node* newNode(const char *s, Node *next);

static Lista buildFromArrayRec(const char *arr[], int n, int i);
static void printListaRec(Lista l);
static void freeListaRec(Lista l);

/* (opzionale) proprietà del nodo: "solo lettere alfabetiche" */
int soloLettere(const char *s);

/* =========================
   PROTOTIPO ESERCIZIO E11 (DA FARE TU)
   =========================
   - Per ogni blocco di parole "solo lettere", elimina ricorsivamente ogni m-esimo nodo del blocco
   - Fuori dai blocchi: non eliminare e resetta conteggio
   - Conteggio si resetta a inizio blocco e dopo ogni eliminazione
   - No cicli: passa contatore in ricorsione
*/
Lista eliminaAFinestre(Lista head, int m);

/* =========================
   MAIN con 3 casi di test
   ========================= */

int main(void) {
    int m = 3;

    /* Caso 1: blocchi + separatori con cifre/punteggiatura */
    const char *t1[] = { "ciao", "come", "stai", "!!!", "oggi", "bene", "ok2", "fine" };
    Lista l1 = buildFromArrayRec(t1, (int)(sizeof(t1)/sizeof(t1[0])), 0);
    printf("=== TEST 1 (m=%d) ===\n", m);
    printf("Input : "); printListaRec(l1); printf("\n");
    l1 = eliminaAFinestre(l1, m);               // <- DA IMPLEMENTARE
    printf("Output: "); printListaRec(l1); printf("\n\n");
    freeListaRec(l1);

    /* Caso 2: blocchi adiacenti (separati da un solo nodo NON-alfabetico) */
    const char *t2[] = { "AAA", "BBB", "###", "CCC", "DDD", "@", "EEE" };
    Lista l2 = buildFromArrayRec(t2, (int)(sizeof(t2)/sizeof(t2[0])), 0);
    printf("=== TEST 2 (blocchi adiacenti, m=%d) ===\n", m);
    printf("Input : "); printListaRec(l2); printf("\n");
    l2 = eliminaAFinestre(l2, m);               // <- DA IMPLEMENTARE
    printf("Output: "); printListaRec(l2); printf("\n\n");
    freeListaRec(l2);

    /* Caso 3: blocchi di 1 elemento + tanti separatori */
    const char *t3[] = { "x", "1", "y", "??", "z", "!" };
    Lista l3 = buildFromArrayRec(t3, (int)(sizeof(t3)/sizeof(t3[0])), 0);
    printf("=== TEST 3 (blocchi di 1 elemento, m=%d) ===\n", m);
    printf("Input : "); printListaRec(l3); printf("\n");
    l3 = eliminaAFinestre(l3, m);               // <- DA IMPLEMENTARE
    printf("Output: "); printListaRec(l3); printf("\n\n");
    freeListaRec(l3);

    return 0;
}



static char* str_dup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *out = (char*)malloc(len + 1);
    if (!out) { fprintf(stderr, "malloc fallita\n"); exit(1); }
    memcpy(out, s, len + 1);
    return out;
}

static Node* newNode(const char *s, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { fprintf(stderr, "malloc fallita\n"); exit(1); }
    n->word = str_dup(s);
    n->next = next;
    return n;
}

static Lista buildFromArrayRec(const char *arr[], int n, int i) {
    if (i >= n) return NULL;
    return newNode(arr[i], buildFromArrayRec(arr, n, i + 1));
}

static void printListaRec(Lista l) {
    if (l == NULL) { printf("NULL"); return; }
    printf("\"%s\"", l->word ? l->word : "(null)");
    printf(" -> ");
    printListaRec(l->next);
}

static void freeListaRec(Lista l) {
    if (!l) return;
    freeListaRec(l->next);
    free(l->word);
    free(l);
}

/* "solo lettere alfabetiche": true se ogni char è isalpha */
int soloLettere(const char *s) {
    if (s == NULL) return 0;
    if (*s == '\0') return 0; // stringa vuota: scegliamo "non valida" per blocco
    unsigned char c = (unsigned char)*s;
    if (!isalpha(c)) return 0;
    return soloLettere(s + 1);
}

/* =========================
   STUB ESERCIZIO (NON SVOLTO)
   ========================= */

Lista f(Lista node, int m, int c)
{
    if (node == NULL)
        return NULL;
    if (soloLettere(node->word) == 0)
    {
        node->next = f(node->next, m, 1);   // reset contatore
        return node;
    }
    
    if (c == m)
    {
        Lista temp = node->next;
        free(node->word);
        free(node);
        return f(temp, m, 1);               // reset dopo eliminazione
    }

    /* nodo dentro il blocco ma non m-esimo */
    node->next = f(node->next, m, c + 1);
    return node;
}
Lista eliminaAFinestre(Lista head, int m)
    {
//        if(head==NULL)
//            return head;
    return f(head, m, 1);
    }
