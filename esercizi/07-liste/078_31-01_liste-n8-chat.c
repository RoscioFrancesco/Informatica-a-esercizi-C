//  Created by Francesco Roscio Ricon on 31/01/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
   STRUTTURA LISTA
   ======================= */
typedef struct Node {
    char *word;
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY (creazione/gestione)
   ======================= */
Lista funz(Lista head);
int trovaparola(Lista start, char parola[]);
static char* str_dup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Node* newNode(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = str_dup(w);
    n->next = next;
    return n;
}

/* Costruisce lista da array di stringhe (mantiene ordine) */
static Lista buildList(const char *arr[], int n) {
    Lista head = NULL, tail = NULL;
    for (int i = 0; i < n; i++) {
        Node *node = newNode(arr[i], NULL);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }
    return head;
}

static void printList(Lista l) {
    printf("[");
    while (l) {
        printf("\"%s\"", l->word ? l->word : "(null)");
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]\n");
}

static void freeList(Lista l) {
    while (l) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}

/* Verifica semplice: conta nodi */
static int lengthList(Lista l) {
    int c = 0;
    while (l) { c++; l = l->next; }
    return c;
}

/* =======================
   PROTOTIPO ESERCIZIO (TUO)
   ======================= */

Lista eliminaDupUltima(Lista head);  // <-- implementa TU questa

/* =======================
   TEST
   ======================= */

static void runTest(const char *name, const char *arr[], int n) {
    printf("\n=== %s ===\n", name);
    Lista l = buildList(arr, n);

    printf("Input  : ");
    printList(l);

    l = funz(l);

    printf("Output : ");
    printList(l);

    printf("Len    : %d\n", lengthList(l));
    freeList(l);
}

int main(void) {
    /* Caso 1: duplicati sparsi */
    const char *t1[] = {"casa","mare","casa","sole","mare","casa"};
    runTest("T1 duplicati sparsi", t1, 6);
    // atteso: mantiene SOLO ultime occorrenze => ["sole" e le ultime di "mare" e "casa"] (ordine coerente col tuo approccio)

    /* Caso 2: tutti uguali */
    const char *t2[] = {"x","x","x","x"};
    runTest("T2 tutti uguali", t2, 4);

    /* Caso 3: nessun duplicato */
    const char *t3[] = {"a","b","c","d"};
    runTest("T3 nessun duplicato", t3, 4);

    /* Caso 4: duplicati consecutivi */
    const char *t4[] = {"aa","aa","bb","bb","bb","cc"};
    runTest("T4 consecutivi", t4, 6);

    /* Caso 5: stringhe con maiuscole/minuscole (strcmp è case-sensitive) */
    const char *t5[] = {"Roma","roma","ROMA","Roma"};
    runTest("T5 case-sensitive", t5, 4);

    /* Caso 6: singolo elemento */
    const char *t6[] = {"solo"};
    runTest("T6 singolo", t6, 1);

    /* Caso 7: lista vuota */
    runTest("T7 vuota", NULL, 0);

    return 0;
}

int trovaparola(Lista start, char parola[])
    {
        if(start==NULL)
            return 0;
        if(strcmp(start->word, parola)==0)
            {
                return 1;
            }
    return trovaparola(start->next, parola);
    }
Lista funz(Lista head)
    {
        if(head==NULL)
            return head;
        if(trovaparola(head->next, head->word))
            {
                Lista temp=head->next;
                free(head->word);
                free(head);
                return funz(temp);
            }
    head->next=funz(head->next);
    return head;
    }
