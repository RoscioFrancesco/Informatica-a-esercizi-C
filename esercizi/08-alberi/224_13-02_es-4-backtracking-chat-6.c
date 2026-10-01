//
//  main.c
//  es 4 backtracking chat -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    char v;
    struct node_s *left, *right;
} node_t;
typedef node_t* tree;

typedef struct ln_s {
    char v;
    struct ln_s *next;
} ln_t;
typedef ln_t* Lista;


int esisteCamminoCheIniziaCon(tree T, Lista pattern);

/* =================== SUPPORTO: albero =================== */

tree creaNodo(char c) {
    tree n = (tree)malloc(sizeof(node_t));
    n->v = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =================== SUPPORTO: lista =================== */

Lista pushBack(Lista L, char c) {
    ln_t *n = (ln_t*)malloc(sizeof(ln_t));
    n->v = c;
    n->next = NULL;
    if (L == NULL) return n;
    ln_t *cur = L;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return L;
}

void stampaLista(const char *msg, Lista L) {
    printf("%s", msg);
    while (L) {
        printf("%c", L->v);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

/* Debug: stampa tutti i percorsi root->leaf */
void stampaPercorsiRec(tree T, char path[], int depth) {
    if (!T) return;
    path[depth] = T->v;

    if (T->left == NULL && T->right == NULL) {
        for (int i = 0; i <= depth; i++) printf("%c", path[i]);
        printf("\n");
        return;
    }

    stampaPercorsiRec(T->left, path, depth + 1);
    stampaPercorsiRec(T->right, path, depth + 1);
}

void stampaPercorsi(tree T) {
    char path[256];
    printf("Percorsi radice->foglia:\n");
    stampaPercorsiRec(T, path, 0);
}

/* ============================ MAIN ============================ */

int main(void) {

    /* ===== ALBERO DI TEST =====
            a
           / \
          b   c
         / \   \
        d   e   a
           /
          f

       Percorsi:
       abd
       abef
       aca
    */
    tree T = creaNodo('a');
    T->left = creaNodo('b');
    T->right = creaNodo('c');
    T->left->left = creaNodo('d');
    T->left->right = creaNodo('e');
    T->left->right->left = creaNodo('f');
    T->right->right = creaNodo('a');

    printf("=== ALBERO ===\n");
    stampaPercorsi(T);
    printf("\n");

    /* ===== PATTERN 1: a -> b (prefisso di abd e abef) ===== */
    Lista P1 = NULL;
    P1 = pushBack(P1, 'a');
    P1 = pushBack(P1, 'b');

    printf("=== TEST 1 ===\n");
    stampaLista("Pattern: ", P1);
    printf("Esiste cammino che inizia con pattern? %d\n\n",
           esisteCamminoCheIniziaCon(T, P1));

    /* ===== PATTERN 2: a -> b -> e (prefisso di abef) ===== */
    Lista P2 = NULL;
    P2 = pushBack(P2, 'a');
    P2 = pushBack(P2, 'b');
    P2 = pushBack(P2, 'e');

    printf("=== TEST 2 ===\n");
    stampaLista("Pattern: ", P2);
    printf("Esiste cammino che inizia con pattern? %d\n\n",
           esisteCamminoCheIniziaCon(T, P2));

    /* ===== PATTERN 3: a -> c -> a (è ESATTAMENTE un cammino) ===== */
    Lista P3 = NULL;
    P3 = pushBack(P3, 'a');
    P3 = pushBack(P3, 'c');
    P3 = pushBack(P3, 'a');

    printf("=== TEST 3 ===\n");
    stampaLista("Pattern: ", P3);
    printf("Esiste cammino che inizia con pattern? %d\n\n",
           esisteCamminoCheIniziaCon(T, P3));

    /* ===== PATTERN 4: a -> b -> e -> f -> x (troppo lungo / mismatch) ===== */
    Lista P4 = NULL;
    P4 = pushBack(P4, 'a');
    P4 = pushBack(P4, 'b');
    P4 = pushBack(P4, 'e');
    P4 = pushBack(P4, 'f');
    P4 = pushBack(P4, 'x');

    printf("=== TEST 4 ===\n");
    stampaLista("Pattern: ", P4);
    printf("Esiste cammino che inizia con pattern? %d\n\n",
           esisteCamminoCheIniziaCon(T, P4));

    /* ===== PATTERN 5: a (prefisso banalissimo: basta che esista una foglia) ===== */
    Lista P5 = NULL;
    P5 = pushBack(P5, 'a');

    printf("=== TEST 5 ===\n");
    stampaLista("Pattern: ", P5);
    printf("Esiste cammino che inizia con pattern? %d\n",
           esisteCamminoCheIniziaCon(T, P5));

    return 0;
}
int f(tree albero, Lista head)
    {
        if(albero==NULL)
            return 0;
        if(head==NULL)
            return 0;
        if(albero->v!=head->v)
            return 0;
        if(head->next==NULL && albero->left==NULL && albero->right==NULL)
            return 1;
        if(f(albero->left, head->next))
            {
                return 1;
            }
        if(f(albero->right, head->next))
            {
                return 1;
            }
    return 0;
    }
int esisteCamminoCheIniziaCon(tree T, Lista pattern)
    {
    return f(T, pattern);
    }
