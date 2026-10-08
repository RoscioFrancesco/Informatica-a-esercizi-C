//
//  main.c
//  chat lista es 5 run massimale -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
/*
 * ESERCIZIO: Eliminazione della sequenza (run) più lunga in una lista
 * 
 * Si consideri una lista concatenata in cui ogni nodo contiene un puntatore 
 * a una stringa allocata dinamicamente. Definiamo "run" una sequenza massimale 
 * di nodi adiacenti in cui tutte le stringhe iniziano con lo stesso carattere.
 * 
 * Scrivere una funzione (es. 'f' o 'eliminaRunPiuLunga') che riceva in 
 * input il puntatore alla testa della lista e svolga i seguenti compiti:
 * 
 * 1. Esplorare la lista per individuare la "run" di lunghezza massima.
 * 2. Rimuovere dalla lista tutti i nodi appartenenti a questa sequenza, 
 *    ricollegando correttamente il nodo precedente all'inizio della run 
 *    con il nodo successivo alla fine della run.
 * 3. Deallocare correttamente (tramite free) la memoria occupata sia dai 
 *    nodi eliminati che dalle relative stringhe in essi contenute.
 * 4. Restituire il puntatore alla testa della lista aggiornata.
 * 
 * Note:
 * - Prestare particolare attenzione al caso in cui la sequenza da eliminare 
 *   si trovi all'inizio della lista (modifica della testa).
 * - Se ci sono più sequenze di pari lunghezza massima, è sufficiente 
 *   eliminarne una (la prima trovata).
 * - È consentito l'uso di funzioni ausiliarie (es. per il calcolo della max
 *   run o per la deallocazione dei nodi).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURA LISTA DI STRINGHE
   ========================= */

typedef struct Node {
    char *word;            /* stringa dinamica */
    struct Node *next;
} Node;

typedef Node* Lista;



/* Elimina la run più lunga (sequenza massimale di parole con stessa iniziale) */
Lista eliminaRunPiuLunga(Lista head);   /* TODO */

/* (opzionali) helper tipici: trovi run da start, trovi max run, elimina [start,finish) ecc.
   Li puoi definire tu come vuoi, qui solo esempi di firma:

   void trovaRun(Lista start, Lista *finish, char iniziale, int *len);
   void trovaMaxRun(Lista head, Lista *startMax, Lista *finishMax, int *lenMax);
   Lista eliminaIntervallo(Lista head, Lista start, Lista finish);
*/

/* =========================
   UTILITY (PER TEST - OK CICLI QUI)
   ========================= */

static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Lista newNodeDup(const char *w, Lista next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = next;
    return n;
}

/* crea lista da array di stringhe mantenendo ordine */
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
        if (l->next) printf(", ");
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Lista tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}



Lista eliminaRunPiuLunga(Lista head) {
    
    return head;
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista f(Lista head);
void freeK(Lista head, int K);
void maxrun(Lista start, Lista *start_max, Lista *finish_max, int *count_max);
void run(Lista start, Lista *finish, int *len);

int main(void) {
    /*
      Run = sequenza massimale di nodi consecutivi con stessa iniziale.

      Caso di test (iniziali):
        a a a | b b | c | d d d d | e | f f

      La run più lunga è quella di 'd' (lunghezza 4): va eliminata.
    */
    const char *parole[] = {
        "alfa", "amico", "ape",     /* run 'a' len=3 */
        "ancora", "aperol",           /* run 'b' len=2 */
        "casa",                     /* run 'c' len=1 */
        "dado", "dito", "duna", "drago",  /* run 'd' len=4 (MAX) */
        "eco",                      /* run 'e' len=1 */
        "fango", "fiume"            /* run 'f' len=2 */
    };
    int n = (int)(sizeof(parole) / sizeof(parole[0]));

    Lista l = fromArray(parole, n);

    printf("=== LISTA ORIGINALE ===\n");
    printLista(l);

    l = f(l);

    printf("\n=== LISTA DOPO eliminaRunPiuLunga ===\n");
    printLista(l);

    freeLista(l);
    return 0;
}
void run(Lista start, Lista *finish, int *len)
    {
        if(start==NULL)
            return;
        if(*finish==NULL)
            return;
        if(start->word[0]!=(*finish)->word[0])
            return;
        (*finish)=(*finish)->next;
        (*len)++;
        run(start, finish, len);
    }
void maxrun(Lista start, Lista *start_max, Lista *finish_max, int *count_max)
    {
        if(start==NULL)
            return;
        int count=0;
        Lista finish=start;
        run(start, &finish, &count);
        if(count>*count_max)
        {
            *count_max=count;
            *start_max=start;
            *finish_max=finish;
        }
        maxrun(start->next, start_max, finish_max, count_max);
    }

void freeK(Lista head, int K)
    {
        if(head==NULL)
            return;
        if(K==0)
            return;
        Lista temp=head->next;
    free(head->word);
        free(head);
        freeK(temp, K-1);
    }
Lista f(Lista head)
    {
        if(head==NULL)
            return head;
    Lista startmax=head;
    Lista finishmax=head;
    int countmax=0;
    maxrun(head, &startmax, &finishmax, &countmax);
    printf("\n%s", startmax->word);
    printf("\n%s", finishmax->word);
    printf("\n%d", countmax);
    if(head==startmax)
        {
            Lista temp=head;
            head=finishmax;
            freeK(temp, countmax);
            return head;
        }
    Lista prev=head;
    while(prev->next!=startmax)
        prev=prev->next;
    prev->next=finishmax;
    freeK(startmax, countmax);
    return head;
    }
