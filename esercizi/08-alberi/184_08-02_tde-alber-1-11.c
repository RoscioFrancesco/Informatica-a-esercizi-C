//  Created by Francesco Roscio Ricon on 08/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ET {
    char dato;
    struct ET *left, *right;
} treeNode;

typedef treeNode* tree;

int contains(tree t, char word[]);
int fromhere(tree albero, char parola[], int segna);
/* =========================
   UTILITY: crea nodo
   ========================= */
static tree newNode(char c) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   UTILITY: stampa (preorder) + free
   ========================= */
static void printPreorder(tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%c ", t->dato);
    printPreorder(t->left);
    printPreorder(t->right);
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST (RUNNABILE)
   ========================= */
int main(void) {
    /*
        Costruiamo un albero esempio.

                 'a'
                /   \
              'b'   'c'
             /  \     \
           'd'  'e'   'f'

       Cammini foglia->radice possibili (concatenando dalla foglia alla radice):
       d b a  -> "dba"
       e b a  -> "eba"
       f c a  -> "fca"
    */

    tree t = newNode('a');
    t->left = newNode('b');
    t->right = newNode('c');
    t->left->left = newNode('d');
    t->left->right = newNode('e');
    t->right->right = newNode('f');

    printf("Albero (preorder): ");
    printPreorder(t);
    printf("\n\n");

    /* Test words */
    char w1[] = "dba";
    char w2[] = "eba";
    char w3[] = "fca";
    char w4[] = "abc";   /* non è foglia->radice, quindi in genere dovrebbe risultare 0 */
    char w5[] = "ba";    

    printf("contains(t, \"%s\") = %d\n", w1, contains(t, w1));
    printf("contains(t, \"%s\") = %d\n", w2, contains(t, w2));
    printf("contains(t, \"%s\") = %d\n", w3, contains(t, w3));
    printf("contains(t, \"%s\") = %d\n", w4, contains(t, w4));
    printf("contains(t, \"%s\") = %d\n", w5, contains(t, w5));

    freeTree(t);
    return 0;
}

/* =========================
   STUB (NON RISOLVERE)
   ========================= */
int contains(tree t, char word[]) {
    return fromhere(t, word, strlen(word)-1);
}

int fromhere(tree albero, char parola[], int segna)
    {
        if(albero==NULL)
            return 0;
        if(parola[segna]!=albero->dato)
            return 0;
        segna--;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(segna==-1)
                    return 1;
                return 0;
            }
    return fromhere(albero->left, parola, segna) ||fromhere(albero->right, parola, segna);
    }

