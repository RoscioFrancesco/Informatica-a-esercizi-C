//
//  main.c
//  zig zag 3
//
//  Created by Francesco Roscio Ricon on 28/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;

typedef Nodo *Tree;
Tree nn(char c, Tree l, Tree r) {
    Tree t = (Tree)malloc(sizeof(Nodo));
    if (!t) {
        perror("malloc");
        exit(1);
    }
    t->c = c;
    t->left = l;
    t->right = r;
    return t;
}
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
char* creavettore(int k);
void stampaZigZag(Tree albero, int k);
int main(void) {

    Tree t = crea();

    printf("Albero: ");
    stampa(t);
    printf("\n\n");

    int k;

//    k = 1;
//    printf("Parole zig-zag di lunghezza %d:\n", k);
//    stampaZigZag(t, k);
//    printf("\n");
//
//    k = 2;
//    printf("Parole zig-zag di lunghezza %d:\n", k);
//    stampaZigZag(t, k);
//    printf("\n");

//    k = 3;
//    printf("Parole zig-zag di lunghezza %d:\n", k);
//    stampaZigZag(t, k);
//    printf("\n");

    k = 4;
    printf("Parole zig-zag di lunghezza %d:\n", k);
    stampaZigZag(t, k);
    printf("\n");

    return 0;
}

char* creavettore(int k)
    {
    char *v=malloc(sizeof(char)*(k+1));
    return v;
    }

void zigzag_from(Tree albero, int dir, int *punt, char v[], int k) //se dir=0 vado a sinistra, se dir=1 vado a destra
    {
        if(albero==NULL)
            return;
        v[*punt]=albero->c;
        (*punt)++;
        if(*punt==k)
            {
                v[k]='\0';
                return;
            }
        if(dir==0)
            {
                if(albero->left==NULL)
                    return;
                zigzag_from(albero->left, 1, punt, v, k);
            }
        if(dir==1)
            {
                if(albero->right==NULL)
                    return;
                zigzag_from(albero->right, 0, punt, v, k);
            }
    }
void stampaZigZag(Tree albero, int k)
    {
        if(albero==NULL)
            return;
        char *v=creavettore(k);
    int punt=0;
    zigzag_from(albero, 1, &punt, v, k);
    if(punt==k)
    printf("%s\n", v);
    zigzag_from(albero, 0, &punt, v, k);
    if(punt==k)
    printf("%s\n", v);
    stampaZigZag(albero->left, k);
    stampaZigZag(albero->right, k);
    free(v);
    }
