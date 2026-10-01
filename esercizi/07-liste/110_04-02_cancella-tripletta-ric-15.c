//
//  main.c
//  cancella tripletta ric -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>
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
int contadispari(Lista p)
    {
        if(p==NULL)
            return 0;
        if(p->val%2==0)
            return 0;
    return 1+contadispari(p->next);
    }
Lista salta(Lista p, int k)
    {
        if(p==NULL)
            return p;
        if(k==0)
            return p;
    return salta(p->next, k-1);
    }

void freeK(Lista p, int k)
    {
        if(p==NULL)
            return;
        if(k==0)
            return;
        Lista temp=p->next;
        free(p);
        freeK(temp, k-1);
    }

Lista cancellaTriplette(Lista head)
    {
        if(head==NULL)
            return head;
        int k=contadispari(head);
        if(k>=3)
            {
                Lista temp=head;
                temp=salta(head, k);
                freeK(head, k);
                return cancellaTriplette(temp);
            }
    else
    {
        head->next=cancellaTriplette(head->next);
        return head;
    }
    }
