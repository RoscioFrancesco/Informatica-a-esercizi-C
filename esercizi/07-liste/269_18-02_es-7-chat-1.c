//
//  main.c
//  es 7 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int val;
    struct nodo* next;
} nodo;

typedef nodo* lista;

void potaBlocchiFinestra(lista *L);

static nodo* newNode(int x){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(!n){ perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static lista pushBack(lista L, int x){
    nodo* n = newNode(x);
    if(L == NULL) return n;
    nodo* cur = L;
    while(cur->next) cur = cur->next;
    cur->next = n;
    return L;
}

static lista buildFromArray(const int a[], int n){
    lista L = NULL;
    for(int i=0;i<n;i++) L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* label, lista L){
    printf("%s", label);
    if(L == NULL){ printf("NULL\n"); return; }
    while(L){
        printf("%d", L->val);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void freeList(lista L){
    while(L){
        nodo* t = L;
        L = L->next;
        free(t);
    }
}
int sommaval(lista head, int k);
int main(void){

    /* --- TEST 1: un blocco valido semplice --- */
    {
        int a[] = {8, 1, 2, 3, 6, 9};
        lista L = buildFromArray(a, 6);

        printf("=== TEST 1 ===\n");
        printList("Input : ", L);

        potaBlocchiFinestra(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 2: due blocchi in sequenza + ripetizione finché stabile --- */
    {
        int a[] = {4, 1, 1, 1, 10, 2, 2, 2, 8};
        lista L = buildFromArray(a, 9);

        printf("=== TEST 2 ===\n");
        printList("Input : ", L);

        potaBlocchiFinestra(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 3: blocco grande “massimale” (non prendere finestre più piccole) --- */
    {
        int a[] = {12, 1, 2, 3, 4, 10, 7};
        lista L = buildFromArray(a, 7);

        printf("=== TEST 3 ===\n");
        printList("Input : ", L);

        potaBlocchiFinestra(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 4: nessun blocco valido --- */
    {
        int a[] = {2, 9, 1, 8};
        lista L = buildFromArray(a, 4);

        printf("=== TEST 4 ===\n");
        printList("Input : ", L);

        potaBlocchiFinestra(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    return 0;
}
//Un blocco-valido è una sequenza contigua di nodi di lunghezza ≥ 4 tale che: il primo e l’ultimo nodo del blocco sono pari tutti i nodi interni sono strettamente minori della media reale degli estremi Media reale = (A + B) / 2.0 Operazione da eseguire su ogni blocco valido massimale: elimina tutti i nodi interni (mantieni gli estremi) sostituisci il valore del primo estremo con la somma dei valori eliminati il secondo estremo resta invariato
int lunghezzaBloccoFinestra(nodo* start)
{
    if(start == NULL || start->next == NULL)
        return 0;

    if(start->val % 2 != 0)   // primo deve essere pari
        return 0;

    nodo* curr = start->next;

    int lunghezzaMassima = 0;

    while(curr != NULL)
    {
        if(curr->val % 2 == 0)   // possibile estremo B
        {
            int lenInterni = 0;
            nodo* tmp = start->next;
            double media = (start->val + curr->val) / 2.0;
            int valido = 1;

            while(tmp != curr)
            {
                if(tmp->val >= media)
                {
                    valido = 0;
                    break;
                }
                lenInterni++;
                tmp = tmp->next;
            }

            if(valido && lenInterni >= 2)   // lunghezza totale ≥ 4
            {
                lunghezzaMassima = lenInterni + 2;  // A + interni + B
            }
        }

        curr = curr->next;
    }

    return lunghezzaMassima;
}

lista eliminaK(lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k && head!=NULL; i++)
        {
            lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
void potaBlocchiFinestra(lista *l)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
        while(*pp!=NULL)
            {
                int len=lunghezzaBloccoFinestra(*pp);
                if(len>=4)
                    {
                        (*pp)->val=sommaval((*pp), len);
                        (*pp)->next=eliminaK((*pp)->next, len-2);
                        pp=&(*pp)->next;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
int sommaval(lista head, int k)
    {
        if(head==NULL || head->next==NULL)
            return 0;
        int somma=0;
        head=head->next;
        for(int i=0; i<k-1; i++)
            {
                somma=somma+head->val;
            }
    return somma;
    }
