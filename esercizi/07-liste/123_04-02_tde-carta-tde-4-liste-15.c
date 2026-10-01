//
//  main.c
//  tde carta tde 4 liste -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int info;
    struct n *next;
} nodo;

typedef nodo *Lista;

typedef struct li {
    Lista lis;          /* testa della sottolista */
    struct li *next;    /* prossimo blocco */
} lisNodo;

typedef lisNodo *ListaDiListe;


ListaDiListe spezza(Lista L, int k);

/* =========================
   UTILITY LISTA DI INT (solo per test)
   ========================= */
static Lista newNodoInt(int v, Lista next) {
    nodo *p = (nodo*)malloc(sizeof(nodo));
    if (!p) { perror("malloc"); exit(1); }
    p->info = v;
    p->next = next;
    return p;
}

static Lista fromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = n - 1; i >= 0; --i)
        L = newNodoInt(a[i], L);
    return L;
}

static void printLista(Lista L) {
    printf("{");
    for (nodo *p = L; p != NULL; p = p->next) {
        printf("%d", p->info);
        if (p->next) printf(", ");
    }
    printf("}");
}

static void freeLista(Lista L) {
    while (L) {
        nodo *tmp = L->next;
        free(L);
        L = tmp;
    }
}

/* =========================
   UTILITY LISTA DI LISTE (solo per test)
   ========================= */
static void printListaDiListe(ListaDiListe LL) {
    int i = 1;
    for (lisNodo *p = LL; p != NULL; p = p->next, i++) {
        printf("L%d = ", i);
        printLista(p->lis);
        if (p->next) printf("  ->  ");
    }
    printf("\n");
}

/* libera sia i nodi della lista di liste sia le sottoliste allocate da spezza */
static void freeListaDiListe(ListaDiListe LL) {
    while (LL) {
        lisNodo *nextLL = LL->next;
        freeLista(LL->lis);
        free(LL);
        LL = nextLL;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
ListaDiListe inserisciincoda(ListaDiListe head, int v[], int count);
Lista crealista(int v[], int len, int i);
int main(void) {
    int a[] = {3, 7, 1, 4, 2, 8, 4, 3, 2};
    int n = (int)(sizeof(a) / sizeof(a[0]));
    int k = 10;

    Lista L = fromArray(a, n);

    printf("Input L = ");
    printLista(L);
    printf("\n");
    printf("k = %d\n\n", k);

    /* chiamata alla tua funzione */
    ListaDiListe LL = spezza(L, k);

    printf("Output lista di liste:\n");
    printListaDiListe(LL);

    /*
      Atteso (in forma logica):
      L1={3,7}  L2={1,4,2}  L3={8}  L4={4,3,2}
    */

    /* verifica che L NON sia stata modificata */
    printf("\nControllo: L dopo spezza (deve essere uguale all'input) = ");
    printLista(L);
    printf("\n");

    /* cleanup */
    freeLista(L);          /* libera lista originale */
    freeListaDiListe(LL);  /* libera copia fatta da spezza */

    return 0;
}
int* f(Lista partenza, int k, Lista *partenzasucc, int *len)
{
    Lista scorri=partenza;
    int somma=0;
    int count=0;
    while (scorri!=NULL && somma+scorri->info<=k)
    {
        count++;
        somma=somma+scorri->info;
        scorri=scorri->next;
    }
    *partenzasucc=scorri;
    scorri=partenza;
    int *v=malloc(sizeof(int)*count);
    for(int j=0; j<count; j++)
        {
            v[j]=scorri->info;
            scorri=scorri->next;
        }
    *len=count;
    return v;
}
ListaDiListe spezza(Lista L, int k)
    {
        if(L==NULL)
            return NULL;
    Lista scorri=L;
    ListaDiListe head=NULL;
    while (scorri!=NULL)
        {
            Lista finish;
            int len=0;
            int *v=f(scorri, k, &finish, &len);
            head=inserisciincoda(head, v, len);
            free(v);
            scorri=finish;
        }
        return head;
    }
ListaDiListe inserisciincoda(ListaDiListe head, int v[], int count)
{
    if(head==NULL)
    {
        ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
        new->next=NULL;
        new->lis=crealista(v, count, 0);
        return new;
    }
    head->next=inserisciincoda(head->next, v, count);
    return head;
}
Lista crealista(int v[], int len, int i) // questa la sbagli sempre
    {
    if(len==i)
        return NULL;
    Lista new = (Lista)malloc(sizeof(*new));
    new->info=v[i];
    new->next=crealista(v, len, i+1);
    return new;
    }
