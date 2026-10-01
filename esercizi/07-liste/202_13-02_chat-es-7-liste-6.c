//
//  main.c
//  chat es 7 liste -6
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
  Elimina ogni sottolista (tra due 0) la cui somma è
  minore della somma della sottolista precedente (rimasta).

  Gli 0 restano come delimitatori.

  Ritorna il numero totale di nodi eliminati (non contando gli 0).
*/
int eliminaSottolisteDominate(Lista *L);

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

/* =========================
   STUB (NON RISOLVO)
   ========================= */

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* T1: esempio + domino */
    int t1[] = {3, 4, 5, 0, 2, 2, 0, 10, 1, 1, 0};  // blocchi: [3,4,5] [2,2] [10,1,1]

    /* T2: più eliminazioni consecutive */
    int t2[] = {5, 0, 1, 1, 0, 2, 0, 10, 0};        // blocchi: [5] [1,1] [2] [10]

    /* T3: nessuna eliminazione (somme non decrescenti) */
    int t3[] = {1, 2, 0, 1, 2, 0, 1, 2, 0};         // blocchi: [1,2] [1,2] [1,2]

    /* T4: sottoliste vuote tra zeri (somma 0) */
    int t4[] = {4, 1, 0, 0, 3, 0};                   // blocchi: [4,1] [] [3]

    struct {
        const char *name;
        int *arr;
        int n;
    } tests[] = {
        {"T1", t1, 11},
        {"T2", t2, 9},
        {"T3", t3, 9},
        {"T4", t4, 6},
    };

    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s ====================\n", tests[i].name);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        int removed = eliminaSottolisteDominate(&L);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));
        printf("Nodi rimossi (non contando gli 0): %d\n", removed);

        freeList(L);
    }

    return 0;
}
int sommasottolista(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        int somma=0;
        while(head!=NULL && head->val!=0)
            {
                somma=somma+head->val;
            }
        return somma;
    }
int contasottoliste(Lista head)  // numero di sottliste
    {
        if(head==NULL)
            return 0;
        int count=0;
        while(head!=NULL)
            {
                if (head->val==0) {
                    count++;
                }
                head=head->next;
            }
        return count;
    }
int riempivett(Lista head)
    {
    int len=contasottoliste(head);
    int *vett=malloc(sizeof(int)*len);
    for(int i=0; i<len; i++)
        {
            vett[i]=0;
        }
    int count=0;
    while(head!=NULL)
        {
            if(head->val==0)
                {
                    vett[count]=sommasottolista(head);
                    count++;
                }
            head=head->next;
        }
    int max=0;
    int posmax=0;
    for(int i=0; i<len; i++)
        {
            if(vett[i]>max)
                {
                    max=vett[i];
                    posmax=i;
                }
        }
    return posmax;
    }
Lista trovablocco(Lista head, int pos)
    {
    int i=0;
    while(head!=NULL)
        {
            if(head->val==0)
                {
                    i++;
                }
            if(i%2==pos)
                {
                    return head;
                }
        }
        return head;
    }
int contablocco(Lista head)
    {
        if(head==NULL)
            return 0;
    head=head->next;
    int count=1;
    while(head!=NULL && head->val!=0)
        {
            count++;
            head=head->next;
        }
    return count;
    }
Lista distruggiK(Lista head, int k)
{
    if(head==NULL)
        return head;
    for(int i=0; head!=NULL && i<k; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
}
int f(Lista *l, Lista inizio, int k)
    {
        if(*l==NULL)
            return 0;
    Lista *pp=l;
    int somma=0;
    while(*pp!=NULL)
        {
            if(*pp==inizio)
                {
                    *pp=distruggiK(*pp, k);
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    return k;
    }
int funz(Lista head)
    {
        if(head==NULL)
            return 0;
    int count=0;
    while (head!=0) {
        count++;
        head=head->next;
    }
    return count;
    }
int eliminaSottolisteDominate(Lista *L) {
    int pos=riempivett(*L);
    Lista inizio=trovablocco(*L, pos);
    int len=funz(inizio);
    return f(L, inizio, len);
}
