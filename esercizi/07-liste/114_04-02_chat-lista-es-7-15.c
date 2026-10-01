//
//  main.c
//  chat lista es 7 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
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



/* Elimina l'intervallo [start, finish) dalla lista */
Lista eliminaIntervallo(Lista head, Lista start, Lista finish);  /* TODO */

/* =========================
   UTILITY (PER TEST)
   ========================= */

static char* dupstr(const char *s) {
    char *p = (char*)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static Lista newNode(const char *w, Lista next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = next;
    return n;
}

static Lista fromArray(const char *a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = newNode(a[i], l);
    }
    return l;
}

static void printLista(Lista l) {
    printf("[");
    while (l) {
        printf("\"%s\"", l->word);
        if (l->next) printf(", ");
        l = l->next;
    }
    printf("]\n");
}

/* ritorna il nodo in posizione idx (0-based) */
static Lista at(Lista head, int idx) {
    int i = 0;
    while (head && i < idx) {
        head = head->next;
        i++;
    }
    return head;
}

/* =========================
   MAIN
   ========================= */
int numero(Lista start, Lista finish);
int main(void) {

    /* Lista di test */
    const char *parole[] = {"A","B","C","D","E","F"};
    int n = sizeof(parole) / sizeof(parole[0]);

    Lista head = fromArray(parole, n);

    /* scegliamo start e finish */
    Lista start  = at(head, 2);   /* "C" */
    Lista finish = at(head, 5);   /* "F" */

    printf("=== LISTA ORIGINALE ===\n");
    printLista(head);

    printf("start  = \"%s\"\n", start ? start->word : "NULL");
    printf("finish = \"%s\"\n", finish ? finish->word : "NULL");
    printf("Intervallo da eliminare: [start, finish)\n");

    /* chiamata funzione d'esame */
    head = eliminaIntervallo(head, start, finish);
    
    printf("\n=== LISTA DOPO ELIMINAZIONE ===\n");
    printLista(head);
}
Lista eliminaIntervallo(Lista head, Lista start, Lista finish);

int numero(Lista start, Lista finish)
    {
        if(start==NULL)
            return 0;
        if(start==finish)
            return 0;
    return 1+ numero(start->next, finish);
    }

void freeK(Lista start, int K)
    {
        if(start==NULL)
            return;
        if(K==0)return;
        Lista temp=start->next;
        free(start->word);
        free(start);
        freeK(temp, K-1);
    }
Lista eliminaIntervallo(Lista head, Lista start, Lista finish)
{
    if(head==NULL)
        return head;
    int num=numero(start, finish);
    Lista prev=head;
    while(prev->next!=start)
        prev=prev->next;
    Lista temp=prev->next;
    prev->next=finish;
    freeK(temp, num);
    return head;
}
