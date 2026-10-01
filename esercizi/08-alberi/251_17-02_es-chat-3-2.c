//
//  main.c
//  es chat 3  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node *left, *right;
} node;

typedef node* tree;

int verificaCammini(tree T);

tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->v = x;
    n->left = n->right = NULL;
    return n;
}

void printPreorder(tree T) {
    if (T == NULL) return;
    printf("%d ", T->v);
    printPreorder(T->left);
    printPreorder(T->right);
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* =========================================================
       TEST 1: TUTTI i cammini validi  -> atteso 1

                 5
               /   \
              7     6
             / \     \
            3   4     2

       Cammini:
       5-7-3 : cresce (5<7) poi decresce (7>3) OK
       5-7-4 : cresce poi decresce OK
       5-6-2 : cresce (5<6) poi decresce (6>2) OK
       Un solo massimo per ogni cammino.
       ========================================================= */
    tree T1 = newNode(5);
    T1->left = newNode(7);
    T1->right = newNode(6);
    T1->left->left = newNode(3);
    T1->left->right = newNode(4);
    T1->right->right = newNode(2);

    printf("=== TEST 1 ===\n");
    printf("Preorder: ");
    printPreorder(T1);
    printf("\n");
    printf("verificaCammini(T1) = %d\n\n", verificaCammini(T1));


    /* =========================================================
       TEST 2: cammino NON valido (doppio cambio) -> atteso 0

                 5
                /
               7
              /
             6
            /
           8

       Cammino unico: 5-7-6-8
       sale (5<7), scende (7>6), poi RISSALE (6<8) => VIOLA (2 cambi)
       ========================================================= */
    tree T2 = newNode(5);
    T2->left = newNode(7);
    T2->left->left = newNode(6);
    T2->left->left->left = newNode(8);

    printf("=== TEST 2 ===\n");
    printf("Preorder: ");
    printPreorder(T2);
    printf("\n");
    printf("verificaCammini(T2) = %d\n\n", verificaCammini(T2));


    
    tree T3 = newNode(5);
    T3->left = newNode(5);
    T3->right = newNode(4);

    printf("=== TEST 3 ===\n");
    printf("Preorder: ");
    printPreorder(T3);
    printf("\n");
    printf("verificaCammini(T3) = %d\n\n", verificaCammini(T3));


    /* cleanup */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);

    return 0;
}
int verifica(int vett[], int len)
    {
    int max=0;
    int j=0;
    for(int i=0; i<len; i++)
        {
            if(vett[i]>max)
                {
                    max=vett[i];
                    j=i;
                }
        }
    if (j == 0 || j == len-1) return 0;
    for(int i=0; i<len; i++)
        {
            if(i<j)
                {
                    if(vett[i+1]<=vett[i])
                        return 0;
                    if(vett[i]>=max)
                        return 0;
                }
            if(i>j && i<len-1)
            {
                if(vett[i+1]>=vett[i])
                    return 0;
                if(vett[i]>=max)
                    return 0;
            }
        }
    return 1;
    }
int f(int depth, tree t, int segna, int vett[])
    {
        if(t==NULL)
            return 1;
        vett[segna]=t->v;
        (depth++);
        segna++;
        if(t->left==NULL && t->right==NULL)
            {
                if(verifica(vett, depth)==0)
                    return 0;
                return 1;
            }
    int sx=f(depth, t->left, segna, vett);
    int dx=f(depth, t->right, segna, vett);
    return sx&&dx;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int prof(tree t)
    {
        if(t==NULL)
            return 0;
    int sx=prof(t->left);
    int dx=prof(t->right);
    return 1+max(sx, dx);
    }

int wrapper(tree t)
    {
        int depth=prof(t);
    int *vett=malloc(sizeof(int)*depth);
    for(int i=0; i<depth; i++)
        {
            vett[i]=0;
        }
    int ris=f(0, t, 0, vett);
    free(vett);
    return ris;
    }
int verificaCammini(tree T)
    {
    return wrapper(T);
    }
