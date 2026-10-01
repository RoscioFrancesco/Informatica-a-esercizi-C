//  Created by Francesco Roscio Ricon on 03/02/26.

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
Lista f(Lista head);
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
Lista eliminafinoaFinish(Lista start, Lista finish);
/* =======================
   HELPER: iniziale case-insensitive
   - se stringa vuota, ritorna '\0'
   ======================= */
static char firstCharCI(const char *w) {
    if (w == NULL || w[0] == '\0') return '\0';
    return (char)tolower((unsigned char)w[0]);
}

/* =======================
   ESERCIZIO E6 (TODO)
   ======================= */


/* info minima per identificare la run da eliminare (esempio) */
typedef struct {
    int start_index;   // indice di inizio run (0-based)
    int length;        // lunghezza run
} RunInfo;
Lista EliminadaStart(Lista head, Lista start, Lista finish);
Lista Eliminafinoafinish(Lista head, Lista finish);
Lista funz(Lista head);
void wrapper(Lista head, Lista *start_max, Lista *finish_max);
void runmax(Lista head, int *len_max, Lista *prec_startmax, Lista *startmax, Lista *finish);
void trovarun(Lista start, Lista *finish, char lettera, int *contatore);

/* TODO: fase 1 - calcola quale run eliminare */
RunInfo trovaRunMassima(Lista l);

/* TODO: fase 2 - elimina la run indicata (ricorsiva), ritorna nuova head */
Lista eliminaRun(Lista l, RunInfo r);

/* wrapper finale (facoltativo) */
static Lista eliminaRunMassima(Lista l) {
    l=funz(l);
    return l;
}

/* =======================
   FUNZIONE DI TEST
   ======================= */
//Lista eliminafinoaFinish(Lista start, Lista finish);
//void runmax(Lista head, Lista *start_max, Lista *finish_max, int *len_max, Lista *prec_startmax, Lista prec_head);
//void run(Lista start, Lista *finish, char lettera, int *contatore);
//Lista f(Lista head);

void run(Lista start, Lista *finish, int *count, char lettera);
Lista Eliminarun(Lista head);
static void testCase(const char *title, const char *arr[], int n) {
    printf("=== %s ===\n", title);

    Lista L = buildListFromArray(arr, n);

    printf("Prima : ");
    printList(L);

    
    L = Eliminarun(L);

    printf("Dopo  : ");
    printList(L);

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
        testCase("Caso 0: lista vuota", arr, 0);
    }

    /* Caso 1: una sola parola -> run max di lunghezza 1 (se decidi di eliminarla) */
    {
        const char *arr[] = {"solo"};
        testCase("Caso 1: singolo nodo", arr, 1);
    }

    
    {
        const char *arr[] = {"a", "b", "c", "d"};
        testCase("Caso 2: tutte run=1 (elimini la prima)", arr, 4);
    }

    /* Caso 3: run massima in testa */
    {
        const char *arr[] = {"Apple", "aero", "ALFA", "bar", "boat"};
        testCase("Caso 3: run max in testa (A...)", arr, 5);
    }

    /* Caso 4: run massima in mezzo */
    {
        const char *arr[] = {"x", "y", "Cat", "cow", "Ciao", "z"};
        testCase("Caso 4: run max in mezzo (C...)", arr, 6);
    }

    /* Caso 5: run massima in coda */
    {
        const char *arr[] = {"one", "two", "Zoo", "zulu", "Zed"};
        testCase("Caso 5: run max in coda (Z...)", arr, 5);
    }

    /* Caso 6: parità di lunghezza -> elimina la prima run più lunga */
    {
        const char *arr[] = {"aa", "ab", "bb", "bc", "cc"};
        /* run: a(2), b(2), c(1) -> parità tra a e b, elimina a */
        testCase("Caso 6: parità (elimini la prima run max)", arr, 5);
    }

    /* Caso 7: case-insensitive (A,a,A) è la stessa run */
    {
        const char *arr[] = {"A1", "a2", "ALast", "b", "B2"};
        testCase("Caso 7: case-insensitive", arr, 5);
    }

    /* Caso 8: stringhe vuote (iniziale '\0'): run di vuote consecutive */
    {
        const char *arr[] = {"", "", "a", "aa", "", "b"};
        testCase("Caso 8: stringhe vuote e run miste", arr, 6);
    }

    /* Caso 9: run max include la testa e lascia lista vuota */
    {
        const char *arr[] = {"x", "x2", "X3"};
        testCase("Caso 9: elimini tutto (run unica max)", arr, 3);
    }
    {
        const char *arr[] = {
            "dog",
            "cat",
            "cow",
            "car",
            "apple",
            "banana"
        };
        testCase("Caso 10: test normale (run in mezzo)", arr, 6);
    }
    return 0;
}

void run(Lista start, Lista *finish, int *count, char lettera)
{
    if(start==NULL || *finish==NULL)
        return;
    while(*finish!=NULL)
    {
        if((*finish)->word[0]!=lettera)
            return;
        (*finish)=(*finish)->next;
        (*count)++;
    }
}
void runmax(Lista head, int *len_max, Lista *prec_startmax, Lista *startmax, Lista *finish)
    {
    if(head==NULL)
        return;
    Lista scorri=head;
    Lista prec=NULL;
    while(scorri!=NULL)
        {
            int count=0;
            Lista start;
            Lista finish2=scorri->next;
            run(scorri, &finish2, &count, scorri->word[0]);
            if(count>*len_max)
                {
                    *len_max=count;
                    *prec_startmax=prec;
                    *startmax=scorri;
                    *finish=finish2;
                }
            prec=scorri;
            scorri=scorri->next;
        }
    }
Lista Eliminarun(Lista head)
    {
    if(head==NULL || head->next==NULL)
        return head;
    Lista prec=NULL;
    Lista startmax=head;
    Lista finish=head->next;
    int lenmax=0;
    runmax(head, &lenmax, &prec, &startmax, &finish);
    if(prec==NULL)
        {
            head=finish;
            while(startmax!=finish)
                {
                    Lista temp=startmax->next;
                    free(startmax->word);
                    free(startmax);
                    startmax=temp;
                }
            return head;
        }
    prec->next=finish;
    while(startmax!=finish)
        {
            Lista temp=startmax->next;
            free(startmax->word);
            free(startmax);
            startmax=temp;
        }
    return head;
    }
