//
//  main.c
//  tde 6 alberi -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ET {
    char parola[1000];
    struct ET *left, *right;
} treeNode;

typedef treeNode *tree;

int f(tree t);

/* ===== SUPPORTO TEST ===== */
tree newNode(const char *s) {
    treeNode *n = (treeNode*)malloc(sizeof(treeNode));
    strcpy(n->parola, s);
    n->left = n->right = NULL;
    return n;
}

void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

typedef struct QN { tree x; int level; struct QN *next; } QN;
void printByLevels(tree t) {
    if (!t) { printf("(albero vuoto)\n"); return; }
    QN *head=NULL, *tail=NULL;

    // enqueue
    QN *q = (QN*)malloc(sizeof(QN));
    q->x=t; q->level=0; q->next=NULL;
    head=tail=q;

    int curL = -1;
    while (head) {
        QN *p = head; head = head->next;
        if (!head) tail = NULL;

        if (p->level != curL) {
            curL = p->level;
            printf("\nLivello %d: ", curL);
        }
        printf("\"%s\"  ", p->x->parola);

        if (p->x->left) {
            QN *a=(QN*)malloc(sizeof(QN));
            a->x=p->x->left; a->level=p->level+1; a->next=NULL;
            if (!tail) head=tail=a; else { tail->next=a; tail=a; }
        }
        if (p->x->right) {
            QN *b=(QN*)malloc(sizeof(QN));
            b->x=p->x->right; b->level=p->level+1; b->next=NULL;
            if (!tail) head=tail=b; else { tail->next=b; tail=b; }
        }
        free(p);
    }
    printf("\n\n");
}
int funz(tree albero, char vett[], int livello);
int f(tree albero);
int main(void) {
    /* ===== ALBERO 1: deve essere OK (f = 1) =====
            "roma"
           /      \
       "rana"    "rete"
        /   \       \
    "casa" "cielo"  "cane"

       Liv0: r
       Liv1: r r
       Liv2: c c c
    */
    tree T1 = newNode("roma");
    T1->left = newNode("rana");
    T1->right = newNode("rete");
    T1->left->left = newNode("casa");
    T1->left->right = newNode("cielo");
    T1->right->right = newNode("cane");

    /* ===== ALBERO 2: deve essere NO (f = 0) =====
            "roma"
           /      \
       "rana"    "rete"
        /   \       \
    "casa" "miele"  "cane"

       Liv2: c m c  -> NON tutte stessa lettera
    */
    tree T2 = newNode("roma");
    T2->left = newNode("rana");
    T2->right = newNode("rete");
    T2->left->left = newNode("casa");
    T2->left->right = newNode("miele");
    T2->right->right = newNode("cane");

    printf("=== TEST 1 (atteso: 1) ===");
    printByLevels(T1);
    printf("f(T1) = %d\n\n", f(T1));

    printf("=== TEST 2 (atteso: 0) ===");
    printByLevels(T2);
    printf("f(T2) = %d\n\n", f(T2));

    freeTree(T1);
    freeTree(T2);
    return 0;
}
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=depth(albero->left);
    int dx=depth(albero->right);
    return 1+max(sx, dx);
    }
int funz(tree albero, char vett[], int livello)
    {
        if(albero==NULL)
            return 1;
        if(vett[livello]=='\0')
            {
                vett[livello]=albero->parola[0];
            }
        else if(vett[livello]!=albero->parola[0])
            return 0;
    return funz(albero->left, vett, livello+1) && funz(albero->right, vett, livello+1);
    }
int f(tree albero)
    {
    int p=depth(albero);
    char *vett=malloc(sizeof(char)*p);
    for(int i=0; i<p; i++)
        {
            vett[i]='\0';
        }
    int ris=funz(albero, vett, 0);
    free(vett);
    return ris;
    }
