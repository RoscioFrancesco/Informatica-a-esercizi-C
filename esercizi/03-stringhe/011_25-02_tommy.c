//
//  main.c
//  tommy
//
//  Created by Francesco Roscio Ricon on 25/02/26.
// input : una stirnga di lunghezza l ed un intero K e stampa tutte le possibili compinazioni di K  caratteri ordinate tra quegli l caratteri. stringa: 01 len 2 k=3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void f(char parola[], int segna, char new[], int k);
int main()
    {
    char parola[100]="01";
    int k=3;
    char *new=malloc(sizeof(char)*k);
    f(parola, 0, new, k);
    }
void f(char parola[], int segna, char new[], int k)
{
    if(segna==k)
        return;
    for(int i=0; i<strlen(parola); i++)
        {
            new[segna]=parola[i];
            new[segna+1]='\0';
            if(k==strlen(new))
            {
                printf("\n%s", new);
            }
            f(parola, segna+1, new, k);
        }
    f(parola, segna+1, new,k);
}


