//
//  main.c
//  es chat 3
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE
   ========================================================= */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node* tree;

int esisteCamminoSottoSoglia(tree T, int K);   

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
              5    12
             / \     \
            2   7     4

        Esempi:
        K = 8  -> cammino 10-5-2 ❌ (10 >= 8)
        K = 11 -> cammino 10-5-2 ✅
        K = 6  -> nessun cammino valido ❌
    */

    tree T = newNode(10,
                newNode(5,
                    newNode(2, NULL, NULL),
                    newNode(7, NULL, NULL)),
                newNode(12,
                    NULL,
                    newNode(4, NULL, NULL)));

    printf("Albero (preorder): ");
    stampaPreorder(T);
    printf("\n\n");

    printf("K = 8  -> %d (atteso 0)\n",
           esisteCamminoSottoSoglia(T, 8));

    printf("K = 11 -> %d (atteso 1)\n",
           esisteCamminoSottoSoglia(T, 11));

    printf("K = 6  -> %d (atteso 0)\n",
           esisteCamminoSottoSoglia(T, 6));

    liberaAlbero(T);
    return 0;
}

int esisteCamminoSottoSoglia(tree T, int K)
    {
        if(T==NULL)
            return 0;
        if(T->left==NULL && T->right==NULL)
        {
            if(T->v<K)
                return 1;
            return 0;
        }
        if(esisteCamminoSottoSoglia(T->left, K))
            {
                if(T->v<K)
                    return 1;
                return 0;
            }
        if(esisteCamminoSottoSoglia(T->right, K))
            {
                if(T->v<K)
                    return 1;
                return 0;
            }
    return 0;
    }

