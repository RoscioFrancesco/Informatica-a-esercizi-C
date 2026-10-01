//
//  main.c
//  tde alberi -2
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char *nome;
    int isFile;
    int dimensione;
    struct Nodo *left;
    struct Nodo *right;
} Nodo;

typedef Nodo * Tree;
Nodo* init();
Nodo* creaNodo(const char *nome, int isFile, int dimensione);
void aggiungiFiglio(Nodo *cartella, Nodo *figlio);
void stampaAlbero(Nodo *nodo, int livello);
int dimensioneCartella(Tree root, char cartella[]);
int sommacartella(Tree albero);

int main() {
    Nodo *root = init();
    printf("Struttura dell'albero:\n");
    stampaAlbero(root, 0);
    int dimC1=dimensioneCartella(root, "Cartella1");
    printf("Cartella 1: %d\n", dimC1);
    int dimC2=dimensioneCartella(root, "Cartella2");
    printf("Cartella 2: %d\n", dimC2);
    int dimsubC2=dimensioneCartella(root, "SubCartella1");
    printf("SubCartella1: %d\n", dimsubC2);
}


// Funzioni Base
Nodo* init(){
    Nodo *root = creaNodo("Root", 0, 0);
    Nodo *cartella1 = creaNodo("Cartella1", 0, 0);
    Nodo *cartella2 = creaNodo("Cartella2", 0, 0);
    Nodo *subCartella1 = creaNodo("SubCartella1", 0, 0);
    Nodo *file1 = creaNodo("File1.txt", 1, 100);
    Nodo *file2 = creaNodo("File2.txt", 1, 200);
    Nodo *file3 = creaNodo("File3.txt", 1, 300);
    Nodo *file4 = creaNodo("File4.txt", 1, 400);
    aggiungiFiglio(root, cartella1);
    aggiungiFiglio(root, cartella2);
    aggiungiFiglio(cartella1, file1);
    aggiungiFiglio(cartella1, file2);
    aggiungiFiglio(cartella2, file3);
    aggiungiFiglio(cartella2, subCartella1);
    aggiungiFiglio(subCartella1, file4);
    return root;
}
Nodo* creaNodo(const char *nome, int isFile, int dimensione) {
    Nodo *nuovo = (Nodo *)malloc(sizeof(Nodo));
    if (nuovo == NULL) {
        printf("Errore di allocazione memoria");
        return NULL;
    }
    nuovo->nome = strdup(nome);
    nuovo->isFile = isFile;
    nuovo->dimensione = isFile ? dimensione : 0;
    nuovo->left = NULL;
    nuovo->right = NULL;
    return nuovo;
}
void aggiungiFiglio(Nodo *cartella, Nodo *figlio) {
    if (cartella->isFile) {
        printf("Errore: Impossibile aggiungere un figlio a un file.\n");
        return;
    }


    if (cartella->left == NULL) {
        cartella->left = figlio;
    } else if (cartella->right == NULL) {
        cartella->right = figlio;
    } else {
        printf("Errore: La cartella '%s' ha già due figli.\n", cartella->nome);
    }
}
void stampaAlbero(Nodo *nodo, int livello) {
    if (nodo == NULL) return;
    for (int i = 0; i < livello; i++) printf("  ");
    if (nodo->isFile) {
        printf("File: %s (%d byte)\n", nodo->nome, nodo->dimensione);
    } else {
        printf("Cartella: %s\n", nodo->nome);
    }
    stampaAlbero(nodo->left, livello + 1);
    stampaAlbero(nodo->right, livello + 1);
}

int sommacartella(Tree albero)
    {
        if(albero==NULL)
            return 0;
    return albero->dimensione+sommacartella(albero->left)+sommacartella(albero->right);
    }
int dimensioneCartella(Tree root, char cartella[])
    {
        if(root==NULL)
            return 0;
        if(strcmp(root->nome, cartella)==0)
            {
                return sommacartella(root);
            }
    return dimensioneCartella(root->left,cartella)+dimensioneCartella(root->right,cartella);
    }
