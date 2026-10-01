//
//  main.c
//  altri alberi -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ====== Strutture date dal testo ====== */
typedef struct ET {
    int dato;
    struct ET *left, *center, *right;
} treeNode;

typedef treeNode* tree;

/* ====== Utility: crea nodo ====== */
tree newNode(int dato, tree l, tree c, tree r) {
    tree t = (tree)malloc(sizeof(treeNode));
    if (!t) { perror("malloc"); exit(1); }
    t->dato = dato;
    t->left = l;
    t->center = c;
    t->right = r;
    return t;
}

/* ====== Utility: libera albero ====== */
void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->center);
    freeTree(t->right);
    free(t);
}

/* ====== Main di test con printf ======
   Costruiamo un albero dove esistono ALMENO DUE cammini distinti con somma = 6.
   Esempio:
          1
       /  |   \
      2   3    5
     / \
    3   4

   Cammini (partenza qualsiasi nodo, verso il basso):
   - 1 -> 2 -> 3 = 6
   - 2 -> 4 = 6
*/
int cerca(tree t, int K);
int main(void) {
    tree t =
        newNode(1,
            newNode(2,
                newNode(3, NULL, NULL, NULL),
                NULL,
                newNode(4, NULL, NULL, NULL)
            ),
            newNode(3, NULL, NULL, NULL),
            newNode(5, NULL, NULL, NULL)
        );

    int totale = 6;
    int ok = cerca(t, totale);

    printf("totale = %d\n", totale);
    printf("cerca(t, %d) = %d\n", totale, ok);
    printf("(Atteso: 1, perche' ci sono almeno 2 cammini distinti con somma %d)\n", totale);

    freeTree(t);
    return 0;
}
//estituisce 1 se esistono almeno due cammini distinti da un qualunque punto dell'albero dall'alto verso il basso in cui la somma dei numeri contenuti nei nodi è uguale a totale. Due cammini sono distinti se differiscono anche solo per un nodo.
void camminofromhere(tree albero ,int somma, int K, int *count)
    {
        if(albero==NULL)
            return;
        somma=somma+albero->dato;
        if(somma==K)
            (*count)++;
    camminofromhere(albero->center, somma, K, count);
    camminofromhere(albero->left, somma, K, count);
    camminofromhere(albero->right, somma, K, count);
    }

void scorrialbero(tree albero, int k, int *tot)
    {
        if(albero==NULL)
            return;
        int count=0;
        camminofromhere(albero, 0, k, &count);
        *tot=(*tot)+count;
    scorrialbero(albero->center, k, tot);
    scorrialbero(albero->left, k, tot);
    scorrialbero(albero->right, k, tot);
    }
int cerca(tree t, int K)
    {
    int tot=0;
    scorrialbero(t, K, &tot);
    if(tot>=2)
        return 1;
    return 0;
    }
