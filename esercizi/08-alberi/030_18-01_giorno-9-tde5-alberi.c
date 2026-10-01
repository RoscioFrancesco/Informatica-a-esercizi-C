//
//  main.c
//  giorno -9 tde5 alberi 
//
//  Created by Francesco Roscio Ricon on 18/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Definizione della struttura del nodo
typedef struct Nodo {
    char *nome;
    int isFile;
    int dimensione;
    struct Nodo *left;  // Figlio sinistro
    struct Nodo *right; // Figlio destro
} Nodo;
typedef Nodo* Root;

// Prototipi delle funzioni
Nodo* init();
Nodo* creaNodo(const char *nome, int isFile, int dimensione);
void aggiungiFiglio(Nodo *cartella, Nodo *figlio);
void stampaAlbero(Nodo *nodo, int livello);
int wrapper(Root albero);
void funzione(Root albero, int*somma);
void dimensioneCartella(Root albero, char nome[], int *sommacartella);
int superwrapper(Root albero, char nome[]);

int main() {
    // Creazione della cartella root
    Nodo *root = init();


    // Stampa della struttura dell'albero
    printf("Struttura dell'albero:\n");
    stampaAlbero(root, 0);
    char cartella[100]="Cartella1";
    int dim=superwrapper(root, cartella);
    printf("%d", dim);
    return 0;
}


// Funzioni Base
Nodo* init(){
    Nodo *root = creaNodo("Root", 0, 0);


    // Creazione delle cartelle
    Nodo *cartella1 = creaNodo("Cartella1", 0, 0);
    Nodo *cartella2 = creaNodo("Cartella2", 0, 0);
    Nodo *subCartella1 = creaNodo("SubCartella1", 0, 0);


    // Creazione dei file
    Nodo *file1 = creaNodo("File1.txt", 1, 100);
    Nodo *file2 = creaNodo("File2.txt", 1, 200);
    Nodo *file3 = creaNodo("File3.txt", 1, 300);
    Nodo *file4 = creaNodo("File4.txt", 1, 400);


    // Costruzione dell'albero
    aggiungiFiglio(root, cartella1);           // Aggiunge Cartella1 a Root
    aggiungiFiglio(root, cartella2);           // Aggiunge Cartella2 a Root


    aggiungiFiglio(cartella1, file1);          // Aggiunge File1.txt a Cartella1
    aggiungiFiglio(cartella1, file2);          // Aggiunge File2.txt a Cartella1


    aggiungiFiglio(cartella2, file3);          // Aggiunge File3.txt a Cartella2
    aggiungiFiglio(cartella2, subCartella1);   // Aggiunge SubCartella1 a Cartella2


    aggiungiFiglio(subCartella1, file4);       // Aggiunge File4.txt a SubCartella1


    return root;
}


// Creazione di un nuovo nodo
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


// Funzione per aggiungere un figlio a una cartella
void aggiungiFiglio(Nodo *cartella, Nodo *figlio) {
    if (cartella->isFile) {
        printf("Errore: Impossibile aggiungere un figlio a un file.\n");
        return;
    }


    if (cartella->left == NULL) {
        cartella->left = figlio; // Aggiunge il figlio come figlio sinistro
    } else if (cartella->right == NULL) {
        cartella->right = figlio; // Aggiunge il figlio come figlio destro
    } else {
        printf("Errore: La cartella '%s' ha già due figli.\n", cartella->nome);
    }
}




// Funzione per stampare l'albero
void stampaAlbero(Nodo *nodo, int livello) {
    if (nodo == NULL) return;


    // Indenta in base al livello corrente
    for (int i = 0; i < livello; i++) printf("  ");


    // Stampa il nodo corrente (file o cartella)
    if (nodo->isFile) {
        printf("File: %s (%d byte)\n", nodo->nome, nodo->dimensione);
    } else {
        printf("Cartella: %s\n", nodo->nome);
    }


    // Stampa ricorsivamente i figli (left e right)
    stampaAlbero(nodo->left, livello + 1);  // Figlio sinistro
    stampaAlbero(nodo->right, livello + 1); // Figlio destro
}


void funzione(Root albero, int*somma)
    {
        if(albero==NULL)
            {
                return;
            }
        if(albero->isFile==0) // quindi è una cartella
        {
            *somma=*somma+albero->dimensione;
            funzione(albero->left, somma);
            funzione(albero->right, somma);
        }
        if(albero->isFile==1) // quindi è un file
        {
            *somma=*somma+albero->dimensione;
            return;
        }
    }

int wrapper(Root albero)
    {
    int somma=0;
    funzione(albero, &somma);
    return somma;
    }

void dimensioneCartella(Root albero, char nome[], int *sommacartella)
    {
        if(albero==NULL)
            return;
        if(strcmp(albero->nome, nome)==0)
            {
                *sommacartella=wrapper(albero);
            }
    dimensioneCartella(albero->left, nome, sommacartella);
    dimensioneCartella(albero->right, nome, sommacartella);
    }

int superwrapper(Root albero, char nome[])
    {
    int sommacartella=0;
    dimensioneCartella(albero, nome, &sommacartella);
    return sommacartella;
    }
