//
//  main.c
//  es chat 5
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node* tree;

int contaPariNelCammino(tree T, tree target);

tree newNode(int v, tree left, tree right)
{
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->v = v;
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
    printf("%d ", T->v);
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
int main(void)
{
    /*
                10
               /  \
              5    8
             / \    \
            2   7    4

        Cammini:
        verso 2 : 10 -> 5 -> 2   (pari: 10,2) = 2
        verso 7 : 10 -> 5 -> 7   (pari: 10)   = 1
        verso 4 : 10 -> 8 -> 4   (pari: 10,8,4) = 3
    */

    tree n2 = newNode(2, NULL, NULL);
    tree n7 = newNode(7, NULL, NULL);
    tree n4 = newNode(4, NULL, NULL);

    tree n5 = newNode(5, n2, n7);
    tree n8 = newNode(8, NULL, n4);
    tree n10 = newNode(10, n5, n8);

    printf("Albero (preorder): ");
    stampaPreorder(n10);
    printf("\n\n");

    printf("contaPariNelCammino(T, n2) = %d (atteso 2)\n",
           contaPariNelCammino(n10, n2));

    printf("contaPariNelCammino(T, n7) = %d (atteso 1)\n",
           contaPariNelCammino(n10, n7));

    printf("contaPariNelCammino(T, n4) = %d (atteso 3)\n",
           contaPariNelCammino(n10, n4));

    liberaAlbero(n10);
    return 0;
}

/* =========================================================
   FUNZIONE DELL'ESERCIZIO (DA SVOLGERE)
   ========================================================= */
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return 0;
    }

int f(tree albero, tree target, int *count)
    {
        if(albero==NULL)
            return 0;
        if(albero==target)
            {
                return 1;
            }
        if(f(albero->left, target, count))
            {
                if(èpari(target->v))
                    (*count)++;
                return 1;
            }
        if(f(albero->right, target, count))
            {
                if(èpari(target->v))
                    (*count)++;
                return 1;
            }
        return 0;
    }
int contaPariNelCammino(tree T, tree target)
    {
    int count=0;
    (void)f(T, target, &count);
    return count;
    }
