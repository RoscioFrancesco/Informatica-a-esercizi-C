//
//  main.c
//  ricorsione 3
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
void f2(Lista *si, Lista *no, Lista head)
    {
        if(head==NULL)
            return;
        f2(si, no, head->next);
        if(contieneCifra(head->word))
            {
                head->next=*si;
                *si=head;
                return;
            }
        else
            {
                head->next=*no;
                *no=head;
                return;
            }
    }

Partizione f(Lista head){
      Partizione p;
    p.yes=NULL;
    p.no=NULL;
    Lista *si=&p.yes;
    Lista *no=&p.no;
    f2(si, no, head);
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
//int aux(Lista curr, Lista *front)
//{
//    /* 1. CASO BASE */
//    if (curr == NULL)
//        return VALORE_BASE;
//
//    /* 2. DISCESA */
//    int ok = aux(curr->next, front);
//    if (!ok)
//        return FALLIMENTO;
//
//    /* 3. LOGICA IN RISALITA */
//    // confronto / decisione / eliminazione / accumulo
//
//    /* 4. AVANZA FRONT */
//    *front = (*front)->next;
//
//    /* 5. RITORNO */
//    return SUCCESSO;
//}
