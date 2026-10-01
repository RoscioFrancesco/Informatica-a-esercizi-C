//
//  main.c
//  zig zag
//
//  Created by Francesco Roscio Ricon on 28/01/26.
//

#include <stdio.h>
#include <stdlib.h>

/* ===== STRUTTURE ===== */

typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;

typedef Nodo* Tree;

/* ===== UTILS ===== */

Tree nn(char c, Tree l, Tree r) {
    Tree t = malloc(sizeof(Nodo));
    t->c = c;
    t->left = l;
    t->right = r;
    return t;
}

Tree crea() {
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


int maxZigZag(Tree t);
int max(int a, int b);
int zig_from(Tree albero, int dir);

int main(void) {

    Tree t = crea();

    printf("Albero: ");
    stampa(t);
    printf("\n");

    int ris = maxZigZag(t);
    printf("Lunghezza massima zig-zag = %d\n", ris);
}
int zig_from(Tree albero, int dir) // 0->vado a sinistra, 1->vdo a dx
    {
        if(albero==NULL)
            return 0;
        if(dir==0)
            {
                if(albero->left==NULL)
                    return 1;
                else
                    {
                        return 1+zig_from(albero->left, 1);
                    }
            }
        else
            {
                if(albero->right==NULL)
                    return 1;
                else
                    {
                        return 1+zig_from(albero->right, 0);
                    }
            }
    }

int maxZigZag(Tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=zig_from(albero, 0);
    int dx=zig_from(albero, 1);
    int max_sd=max(sx,dx);
    
    int sx_best=maxZigZag(albero->left);
    int dx_best=maxZigZag(albero->right);
    
    return max(max_sd, max(sx_best, dx_best));
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
