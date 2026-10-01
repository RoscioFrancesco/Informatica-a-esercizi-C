//
//  main.c
//  es tde 1 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

int uniformementeOscillante(Lista L);


Lista inserisciInCoda(Lista head, int valore) {
    Nodo *new = (Nodo*)malloc(sizeof(Nodo));
    new->val = valore;
    new->next = NULL;

    if (head == NULL)
        return new;

    Nodo *scorri = head;
    while (scorri->next != NULL)
        scorri = scorri->next;

    scorri->next = new;
    return head;
}

void stampaLista(Lista head) {
    printf("[ ");
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("]");
}

void liberaLista(Lista head) {
    Nodo *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


/* =========================
   MAIN DI TEST
   ========================= */
int len_decrecente(Lista head);
int len_crecente(Lista head);
int main() {

    printf("=== TEST LISTA UNIFORMEMENTE OSCILLANTE ===\n\n");

    /* ===== ESEMPIO 1 ===== */
    Lista L1 = NULL;
    int v1[] = {4,5,7,3,1,5,9,4,3};
    int n1 = 9;

    for(int i=0; i<n1; i++)
        L1 = inserisciInCoda(L1, v1[i]);

    printf("Lista 1: ");
    stampaLista(L1);
    printf("\n");

    int r1 = uniformementeOscillante(L1);
    printf("Risultato ottenuto: %d\n", r1);
    printf("Output atteso   : 1\n\n");


    /* ===== ESEMPIO 2 ===== */
    Lista L2 = NULL;
    int v2[] = {0,1,0,-1,0,1,0,-1};
    int n2 = 8;

    for(int i=0; i<n2; i++)
        L2 = inserisciInCoda(L2, v2[i]);

    printf("Lista 2: ");
    stampaLista(L2);
    printf("\n");

    int r2 = uniformementeOscillante(L2);
    printf("Risultato ottenuto: %d\n", r2);
    printf("Output atteso   : 0\n\n");


    /* ===== LIBERO MEMORIA ===== */
    liberaLista(L1);
    liberaLista(L2);

    return 0;
}



int uniformementeOscillante(Lista L) {
    int hasprec=0;
    int num=0;
    Lista scorri=L;
    while (scorri!=NULL) {
        int cr=len_crecente(scorri);
        int decr=len_decrecente(scorri);
        if(hasprec==0)
            {
                hasprec=1;
                if(cr!=0)
                    num=cr;
                if(decr!=0)
                    num=decr;
            }
        else
            {
                if(cr!=0 && num!=cr)
                    return 0;
                if(decr!=0 && num!=decr)
                    return 0;
            }
        if(cr>0)
            {
                for(int i=0; i<cr; i++)
                    {
                        scorri=scorri->next;
                    }
            }
        if(decr>0)
            {
                for(int i=0; i<decr; i++)
                    {
                        scorri=scorri->next;
                    }
            }
        if(cr+decr==0)
        {
            scorri=scorri->next;
        }
    }
    return 1;
}
int len_crecente(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        while(head!=NULL && head->next!=NULL)
            {
                if(!(head->next->val>head->val))
                    {
                        return count;
                    }
                count++;
                head=head->next;
            }
    return count;
}
int len_decrecente(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
    while(head!=NULL && head->next!=NULL)
        {
            if(!(head->next->val<head->val))
                {
                    return count;
                }
            count++;
            head=head->next;
        }
    return count;
    }
