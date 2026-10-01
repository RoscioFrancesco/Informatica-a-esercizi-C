//
//  main.c
//  tde carta tde 4 alberi -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct t {
    char lettera;
    struct t *left, *right;
} Nodo;

typedef Nodo *Tree;


void f(Tree t, char *percorso, char *parola);

/* =========================
   UTILITY: creazione / stampa / free
   ========================= */
static Tree newNode(char c, Tree left, Tree right) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->lettera = c;
    n->left = left;
    n->right = right;
    return n;
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* stampa preorder per controllare la struttura */
static void printTree(Tree t) {
    if (!t) { printf("NULL"); return; }
    printf("%c(", t->lettera);
    printTree(t->left);
    printf(", ");
    printTree(t->right);
    printf(")");
}

/* =========================
   MAIN DI TEST
   ========================= */
void funz(Tree albero, int scorri_parola, char parola[], char direzione[], int len_direzione, int *scorri_direzione);
int main(void) {
    /*
        Costruiamo questo albero:

                 A
               /   \
              B     C
             / \   / \
            D   E F   G

        Percorso: ""      -> "A"
                  "s"     -> "AB"
                  "d"     -> "AC"
                  "ss"    -> "ABD"
                  "sd"    -> "ABE"
                  "ds"    -> "ACF"
                  "dd"    -> "ACG"
    */

    Tree t =
        newNode('A',
            newNode('B',
                newNode('D', NULL, NULL),
                newNode('E', NULL, NULL)
            ),
            newNode('C',
                newNode('F', NULL, NULL),
                newNode('G', NULL, NULL)
            )
        );

    printf("Albero (preorder): ");
    printTree(t);
    printf("\n\n");

    /* casi di test */
    const char *tests[] = { "", "s", "d", "ss", "sd", "ds", "dd" };
    int ntests = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int i = 0; i < ntests; i++) {
        const char *percorso = tests[i];

        /* parola deve essere abbastanza grande: al massimo lunghezza(percorso)+1 */
        char parola[128];
        parola[0] = '\0';

        printf("Test %d\n", i + 1);
        printf("  percorso = \"%s\"\n", percorso);

        /* chiami la tua funzione */
        f(t, (char*)percorso, parola);

        printf("  parola   = \"%s\"\n", parola);
        printf("\n");
    }

    /* esempio extra: percorso più lungo (potresti decidere cosa fare) */
    {
        char percorso[] = "ssd"; /* qui da D non c'è destra: dipende dalla tua gestione */
        char parola[128] = {0};
        printf("Extra:\n");
        printf("  percorso = \"%s\"\n", percorso);
        f(t, percorso, parola);
        printf("  parola   = \"%s\"\n", parola);
        printf("\n");
    }

    freeTree(t);
    return 0;
}
void funz(Tree albero, int scorri_parola, char parola[], char direzione[], int len_direzione, int *scorri_direzione)
    {
        if(albero==NULL)
            return;
        parola[scorri_parola]=albero->lettera;
        scorri_parola++;
        if(*scorri_direzione==len_direzione)
        {
            parola[len_direzione+1]='\0';
            return;
        }
        if(direzione[*scorri_direzione]=='s')
            {
                (*scorri_direzione)++;
                funz(albero->left, scorri_parola, parola, direzione, len_direzione, scorri_direzione);
            }
        else
            {
                (*scorri_direzione)++;
                funz(albero->right, scorri_parola, parola, direzione, len_direzione, scorri_direzione);
            }
    }
void f(Tree t, char percorso[], char parola[])
    {
    int scorridirez=0;
    funz(t, 0, parola, percorso, strlen(percorso), &scorridirez);
    }
