//
//  main.c
//  liste rifaccio n4 chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =======================
   STRUTTURA LISTA PAROLE
   ======================= */
typedef struct Node {
    char *word;          // stringa allocata dinamicamente
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY (solo per test)
   ======================= */

static char* my_strdup(const char *s) {
    if (!s) return NULL;
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
    for (int i = n - 1; i >= 0; --i)
        l = newNode(arr[i], l);
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

/* =======================
   PROPRIETA' ANCHOR (ESEMPIO PER TEST)
   -----------------------
   Per testiamo una proprietà semplice:
   ANCHOR(word) = parola che inizia con '#'
   (es: "#A", "#ancora", "#1" sono ancore)
   ======================= */
static int isAnchorWord(const char *w) {
    return (w != NULL && w[0] == '#');
}

/* =======================
   ESERCIZIO E4 (TODO)
   ======================= */
/*
  TODO: Per ogni nodo che soddisfa ANCHOR, elimina le successive k parole (se esistono).
  - Il nodo ancora resta.
  - Se due ancore sono vicine, le eliminazioni possono sovrapporsi: se un nodo viene eliminato
    non può diventare ancora (priorità alla cancellazione).
  - Senza cicli nella soluzione, O(n).
  - Restituisci anche quante eliminazioni effettive sono state fatte.
*/
int èancora(char parola[]);
Lista f(Lista l, int K, int *removed_count, int skip);
Lista eliminaKDopoAncora(Lista l, int K, int *removed_count);

/* =======================
   FUNZIONE DI TEST (build + stampa prima/dopo)
   ======================= */
static void testCase(const char *title, const char *arr[], int n, int k) {
    printf("=== %s ===\n", title);
    printf("k = %d, ANCHOR = parola che inizia con '#'\n", k);

    Lista L = buildListFromArray(arr, n);

    printf("Prima : ");
    printList(L);

    int removed = 0;

    L=f(L, k, &removed, 0);

    printf("Dopo  : ");
    printList(L);
    printf("Eliminazioni effettive: %d\n", removed);

    freeList(L);
    printf("\n");
}

/* =======================
   MAIN: CASI MIRATI
   ======================= */
int main(void) {
    /* Caso 0: lista vuota */
    {
        const char **arr = NULL;
        testCase("Caso 0: lista vuota", arr, 0, 3);
    }

    /* Caso 1: nessuna ancora -> lista invariata, removed=0 */
    {
        const char *arr[] = {"a", "b", "c", "d"};
        testCase("Caso 1: nessuna ancora", arr, 4, 2);
    }

    /* Caso 2: ancora in testa -> elimina i primi k successivi */
    {
        const char *arr[] = {"#A", "w1", "w2", "w3", "tail"};
        testCase("Caso 2: ancora in testa", arr, 5, 2);
    }

    /* Caso 3: ancora in mezzo -> elimina k successivi, preserva ordine resto */
    {
        const char *arr[] = {"x", "y", "#M", "p", "q", "r", "z"};
        testCase("Caso 3: ancora in mezzo", arr, 7, 3);
    }

    /* Caso 4: ancora vicino alla fine -> eliminazioni effettive < k */
    {
        const char *arr[] = {"a", "b", "c", "#END", "last"};
        testCase("Caso 4: ancora vicino alla fine", arr, 5, 4);
    }

    /* Caso 5: due ancore distanti -> entrambe attive */
    {
        const char *arr[] = {"#A", "1", "2", "3", "#B", "x", "y", "z"};
        testCase("Caso 5: due ancore distanti", arr, 8, 2);
    }

    /* Caso 6: ancore vicine: sovrapposizione (priorità alla cancellazione)
       Esempio: se k=2 e abbiamo "#A", "u", "#B", "v", ...
       "#B" potrebbe cadere dentro il range eliminato da "#A" -> quindi viene eliminata e NON agisce da ancora.
    */
    {
        const char *arr[] = {"#A", "u", "#B", "v", "w", "tail"};
        testCase("Caso 6: ancore vicine (sovrapposizione)", arr, 6, 2);
    }

    /* Caso 7: tre ancore con sovrapposizioni multiple */
    {
        const char *arr[] = {"#1", "a", "#2", "b", "#3", "c", "d", "e"};
        testCase("Caso 7: molte ancore ravvicinate", arr, 8, 2);
    }

    /* Caso 8: k = 0 -> non si elimina nulla */
    {
        const char *arr[] = {"#A", "x", "y", "#B", "z"};
        testCase("Caso 8: k=0", arr, 5, 0);
    }

    return 0;
}

/*
  TODO: Per ogni nodo che soddisfa ANCHOR, elimina le successive k parole (se esistono).
  - Il nodo ancora resta.
  - Se due ancore sono vicine, le eliminazioni possono sovrapporsi: se un nodo viene eliminato
    non può diventare ancora (priorità alla cancellazione).
  - Senza cicli nella soluzione, O(n).
  - Restituisci anche quante eliminazioni effettive sono state fatte.
*/
Lista eliminaKDopoAncora(Lista l, int K, int *removed_count)
    {
    return f(l, K, removed_count, 0);
    }

Lista f(Lista l, int K, int *removed_count, int skip) // skip mi indica quanti elemtin devo ancor aliminare
    {
        if(l==NULL)
            return l;
        if(skip>0)
            {
                Lista temp=l->next;
                free(l->word);
                free(l);
                (*removed_count)++;
                return f(temp, K, removed_count, skip-1);
            }
        if(K>0 && èancora(l->word))
            {
                l->next=f(l->next, K, removed_count, K);
            }
        l->next=f(l->next, K, removed_count, 0);
        return l;
    }
int èancora(char parola[])
    {
        if(parola[0]=='#')
            return 1;
    return 0;
    }
