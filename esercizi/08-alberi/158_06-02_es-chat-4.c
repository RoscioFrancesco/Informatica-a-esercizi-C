//
//  main.c
//  es chat 4
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE
   ========================================================= */
typedef struct nodeS {
    char c;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* =========================================================
   PROTOTIPI
   ========================================================= */
char* stringaCammino(tree T, tree target);   

/* =========================================================
   FUNZIONI DI SUPPORTO (per test)
   ========================================================= */
tree newNode(char c, tree left, tree right)
{
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->c = c;
    n->left = left;
    n->right = right;
    return n;
}

void stampaPreorder(tree T)
{
    if (T == NULL) {
        printf("NULL ");
        return;
    }
    printf("%c ", T->c);
    stampaPreorder(T->left);
    stampaPreorder(T->right);
}

void liberaAlbero(tree T)
{
    if (T == NULL) return;
    liberaAlbero(T->left);
    liberaAlbero(T->right);
    free(T);
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int f(tree albero, int *depthtarget, tree target);
int main(void)
{
    /*
                 'A'
                /   \
              'B'     'C'
             /   \       \
           'D'   'E'       'F'

        Cammini:
        A-B-D  -> "ABD"
        A-B-E  -> "ABE"
        A-C-F  -> "ACF"
    */

    tree nD = newNode('D', NULL, NULL);
    tree nE = newNode('E', NULL, NULL);
    tree nF = newNode('F', NULL, NULL);

    tree nB = newNode('B', nD, nE);
    tree nC = newNode('C', NULL, nF);
    tree nA = newNode('A', nB, nC);

    printf("Albero (preorder): ");
    stampaPreorder(nA);
    printf("\n\n");

    char *s1 = stringaCammino(nA, nD);
    printf("Cammino verso D: %s (atteso \"ABD\")\n", s1);

    char *s2 = stringaCammino(nA, nE);
    printf("Cammino verso E: %s (atteso \"ABE\")\n", s2);

    char *s3 = stringaCammino(nA, nF);
    printf("Cammino verso F: %s (atteso \"ACF\")\n", s3);

    free(s1);
    free(s2);
    free(s3);
    liberaAlbero(nA);

    return 0;
}

/* =========================================================
   FUNZIONE DELL'ESERCIZIO (DA SVOLGERE)
   ========================================================= */
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth_max(tree albero)
    {
        if(albero==NULL)
            return 0;
        int sx=depth_max(albero->left);
        int dx=depth_max(albero->right);
        return 1+max(sx, dx);
    }
int f(tree albero, int *depthtarget, tree target)
    {
        if(albero==NULL)
            return 0;
        if(albero==target)
            {
                (*depthtarget)++;
                return 1;
            }
        if(f(albero->left, depthtarget, target))
            {
                (*depthtarget)++;
                return 1;
            }
        if(f(albero->right, depthtarget, target))
            {
                (*depthtarget)++;
                return 1;
            }
        return 0;
    }
int riempistringa(tree albero, char stringa[], tree target, int len, int segnaposto)
    {
        if(albero==NULL)
            return 0;
        if(albero==target)
            {
                stringa[segnaposto]=albero->c;
                stringa[segnaposto+1]='\0';
                return 1;
            }
        if(riempistringa(albero->left, stringa, target, len, segnaposto+1))
            {
                stringa[segnaposto]=albero->c;
                return 1;
            }
        if(riempistringa(albero->right, stringa, target, len, segnaposto+1))
            {
                stringa[segnaposto]=albero->c;
                return 1;
            }
        return 0;
    }
char* stringaCammino(tree T, tree target)
    {
    int depth=0;
    f(T, &depth, target);
    printf("%d", depth);
    char *stringa=malloc(sizeof(char)*(depth+1));
    riempistringa(T, stringa, target, depth+1, 0);
    return stringa;
    }
