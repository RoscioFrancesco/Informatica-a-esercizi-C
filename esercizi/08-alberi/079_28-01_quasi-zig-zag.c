//
//  main.c
//  quasi zig zag
//
//  Created by Francesco Roscio Ricon on 28/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== STRUTTURE ===== */

typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;

typedef Nodo *Tree;

/* ===== UTILS ===== */

Tree nn(char c, Tree l, Tree r) {
    Tree t = (Tree)malloc(sizeof(Nodo));
    if (!t) { perror("malloc"); exit(1); }
    t->c = c;
    t->left = l;
    t->right = r;
    return t;
}

/*
                 c
               /   \
              i     s
             / \   / \
            a   p k   r
             \         \
              o         w
*/
Tree crea(void) {
    return nn('c',
              nn('i',
                 nn('a', NULL, nn('o', NULL, NULL)),
                 nn('p', NULL, NULL)),
              nn('s',
                 nn('k', NULL, NULL),
                 nn('r', NULL, nn('w', NULL, NULL))));
}

void stampa(Tree t) {
    if (!t) return;
    printf("(");
    stampa(t->left);
    printf(" %c ", t->c);
    stampa(t->right);
    printf(")");
}

/* ===== MAIN DI TEST ===== */
int quasizigzag(Tree t, char parola[]);
int quasizigzagfrom(Tree albero, char parola[], int punt, int dir, int count);
Tree crea_test_killer(void);

int main(void) {
    Tree t = crea();

    printf("Albero: ");
    stampa(t);
    printf("\n\n");

    const char *tests[] = {
        "cia",   // c->i->a (sx,sx)  rompe una volta => dovrebbe essere 1
        "ciao",  // c->i->a->o (sx,sx,dx) rompe una volta => 1
        "srw",   // s->r->w (dx,dx) rompe una volta => 1
        "cip",   // zig-zag perfetto => 1
        "iao",   // zig-zag perfetto => 1
        "csk",   // c->s->k (dx,sx) zig-zag => 1
        "crw",   // c->s->r->w (dx,dx,dx) rompe 2 volte => 0 (atteso)
        "sss",   // impossibile (nodi ripetuti non in cammino) => 0
        "irw",   // i->? non arriva a r con cammino discendente => 0
        NULL};

    for (int i = 0; tests[i] != NULL; i++) {
        printf("%s -> %d\n", tests[i], quasizigzag(t, tests[i]));
    }

    Tree t2 = crea_test_killer();

    printf("abc -> %d (atteso 1)\n", quasizigzag(t2, "abc"));
    printf("ab  -> %d (atteso 1)\n", quasizigzag(t2, "ab"));
    printf("ac  -> %d (atteso 0)\n", quasizigzag(t2, "ac"));

}



int quasizigzagfrom(Tree albero, char parola[], int punt, int dir, int count) // dir=1 vai a dx la prossmia, dir=0 vai a sx la prossima
{
    if(albero==NULL)
        return 0;
    if(parola[punt]==albero->c)
    {
        (punt)++;
    }
    else
    {
        return 0;
    }
    if(parola[punt]=='\0')
    {
        return 1;
    }
    if(dir==1 && count==0)
    {
        return quasizigzagfrom(albero->right, parola, punt, 0, count) || quasizigzagfrom(albero->right, parola, punt, 1, 1);
    }
    if(dir==0 && count==0)
    {
        return quasizigzagfrom(albero->left, parola, punt, 1, count) || quasizigzagfrom(albero->left, parola, punt, 0, 1);
    }
    if(dir==1 && count==1)
    {
        if(albero->right==NULL)
            return 0;
        return quasizigzagfrom(albero->right, parola, punt, 0, count);
    }
    if(dir==0 && count==1)
    {
        if(albero->left==NULL)
            return 0;
        return quasizigzagfrom(albero->left, parola, punt, 1, count);
    }
    return 0;
}

int quasizigzag(Tree t, char parola[])
    {
    if(t==NULL)
        return 0;
    return quasizigzagfrom(t, parola, 0, 0, 0) || quasizigzagfrom(t, parola, 0, 1, 0) || quasizigzag(t->left, parola) || quasizigzag(t->right, parola);
        
    }

Tree crea_test_killer(void) {
    //    a
    //   /
    //  b
    // /
    //c
    return nn('a',
              nn('b',
                 nn('c', NULL, NULL),
                 NULL),
              NULL);
}
