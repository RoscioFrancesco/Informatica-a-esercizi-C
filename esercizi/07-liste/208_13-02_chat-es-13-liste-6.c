//
//  main.c
//  chat es 13 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int dato;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;
Lista pushBack(Lista l, int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->dato = x;
    n->next = NULL;

    if (l == NULL) return n;

    Nodo *cur = l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return l;
}
void stampaLista(const char *titolo, Lista l) {
    printf("%s", titolo);
    while (l != NULL) {
        printf("%d", l->dato);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}
void liberaLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}


Lista rendiNonDecrescenteEliminandoK(Lista L, int k);
/* oppure, se preferisci:
   Lista rendiNonDecrescenteEliminandoK(Lista *pL, int k);
*/

int main(void) {
    /* TEST 1: 5 -> 1 -> 2 -> 3, k=1 */
    Lista L1 = NULL;
    L1 = pushBack(L1, 5);
    L1 = pushBack(L1, 1);
    L1 = pushBack(L1, 2);
    L1 = pushBack(L1, 3);

    int k1 = 1;
    printf("=== TEST 1 ===\n");
    stampaLista("Input : ", L1);
    printf("k = %d\n", k1);

    Lista R1 = rendiNonDecrescenteEliminandoK(L1, k1);

    stampaLista("Output: ", R1);
    printf("\n");

    /* TEST 2: 1 -> 4 -> 2 -> 3, k=1 */
    Lista L2 = NULL;
    L2 = pushBack(L2, 1);
    L2 = pushBack(L2, 4);
    L2 = pushBack(L2, 2);
    L2 = pushBack(L2, 3);

    int k2 = 1;
    printf("=== TEST 2 ===\n");
    stampaLista("Input : ", L2);
    printf("k = %d\n", k2);

    Lista R2 = rendiNonDecrescenteEliminandoK(L2, k2);

    stampaLista("Output: ", R2);
    printf("\n");

    /* TEST 3: già non-decrescente, k=2 */
    Lista L3 = NULL;
    L3 = pushBack(L3, 1);
    L3 = pushBack(L3, 2);
    L3 = pushBack(L3, 2);
    L3 = pushBack(L3, 5);

    int k3 = 2;
    printf("=== TEST 3 ===\n");
    stampaLista("Input : ", L3);
    printf("k = %d\n", k3);

    Lista R3 = rendiNonDecrescenteEliminandoK(L3, k3);

    stampaLista("Output: ", R3);
    printf("\n");

    /* TEST 4: eliminazioni multiple con violazioni ripetute */
    Lista L4 = NULL;
    L4 = pushBack(L4, 3);
    L4 = pushBack(L4, 1);
    L4 = pushBack(L4, 2);
    L4 = pushBack(L4, 0);
    L4 = pushBack(L4, 4);

    int k4 = 2;
    printf("=== TEST 4 ===\n");
    stampaLista("Input : ", L4);
    printf("k = %d\n", k4);

    Lista R4 = rendiNonDecrescenteEliminandoK(L4, k4);

    stampaLista("Output: ", R4);
    printf("\n");

    
    liberaLista(R1);
    liberaLista(R2);
    liberaLista(R3);
    liberaLista(R4);

    return 0;
}
Lista cancellaK(Lista head, int k)
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
void f(Lista *l, int k)
    {
        if(*l==NULL)
            return;
    Lista *pp=l;
        while(*pp!=NULL && (*pp)->next!=NULL)
            {
                if((*pp)->dato>(*pp)->next->dato && k>0)
                    {
                        Lista temp=*pp;
                        *pp=(*pp)->next;
                        free(temp);
                        k--;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
Lista rendiNonDecrescenteEliminandoK(Lista L, int k)
    {
    f(&L, k);
    return L;
    }
