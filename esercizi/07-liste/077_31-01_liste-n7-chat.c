//  Created by Francesco Roscio Ricon on 31/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
   - qui i cicli sono OK
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

static void printListWords(Lista l) {
    printf("[");
    for (Node *p = l; p != NULL; p = p->next) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
    }
    printf("]");
}

static void printListInts(Lista l) {
    printf("[");
    for (Node *p = l; p != NULL; p = p->next) {
        printf("%d", atoi(p->word));
        if (p->next) printf(" -> ");
    }
    printf("]");
}

static void freeList(Lista l) {
    while (l != NULL) {
        Node *tmp = l;
        l = l->next;
        free(tmp->word);
        free(tmp);
    }
}
Lista wrapper(Lista head);
Lista f(Lista head, char prec[], int *hasprec);
/* =======================
   CONTROLLI (per test)
   ======================= */
static int isStrictlyIncreasing(Lista l) {
    if (!l || !l->next) return 1;
    int prev = atoi(l->word);
    for (Node *p = l->next; p != NULL; p = p->next) {
        int cur = atoi(p->word);
        if (cur <= prev) return 0;
        prev = cur;
    }
    return 1;
}

/* =======================
   OUTPUT E7: lista + numero eliminazioni
   ======================= */
typedef struct {
    Lista head;
    int removed;
} E7Result;


E7Result E7_eliminaNonCrescente(Lista l /*, eventuali parametri ricorsivi */) {
    (void)l;

    E7Result r;
    r.head = l;
    r.removed = 0;

    l=wrapper(l);
    return r;
}

/* =======================
   FUNZIONE DI TEST
   ======================= */
static void testCaseE7(const char *title, const char *arr[], int n) {
    printf("=== %s ===\n", title);

    Lista L = buildListFromArray(arr, n);

    printf("Prima (parole): ");
    printListWords(L);
    printf("\n");

    printf("Prima (atoi)  : ");
    printListInts(L);
    printf("\n");

    E7Result out = E7_eliminaNonCrescente(L);

    printf("Dopo  (parole): ");
    printListWords(out.head);
    printf("\n");

    printf("Dopo  (atoi)  : ");
    printListInts(out.head);
    printf("\n");

    printf("Rimosse: %d\n", out.removed);
    printf("Strictly increasing? %s\n", isStrictlyIncreasing(out.head) ? "SI" : "NO");

    freeList(out.head);
    printf("\n");
}

/* =======================
   MAIN: CASI MIRATI
   ======================= */
int main(void) {

    /* Caso 0: lista vuota */
    {
        const char **arr = NULL;
        testCaseE7("Caso 0: lista vuota", arr, 0);
    }

    /* Caso 1: singolo nodo */
    {
        const char *arr[] = {"10"};
        testCaseE7("Caso 1: singolo nodo", arr, 1);
    }

    /* Caso 2: già strettamente crescente */
    {
        const char *arr[] = {"1", "2", "3", "10"};
        testCaseE7("Caso 2: già crescente", arr, 4);
    }

    /* Caso 3: tutti uguali (patologico) */
    {
        const char *arr[] = {"5", "5", "5", "5"};
        testCaseE7("Caso 3: tutti uguali", arr, 4);
    }

    /* Caso 4: strettamente decrescente (patologico) */
    {
        const char *arr[] = {"9", "7", "3", "1"};
        testCaseE7("Caso 4: decrescente", arr, 4);
    }

    /* Caso 5: alternanza che richiede eliminazioni */
    {
        const char *arr[] = {"1", "3", "2", "4", "3", "5"};
        testCaseE7("Caso 5: alternanza", arr, 6);
    }

    /* Caso 6: con numeri negativi */
    {
        const char *arr[] = {"-3", "-2", "-2", "-1", "0"};
        testCaseE7("Caso 6: negativi e duplicati", arr, 5);
    }

    /* Caso 7: con zeri e spazi (atoi gestisce prefissi/spazi) */
    {
        const char *arr[] = {" 1", "02", "2", " 3", "10"};
        testCaseE7("Caso 7: spazi e zeri", arr, 5);
    }

    /* Caso 8: parole non numeriche (atoi -> 0) */
    {
        const char *arr[] = {"x", "y", "1", "z", "2"};
        testCaseE7("Caso 8: non numeriche (atoi=0)", arr, 5);
    }

    /* Caso 9: grandi salti e violazioni locali */
    {
        const char *arr[] = {"1", "100", "50", "60", "70", "65", "200"};
        testCaseE7("Caso 9: violazioni locali", arr, 7);
    }

    return 0;
}
Lista f(Lista head, char prec[], int *hasprec)
    {
        if(head==NULL)
            return head;
        if(*hasprec==1)
            {
                if(atoi(prec)>=atoi(head->word))
                    {
                        Lista temp=head->next;
                        free(head->word);
                        free(head);
                        return f(temp, prec, hasprec);
                    }
            }
    *hasprec=1;
    head->next=f(head->next, head->word, hasprec);
    return head;
    }
Lista wrapper(Lista head)
    {
    int hasprec=0;
    return f(head, 0, &hasprec);
    }
