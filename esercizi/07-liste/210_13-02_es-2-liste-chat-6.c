//
//  main.c
//  es 2 liste chat -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct N {
    int v;
    struct N *next;
} Nodo;

typedef Nodo* Lista;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
/* Elimina ogni blocco delimitato da 0 (zeri inclusi) la cui somma interna è dispari */
Lista eliminaBlocchiDispariDelimitatiDaZero(Lista L);  // TODO: da implementare

/* =========================
   UTILITY
   ========================= */
static Nodo* newNode(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->v = x;
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista L, int x) {
    Nodo* nn = newNode(x);
    if(L == NULL) return nn;
    Nodo* t = L;
    while(t->next) t = t->next;
    t->next = nn;
    return L;
}

static Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for(int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* msg, Lista L) {
    printf("%s", msg);
    if(L == NULL) { printf("NULL\n"); return; }
    while(L) {
        printf("%d", L->v);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void f(Lista *l);
int main(void) {
    /* Test 1: esempio del testo */
    int t1[] = {0,3,4,0,2,2,0,5,1,0};
    Lista L1 = buildFromArray(t1, 10);

    printf("=== TEST 1 (esempio) ===\n");
    printList("Input:  ", L1);
    Lista R1 = eliminaBlocchiDispariDelimitatiDaZero(L1);
    printList("Output: ", R1);
    freeList(R1);

    /* Test 2: tutti i blocchi dispari -> risultato NULL (perché elimini anche gli zeri) */
    int t2[] = {0,1,0,0,3,0};
    Lista L2 = buildFromArray(t2, 6);

    printf("\n=== TEST 2 (tutto eliminato) ===\n");
    printList("Input:  ", L2);
    Lista R2 = eliminaBlocchiDispariDelimitatiDaZero(L2);
    printList("Output: ", R2);
    freeList(R2);

    /* Test 3: nessun blocco dispari -> lista invariata */
    int t3[] = {0,2,0,0,4,0};
    Lista L3 = buildFromArray(t3, 6);

    printf("\n=== TEST 3 (niente eliminazioni) ===\n");
    printList("Input:  ", L3);
    Lista R3 = eliminaBlocchiDispariDelimitatiDaZero(L3);
    printList("Output: ", R3);
    freeList(R3);

    return 0;
}

//La lista contiene blocchi separati da 0:
//
//0 → 3 → 4 → 0 → 2 → 2 → 0 → 5 → 1 → 0
//Elimina ogni blocco (inclusi gli zeri ai bordi) la cui somma interna è dispari.
Lista eliminaBlocchiDispariDelimitatiDaZero(Lista L) {
    f(&L);
    return L;
}
int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=1;
        head=head->next;
        int somma=0;
        while(head!=NULL)
            {
                if(head->v==0)
                    break;
                count++;
                somma=somma+head->v;
                head=head->next;
            }
    if(somma%2==1 || somma==0)
        return count;
    else
        return 0;
    }
Lista distruggiK(Lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
void f(Lista *l)
    {
        if(*l==NULL)
            return;
    Lista *pp=l;
        while(*pp!=NULL)
            {
                int len=0;
                if((*pp)->v==0)
                    len=blocco(*pp);
                if(len>0)
                    {
                        *pp=distruggiK(*pp, len);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
