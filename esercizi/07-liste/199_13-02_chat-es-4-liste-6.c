//
//  main.c
//  chat es 4 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;


/*
  Elimina ogni blocco massimale di nodi consecutivi tale che:
  ogni nodo del blocco è strettamente minore del minimo degli elementi
  successivi al blocco.

  Suggerito:
  - L è puntatore a testa per poter cambiare anche l'inizio.
  - ritorna quanti nodi sono stati eliminati (debug comodo)
*/
int eliminaBlocchiMonotoniaFutura(Lista *L);

/* =========================
   UTILITY LISTA
   ========================= */
Lista newNode(int v) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = NULL;
    return n;
}

void pushBack(Lista *L, int v) {
    Lista n = newNode(v);
    if (*L == NULL) { *L = n; return; }
    Lista cur = *L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

void printList(const char *label, Lista L) {
    printf("%s[", label);
    for (Lista cur = L; cur != NULL; cur = cur->next) {
        printf("%d", cur->val);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

int length(Lista L) {
    int c = 0;
    while (L) { c++; L = L->next; }
    return c;
}

void freeList(Lista L) {
    while (L) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}
Lista eliminaK(Lista head, int K);
int main(void) {
    /* Test scelti per far scattare blocchi diversi */
    int t1[] = {5, 3, 8, 2, 7};          // dovrebbe eliminare solo "2"
    int t2[] = {1, 2, 3, 4};              // dovrebbe eliminare "1 2 3"
    int t3[] = {4, 1, 3, 2, 5};           // dovrebbe eliminare "4 1 3 2"
    int t4[] = {6, 1, 7, 2, 3, 10};       // dovrebbe eliminare "6 1 7 2 3"
    int t5[] = {2, 9, 1, 8, 7, 3};        // dovrebbe eliminare solo "1"

    struct {
        const char *name;
        int *arr;
        int n;
    } tests[] = {
        {"T1", t1, 5},
        {"T2", t2, 4},
        {"T3", t3, 5},
        {"T4", t4, 6},
        {"T5", t5, 6},
    };

    int nt = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s ====================\n", tests[i].name);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        int removed = eliminaBlocchiMonotoniaFutura(&L);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));
        printf("Nodi rimossi (ritorno funzione): %d\n", removed);

        freeList(L);
    }

    return 0;
}
int minimoDa(Lista head) {
    if (head == NULL) return 0;  // non dovrebbe servire se usata bene
    int min = head->val;
    head = head->next;
    while (head != NULL) {
        if (head->val < min)
            min = head->val;
        head = head->next;
    }
    return min;
}

int trovablocco(Lista head) {
    if (head == NULL)
        return 0;

    int len = 0;
    Lista cur = head;

    while (cur != NULL) {

        // il blocco deve avere almeno un elemento successivo
        if (cur->next == NULL)
            break;

        int minSucc = minimoDa(cur->next);

        if (cur->val < minSucc) {
            len++;
            cur = cur->next;
        } else {
            break;
        }
    }

    return len;
}
int eliminaBlocchiMonotoniaFutura(Lista *L) {
    if(*L==NULL)
        return 0;
    Lista *pp=L;
    int somma=0;
    while (*pp!=NULL) {
        int val=trovablocco(*pp);
        somma=somma+val;
        if(val>0)
            {
                *pp=eliminaK(*pp, val);
            }
        else
            {
                pp=&(*pp)->next;
            }
    }
    return somma;
}
Lista eliminaK(Lista head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K && head!=NULL; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
