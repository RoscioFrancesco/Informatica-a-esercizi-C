//
//  main.c
//  es chat 2 alberi -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//



#include <stdio.h>
#include <stdlib.h>

#define K 10

typedef struct N {
    int v;                 /* 0..9 */
    struct N *left, *right;
} Node;

typedef Node* tree;

typedef struct EL{
    int array[10];
    struct EL* next;
}Vagone;
typedef Vagone* Lista; // faccio una lista di array

int esistonoDueCamminiStessaFirmaVersoTarget(tree t, int TARGET);  /* TODO */
Lista inseriscincoda(Lista head, int vett[]);
/* =========================
   UTILITY PER TEST
   ========================= */
static tree newNode(int v) {
    tree n = (tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* Preorder con parentesi per capire meglio la struttura */
static void printPreorder(tree t) {
    if (!t) { printf("NULL"); return; }
    printf("%d(", t->v);
    printPreorder(t->left);
    printf(",");
    printPreorder(t->right);
    printf(")");
}

/* =========================
   ALBERI DI TEST GRANDI
   ========================= */


static tree buildTest_BIG_OK(void) {
    tree r = newNode(4);

    r->left = newNode(2);
    r->right = newNode(2);

    r->left->left = newNode(1);
    r->left->right = newNode(3);

    r->right->left = newNode(3);
    r->right->right = newNode(1);

    /* livello 3 */
    r->left->left->left = newNode(7);
    r->left->left->right = newNode(5);

    r->left->right->left = newNode(6);
    r->left->right->right = newNode(7);

    r->right->left->left = newNode(6);
    r->right->left->right = newNode(7);

    r->right->right->left = newNode(7);
    r->right->right->right = newNode(5);

    /* livello 4 (aggiunte per complessità) */
    r->left->left->right->left = newNode(7);          /* sotto il 5 */
    r->left->right->right->right = newNode(7);        /* sotto il 7 (dx) */
    r->right->left->right->right = newNode(0);        /* sotto il 7 (dx) */

    /* livello 5 */
    r->left->right->right->right->left = newNode(4);  /* sotto il 7 extra */

    return r;
}


static tree buildTest_BIG_NO(void) {
    tree r = newNode(8);

    r->left = newNode(4);
    r->right = newNode(4);

    r->left->left = newNode(2);
    r->left->right = newNode(6);

    r->right->left = newNode(6);
    r->right->right = newNode(2);

    r->left->left->left = newNode(9);
    r->left->left->right = newNode(1);

    r->left->right->left = newNode(3);
    r->left->right->right = newNode(9);

    r->right->left->left = newNode(9);
    r->right->left->right = newNode(5);

    r->right->right->left = newNode(7);
    r->right->right->right = newNode(9);

    /* extra profondità */
    r->left->left->right->left = newNode(0);
    r->left->left->right->right = newNode(9);

    r->right->left->right->right = newNode(1);
    r->right->right->right->left = newNode(2);

    return r;
}

/*
TEST 3 (ancora più profondo, TARGET=3):
Serve per beccare soluzioni che sbagliano il backtracking (decremento).

              0
               \
                1
                 \
                  2
                   \
                    3
                   /
                  2
                 /
                3
               /
              3
*/
static tree buildTest_DEEP(void) {
    tree r = newNode(0);
    r->right = newNode(1);
    r->right->right = newNode(2);
    r->right->right->right = newNode(3);
    r->right->right->right->left = newNode(2);
    r->right->right->right->left->left = newNode(3);
    r->right->right->right->left->left->left = newNode(3);
    return r;
}

/* =========================
   MAIN DI TEST
   ========================= */
int verificalista(Lista head);
int esistonoDueCamminiStessaFirmaVersoTarget(tree albero, int target);
Lista inseriscincoda(Lista head, int vett[]);
void f(tree albero, int vett[], int target, Lista *head);

int main(void) {
    tree t1 = buildTest_BIG_OK();
    tree t2 = buildTest_BIG_NO();
    tree t3 = buildTest_DEEP();

    int TARGET;

    TARGET = 7;
    printf("=== TEST 1 (BIG OK?, TARGET=%d) ===\n", TARGET);
    printf("Preorder: ");
    printPreorder(t1);
    printf("\n");
    printf("Risultato = %d\n\n", esistonoDueCamminiStessaFirmaVersoTarget(t1, TARGET));

    TARGET = 9;
    printf("=== TEST 2 (BIG NO?, TARGET=%d) ===\n", TARGET);
    printf("Preorder: ");
    printPreorder(t2);
    printf("\n");
    printf("Risultato = %d\n\n", esistonoDueCamminiStessaFirmaVersoTarget(t2, TARGET));

    TARGET = 3;
    printf("=== TEST 3 (DEEP, TARGET=%d) ===\n", TARGET);
    printf("Preorder: ");
    printPreorder(t3);
    printf("\n");
    printf("Risultato = %d\n\n", esistonoDueCamminiStessaFirmaVersoTarget(t3, TARGET));

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);

    return 0;
}


void f(tree albero, int vett[], int target, Lista *head)
    {
        if(albero==NULL)
            return;
        vett[albero->v]++;
        if(albero->v==target)
            {
                *head=inseriscincoda(*head, vett);
                vett[albero->v]--; // capire bene questo backtracking
                return;
            }
        f(albero->left, vett, target, head);
        f(albero->right, vett, target, head);
        vett[albero->v]--;
    }
Lista inseriscincoda(Lista head, int vett[])
    {
        if(head==NULL)
        {
            Lista new=(Lista)malloc(sizeof(*new));
            new->next=NULL;
            for(int i=0; i<10; i++)
            {
                new->array[i]=vett[i];
            }
            new->next=NULL;
            return new;
        }
        head->next=inseriscincoda(head->next, vett);
        return head;
    }
int verificalista(Lista head)
    {
        if(head==NULL)
            return 0;
    Lista scorri=head;
    while (scorri!=NULL) {
        Lista succ=scorri->next;
        while (succ!=NULL) {
            int flag=1;
            for (int i=0; i<10; i++) {
                if(scorri->array[i]!=succ->array[i])
                    flag=0;
            }
            if(flag==1)
                return 1;
            succ=succ->next;
        }
        scorri=scorri->next;
    }
    return 0;
    }
int fromhere(tree albero, int target)
    {
    int vett[10]={0};
    Lista head=NULL;
    f(albero, vett, target, &head);
    return verificalista(head);
    }
int esistonoDueCamminiStessaFirmaVersoTarget(tree t, int TARGET)
    {
        if(t==NULL)
            return 0;
        if(fromhere(t, TARGET))
            return 1;
    return esistonoDueCamminiStessaFirmaVersoTarget(t->left, TARGET)|| esistonoDueCamminiStessaFirmaVersoTarget(t->right, TARGET);
    }
