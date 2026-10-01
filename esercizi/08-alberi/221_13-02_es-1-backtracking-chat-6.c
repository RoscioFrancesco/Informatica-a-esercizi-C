//
//  main.c
//  es 1 backtracking chat -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* ================= STRUTTURE ================= */

typedef struct node_s {
    char v;
    struct node_s *left, *right;
} node_t;

typedef node_t* tree;


int contaFoglieKVocali(tree T, int K);

/* ================= FUNZIONI DI SUPPORTO ================= */

tree creaNodo(char c) {
    tree n = (tree)malloc(sizeof(node_t));
    n->v = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* Debug: stampa tutti i percorsi root->leaf come stringhe */
void stampaPercorsiRec(tree T, char path[], int depth) {
    if (T == NULL) return;

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

/* =========================== MAIN =========================== */

int main(void) {

    /* ===== TEST 1 =====
       Albero:
             a
            / \
           b   e
          / \   \
         c   i   d

       Percorsi:
       a b c  -> "abc"   vocali: a=1
       a b i  -> "abi"   vocali: a,i =2
       a e d  -> "aed"   vocali: a,e =2
    */
    tree T1 = creaNodo('a');
    T1->left = creaNodo('b');
    T1->right = creaNodo('e');
    T1->left->left = creaNodo('c');
    T1->left->right = creaNodo('i');
    T1->right->right = creaNodo('d');

    printf("=== TEST 1 ===\n");
    stampaPercorsi(T1);

    printf("K=1 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T1, 1));
    printf("K=2 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T1, 2));
    printf("K=3 -> contaFoglieKVocali = %d\n\n", contaFoglieKVocali(T1, 3));


    /* ===== TEST 2 =====
       Albero:
             u
            / \
           a   x
          / \   \
         t   o   i

       Percorsi:
       u a t -> "uat" vocali: u,a =2
       u a o -> "uao" vocali: u,a,o =3
       u x i -> "uxi" vocali: u,i =2
    */
    tree T2 = creaNodo('u');
    T2->left = creaNodo('a');
    T2->right = creaNodo('x');
    T2->left->left = creaNodo('t');
    T2->left->right = creaNodo('o');
    T2->right->right = creaNodo('i');

    printf("=== TEST 2 ===\n");
    stampaPercorsi(T2);

    printf("K=2 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T2, 2));
    printf("K=3 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T2, 3));
    printf("K=1 -> contaFoglieKVocali = %d\n\n", contaFoglieKVocali(T2, 1));


    /* ===== TEST 3 =====
       Albero con un solo nodo:
          b
       Percorso: "b" vocali=0 (foglia)
    */
    tree T3 = creaNodo('b');

    printf("=== TEST 3 ===\n");
    stampaPercorsi(T3);

    printf("K=0 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T3, 0));
    printf("K=1 -> contaFoglieKVocali = %d\n\n", contaFoglieKVocali(T3, 1));


    /* ===== TEST 4 =====
       Albero vuoto: nessun percorso
    */
    tree T4 = NULL;

    printf("=== TEST 4 ===\n");
    printf("Albero vuoto\n");
    printf("K=0 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T4, 0));
    printf("K=2 -> contaFoglieKVocali = %d\n", contaFoglieKVocali(T4, 2));

    return 0;
}
int èvocale(char lettera)
    {
        if(lettera=='a' || lettera=='e' || lettera=='i' || lettera=='o' || lettera=='u')
            return 1;
    return 0;
    }
void f(tree albero, int *countvocali, int K, int *countfoglie)
    {
        if(albero==NULL)
            return;
    int flag=0;
    if(èvocale(albero->v))
        {
            (*countvocali)++;
            flag=1;
        }
    if(albero->left==NULL && albero->right==NULL)
        {
            if(*countvocali==K)
                (*countfoglie)++;
            if(flag==1)
                {
                    (*countvocali)--;
                }
            return;
        }
        f(albero->left, countvocali, K, countfoglie);
        f(albero->right, countvocali, K, countfoglie);
    if(flag==1)
        {
            (*countvocali)--;
        }
    }
int contaFoglieKVocali(tree T, int K)
    {
    int countfoglie=0;
    int countvocali=0;
    f(T, &countvocali, K, &countfoglie);
    return countfoglie;
    }
