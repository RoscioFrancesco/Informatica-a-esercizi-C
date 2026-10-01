//
//  main.c
//  liste n3 chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

/* =======================
   STRUTTURA LISTA PAROLE
   ======================= */
typedef struct Node {
    char *word;          // stringa dinamica
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY: strdup / newNode / build / print / free
   (possono usare cicli, sono "di test")
   ======================= */

static char* my_strdup(const char *s) {
    size_t n = strlen(s);
    char *d = (char*)malloc(n + 1);
    if (!d) { perror("malloc"); exit(1); }
    memcpy(d, s, n + 1);
    return d;
}

static Node* newNode(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = my_strdup(w);
    n->next = next;
    return n;
}

static Lista buildListFromArray(const char *arr[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i) {
        l = newNode(arr[i], l);
    }
    return l;
}

static void printList(Lista l) {
    printf("[");
    for (Node *p = l; p != NULL; p = p->next) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
    }
    printf("]\n");
}

static void freeList(Lista l) {
    while (l != NULL) {
        Node *tmp = l;
        l = l->next;
        free(tmp->word);
        free(tmp);
    }
}
int BB (char parola[]);
int AA(char parola[]);
Lista eliminafinoaBB(Lista l);
Lista EliminadaAA(Lista head);
int BB (char parola[]);
int AA(char parola[]);
/* =======================
   MATCH REGEX (helper utile per la tua soluzione)
   ======================= */
static int matchRegex(const char *pattern, const char *text) {
    regex_t re;
    int ok = 0;

    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Errore regcomp su pattern: %s\n", pattern);
        return 0;
    }
    ok = (regexec(&re, text, 0, NULL, 0) == 0);
    regfree(&re);
    return ok;
}

/* =======================
   ESERCIZIO E3 (TODO)
   ======================= */
/*
  TODO: elimina ricorsivamente tutte le parole comprese tra un nodo che matcha REGEX_A
  e il successivo che matcha REGEX_B (ESCLUSIVI).
  - A e B NON si eliminano.
  - Se A senza B successivo -> non eliminare nulla dopo quell'A.
  - Preservare ordine relativo dei nodi non rimossi.
  - Vietato creare nuovi nodi.
*/
Lista eliminaIntervalliAB(Lista l, const char *REGEX_A, const char *REGEX_B);

/* =======================
   FUNZIONE DI TEST (build + stampa prima/dopo)
   ======================= */
static void testCase(const char *title, const char *REGEX_A, const char *REGEX_B,
                     const char *arr[], int n) {
    printf("=== %s ===\n", title);
    printf("REGEX_A = /%s/\n", REGEX_A);
    printf("REGEX_B = /%s/\n", REGEX_B);

    Lista L = buildListFromArray(arr, n);

    printf("Prima : ");
    printList(L);

    L=EliminadaAA(L);

    printf("Dopo  : ");
    printList(L);

    freeList(L);
    printf("\n");
}

/* =======================
   MAIN con casi mirati
   ======================= */
int BB (char parola[]);
int AA(char parola[]);
Lista eliminafinoaBB(Lista l);
Lista EliminadaAA(Lista head);
int BB (char parola[]);
int AA(char parola[]);

int main(void) {
    /* Esempio regex:
       - A: parole che iniziano con "AA"
       - B: parole che finiscono con "BB"
       (puoi cambiarle come vuoi)
    */
    const char *A = "^AA";
    const char *B = "BB$";

    /* Caso 1: intervallo completo (A ... B) => elimina solo interno */
    {
        const char *arr[] = {"x", "AA_start", "p", "q", "rBB", "y"};
        testCase("Caso 1: A ... B completo (elimina p,q)", A, B, arr, 6);
    }

    /* Caso 2: più intervalli disgiunti (A...B) poi (A...B) */
    {
        const char *arr[] = {"AA1", "u", "vBB", "keep", "AA2", "m", "n", "zBB", "end"};
        testCase("Caso 2: due intervalli disgiunti", A, B, arr, 9);
    }

    /* Caso 3: A senza B successivo => NON eliminare nulla dopo quell'A */
    {
        const char *arr[] = {"x", "AA_orfano", "p", "q", "r", "fine"};
        testCase("Caso 3: A senza B (intervallo incompleto, non si elimina)", A, B, arr, 6);
    }

    /* Caso 4: B prima di A (B da solo non fa nulla) */
    {
        const char *arr[] = {"tBB", "x", "AA_start", "k", "zBB", "tail"};
        testCase("Caso 4: B prima di A (poi intervallo normale)", A, B, arr, 6);
    }

    /* Caso 5: A e B adiacenti => intervallo interno vuoto (non elimina nulla) */
    {
        const char *arr[] = {"x", "AA_here", "ZBB", "y"};
        testCase("Caso 5: A e B adiacenti (nessun interno)", A, B, arr, 4);
    }

    /* Caso 6: lista vuota */
    {
        const char **arr = NULL;
        testCase("Caso 6: lista vuota", A, B, arr, 0);
    }

    /* Caso 7: A in testa */
    {
        const char *arr[] = {"AA_head", "a", "b", "cBB", "tail"};
        testCase("Caso 7: A in testa", A, B, arr, 5);
    }

    return 0;
}
/*
  TODO: elimina ricorsivamente tutte le parole comprese tra un nodo che matcha REGEX_A
  e il successivo che matcha REGEX_B (ESCLUSIVI).
  - A e B NON si eliminano.
  - Se A senza B successivo -> non eliminare nulla dopo quell'A.
  - Preservare ordine relativo dei nodi non rimossi.
  - Vietato creare nuovi nodi.
*/
/* Esempio regex:
   - A: parole che iniziano con "AA"
   - B: parole che finiscono con "BB"
   (puoi cambiarle come vuoi)
*/

int AA(char parola[])
    {
    int len=strlen(parola);
    if(parola[0]=='A' && parola[1]=='A')
        return 1;
    return 0;
    }
int BB (char parola[])
    {
    int len=strlen(parola);
    if(parola[len-1]=='B' && parola[len-2]=='B')
        return 1;
    return 0;
    }
Lista EliminadaAA(Lista head)
    {
        if(head==NULL)
          return head;
        if(AA(head->word))
            {
                head->next=eliminafinoaBB(head->next);
                if (head->next != NULL && BB(head->next->word))
                    head->next->next = EliminadaAA(head->next->next); // riprendo a cercare dopo B
                    return head;
            }
    head->next=EliminadaAA(head->next);
    return head;
    }

Lista eliminafinoaBB(Lista l)
    {
        if(l==NULL)
            return l;
        Lista next=l->next;
        int stop=BB(l->word);
        if(stop)
            return l;
        free(l->word);
        free(l);
        return eliminafinoaBB(next);
    }
