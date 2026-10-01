//  Created by Francesco Roscio Ricon on 30/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* Albero;

typedef Albero *Puntatore;
/* =======================
   UTILITY
   ======================= */

static Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

static void freeTree(Albero t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void printTree2D(Albero t, int space) {
    if (!t) return;
    space += 6;
    printTree2D(t->right, space);
    for (int i = 6; i < space; i++) printf(" ");
    printf("%d\n", t->val);
    printTree2D(t->left, space);
}

static void printTree(Albero t) {
    printf("\n--- Albero (ruotato: destra in alto) ---\n");
    printTree2D(t, 0);
    printf("---------------------------------------\n");
}

/* =======================
   PROPRIETÀ: ZIGZAG
   ======================= */

/*
  Convenzione per la direzione dell’ultimo passo:
  lastDir = 0 : nessun passo ancora (alla radice)
  lastDir = -1: ultimo passo è stato verso sinistra
  lastDir = +1: ultimo passo è stato verso destra

  Un passo è valido se:
  - lastDir == 0 => puoi andare sia a sinistra che a destra
  - lastDir == -1 => devi andare a destra
  - lastDir == +1 => devi andare a sinistra
*/

static bool isLeaf(Albero t) {
    return t && !t->left && !t->right;
}

/* Stampa (ricorsiva) quali foglie hanno un cammino zigzag dalla radice */
static void stampaFoglieZigZagAux(Albero t, int lastDir, bool okSoFar) {
    if (!t) return;

    if (isLeaf(t)) {
        printf("Foglia %d -> cammino zigzag? %s\n", t->val, (okSoFar ? "SI" : "NO"));
        return;
    }

    /* prova andare a sinistra */
    if (t->left) {
        bool okNext =
            okSoFar &&
            (lastDir == 0 || lastDir == +1); /* se ultimo era destra (+1) ora devo andare sinistra (-1) */
        /* Attenzione: qui sto facendo il controllo “al passo”:
           - se lastDir==+1 (destra), andare a sinistra è ok
           - se lastDir==0, andare a sinistra è ok
           - se lastDir==-1 (sinistra), andare a sinistra NON è ok
        */
        if (lastDir == -1) okNext = false;

        stampaFoglieZigZagAux(t->left, -1, okNext);
    }

    /* prova andare a destra */
    if (t->right) {
        bool okNext =
            okSoFar &&
            (lastDir == 0 || lastDir == -1);
        if (lastDir == +1) okNext = false;

        stampaFoglieZigZagAux(t->right, +1, okNext);
    }
}

static void stampaFoglieZigZag(Albero t) {
    printf("\nFoglie e validità zigzag (solo per aiutarti a testare):\n");
    if (!t) {
        printf("(albero vuoto)\n");
        return;
    }
    stampaFoglieZigZagAux(t, 0, true);
}




Albero alberoRidottoZigZag(Albero t);

/* =======================
   ESEMPI MIRATI
   ======================= */

/*
  ESEMPIO A: Zigzag “puro” su entrambi i lati

            1
          /   \
         2     3
          \   /
           4 5
          /   \
         6     7

  Cammini radice-foglia:
  1-2-4-6 : L, R, L  -> zigzag SI
  1-3-5-7 : R, L, R  -> zigzag SI
*/
static Albero esempioA(void) {
    return newNode(1,
        newNode(2,
            NULL,
            newNode(4,
                newNode(6, NULL, NULL),
                NULL)),
        newNode(3,
            newNode(5,
                NULL,
                newNode(7, NULL, NULL)),
            NULL));
}

/*
  ESEMPIO B: Violazione (due sinistre consecutive)

            10
           /
          8
         /
        6
         \
          5

  Cammino unico: L, L, R -> NON zigzag (c’è L,L)
  Quindi l’albero ridotto dovrebbe risultare VUOTO (NULL) se richiedi
  cammini zigzag fino a foglia.
*/
static Albero esempioB(void) {
    return newNode(10,
        newNode(8,
            newNode(6,
                NULL,
                newNode(5, NULL, NULL)),
            NULL),
        NULL);
}

/*
  ESEMPIO C: Misto (alcuni cammini validi, altri no)

              5
            /   \
           2     9
          / \     \
         1   4     12
              \
               7

  Cammini:
  5-2-1       : L, L        -> NO (L,L)
  5-2-4-7     : L, R, R     -> NO (R,R)
  5-9-12      : R, R        -> NO (R,R)

  Qui nessun cammino è zigzag => ridotto NULL.
  (È un buon test “tutto eliminato”.)
*/
static Albero esempioC(void) {
    return newNode(5,
        newNode(2,
            newNode(1, NULL, NULL),
            newNode(4,
                NULL,
                newNode(7, NULL, NULL))),
        newNode(9,
            NULL,
            newNode(12, NULL, NULL)));
}

/*
  ESEMPIO D: Un cammino valido e uno invalido

              1
            /   \
           2     3
            \     \
             4     5
            /
           6

  Cammini:
  1-2-4-6 : L, R, L -> SI
  1-3-5   : R, R    -> NO

  Ridotto atteso: mantiene il ramo sinistro (1-2-4-6) e pota quello destro.
*/
static Albero esempioD(void) {
    return newNode(1,
        newNode(2,
            NULL,
            newNode(4,
                newNode(6, NULL, NULL),
                NULL)),
        newNode(3,
            NULL,
            newNode(5, NULL, NULL)));
}

/*
  ESEMPIO E: Nodo singolo (radice = foglia)
  Cammino vuoto -> zigzag “trivialmente” SI
  Ridotto atteso: uguale all’originale (solo nodo).
*/
static Albero esempioE(void) {
    return newNode(42, NULL, NULL);
}

/* =======================
   MAIN TEST
   ======================= */

static void runTest(const char* nome, Albero t) {
    printf("\n==================== %s ====================\n", nome);
    printf("ORIGINALE:\n");
    printTree(t);

    stampaFoglieZigZag(t);

    Albero rid = alberoRidottoZigZag(t);
    printf("\nRIDOTTO (ora NULL finché non lo implementi):\n");
    printTree(rid);

    freeTree(rid);
}
int max(int a, int b);
int profonditàmax(Albero t);

int main(void) {
    Albero a = esempioA();
    Albero b = esempioB();
    Albero c = esempioC();
    Albero d = esempioD();
    Albero e = esempioE();

    runTest("ESEMPIO A (due cammini zigzag)", a);
    runTest("ESEMPIO B (violazione L,L)", b);
    runTest("ESEMPIO C (nessun cammino zigzag)", c);
    runTest("ESEMPIO D (uno zigzag, uno no)", d);
    runTest("ESEMPIO E (nodo singolo)", e);

    freeTree(a);
    freeTree(b);
    freeTree(c);
    freeTree(d);
    freeTree(e);

    return 0;
}
int profonditàmax(Albero t)
    {
    if(t==NULL)
        return 0;
    int sx=profonditàmax(t->left);
    int dx=profonditàmax(t->right);
    return  max(sx, dx)+1;
}

int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
Puntatore inizializza(int n)
    {
    Puntatore v;
    v=malloc(sizeof(*v)*n);
    for(int i=0; i<n; i++)
        {
            v[i]=NULL;
        }
    return v;
}
void libera(Puntatore v[])
    {
        int i=0;
        while(v[i]!=NULL)
            {
                free(v[i]);
                i++;
            }
    return;
    }
void f(Albero t, int dir_expected, int flag, Puntatore v[], int segna) // dir_expected=-1 se mi aspetto che vada a sinistra, dir_expected=1 se mi aspetto dx
    {
        if(t==NULL)
            return;
        int next_dir_expecte=-dir_expected;
        v[segna]=t;
        if(dir_expected==1)
            {
                f(t->left, next_dir_expecte, flag+1, v, segna+1);
                f(t->right, next_dir_expecte, flag, v, segna+1);
            }
        if(dir_expected==-1)
            {
                f(t->left, next_dir_expecte, flag, v, segna+1);
                f(t->right, next_dir_expecte, flag+1, v, segna+1);
            }
        if(t->left==NULL && t->right==NULL && flag!=0)
        {
            free(v);
        }
        return;
    }

Albero alberoRidottoZigZag(Albero t)
    {
        int profondità=profonditàmax(t);
        Puntatore v=inizializza(profondità);
    f(t, 1, 0, v, 0);
    f(t, -1, 0, v, 0);
    free(v);
    return t;
    }
// rivedere dopo
