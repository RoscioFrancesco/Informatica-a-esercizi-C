//
//  main.c
//  vett dinamici 2 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE DATI
   ========================================================= */
typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef Node* Lista;


Lista cancellaTriplette(Lista head);

/* =========================================================
   UTILITY (QUI I CICLI SONO OK PER TEST)
   ========================================================= */
static Node* newNode(int x, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = next;
    return n;
}

/* crea lista da array mantenendo ordine */
static Lista fromArray(const int a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--)
        l = newNode(a[i], l);
    return l;
}

static void printLista(const char *msg, Lista l) {
    printf("%s", msg);
    while (l != NULL) {
        printf("%d", l->val);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Node *tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
void blocco(Lista start, Lista *finish, int *count) ;

int main(void) {
    int a1[] = {1, 40, 15, 16, 3, 15, 5, 6};
    int n1 = (int)(sizeof(a1) / sizeof(a1[0]));
    Lista l1 = fromArray(a1, n1);

    printf("=== TEST 1 (esempio consegna) ===\n");
    printLista("Prima: ", l1);
    l1 = cancellaTriplette(l1);     
    printLista("Dopo : ", l1);
    printf("\n");
    freeLista(l1);

    /* Test 2: tripla all'inizio */
    int a2[] = {3, 5, 7, 10, 2};
    int n2 = (int)(sizeof(a2) / sizeof(a2[0]));
    Lista l2 = fromArray(a2, n2);

    printf("=== TEST 2 (tripla all'inizio) ===\n");
    printLista("Prima: ", l2);
    l2 = cancellaTriplette(l2);
    printLista("Dopo : ", l2);
    printf("\n");
    freeLista(l2);

    /* Test 3: tripla alla fine */
    int a3[] = {2, 4, 9, 11, 13};
    int n3 = (int)(sizeof(a3) / sizeof(a3[0]));
    Lista l3 = fromArray(a3, n3);

    printf("=== TEST 3 (tripla alla fine) ===\n");
    printLista("Prima: ", l3);
    l3 = cancellaTriplette(l3);
    printLista("Dopo : ", l3);
    printf("\n");
    freeLista(l3);

    /* Test 4: nessuna tripla */
    int a4[] = {1, 2, 3, 4, 5, 6}; /* dispari mai >=3 consecutivi */
    int n4 = (int)(sizeof(a4) / sizeof(a4[0]));
    Lista l4 = fromArray(a4, n4);

    printf("=== TEST 4 (nessuna tripla) ===\n");
    printLista("Prima: ", l4);
    l4 = cancellaTriplette(l4);
    printLista("Dopo : ", l4);
    printf("\n");
    freeLista(l4);

    return 0;
}
/* TODO: rimuove sequenze di >=3 dispari consecutivi */

Lista cancellaTriplette(Lista head)
    {
        if(head==NULL || head->next==NULL || head->next->next==NULL)
            return head;
        Lista scorri=head;
        Lista prec=NULL;
        while(scorri!=NULL)
            {
                if(scorri->val%2==1)
                    {
                        Lista finish=scorri;
                        int count=0;
                        blocco(scorri, &finish, &count);
                        if(count>=3)
                        {
                            if(prec==NULL)
                            {
                                Lista temp=head;
                                head=finish;
                                for(int i=0; i<count; i++)
                                {
                                    Lista temp2=temp->next;
                                    free(temp);
                                    temp=temp2;
                                }
                                head=finish;
                                scorri=head;
                            }
                            else
                            {
                                Lista temp=prec->next;
                                prec->next=finish;
                                for(int i=0; i<count; i++)
                                {
                                    Lista temp2=temp->next;
                                    free(temp);
                                    temp=temp2;
                                }
                                scorri=finish;
                            }
                        }
                        else
                        {
                            prec=scorri;
                            scorri=scorri->next;
                        }
                    }
                else
                    {
                        prec=scorri;
                        scorri=scorri->next;
                    }
            }
        return head;
    }
void blocco(Lista start, Lista *finish, int *count) // finish segna il primo nodo pari dopo il blocco dispari e count indica il numero di elementi dispari nel blocco
    {
        while(*finish!=NULL && (*finish)->val%2==1)
            {
                (*count)++;
                (*finish)=(*finish)->next;
            }
    }
