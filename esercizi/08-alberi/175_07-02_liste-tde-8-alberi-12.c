//  Created by Francesco Roscio Ricon on 07/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_s {
    char d;
    struct node_s *left, *right;
} node_t;

typedef node_t *tree;

int countPalPaths(tree t);

/* =========================
   UTILITY: CREA NODO
   ========================= */
static tree newNode(char c) {
    tree n = (tree)malloc(sizeof(node_t));
    if (!n) { perror("malloc"); exit(1); }
    n->d = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   UTILITY: FREE ALBERO
   ========================= */
static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   UTILITY: STAMPA ALBERO (preorder)
   ========================= */
static void printPreorder(tree t) {
    if (!t) {
        printf("NULL ");
        return;
    }
    printf("%c ", t->d);
    printPreorder(t->left);
    printPreorder(t->right);
}

/* =========================
   COSTRUISCI UN ALBERO DI TEST
   (percorsi radice->foglia con lettere)
   =========================
   Struttura:

           a
         /   \
        b     a
       / \     \
      a   c     b
         /     / \
        c     a   b

   Percorsi:
   1) a-b-a          = "aba"   (palindromo)  ✅
   2) a-b-c-c        = "abcc"  (no)          ❌
   3) a-a-b-a        = "aaba"  (no)          ❌
   4) a-a-b-b        = "aabb"  (no)          ❌
   (quindi qui atteso = 1, se la tua funzione è corretta)
*/
static tree buildTestTree1(void) {
    tree r = newNode('a');

    r->left = newNode('b');
    r->right = newNode('a');

    r->left->left = newNode('a');
    r->left->right = newNode('c');
    r->left->right->left = newNode('c');

    r->right->right = newNode('b');
    r->right->right->left = newNode('a');
    r->right->right->right = newNode('b');

    return r;
}

/* =========================
   SECONDO TEST: tutti palindromi "aaa", "aaaa", ecc.
   =========================
            a
          /   \
         a     a
        /       \
       a         a

   Percorsi:
   a-a-a = "aaa"  ✅
   a-a-a = "aaa"  ✅
   atteso = 2
*/
static tree buildTestTree2(void) {
    tree r = newNode('a');
    r->left = newNode('a');
    r->right = newNode('a');
    r->left->left = newNode('a');
    r->right->right = newNode('a');
    return r;
}

/* =========================
   MAIN DI TEST
   ========================= */
int stringapalindroma(char parola[]);
void f(tree albero, char parola[], int segna, int *count);
int main(void) {
    tree t1 = buildTestTree1();
    tree t2 = buildTestTree2();

    printf("Albero t1 (preorder): ");
    printPreorder(t1);
    printf("\n");

    int ans1 = countPalPaths(t1);  /* TODO */
    printf("countPalPaths(t1) = %d (atteso 1)\n\n", ans1);

    printf("Albero t2 (preorder): ");
    printPreorder(t2);
    printf("\n");

    int ans2 = countPalPaths(t2);  /* TODO */
    printf("countPalPaths(t2) = %d (atteso 2)\n\n", ans2);

    freeTree(t1);
    freeTree(t2);
    return 0;

}



int stringapalindroma(char parola[])
    {
    int len=strlen(parola);
    for(int i=0, j=len-1; i<j; i++, j--)
        {
            if(parola[i]!=parola[j])
                return 0;
        }
    return 1;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
        return b;
    }
int profondità(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=profondità(albero->left);
    int dx=profondità(albero->right);
    return 1+max(sx, dx);
    }
void f(tree albero, char parola[], int segna, int *count)
    {
        if(albero==NULL)
            return;
        parola[segna]=albero->d;
        if(albero->left==NULL && albero->right==NULL)
            {
                parola[segna+1]='\0';
                if(stringapalindroma(parola)==1)
                    (*count)++;
            }
    f(albero->left, parola, segna+1, count);
    f(albero->right, parola, segna+1, count);
    }
int countPalPaths(tree t)
    {
    int len=profondità(t);
    char *parola=malloc(sizeof(char)*(len+1));
    int ris=0;
    f(t, parola, 0, &ris);
    free(parola);
    return ris;
    }
