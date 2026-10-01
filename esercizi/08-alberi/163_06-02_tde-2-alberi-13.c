//
//  main.c
//  tde 2 alberi -13
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE (come da testo)
   ========================================================= */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node *tree;

/* =========================================================
   PROTOTIPI (funzione dell'esercizio)
   ========================================================= */
int dueFoglieStessoGrado(tree T);   /* TODO */

/* =========================================================
   UTILITY PER TEST
   ========================================================= */
static node* newNode(int v, node* left, node* right)
{
    node* n = (node*)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = v;
    n->left = left;
    n->right = right;
    return n;
}

static void stampaPreorder(tree T)
{
    if (!T) { printf("NULL "); return; }
    printf("%d ", T->v);
    stampaPreorder(T->left);
    stampaPreorder(T->right);
}

static void freeTree(tree T)
{
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int wrapper_calcolagrado(tree root, tree nodo_mio);
int calcolagrado(tree root, tree nodo_mio);
int cercaESomma(tree root, tree target, int *somma);
int main()
{
    
    tree T1 = newNode(5,
                newNode(2,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(3,
                    NULL,
                    newNode(6, NULL, NULL)));

    
    tree T2 = newNode(1,
                newNode(2,
                    newNode(4, NULL, NULL),
                    newNode(5, NULL, NULL)),
                newNode(3,
                    NULL,
                    newNode(6, NULL, NULL)));

    printf("Albero T1 (preorder): ");
    stampaPreorder(T1);
    printf("\n");
    printf("Risultato T1 = %d (atteso 1)\n\n", dueFoglieStessoGrado(T1));

    printf("Albero T2 (preorder): ");
    stampaPreorder(T2);
    printf("\n");
    printf("Risultato T2 = %d (atteso 0)\n\n", dueFoglieStessoGrado(T2));

    freeTree(T1);
    freeTree(T2);

    return 0;
}


int cercaESomma(tree root, tree target, int *somma)
{
    if(root==NULL)
        return 0;
    if(root==target)
        {
            *somma=*somma+target->v;
            return 1;
        }
    if(cercaESomma(root->left, target, somma))
        {
            *somma=*somma+root->v;
            return 1;
        }
    if(cercaESomma(root->right, target, somma))
        {
            *somma=*somma+root->v;
            return 1;
        }
    return 0;
}
int calcolagrado(tree root, tree nodo_mio)
    {
        int somma=0;
        cercaESomma(root, nodo_mio, &somma);
        return somma;
    }
int scorrialbero(tree root, tree albero, int grado_compare, tree nodo_compare)
    {
        if(root==NULL || albero==NULL)
            return 0;
        if(grado_compare==calcolagrado(root, albero) && albero!=nodo_compare)
            return 1;
    return scorrialbero(root, albero->left, grado_compare, nodo_compare) || scorrialbero(root, albero->right, grado_compare, nodo_compare);
    }
int funz(tree T, tree root)
    {
        if(T==NULL || root==NULL)
            return 0;
        int grado=calcolagrado(root, T);
        if (scorrialbero(root, root, grado, T))
        {
            return 1;
        }
    return funz(T->left, root) || funz(T->right, root);
    }

int dueFoglieStessoGrado(tree T)
    {
    return funz(T, T);
    }
