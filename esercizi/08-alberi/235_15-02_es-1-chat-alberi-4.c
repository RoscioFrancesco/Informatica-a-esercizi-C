//  Created by Francesco Roscio Ricon on 15/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static int isLeaf(tree t) {
    return (t != NULL && t->left == NULL && t->right == NULL);
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

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* ============================
   ESERCIZIO (DA SVOLGERE)
   ============================ */


/* STUB: compila e gira, ma NON risolve l'esercizio */
int foglieSpecchiateValide(tree T);

/* ============================
   COSTRUZIONE ALBERI DI TEST
   ============================ */

/* Test 1: albero completo con foglie specchiate valide (ATTESO: 1)
        1
      /   \
     2     3
    / \   / \
   4  5  6  7
Coppie specchiate (livello 3):
- 4 (LL) con 7 (RR): 4+7=11, 11%3!=0  -> per renderlo valido, metto 5 invece di 4
- 5 (LR) con 6 (RL): 5+6=11, 11%3!=0 -> metto 1 e 2 ecc.

Quindi scegliamo foglie che rispettano divisibilità per 3:
es: coppie: (3,6) somma=9 OK, (4,2) somma=6 OK
*/
static tree buildTest1_valido(void) {
    tree r = newNode(10);
    r->left = newNode(20);
    r->right = newNode(30);

    r->left->left = newNode(3);   /* specchiata con r->right->right */
    r->left->right = newNode(4);  /* specchiata con r->right->left  */

    r->right->left = newNode(2);
    r->right->right = newNode(6);

    /* livello foglie = 3:
       3 + 6 = 9  -> 9 % 3 == 0
       4 + 2 = 6  -> 6 % 3 == 0
    */
    return r;
}

/* Test 2: manca una foglia specchiata (ATTESO: 0)
        1
      /   \
     2     3
    /
   4
Foglia 4 (LL) non ha specchiata (RR) -> fallisce.
*/
static tree buildTest2_mancaSpecchio(void) {
    tree r = newNode(1);
    r->left = newNode(2);
    r->right = newNode(3);
    r->left->left = newNode(4);
    return r;
}

/* Test 3: foglie specchiate esistono ma somma non divisibile per livello (ATTESO: 0)
        1
      /   \
     2     3
    /       \
   4         7
Foglie specchiate a livello 3: 4 e 7 -> 11 % 3 != 0
*/
static tree buildTest3_divisibilitaKO(void) {
    tree r = newNode(1);
    r->left = newNode(2);
    r->right = newNode(3);
    r->left->left = newNode(4);
    r->right->right = newNode(7);
    return r;
}

/* ============================
   MAIN
   ============================ */
int verifica(tree t, char parola[], int val_specchiata, int livello, int segna);
int f(tree t, char parola[], int livello, int segna, tree root);
int main(void) {
    /* TEST 1 */
    tree T1 = buildTest1_valido();
    printf("=== TEST 1 (atteso: 1) ===\n");
    printf("Albero (preorder): ");
    stampaPreorder(T1);
    printf("\n");
    int r1 = foglieSpecchiateValide(T1);
    printf("Risultato (ottenuto): %d\n", r1);
    printf("Risultato ATTESO (corretto): 1\n\n");
    freeTree(T1);

    /* TEST 2 */
    tree T2 = buildTest2_mancaSpecchio();
    printf("=== TEST 2 (atteso: 0) ===\n");
    printf("Albero (preorder): ");
    stampaPreorder(T2);
    printf("\n");
    int r2 = foglieSpecchiateValide(T2);
    printf("Risultato (ottenuto): %d\n", r2);
    printf("Risultato ATTESO (corretto): 0\n\n");
    freeTree(T2);

    /* TEST 3 */
    tree T3 = buildTest3_divisibilitaKO();
    printf("=== TEST 3 (atteso: 0) ===\n");
    printf("Albero (preorder): ");
    stampaPreorder(T3);
    printf("\n");
    int r3 = foglieSpecchiateValide(T3);
    printf("Risultato (ottenuto): %d\n", r3);
    printf("Risultato ATTESO (corretto): 0\n\n");
    freeTree(T3);

    return 0;
}
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree t)
    {
        if(t==NULL)
            return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return max(sx, dx)+1;
    }
char *copia_e_inverti(char parola[])
    {
    char *copia=malloc(sizeof(char)*(strlen(parola)+1));
    for(int i=0; i<(strlen(parola)); i++)
        {
            if(parola[i]=='s')
                copia[i]='d';
            else
                copia[i]='s';
        }
    copia[strlen(parola)]='\0';
    return copia;
    }
int verifica(tree t, char parola[], int val_specchiata, int livello, int segna)
    {
        if(t==NULL)
            return 0;

        if(t->left==NULL && t->right==NULL)
            {
                if(parola[segna]=='\0')
                    {
                        int somma=t->dato+val_specchiata;
                        if(somma%livello==0)
                            return 1;
                        return 0;
                    }
                return 0;
            }
        livello++;
        if(parola[segna]=='s')
            return verifica(t->left, parola, val_specchiata, livello, segna+1);
        if(parola[segna]=='d')
            return verifica(t->right, parola, val_specchiata, livello, segna+1);
    return 0;
    }
int f(tree t, char parola[], int livello, int segna, tree root)
    {
        if(t==NULL)
            return 0;
        int sx=0;
        int dx=0;
        if(t->left!=NULL)
            {
                parola[segna]='s';
                sx=f(t->left, parola, livello+1, segna+1, root);
            }
        if(t->right!=NULL)
            {
                parola[segna]='d';
                dx=f(t->right, parola, livello+1, segna+1, root);
            }
        if(t->left==NULL && t->right==NULL)
            {
                parola[segna]='\0';
                char *new=copia_e_inverti(parola);
                int ris=verifica(root, new, t->dato, 1, 0);
                free(new);
                return ris;
            }
    return sx && dx;

    }
int foglieSpecchiateValide(tree T)
    {
    int d=depth(T);
    char *vett=malloc(sizeof(char)*d);
    int ris= f(T, vett, 0, 0, T);
    free(vett);
    return ris;
    }
