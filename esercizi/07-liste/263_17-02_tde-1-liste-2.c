//
//  main.c
//  tde 1 liste  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo *Lista;

/* =========================
   PROTOTIPO ESERCIZIO
   ========================= */
void stampaQuasiComuni(Lista lis[], int N);

/* =========================
   FUNZIONI DI SUPPORTO (TEST)
   ========================= */
Nodo *newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->numero = x;
    n->next = NULL;
    return n;
}

Lista pushBack(Lista L, int x) {
    if (L == NULL) return newNode(x);
    Nodo *cur = L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = newNode(x);
    return L;
}

void printList(const char *label, Lista L) {
    printf("%s", label);
    if (L == NULL) {
        printf("NULL\n");
        return;
    }
    while (L != NULL) {
        printf("%d", L->numero);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeList(Lista L) {
    while (L != NULL) {
        Nodo *tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int contaLDL(int x, Lista array[], int len);
int trovato(int x, Lista head);
Lista inseriscincoda(Lista head, int x);
int main(void) {

    /* ===== TEST 1: N = 4 liste =====
       Quasi-comuni = numeri presenti in tutte le liste tranne una (cioè in N-1 liste).
       Costruiamo liste con due quasi-comuni: 3 (manca nella 4a) e 10 (manca nella 2a).
    */
    int N1 = 4;
    Lista v1[4] = {NULL, NULL, NULL, NULL};

    /* L0: 1 -> 2 -> 3 -> 4 -> 5 -> 10 */
    v1[0] = pushBack(v1[0], 1);
    v1[0] = pushBack(v1[0], 2);
    v1[0] = pushBack(v1[0], 3);
    v1[0] = pushBack(v1[0], 4);
    v1[0] = pushBack(v1[0], 5);
    v1[0] = pushBack(v1[0], 10);

    /* L1: 2 -> 3 -> 4 -> 6 */
    v1[1] = pushBack(v1[1], 2);
    v1[1] = pushBack(v1[1], 3);
    v1[1] = pushBack(v1[1], 4);
    v1[1] = pushBack(v1[1], 6);

    /* L2: 2 -> 3 -> 4 -> 7 -> 8 -> 10 */
    v1[2] = pushBack(v1[2], 2);
    v1[2] = pushBack(v1[2], 3);
    v1[2] = pushBack(v1[2], 4);
    v1[2] = pushBack(v1[2], 7);
    v1[2] = pushBack(v1[2], 8);
    v1[2] = pushBack(v1[2], 10);

    /* L3: 2 -> 4 -> 9 -> 10 */
    v1[3] = pushBack(v1[3], 2);
    v1[3] = pushBack(v1[3], 4);
    v1[3] = pushBack(v1[3], 9);
    v1[3] = pushBack(v1[3], 10);

    printf("===== TEST 1 =====\n");
    for (int i = 0; i < N1; i++) {
        char label[32];
        snprintf(label, sizeof(label), "Lista %d: ", i);
        printList(label, v1[i]);
    }
    printf("Output stampaQuasiComuni: ");
    stampaQuasiComuni(v1, N1);
    printf("\n\n");

    /* ===== TEST 2: N = 3 liste (nessun quasi-comune) ===== */
    int N2 = 3;
    Lista v2[3] = {NULL, NULL, NULL};

    /* A: 5 -> 5 -> 1 -> 2 */
    v2[0] = pushBack(v2[0], 5);
    v2[0] = pushBack(v2[0], 5);
    v2[0] = pushBack(v2[0], 1);
    v2[0] = pushBack(v2[0], 2);

    /* B: 5 -> 3 -> 2 -> 2 */
    v2[1] = pushBack(v2[1], 5);
    v2[1] = pushBack(v2[1], 3);
    v2[1] = pushBack(v2[1], 2);
    v2[1] = pushBack(v2[1], 2);

    /* C: 5 -> 2 -> 4 */
    v2[2] = pushBack(v2[2], 5);
    v2[2] = pushBack(v2[2], 2);
    v2[2] = pushBack(v2[2], 4);

    printf("===== TEST 2 =====\n");
    for (int i = 0; i < N2; i++) {
        char label[32];
        snprintf(label, sizeof(label), "Lista %d: ", i);
        printList(label, v2[i]);
    }
    printf("Output stampaQuasiComuni: ");
    stampaQuasiComuni(v2, N2);
    printf("\n");

    /* cleanup */
    for (int i = 0; i < N1; i++) freeList(v1[i]);
    for (int i = 0; i < N2; i++) freeList(v2[i]);

    return 0;
}



void stampaQuasiComuni(Lista lis[], int N) {
    Lista new=NULL;
    for(int i=0; i<N; i++)
        {
            Lista scorri=lis[i];
            while(scorri!=NULL)
                {
                    int num=contaLDL(scorri->numero, lis, N);
                    if(num==N-1 && trovato(scorri->numero, new)==0)
                        {
                            new=inseriscincoda(new, scorri->numero);
                            printf("%d-->", scorri->numero);
                        }
                    scorri=scorri->next;
                }
        }
}
int trovato(int x, Lista head)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(head->numero==x)
                    return 1;
                head=head->next;
            }
    return 0;
    }
int contaLDL(int x, Lista array[], int len)
    {
    int count=0;
    for(int i=0; i<len; i++)
        {
            count=count+trovato(x, array[i]);
        }
    return count;
    }
Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(Nodo));
                new->next=NULL;
                new->numero=x;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
