//
//  main.c
//  liste 4 -16
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================================================
   STRUTTURE DATI
   ========================================================= */
typedef struct Node {
    char *word;           /* stringa dinamica */
    struct Node *next;
} Node;

typedef Node* Lista;

/* coppia di liste (P vera / P falsa) */
typedef struct {
    Lista yes;   /* nodi che soddisfano P */
    Lista no;    /* nodi che NON soddisfano P */
} Partizione;

/* =========================================================
   UTILITY (QUI i cicli SONO OK per test)
   ========================================================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Node* newNodeDup(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = next;
    return n;
}

static Lista fromArray(const char *a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i)
        l = newNodeDup(a[i], l);
    return l;
}

static void printLista(const char *label, Lista l) {
    printf("%s: [", label);
    for (Node *p = l; p != NULL; p = p->next) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
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
static int contieneCifra(const char *w);
/* =========================================================
   PROPRIETÀ P (ESEMPIO)
   ========================================================= */
/* P(w) = la parola contiene almeno una cifra */
static int contieneCifra(const char *w) {
    if (!w) return 0;
    for (int i = 0; w[i] != '\0'; i++) {
        if (isdigit((unsigned char)w[i])) return 1;
    }
    return 0;
}


void f2(Lista lis, Lista * si, Lista * no){
      if(lis==NULL) return;
      f2(lis->next, si, no);
    
      if(contieneCifra(lis->word))
        {
            lis->next = *si;
            *si=lis;
            return;
         }
      
      lis->next = *no;
      *no = lis;
      return;
}

Partizione f(Lista head){
      Lista si=NULL, no=NULL;
      f2(head, &si, &no);
      Partizione p;
      p.no=no; p.yes=si;
      return p;
}


int main(void) {
    const char *words[] = {
        "ciao", "x9", "abc", "42", "hello", "7z", "fine"
    };
    int n = (int)(sizeof(words) / sizeof(words[0]));

    Lista l = fromArray(words, n);

    printf("Lista iniziale:\n");
    printLista("L", l);

    Partizione p = f(l);

    printf("\nDopo partizione stabile (senza nuovi nodi):\n");
    printLista("YES (P vera: contiene cifra)", p.yes);
    printLista("NO  (P falsa: non contiene cifra)", p.no);

    freeLista(p.yes);
    freeLista(p.no);

    return 0;
}
