//
//  main.c
//  es 5 backtracking chat -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
#include <stdio.h>
#include <stdlib.h>
typedef struct node_s {
    char v;
    struct node_s *left, *right;
} node_t;

typedef node_t* tree;

int contaPercorsiSaldo(tree T);

tree creaNodo(char c) {
    tree n = (tree)malloc(sizeof(node_t));
    n->v = c;
    n->left = NULL;
    n->right = NULL;
    return n;
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

    /* ===== TEST 1 =====
       Albero:
             a
            / \
           b   e
          / \   \
         a   c   a

       Percorsi:
       a b a -> saldo: +1, 0, +1   (mai <0) e finale >0 -> VALIDO
       a b c -> saldo: +1, 0, -1   (scende sotto 0)      -> NON valido
       a e a -> saldo: +1, +2, +3  (mai <0) finale >0    -> VALIDO
       Atteso: 2
    */
    tree T1 = creaNodo('a');
    T1->left = creaNodo('b');
    T1->right = creaNodo('e');
    T1->left->left = creaNodo('a');
    T1->left->right = creaNodo('c');
    T1->right->right = creaNodo('a');

    printf("=== TEST 1 ===\n");
    stampaPercorsi(T1);
    printf("Percorsi validi (saldo>0 e mai sotto 0): %d\n\n", contaPercorsiSaldo(T1));


    
    tree T2 = creaNodo('b');
    T2->left = creaNodo('a');
    T2->right = creaNodo('c');
    T2->right->left = creaNodo('a');

    printf("=== TEST 2 ===\n");
    stampaPercorsi(T2);
    printf("Percorsi validi (saldo>0 e mai sotto 0): %d\n\n", contaPercorsiSaldo(T2));


    /* ===== TEST 3 (sottozero nel mezzo) =====
       Albero:
             a
            /
           b
          /
         b
        /
       a

       Percorso:
       a b b a -> saldo: +1, 0, -1, 0  (sottozero a metà) -> NON valido
       Atteso: 0
    */
    tree T3 = creaNodo('a');
    T3->left = creaNodo('b');
    T3->left->left = creaNodo('b');
    T3->left->left->left = creaNodo('a');

    printf("=== TEST 3 ===\n");
    stampaPercorsi(T3);
    printf("Percorsi validi (saldo>0 e mai sotto 0): %d\n\n", contaPercorsiSaldo(T3));


    /* ===== TEST 4 (singolo nodo vocale) =====
       Albero:
         a

       Percorso: "a" -> saldo +1 (mai<0, finale>0) -> valido
       Atteso: 1
    */
    tree T4 = creaNodo('a');

    printf("=== TEST 4 ===\n");
    stampaPercorsi(T4);
    printf("Percorsi validi (saldo>0 e mai sotto 0): %d\n\n", contaPercorsiSaldo(T4));


    /* ===== TEST 5 (foglia consonante ma saldo resta positivo) =====
       Albero:
           a
            \
             e
              \
               b

       Percorso: a e b -> saldo: +1, +2, +1 (mai<0, finale>0) -> valido
       Atteso: 1
    */
    tree T5 = creaNodo('a');
    T5->right = creaNodo('e');
    T5->right->right = creaNodo('b');

    printf("=== TEST 5 ===\n");
    stampaPercorsi(T5);
    printf("Percorsi validi (saldo>0 e mai sotto 0): %d\n", contaPercorsiSaldo(T5));

    return 0;
}
int èvocale(char l)
    {
        if(l=='a'||l=='e'|| l=='i'|| l=='o'|| l=='u')
            return 1;
    return 0;
    }
void f(tree albero, int punteggio, int *count_foglie)
    {
        if(albero==NULL)
            return;
        if(èvocale(albero->v))
            punteggio++;
        else
            punteggio--;
        if(punteggio>=0)
            {
                f(albero->left, punteggio, count_foglie);
                f(albero->right, punteggio, count_foglie);
            }
        if(albero->left==NULL && albero->right==NULL && punteggio>0)
            (*count_foglie)++;
    }
int contaPercorsiSaldo(tree T)
    {
    int num=0;
    f(T, 0, &num);
    return num;
    }
