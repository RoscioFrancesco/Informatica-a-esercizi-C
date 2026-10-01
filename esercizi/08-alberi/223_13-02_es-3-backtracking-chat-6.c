//
//  main.c
//  es 3 backtracking chat -6
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

int contaPercorsiNo2Consonanti(tree T);

tree creaNodo(char c) {
    tree n = (tree)malloc(sizeof(node_t));
    n->v = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

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

/* ============================ MAIN ============================ */

int main(void) {

    /* ===== TEST 1 =====
       Albero:
             a
            / \
           b   e
          / \   \
         a   c   d

       Percorsi:
       a b a -> "aba"  (b consonante ma non consecutiva)        -> valido
       a b c -> "abc"  (b,c consonanti consecutive)             -> NON valido
       a e d -> "aed"  (d consonante, e vocale)                 -> valido
       Atteso: 2
    */
    tree T1 = creaNodo('a');
    T1->left = creaNodo('b');
    T1->right = creaNodo('e');
    T1->left->left = creaNodo('a');
    T1->left->right = creaNodo('c');
    T1->right->right = creaNodo('d');

    printf("=== TEST 1 ===\n");
    stampaPercorsi(T1);
    printf("Percorsi validi (no 2 consonanti consecutive): %d\n\n",
           contaPercorsiNo2Consonanti(T1));


    /* ===== TEST 2 =====
       Albero:
             b
            / \
           a   c
          / \   \
         d   e   a

       Percorsi:
       b a d -> "bad"  (d consonante, ma prima c'è 'a') -> valido
       b a e -> "bae"  (solo una consonante per volta)  -> valido
       b c a -> "bca"  (b,c consonanti consecutive)     -> NON valido
       Atteso: 2
    */
    tree T2 = creaNodo('b');
    T2->left = creaNodo('a');
    T2->right = creaNodo('c');
    T2->left->left = creaNodo('d');
    T2->left->right = creaNodo('e');
    T2->right->right = creaNodo('a');

    printf("=== TEST 2 ===\n");
    stampaPercorsi(T2);
    printf("Percorsi validi (no 2 consonanti consecutive): %d\n\n",
           contaPercorsiNo2Consonanti(T2));


    /* ===== TEST 3 =====
       Albero a catena:
         a
          \
           b
            \
             c

       Percorso: "abc" (b,c consonanti consecutive) -> Atteso: 0
    */
    tree T3 = creaNodo('a');
    T3->right = creaNodo('b');
    T3->right->right = creaNodo('c');

    printf("=== TEST 3 ===\n");
    stampaPercorsi(T3);
    printf("Percorsi validi (no 2 consonanti consecutive): %d\n\n",
           contaPercorsiNo2Consonanti(T3));


    /* ===== TEST 4 =====
       Albero con un solo nodo consonante:
         z
       Percorso: "z" -> valido (non esistono due consonanti consecutive)
       Atteso: 1
    */
    tree T4 = creaNodo('z');

    printf("=== TEST 4 ===\n");
    stampaPercorsi(T4);
    printf("Percorsi validi (no 2 consonanti consecutive): %d\n",
           contaPercorsiNo2Consonanti(T4));

    return 0;
}
//Conta i percorsi radice→foglia in cui non esistono due consonanti consecutive.
int èvocale(char lettera)
    {
        if(lettera=='a' || lettera=='e' || lettera=='i' || lettera=='o' || lettera=='u')
            return 1;
    return 0;
    }
void f(tree albero, int *count)
    {
        if(albero==NULL)
            return;
        if(!èvocale(albero->v))
            {
                if(albero->left!=NULL && èvocale(albero->left->v))
                    f(albero->left, count);
                if(albero->right!=NULL && èvocale(albero->right->v))
                    f(albero->right, count);
            }
        else
            {
                f(albero->left, count);
                f(albero->right, count);
            }
        if(albero->left==NULL && albero->right==NULL)
        {
            (*count)++;
            return;
        }
    }
int contaPercorsiNo2Consonanti(tree T)
    {
    int count=0;
    f(T, &count);
    return count;
    }
