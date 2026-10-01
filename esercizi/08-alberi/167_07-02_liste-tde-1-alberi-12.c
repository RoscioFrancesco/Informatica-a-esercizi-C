//  Created by Francesco Roscio Ricon on 07/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE DATI (come testo)
   ========================= */
typedef struct node_s {
    char nome[100], cognome[100];
    struct node_s *left, *right;
} node_t;

typedef node_t *tree;


void cognomeDiffuso(tree T, char str[]);   /* TODO: da svolgere */

/* =========================
   UTILITY PER TEST (main)
   ========================= */
static tree newNode(const char *nome, const char *cognome, tree left, tree right)
{
    tree n = (tree)malloc(sizeof(node_t));
    if(!n) { perror("malloc"); exit(1); }
    strncpy(n->nome, nome, sizeof(n->nome)-1);
    n->nome[sizeof(n->nome)-1] = '\0';
    strncpy(n->cognome, cognome, sizeof(n->cognome)-1);
    n->cognome[sizeof(n->cognome)-1] = '\0';
    n->left = left;
    n->right = right;
    return n;
}

static void printTreePreorder(tree T, int depth)
{
    if(T == NULL) return;
    for(int i=0; i<depth; i++) printf("  ");
    printf("- %s %s\n", T->nome, T->cognome);
    printTreePreorder(T->left, depth+1);
    printTreePreorder(T->right, depth+1);
}

static void freeTree(tree T)
{
    if(T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================
   MAIN DI TEST
   ========================= */
void contagognome(tree albero, char cognome[], int *count);
void cognomeDiffuso(tree T, char str[]);
void scorrialbero(tree albero, tree root, int *max, char massimo[]);
int wrapper_cognome(tree albero, char cognome[]);
void scorrialbero(tree albero, tree root, int *max, char massimo[]);
void contacognome(tree albero, char cognome[], int *count);

int main(void)
{
    /*
      Albero di esempio (gerarchia):
            Mario Rossi
           /           \
      Luca Bianchi   Anna Rossi
        /     \           \
   Sara Rossi  Paolo Verdi  Giulia Neri

      Cognome più diffuso qui: "Rossi" (3 occorrenze)
      (supponiamo sia unico come da testo)
    */
    tree T =
        newNode("Mario", "Rossi",
            newNode("Luca", "Bianchi",
                newNode("Sara", "Rossi", NULL, NULL),
                newNode("Paolo", "Verdi", NULL, NULL)
            ),
            newNode("Anna", "Rossi",
                NULL,
                newNode("Giulia", "Neri", NULL, NULL)
            )
        );

    printf("Gerarchia aziendale (preorder):\n");
    printTreePreorder(T, 0);

    char risultato[100] = "";   /* qui va scritto il cognome più diffuso */
    cognomeDiffuso(T, risultato);

    printf("\nCognome piu' diffuso: %s\n", risultato);

    freeTree(T);
    return 0;
}

/* =========================
   FUNZIONE DA SVOLGERE
   ========================= */
void contacognome(tree albero, char cognome[], int *count)
    {
        if(albero==NULL)
            return;
        if(strcmp(albero->cognome, cognome)==0)
            {
                (*count)++;
            }
    contacognome(albero->left, cognome, count);
    contacognome(albero->right, cognome, count);
    }
int wrapper_cognome(tree albero, char cognome[])
    {
        if(albero==NULL)
            return 0;
        int conta=0;
        contacognome(albero, cognome, &conta);
        return conta;
    }
void scorrialbero(tree albero, tree root, int *max, char massimo[])
    {
        if(albero==NULL)
            return;
        int conta_cognome=wrapper_cognome(root, albero->cognome);
        if(conta_cognome>*max)
            {
                *max=conta_cognome;
                strcpy(massimo, albero->cognome);
            }
    scorrialbero(albero->left, root, max, massimo);
    scorrialbero(albero->right, root, max, massimo);
    }

void cognomeDiffuso(tree T, char str[])
    {
    int max=0;
    scorrialbero(T, T, &max, str);
    }
