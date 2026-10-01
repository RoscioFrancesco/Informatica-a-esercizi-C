//
//  main.c
//  esercitazione numeri triangolari
//
//  Created by Francesco Roscio Ricon on 06/10/25.
//

#include <stdio.h>

int main() {
    int N, i , tmp;
    i=0;
    tmp=0;
    do {
        printf("Inserisci il numero\n");
        scanf("%d", &N);
        if (N<0) printf("Il numero è minore di 0\n");
    }while(N<0);
    while(tmp<N)
    {
        i++;
        tmp = tmp+i;
    }
    if (tmp==N)
        printf("Il numero è triangolare\n");
    else
        printf("Il numero non è triangolare\n");
}
