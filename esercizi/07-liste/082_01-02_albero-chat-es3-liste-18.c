//
//  main.c
//  albero chat es3 liste -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
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
int parolaOK(const char *s);
static Lista buildFromArrayRec(const char *arr[], int n, int i);
static void printListaRec(Lista l);
static void freeListaRec(Lista l);

/* proprietà richieste dall’esercizio (helper) */
int parolaValida(const char *s);          // solo [a-zA-Z_]
int contieneMarkerHash(const char *s);    // contiene '#'

/* =========================
   PROTOTIPO ESERCIZIO E12 (DA FARE TU) — NON SVOLTO QUI
   =========================
   - modalità normale / modalità eliminazione
   - quando trovi la prima parola non valida:
       elimina quel nodo e tutti i successivi fino a (esclusa) la prima parola valida che contiene '#'
   - se marker non esiste: elimina fino a fine
   - se la parola non valida è già un marker: elimina solo quel nodo
*/
Lista eliminaFinoAMarker(Lista head);
Lista f(Lista head, int *flag);
/* =========================
   MAIN con test mirati
   ========================= */

int main(void) {
    /* Test 1: parola non valida -> elimina fino a marker valido con '#' (escluso) */
    const char *t1[] = {
        "ok_", "alpha", "bad!", "x", "y", "good#resume", "z"
    };
    Lista l1 = buildFromArrayRec(t1, (int)(sizeof(t1)/sizeof(t1[0])), 0);
    printf("=== TEST 1 ===\n");
    printf("Input : "); printListaRec(l1); printf("\n");
    l1 = eliminaFinoAMarker(l1);   
    printf("Output: "); printListaRec(l1); printf("\n\n");
    freeListaRec(l1);

    /* Test 2: marker non esiste -> elimina fino a fine lista */
    const char *t2[] = {
        "ok", "still_ok", "oops$", "resto", "ancora"
    };
    Lista l2 = buildFromArrayRec(t2, (int)(sizeof(t2)/sizeof(t2[0])), 0);
    printf("=== TEST 2 (marker assente) ===\n");
    printf("Input : "); printListaRec(l2); printf("\n");
    l2 = eliminaFinoAMarker(l2);   
    printf("Output: "); printListaRec(l2); printf("\n\n");
    freeListaRec(l2);

    /* Test 3: la parola non valida è già un marker (#) -> elimina solo quel nodo */
    const char *t3[] = {
        "ok", "bad#@", "keep_", "fine"
    };
    Lista l3 = buildFromArrayRec(t3, (int)(sizeof(t3)/sizeof(t3[0])), 0);
    printf("=== TEST 3 (non valida e marker insieme) ===\n");
    printf("Input : "); printListaRec(l3); printf("\n");
    l3 = eliminaFinoAMarker(l3);   
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

/* =========================
   HELPER DI PROPRIETÀ (RICORSIVI, no cicli)
   ========================= */

/* true se la stringa contiene almeno un '#'
   (nota: qui è permesso usare ricorsione, niente cicli) */
int contieneMarkerHash(const char *s) {
    if (s == NULL) return 0;
    if (*s == '\0') return 0;
    if (*s == '#') return 1;
    return contieneMarkerHash(s + 1);
}

/* true se ogni carattere appartiene a [a-zA-Z_]
   (stringa vuota considerata NON valida qui; cambia se vuoi) */
int parolaValida(const char *s) {
    if (s == NULL) return 0;
    if (*s == '\0') return 0;

    unsigned char c = (unsigned char)*s;

    if (!(isalpha(c) || c == '_'))
        return 0;

    if (*(s + 1) == '\0')
        return 1;

    return parolaValida(s + 1);
}

/* =========================
   STUB ESERCIZIO (NON SVOLTO)
   =========================
/* =========================
   PROTOTIPO ESERCIZIO E12 (DA FARE TU) — NON SVOLTO QUI
   =========================
   - modalità normale / modalità eliminazione
   - quando trovi la prima parola non valida:
       elimina quel nodo e tutti i successivi fino a (esclusa) la prima parola valida che contiene '#'
   - se marker non esiste: elimina fino a fine
   - se la parola non valida è già un marker: elimina solo quel nodo
*/

int parolaOK(const char *s)
{
    if (s == NULL)
        return 0;

    /* fine stringa: tutti i caratteri erano validi */
    if (*s == '\0')
        return 1;

    /* carattere NON consentito */
    if (!(isalpha((unsigned char)*s) || *s == '_'))
        return 0;

    /* controlla il resto della stringa */
    return parolaOK(s + 1);
}
int marker(char parola[])
    {
    int i=0;
    while (parola[i]!='\0') {
        if(parola[i]=='#')
            return 1;
        i++;
    }
    return 0;
    }
Lista f(Lista head, int *flag)
    {
        if(head==NULL)
            return head;
//        if(parolaOK(head->word) && marker(head->word) && *flag==0)
//            {
//                Lista temp=head->next;
//                free(head->word);
//                free(head);
//                return f(temp, flag);
//            }
        if(marker(head->word)&&parolaOK(head->word)==0 && *flag==0)
            {
                Lista temp=head->next;
                free(head->word);
                free(head);
                return f(temp, flag);
            }
        if(marker(head->word)==1 && *flag==1)
        {
            *flag=0;
            head->next=f(head->next, flag);
            return head;
        }
        if(parolaOK(head->word)==0 || *flag==1)
            {
            *flag=1;
            Lista temp=head->next;
            free(head->word);
            free(head);
            return f(temp, flag);
            }
        head->next=f(head->next, flag);
        return head;
    }
Lista eliminaFinoAMarker(Lista head)
    {
    int flag=0;
    return f(head, &flag);
    }
