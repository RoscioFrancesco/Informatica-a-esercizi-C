//
//  main.c
//  albero chat es4 liste-18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURA LISTA DI STRINGHE
   ========================= */

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

typedef Node* Lista;



/* G(l): somma delle lunghezze delle parole multipla di 7 (ricorsiva, senza cicli) */
int G(Lista l);  /* TODO */
Lista eliminaPrefissoMinimo(Lista l, int *k); /* TODO */
int verificata(Lista head);
/* =========================
   UTILITY (PER TEST - OK USARE CICLI QUI)
   ========================= */

static char *dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Lista push_back(Lista l, const char *w) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = NULL;

    if (l == NULL) return n;

    Node *cur = l;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return l;
}

static Lista buildFromArray(const char *a[], int n) {
    Lista l = NULL;
    for (int i = 0; i < n; i++) l = push_back(l, a[i]);
    return l;
}

static void printLista(Lista l) {
    printf("[");
    while (l) {
        printf("\"%s\"(len=%zu)", l->word, strlen(l->word));
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}

/* Calcolo somma lunghezze: SOLO per stampe nel main (qui i cicli sono ok) */
static int sommaLunghezze(Lista l) {
    int s = 0;
    while (l) {
        s += (int)strlen(l->word);
        l = l->next;
    }
    return s;
}

static void runTest(const char *name, const char *arr[], int n, int expected_k) {
    printf("\n=====================================\n");
    printf("TEST: %s\n", name);
    printf("Atteso (k minimo) = %d\n", expected_k);
    printf("=====================================\n");

    Lista l = buildFromArray(arr, n);

    printf("Lista iniziale: ");
    printLista(l);
    printf("Somma len iniziale = %d, mod 7 = %d\n", sommaLunghezze(l), sommaLunghezze(l) % 7);

    printf("G(lista iniziale) = %d  (dopo tua implementazione)\n", G(l));

    int k = 0;
    Lista newHead = eliminaPrefissoMinimo(l, &k);

    printf("\nRisultato funzione:\n");
    printf("k restituito = %d\n", k);

    printf("Lista risultante: ");
    printLista(newHead);
    printf("Somma len risultante = %d, mod 7 = %d\n",
           sommaLunghezze(newHead), sommaLunghezze(newHead) % 7);

    printf("G(lista risultante) = %d  (dopo tua implementazione)\n", G(newHead));

    /* Nota: se elimini nodi, la tua funzione deve anche liberarli.
       Qui libero solo la lista rimasta. */
    freeLista(newHead);
}

int main(void) {
    

    /* Caso A: G già vera => k minimo = 0
       lunghezze: 4+3 = 7 */
    const char *A[] = {"casa", "tre"};

    /* Caso B: serve eliminare 1 elemento => k minimo = 1
       lunghezze: 1 + 4 + 3 = 8  (mod7=1)
       togli "a"(1) => 4+3=7 (ok) */
    const char *B[] = {"a", "casa", "tre"};

    /* Caso C: serve eliminare 2 elementi => k minimo = 2
       lunghezze: 1 + 1 + 4 + 3 = 9 (mod7=2)
       togli primi 2 => 4+3=7 (ok)
       togli 1 solo => 1+4+3=8 (no) */
    const char *C[] = {"a", "b", "casa", "tre"};

    /* Caso D: serve eliminare 4 elementi => k minimo = 4
       lunghezze: 1+1+1+1+4+3 = 11 (mod7=4)
       togli primi 4 => 4+3=7 (ok)
       togli 3 => 1+4+3=8 (no) */
    const char *D[] = {"a", "b", "c", "d", "casa", "tre"};

    /* Caso E: impossibile renderla vera eliminando un prefisso => elimini tutta la lista
       lunghezze: 1+1+1=3
       suffissi hanno somme: 3,2,1,0 -> nessuna è multipla di 7 tranne 0 (lista vuota)
       MA attenzione: se tu consideri lista vuota con somma=0 => G vera,
       allora eliminando tutta la lista rende G vera.
       L’esercizio dice: "se G non può diventare vera eliminando un prefisso, elimina l'intera lista"
       quindi qui atteso k = n (3), lista risultante NULL.
    */
    const char *E[] = {"a", "b", "c"};
    int k=0;
    runTest("A) G gia' vera (k=0)", A, 2, 0);
    runTest("B) k minimo = 1", B, 3, 1);
    runTest("C) k minimo = 2", C, 4, 2);
    runTest("D) k minimo = 4", D, 6, 4);
    runTest("E) impossibile -> elimina tutto (k=n)", E, 3, 3);

    return 0;
}

/* =========================
   STUB: TU COMPLETI (NO SOLUZIONE)
   ========================= */

int G(Lista l) {
    /* TODO: ricorsiva, senza cicli:
       ritorna 1 se somma lunghezze % 7 == 0, altrimenti 0 */
    (void)l;
    return 0;
}

Lista eliminaPrefissoMinimo(Lista l, int *k) {
    if(l==NULL)
        {
            return l;
        }
    if(verificata(l)==0)
        {
            Lista temp=l->next;
            free(l->word);
            free(l);
            (*k)++;
            return eliminaPrefissoMinimo(temp, k);
        }
    return l;
}
/* elimina prefisso minimo che rende G vera sul suffisso rimanente (ricorsiva, senza cicli) */
int somma(Lista head)
    {
        if(head==NULL)
            return 0;
    return strlen(head->word)+somma(head->next);
    }
int verificata(Lista head)
    {
    int j=somma(head);
    if(j%7==0)
        return 1;
    return 0;
    }
