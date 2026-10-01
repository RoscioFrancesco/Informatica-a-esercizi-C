//
//  main.c
//  es 6 alberi campi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo, refuso corretto)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node * tree;

typedef struct ELLista {
    tree foglia;              /* punta ad una foglia dell'albero */
    struct ELLista *next;
} nodeLista;

typedef nodeLista * Lista;

/* =========================
   PROTOTIPO FUNZIONE RICHIESTA
   ========================= */

Lista listaFoglie(tree t);


static tree nuovoNodo(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}


int contanodi(tree head);
void f(tree *radice, Lista* head, int *count, int num);



Lista listaFoglie(tree t) {
    Lista head=NULL;
    int count=0;
    int num=contanodi(t);
    f(&t, &head, &count, num);
    return head;
}

/* =========================
   STAMPA LISTA (per test)
   ========================= */
static void stampaLista(Lista L) {
    printf("Foglie nella lista (valori dei nodi foglia): ");
    while (L != NULL) {
        if (L->foglia != NULL)
            printf("%d ", L->foglia->dato);
        else
            printf("NULL ");
        L = L->next;
    }
    printf("\n");
}

/* =========================
   MAIN
   ========================= */
int contanodi(tree head);
Lista insericincoda(Lista head, tree singola);
void f(tree *radice, Lista* head, int *count, int num);
int main() {
    tree T;
    Lista L;

    /* Costruisco un albero di esempio:
             1
            / \
           2   3
          /   / \
         4   5   6

       Foglie: 4, 5, 6
    */
    T = nuovoNodo(1);
    T->left = nuovoNodo(2);
    T->right = nuovoNodo(3);
    T->left->left = nuovoNodo(4);
    T->right->left = nuovoNodo(5);
    T->right->right = nuovoNodo(6);

    
    L = listaFoglie(T);

    /* Stampo la lista ottenuta */
    stampaLista(L);

    return 0;
}

void f(tree *radice, Lista* head, int *count, int num)
    {
        if(radice==NULL || *radice==NULL)
            return;
        *head=insericincoda(*head, *radice);
        (*count)++;
        if(*count==num)
            return;
    tree *sx=&(*radice)->left;
    tree *dx=&(*radice)->right;
    f(sx, head, count, num);
    f(dx, head, count, num);
    }

int contanodi(tree head)
    {
        if(head==NULL)
            return 0;
    return 1+contanodi(head->left)+contanodi(head->right);
    }
Lista insericincoda(Lista head, tree singola)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->foglia=singola;
                return new;
            }
        head->next=insericincoda(head->next, singola);
        return head;
    }
