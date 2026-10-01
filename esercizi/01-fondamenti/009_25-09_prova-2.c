//
//  main.c
//  prova.2
//
//  Created by Francesco Roscio Ricon on 25/09/25.
//

#include <stdio.h>

int main() {
    int prezzo, rimanente, n50, n20, n5, n2, n1;
    printf("Inserire il prezzo:");
    scanf("%d",&prezzo);
    n50 = prezzo / 50; // in questo modo trovo il numero di banconote da 50 necessario
    rimanente= prezzo % 50; // è il resto intero della divisione
    n20 = rimanente / 20; //trovo il numero di banconote da 20
    rimanente = rimanente % 20;
    n5 = rimanente / 5;
    rimanente = rimanente % 5;
    n2 = rimanente / 2;
    rimanente = rimanente % 2;
    n1 =rimanente / 1;
    rimanente = rimanente % 1;
    printf("Il numero minimo di banconote da 50 è pari a %d\n il numero di quelle da 20 è pari a %d\n il numero di quelle da 5 è pari a %d\n il numero di quelle da 2 euro è pari a %d\n il numero di quelle da 1 euro è pari a %d\n" ,n50 ,n20 , n5 ,n2, n1);
    return 0;
}
