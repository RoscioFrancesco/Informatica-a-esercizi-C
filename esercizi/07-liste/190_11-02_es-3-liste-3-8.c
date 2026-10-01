//
//  main.c
//  es 3 liste 3 -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE BASE
   ========================= */

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo * Lista;

/* Lista di liste */
typedef struct nodoLista {
    Lista sub;                 /* sottolista palindromica */
    struct nodoLista *next;
} NodoLista;

typedef NodoLista * ListaDiListe;



ListaDiListe sottolistePalindromiche(Lista L);


/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

static Nodo *nuovoNodo(int v) {
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista head, int v) {
    Nodo *n = nuovoNodo(v);
    if (head == NULL) return n;

    Nodo *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d", l->valore);
        if (l->next != NULL) printf(" -> ");
        l = l->next;
    }
    printf("\n");
}

static void stampaListaDiListe(ListaDiListe ll) {
    int idx = 1;
    while (ll != NULL) {
        printf("Sottolista %d: [", idx);
        Nodo *cur = ll->sub;
        while (cur != NULL) {
            printf("%d", cur->valore);
            if (cur->next != NULL) printf(" -> ");
            cur = cur->next;
        }
        printf("]\n");
        ll = ll->next;
        idx++;
    }
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}

static void freeListaDiListe(ListaDiListe ll) {
    while (ll != NULL) {
        NodoLista *tmp = ll;
        ll = ll->next;
        freeLista(tmp->sub);
        free(tmp);
    }
}


ListaDiListe inseriscincodaLDL(ListaDiListe head, Lista start, int k);
int distanza(Lista head);
int main(void) {

    /* Input esempio:
       1 -> 2 -> 3 -> 2 -> 1 -> 4 -> 5 -> 5 -> 6
       Output atteso:
       [1 -> 2 -> 3 -> 2 -> 1]
       [5 -> 5]
    */
    int v[] = {1, 2, 3, 2, 1, 4, 5, 5, 6};
    int n = (int)(sizeof(v) / sizeof(v[0]));

    Lista L = NULL;
    for (int i = 0; i < n; i++)
        L = pushBack(L, v[i]);

    printf("Lista di input:\n");
    stampaLista(L);

    ListaDiListe out = sottolistePalindromiche(L);

    printf("\nOutput (sottoliste palindromiche massimali):\n");
    if (out == NULL) {
        printf("(NULL) <-- implementa sottolistePalindromiche\n");
    } else {
        stampaListaDiListe(out);
    }

    printf("\nLista originale dopo la chiamata (non deve cambiare):\n");
    stampaLista(L);

    /* Deallocazioni */
    freeLista(L);
    freeListaDiListe(out);

    return 0;
}

Lista invertitilista(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
    Lista temp=invertitilista(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
    }
int compara(Lista l1, Lista l2, int *count) // 1 se va copiata, 0 se no
    {
        if(l1==NULL && l2==NULL && (*count)>=2)
            return 1;
        if(l1==NULL || l2==NULL)
            return 0;
        if(l1->valore!=l2->valore)
            return 0;
        (*count)++;
    return compara(l1->next, l2->next, count);
    }
Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->valore=x;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
Lista copiaK(Lista head, int k)
    {
    Lista new=NULL;
    for(int i=0; i<k; i++)
        {
            new=inseriscincoda(new, head->valore);
            head=head->next;
        }
    return new;
    }
int palindroma(Lista start, int k)
    {
    Lista new=copiaK(start, k);
    Lista invertita=copiaK(start, k);
    invertita=invertitilista(invertita);
    int count=0;
    if(compara(new, invertita, &count)==1)
    {
        freeLista(new);
        free(invertita);
        return 1;
    }
    return 0;
    }
ListaDiListe sottolistePalindromiche(Lista head)
    {
        if(head==NULL)
            return NULL;
        ListaDiListe new=NULL;
        while (head!=NULL) {
            for(int i=1; i<distanza(head); i++)
                {
                    if (palindroma(head, i)) {
                        new=inseriscincodaLDL(new, head, i);
                    }
                }
            head=head->next;
        }
    return new;
    }
ListaDiListe inseriscincodaLDL(ListaDiListe head, Lista start, int k)
    {
        if(head==NULL)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->next=NULL;
                new->sub=copiaK(start, k);
                return new;
            }
        head->next=inseriscincodaLDL(head->next, start, k);
        return head;
    }
int distanza(Lista head)
    {
    int count=0;
    while (head!=NULL) {
        count++;
        head=head->next;
    }
    return count;
    }

