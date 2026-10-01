//
//  main.c
//  es 3 alberi  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE
   ========================= */
typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} Node;

typedef Node* Tree;


int contaDominanti(Tree T);
int max(int a, int b);
int wrap(Tree t, int storico[]);
/* =========================
   SUPPORTO: alloc/free
   ========================= */
Tree newNode(int v) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(Tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================
   STAMPE UTILI
   ========================= */
void printInorder(Tree T) {
    if (!T) return;
    printInorder(T->left);
    printf("%d ", T->val);
    printInorder(T->right);
}

/* Altezza (in #archi) per debug: foglia=0, NULL=-1 */
int heightEdges(Tree T) {
    if (T == NULL) return -1;
    int hl = heightEdges(T->left);
    int hr = heightEdges(T->right);
    return 1 + (hl > hr ? hl : hr);
}

/* Somme per livello A(d) del sottoalbero radicato in root.
   È SOLO debug: stampa A(0), A(1), ... (non decide “dominante”). */
void printLevelSums(Tree root) {
    if (root == NULL) {
        printf("(albero vuoto)\n");
        return;
    }

    /* coda semplice (array) */
    Tree q[1024];
    int head = 0, tail = 0;
    q[tail++] = root;

    int level = 0;

    while (head < tail) {
        int levelCount = tail - head;
        long long sum = 0;

        for (int i = 0; i < levelCount; i++) {
            Tree cur = q[head++];
            sum += cur->val;
            if (cur->left)  q[tail++] = cur->left;
            if (cur->right) q[tail++] = cur->right;
        }

        printf("A(%d) = %lld\n", level, sum);
        level++;
    }
}

/* Trova un nodo per valore (prima occorrenza in preorder) per fare debug mirato */
Tree findFirst(Tree T, int target) {
    if (!T) return NULL;
    if (T->val == target) return T;
    Tree a = findFirst(T->left, target);
    if (a) return a;
    return findFirst(T->right, target);
}

int depth(Tree t);
void riempi(Tree t, int vett[], int liv);
void f(Tree t, int storico[], int *count_dominanti, int prof);
int main(void) {

    /* =========================================================
       TEST 1: albero piccolo (altezza >=2)
              1
            /   \
           2     3
          /
         4
       ========================================================= */
    Tree T1 = newNode(1);
    T1->left = newNode(2);
    T1->right = newNode(3);
    T1->left->left = newNode(4);

    printf("\n%d", depth(T1));
    printf("=== TEST 1 ===\n");
    printf("Inorder: ");
    printInorder(T1);
    printf("\nAltezza (archi): %d\n", heightEdges(T1));

    printf("SOMME PER LIVELLO dal nodo radice (val=1):\n");
    printLevelSums(T1);

    printf("contaDominanti(T1) = %d\n\n", contaDominanti(T1));


    /* =========================================================
       TEST 2: albero più pieno
                10
              /    \
             5      7
            / \    / \
           1   2  3   4
       ========================================================= */
    Tree T2 = newNode(10);
    T2->left = newNode(5);
    T2->right = newNode(7);
    T2->left->left = newNode(1);
    T2->left->right = newNode(2);
    T2->right->left = newNode(3);
    T2->right->right = newNode(4);

    printf("=== TEST 2 ===\n");
    printf("Inorder: ");
    printInorder(T2);
    printf("\nAltezza (archi): %d\n", heightEdges(T2));

    printf("SOMME PER LIVELLO dal nodo radice (val=10):\n");
    printLevelSums(T2);

    /* debug mirato su un nodo interno */
    Tree sub = findFirst(T2, 5);
    if (sub) {
        printf("SOMME PER LIVELLO dal nodo (val=5):\n");
        printLevelSums(sub);
    }

    printf("contaDominanti(T2) = %d\n\n", contaDominanti(T2));


    /* =========================================================
       TEST 3: con valori negativi (per testare somme e “tutte diverse”)
                 0
               /   \
             -2     5
             /       \
            4        -1
                      /
                     3
       ========================================================= */
    Tree T3 = newNode(0);
    T3->left = newNode(-2);
    T3->right = newNode(5);
    T3->left->left = newNode(4);
    T3->right->right = newNode(-1);
    T3->right->right->left = newNode(3);

    printf("=== TEST 3 ===\n");
    printf("Inorder: ");
    printInorder(T3);
    printf("\nAltezza (archi): %d\n", heightEdges(T3));

    printf("SOMME PER LIVELLO dal nodo radice (val=0):\n");
    printLevelSums(T3);

    printf("contaDominanti(T3) = %d\n\n", contaDominanti(T3));


    /* cleanup */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);

    return 0;
}
//Albero binario di interi. Per ogni nodo x, considera il suo sottoalbero e definisci: A(d) = somma dei valori dei nodi a distanza d da x (livello relativo).
//Un nodo x è dominante se: esistono almeno 3 livelli nel suo sottoalbero (altezza ≥ 2) e vale: A(0) < A(1) < A(2) (prime tre somme di livello strettamente crescenti) inoltre, nessun livello successivo può avere somma uguale ad un livello precedente (tutte le somme dei livelli devono essere diverse)
int depth(Tree t)
    {
        if(t==NULL)
            return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return 1+max(sx, dx);
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int èdominante(Tree t, int p_nodo, int vett_storico[])
    {
    int d_fondo=depth(t);
    if(d_fondo<3)
        return 0;
    int *vett=malloc(sizeof(int)*3);
    for(int i=0; i<3;i++)
        {
            vett[i]=0;
        }
    riempi(t, vett, 0);
    vett_storico[p_nodo]=vett[0];
    vett_storico[p_nodo+1]=vett[1];
    vett_storico[p_nodo+2]=vett[2];
    if(vett[0]<vett[1] && vett[1]<vett[2])
    {
        free(vett);
        return 1;
    }
    free(vett);
    return 0;
    }
void riempi(Tree t, int vett[], int liv)
{
    if(t==NULL)
        return;
    if(liv>2)
        return;
    vett[liv]=vett[liv]+t->val;
    riempi(t->left, vett, liv+1);
    riempi(t->right, vett, liv+1);
}
int wrap(Tree t, int storico[])
    {
    int countdom=0;
    f(t, storico, &countdom, 0);
    return countdom;
    }
void f(Tree t, int storico[], int *count_dominanti, int prof)
    {
        if(t==NULL)
            return;
        if(èdominante(t, prof, storico))
            {
                (*count_dominanti)++;
            }
    f(t->left, storico, count_dominanti, prof+1);
    f(t->right, storico, count_dominanti, prof+1);
    }
int contaDominanti(Tree T)
    {
    int p=depth(T);
    int *storico=malloc(sizeof(int)*p);
    for(int i=0; i<p; i++)
        {
            storico[i]=0;
        }
    int ris=wrap(T, storico);
//    for(int i=0;i<p; i++)
//        {
//            for(int j=i+1; j<p; j++)
//                {
//                    if(storico[i]==storico[j])
//                        return 0;
//                }
//        }
    return ris;
    }
