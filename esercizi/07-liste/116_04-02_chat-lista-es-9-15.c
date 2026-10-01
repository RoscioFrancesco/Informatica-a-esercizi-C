//
//  main.c
//  chat lista es 9 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   STRUTTURA LISTA DI STRINGHE
   ========================================================= */
typedef struct Node {
    char *word;           /* stringa dinamica */
    struct Node *next;
} Node;

typedef Node* Lista;

Lista eliminaConStato(Lista head);  /* TODO */

/* =========================================================
   UTILITY (qui i cicli sono OK per test)
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

/* crea lista da array (mantiene ordine) */
static Lista fromArray(const char *a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = newNodeDup(a[i], l);
    }
    return l;
}

static void printLista(Lista l) {
    printf("[");
    while (l) {
        printf("\"%s\"", l->word);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Node *t = l->next;
        free(l->word);
        free(l);
        l = t;
    }
}

/* =========================================================
   MAIN DI TEST (POPOLATO BENE)
   ========================================================= */
int scout(Lista p);
Lista f(Lista head);
void cancellablocco(Lista head, int k);
int scout(Lista p);

int main(void) {
    /* Caso con più blocchi e marker adiacenti */
    const char *a1[] = {
        "BEGIN", "s", "x", "y", "END", "B",
        "BEGIN", "C", "END", "D",
        "BEGIN", "END",
        "E"
    };
    int n1 = (int)(sizeof(a1) / sizeof(a1[0]));

    /* Caso con BEGIN senza END (cancellazione fino a fine lista) */
    const char *a2[] = { "p", "q", "BEGIN", "r", "s", "t" };
    int n2 = (int)(sizeof(a2) / sizeof(a2[0]));

    /* Caso senza marker (nessuna cancellazione) */
    const char *a3[] = { "uno", "due", "tre" };
    int n3 = (int)(sizeof(a3) / sizeof(a3[0]));

    Lista L1 = fromArray(a1, n1);
    Lista L2 = fromArray(a2, n2);
    Lista L3 = fromArray(a3, n3);

    printf("=== INPUT L1 ===\n"); printLista(L1);
    printf("=== INPUT L2 ===\n"); printLista(L2);
    printf("=== INPUT L3 ===\n"); printLista(L3);
    
    printf("\n%d", scout(L1->next));

    
    L1 = f(L1);
    L2 = f(L2);
    L3 = f(L3);

    printf("\n=== OUTPUT L1 ===\n"); printLista(L1);
    printf("=== OUTPUT L2 ===\n"); printLista(L2);
    printf("=== OUTPUT L3 ===\n"); printLista(L3);

    freeLista(L1);
    freeLista(L2);
    freeLista(L3);
    return 0;
}


void cancellablocco(Lista head, int k)
    {
        if(head==NULL)
            return;
        if(k==0)
            return;
        Lista temp=head->next;
        free(head->word);
        free(head);
        cancellablocco(temp, k-1);
    }
int scout(Lista p)
    {
        if(p==NULL)
            return 0;
        if(strcmp(p->word, "END")==0)
            return 1;
        return 1+scout(p->next);
    }
Lista f(Lista head)
    {
        if(head==NULL)
            return head;
    Lista scorri=head;
    Lista prec=NULL;
    while(scorri!=NULL)
        {
            if(strcmp(scorri->word, "BEGIN")==0)
                {
                    int num=scout(scorri);
                    Lista dopo_end=scorri;
                    for(int i=0; dopo_end!=NULL && i<num; i++)
                        {
                            dopo_end=dopo_end->next;
                        }
                    if(head==scorri)
                        {
                            Lista temp=head;
                            head=dopo_end;
                            cancellablocco(temp, num);
                            scorri=head;
                            prec=NULL;
                        }
                    else
                    {
                        prec->next=dopo_end;
                        cancellablocco(scorri, num);
                        scorri=prec->next;
                    }
                }
            else
                {
                    prec=scorri;
                    scorri=scorri->next;
                }
        }
    return head;
    }
