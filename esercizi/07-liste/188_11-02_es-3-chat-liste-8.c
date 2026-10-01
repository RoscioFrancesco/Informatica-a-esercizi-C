//
//  main.c
//  es 3 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;

Lista potaturaStorica(Lista l);

Nodo *nuovoNodo(int v) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->valore = v;
    n->next = NULL;
    return n;
}

void pushBack(Lista *l, int v) {
    Nodo *n = nuovoNodo(v);
    if (*l == NULL) {
        *l = n;
        return;
    }
    Nodo *c = *l;
    while (c->next) c = c->next;
    c->next = n;
}

void stampaLista(Lista l) {
    while (l) {
        printf("%d", l->valore);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}

void freeLista(Lista l) {
    while (l) {
        Nodo *tmp = l->next;
        free(l);
        l = tmp;
    }
}
Lista f(Lista l, Lista *head);
int main() {
        Lista l = NULL;
        
        /* Esempio con varie ripetizioni */
        pushBack(&l, 5);
        pushBack(&l, 3);
        pushBack(&l, 5);
        pushBack(&l, 5);
        pushBack(&l, 3);
        pushBack(&l, 5);
        pushBack(&l, 7);
        pushBack(&l, 3);
        
        printf("Lista iniziale:\n");
        stampaLista(l);
        
        l = potaturaStorica(l);
        
        printf("\nLista dopo potaturaStorica:\n");
        stampaLista(l);
        
        freeLista(l);
        return 0;
    }
    
int dopo(Lista start, int x)
    {
        if(start==NULL)
            return 0;
        Lista succ=start->next;
        int count=0;
        while (succ!=NULL) {
            if(succ->valore==x)
                count++;
            succ=succ->next;
        }
        if(count>=2)
            return 1;
        return 0;
    }
int prima(Lista head, Lista mio, int x)
    {
        int count=0;
        Lista scorri=head;
        while (scorri!=NULL && scorri!=mio) {
            if(scorri->valore==x)
                count++;
            scorri=scorri->next;
        }
        if(count>=2)
            return 1;
        return 0;
    }
Lista f(Lista l, Lista *head)
    {
        if(l==NULL)
            return l;
        if(prima(*head, l, l->valore) || dopo(l, l->valore))
            {
                if(l==*head)
                    *head=(*head)->next;
                Lista temp=l->next;
                free(l);
                return f(temp, head);
            }
        l->next=f(l->next, head);
        return l;
    }
Lista potaturaStorica(Lista l)
    {
    Lista head=l;
    head=f(l, &head);
    return head;
    }
