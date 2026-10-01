//
//  main.c
//  es 2 chat alberi -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ============================
   STRUTTURE DATI
   ============================ */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

/* ============================
   HELPERS: creazione / stampa / free
   ============================ */
static tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    n->dato = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL");
        return;
    }
    printf("%d(", t->dato);
    stampaPreorder(t->left);
    printf(",");
    stampaPreorder(t->right);
    printf(")");
}

/* ============================
   ESERCIZIO 2 (DA SVOLGERE)
   ============================ */


/* STUB: compila e gira, ma NON risolve l'esercizio */

/* TEST 1 (atteso: 1) con K=3
       5
      / \
     6   7
    / \
   8   9

Cammino valido: 5 -> 6 -> 8  (len=3)
- 6 è multiplo di 3: poi ci sono solo 1 passo (verso 8), quindi ok.
*/
static tree buildTest1(void) {
    tree r = newNode(5);
    r->left = newNode(6);
    r->right = newNode(7);
    r->left->left = newNode(8);
    r->left->right = newNode(9);
    return r;
}

/* TEST 2 (atteso: 0) con K=3
       3
      /
     6
    /
   9

Cammino unico: 3 -> 6 -> 9 (len=3)
- 3 multiplo, cooldown 2: nei prossimi 2 passi (6 e 9) NON possono essere multipli
  ma lo sono -> invalido.
*/
static tree buildTest2(void) {
    tree r = newNode(3);
    r->left = newNode(6);
    r->left->left = newNode(9);
    return r;
}

/* TEST 3 (atteso: 0) perché cammini troppo corti (len<3), K=5
      10
     /  \
    1    2

I cammini radice->foglia hanno lunghezza 2, quindi invalidi a prescindere.
*/
static tree buildTest3(void) {
    tree r = newNode(10);
    r->left = newNode(1);
    r->right = newNode(2);
    return r;
}

/* TEST 4 (atteso: 1) con K=0 (multiplo sempre falso per tutti)
       4
      /
     2
    /
   6

Con K==0 trattiamo “multiplo” come sempre falso -> nessun vincolo cooldown.
Cammino 4->2->6 len=3 => valido.
*/
static tree buildTest4(void) {
    tree r = newNode(4);
    r->left = newNode(2);
    r->left->left = newNode(6);
    return r;
}
int esisteCamminoCooldown(tree T, int K);
/* ============================
   MAIN
   ============================ */
int main(void) {
    /* TEST 1 */
    {
        tree T = buildTest1();
        int K = 3;
        printf("=== TEST 1 (atteso: 1) ===\n");
        printf("K = %d\n", K);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");
        int r = esisteCamminoCooldown(T, K);
        printf("Risultato (ottenuto): %d\n", r);
        printf("Risultato ATTESO (corretto): 1\n\n");
        freeTree(T);
    }

    /* TEST 2 */
    {
        tree T = buildTest2();
        int K = 3;
        printf("=== TEST 2 (atteso: 0) ===\n");
        printf("K = %d\n", K);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");
        int r = esisteCamminoCooldown(T, K);
        printf("Risultato (ottenuto): %d\n", r);
        printf("Risultato ATTESO (corretto): 0\n\n");
        freeTree(T);
    }

    /* TEST 3 */
    {
        tree T = buildTest3();
        int K = 5;
        printf("=== TEST 3 (atteso: 0) ===\n");
        printf("K = %d\n", K);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");
        int r = esisteCamminoCooldown(T, K);
        printf("Risultato (ottenuto): %d\n", r);
        printf("Risultato ATTESO (corretto): 0\n\n");
        freeTree(T);
    }

    /* TEST 4 */
    {
        tree T = buildTest4();
        int K = 0;
        printf("=== TEST 4 (atteso: 1) ===\n");
        printf("K = %d\n", K);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");
        int r = esisteCamminoCooldown(T, K);
        printf("Risultato (ottenuto): %d\n", r);
        printf("Risultato ATTESO (corretto): 1\n\n");
        freeTree(T);
    }

    return 0;
}



int f(tree t, int K, int livello, int cooldown)
    {
        if(t==NULL)
            return 0;
        if(cooldown!=0 && t->dato%K==0)
            return 0;
        if(cooldown==0 &&t->dato%K==0 && cooldown==0)
            {
                cooldown=2;
            }
        if(t->left==NULL && t->right==NULL)
            {
                if(livello>=3)
                    return 1;
                return 0;
            }
        int newcool=0;
        if(cooldown!=0)
            newcool=cooldown-1;
    return f(t->left, K, livello+1, newcool) || f(t->right, K, livello+1, newcool);
    }
int esisteCamminoCooldown(tree T, int K)
    {
    if(T==NULL)
        return 0;
    if(K==0)
        return 1;
    return f(T, K, 1, 0);
    }
