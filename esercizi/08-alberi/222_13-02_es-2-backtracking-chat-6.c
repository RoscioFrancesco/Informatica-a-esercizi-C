//
//  main.c
//  es 2 backtracking chat -6
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

int contaFoglieConRipetizione(tree T);

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
void f(int vett[], tree albero, int *count);
int verificavett(int vett[]);
int main(void) {

    /* ===== TEST 1 =====
       Albero:
             a
            / \
           b   c
          / \   \
         d   a   d

       Percorsi:
       a b d  -> "abd"  (nessuna ripetizione)  -> NON valido
       a b a  -> "aba"  (a ripetuta)           -> valido
       a c d  -> "acd"  (nessuna ripetizione)  -> NON valido
       Atteso: 1
    */
    tree T1 = creaNodo('a');
    T1->left = creaNodo('b');
    T1->right = creaNodo('c');
    T1->left->left = creaNodo('d');
    T1->left->right = creaNodo('a');
    T1->right->right = creaNodo('d');

    printf("=== TEST 1 ===\n");
    stampaPercorsi(T1);
    printf("Foglie con ripetizione: %d\n\n", contaFoglieConRipetizione(T1));


    /* ===== TEST 2 =====
       Albero:
             a
            / \
           b   a
          /     \
         c       b

       Percorsi:
       a b c  -> "abc"  (no ripetizioni) -> NON valido
       a a b  -> "aab"  (a ripetuta)     -> valido
       Atteso: 1
    */
    tree T2 = creaNodo('a');
    T2->left = creaNodo('b');
    T2->right = creaNodo('a');
    T2->left->left = creaNodo('c');
    T2->right->right = creaNodo('b');

    printf("=== TEST 2 ===\n");
    stampaPercorsi(T2);
    printf("Foglie con ripetizione: %d\n\n", contaFoglieConRipetizione(T2));


    /* ===== TEST 3 =====
       Albero:
             z
            /
           y
          /
         x

       Percorso: "zyx" (no ripetizioni) -> Atteso: 0
    */
    tree T3 = creaNodo('z');
    T3->left = creaNodo('y');
    T3->left->left = creaNodo('x');

    printf("=== TEST 3 ===\n");
    stampaPercorsi(T3);
    printf("Foglie con ripetizione: %d\n\n", contaFoglieConRipetizione(T3));


    /* ===== TEST 4 =====
       Albero con un solo nodo:
         q
       Percorso: "q" (no ripetizioni) -> Atteso: 0
    */
    tree T4 = creaNodo('q');

    printf("=== TEST 4 ===\n");
    stampaPercorsi(T4);
    printf("Foglie con ripetizione: %d\n\n", contaFoglieConRipetizione(T4));


    
    tree T5 = creaNodo('a');
    T5->left = creaNodo('b');
    T5->left->left = creaNodo('a');
    T5->left->left->left = creaNodo('c');

    printf("=== TEST 5 ===\n");
    stampaPercorsi(T5);
    printf("Foglie con ripetizione: %d\n", contaFoglieConRipetizione(T5));

    return 0;
}
void f(int vett[], tree albero, int *count)
    {
        if(albero==NULL)
            return;
        int num=albero->v-'a';
        vett[num]++;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(verificavett(vett))
                    (*count)++;
            }
    f(vett, albero->left, count);
    f(vett, albero->right, count);
    
    vett[num]--;
    }
int verificavett(int vett[])
    {
    for(int i=0; i<26; i++)
        {
            if(vett[i]>=2)
                return 1;
        }
    return 0;
    }
int contaFoglieConRipetizione(tree T)
    {
    int *vett=malloc(sizeof(int)*26);
    for(int i=0; i<26; i++)
        {
            vett[i]=0;
        }
    int count=0;
    f(vett, T, &count);
    free(vett);
    return count;
    }
