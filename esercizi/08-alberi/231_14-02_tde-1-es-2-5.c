//
//  main.c
//  tde 1 es 2 -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURA ALBERO (come testo)
   ========================= */
typedef struct node_s {
    char nome[100], cognome[100];
    struct node_s *left, *right;
} node_t;

typedef node_t* tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
void cognomeDiffuso(tree T, char str[]);  // TODO: da implementare

/* =========================
   UTILITY PER TEST
   ========================= */
static tree newNode(const char *nome, const char *cognome) {
    tree n = (tree)malloc(sizeof(node_t));
    if(!n) { perror("malloc"); exit(1); }
    strncpy(n->nome, nome, sizeof(n->nome)-1);
    n->nome[sizeof(n->nome)-1] = '\0';
    strncpy(n->cognome, cognome, sizeof(n->cognome)-1);
    n->cognome[sizeof(n->cognome)-1] = '\0';
    n->left = n->right = NULL;
    return n;
}

static void freeTree(tree T) {
    if(!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

static void printPreorder(tree T) {
    if(!T) return;
    printf("%s %s  |  ", T->nome, T->cognome);
    printPreorder(T->left);
    printPreorder(T->right);
}
void wrapper(int *max, tree root, tree albero, char massimo[]);
/* =========================
   MAIN DI TEST
   ========================= */
void conta(tree root, char cognome[], int *count);
int main(void) {
    /*
       Creo un albero (gerarchia) con cognome più diffuso = "Rossi" (unico).

                 Luca Bianchi
                /            \
        Anna Rossi          Marco Verdi
          /     \             /
     Paolo Rossi  Sara Neri  Giulia Rossi
    */

    tree T = newNode("Luca",  "Bianchi");
    T->left  = newNode("Anna",  "Rossi");
    T->right = newNode("Marco", "Verdi");
    T->left->left   = newNode("Paolo",  "Rossi");
    T->left->right  = newNode("Sara",   "Neri");
    T->right->left  = newNode("Giulia", "Rossi");

    printf("=== ALBERO (preorder) ===\n");
    printPreorder(T);
    printf("\n\n");

    char out[100] = "???";
    cognomeDiffuso(T, out);

    printf("Cognome piu diffuso: %s\n", out);

    freeTree(T);
    return 0;
}


void cognomeDiffuso(tree T, char str[]) {
    int max=0;
    wrapper(&max, T, T, str);
    return;
}
void conta(tree root, char cognome[], int *count)
    {
        if(root==NULL)
            return;
        if(strcmp(cognome, root->cognome)==0)
            (*count)++;
    conta(root->left, cognome, count);
    conta(root->right, cognome, count);
    }
void wrapper(int *max, tree root, tree albero, char massimo[])
    {
    if(albero==NULL)
        return;
    int count=0;
    conta(root, albero->cognome, &count);
    if(count>*max)
        {
            *max=count;
            strcpy(massimo, albero->cognome);
        }
    wrapper(max, root, albero->left, massimo);
    wrapper(max, root, albero->right, massimo);
    }
