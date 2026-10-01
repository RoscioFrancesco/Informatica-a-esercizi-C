//
//  main.c
//  alberi es 2 b chat
//
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

/* =======================
   UTILITY ALBERO
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
bool camminoMediaCrescente(Albero t);;





/* =======================
   ESEMPI DI TEST
   ======================= */

/*
  ESEMPIO 1: un cammino sicuramente valido (medie crescono sempre)

        1
         \
          3
           \
            6
             \
              10

  Medie: 1 ; (1+3)/2=2 ; (1+3+6)/3=3.33 ; (1+3+6+10)/4=5  -> cresce sempre
  Quindi atteso: TRUE
*/
static Albero esempio1_valido(void) {
    return newNode(1, NULL,
        newNode(3, NULL,
            newNode(6, NULL,
                newNode(10, NULL, NULL))));
}

/*
  ESEMPIO 2: nessun cammino valido (medie non strettamente crescenti)

        5
       / \
      4   3

  Cammini:
  - 5->4: media 5 poi (5+4)/2=4.5 (scende) => NO
  - 5->3: media 5 poi (5+3)/2=4 (scende)   => NO
  Atteso: FALSE
*/
static Albero esempio2_non_valido(void) {
    return newNode(5,
        newNode(4, NULL, NULL),
        newNode(3, NULL, NULL));
}

/*
  ESEMPIO 3: misto, solo un ramo è valido

            2
          /   \
         1     5
              /
             9

  Cammini:
  - 2->1: 2 poi 1.5 (scende) => NO
  - 2->5->9: 2 ; (2+5)/2=3.5 ; (2+5+9)/3=5.33 => SI
  Atteso: TRUE
*/
static Albero esempio3_misto(void) {
    return newNode(2,
        newNode(1, NULL, NULL),
        newNode(5,
            newNode(9, NULL, NULL),
            NULL));
}

/*
  ESEMPIO 4: zeri e negativi (utile per testare calcoli media)

            0
           / \
         -1   2
              \
               2

  Cammini:
  - 0->-1: 0 poi -0.5 (scende) => NO
  - 0->2->2: 0 ; 1 ; (0+2+2)/3=1.33 (sale) => SI (0 < 1 < 1.33)
  Atteso: TRUE
*/
static Albero esempio4_zeri_negativi(void) {
    return newNode(0,
        newNode(-1, NULL, NULL),
        newNode(2, NULL,
            newNode(2, NULL, NULL)));
}


static Albero esempio5_singolo(void) {
    return newNode(7, NULL, NULL);
}

/*
  ESEMPIO 6: caso “trabocchetto” con medie uguali (serve strettamente crescente)

        2
         \
          2

  Medie: 2 ; (2+2)/2 = 2  -> NON è strettamente maggiore
  Atteso: FALSE
*/
static Albero esempio6_media_uguale(void) {
    return newNode(2, NULL,
        newNode(2, NULL, NULL));
}

/* =======================
   MAIN DI TEST
   ======================= */

static void test(const char* nome, Albero t) {
    printf("\n==================== %s ====================\n", nome);
    printTree(t);

    bool ans = camminoMediaCrescente(t);
    printf("camminoMediaCrescente -> %s\n", ans ? "TRUE" : "FALSE");
}
int f(Albero t, float somma, int count, float mediaprec, int *hasprec);
bool camminoMediaCrescente(Albero t);
int main(void) {
    Albero t1 = esempio1_valido();
    Albero t2 = esempio2_non_valido();
    Albero t3 = esempio3_misto();
    Albero t4 = esempio4_zeri_negativi();
    Albero t5 = esempio5_singolo();
    Albero t6 = esempio6_media_uguale();

    test("ESEMPIO 1 (cammino valido facile)", t1);
    test("ESEMPIO 2 (nessun cammino valido)", t2);
    test("ESEMPIO 3 (solo un ramo valido)", t3);
    test("ESEMPIO 4 (zeri e negativi)", t4);
    test("ESEMPIO 5 (nodo singolo)", t5);
    test("ESEMPIO 6 (media uguale -> fallisce)", t6);

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    freeTree(t4);
    freeTree(t5);
    freeTree(t6);

    return 0;
}


int f(Albero t, float somma, int count, float mediaprec, int *hasprec)
    {
        if(t==NULL)
            return 0;
    somma=somma+t->val;
    count++;
    float media=somma/count;
    if(*hasprec==1)
        {
            if(media<mediaprec)
                return 0;
            mediaprec=media;
        }
    if(t->left==NULL && t->right==NULL)
        return 1;
    *hasprec=1;
    return f(t->left, somma, count, mediaprec, hasprec)|| f(t->right, somma, count, mediaprec,hasprec);
    }
bool camminoMediaCrescente(Albero t)
    {
    int flag=0;
    return f(t, 0, 0, 0, &flag);
    }
