//
//  main.c
//  prova
//
//  Created by Francesco Roscio Ricon on 12/10/25.
//

#include <stdio.h>

int main() {
#define nmax 100
    int v1[nmax], v2[nmax], v3[nmax*2];
    int i, n1, n2, counter3, i1, i2, flag;

    do {
        printf("Quanti numeri vuoi inserire nel primo array? ");
        scanf("%d", &n1);
    } while(n1 < 0 || n1 > nmax);

    do {
        printf("Quanti numeri vuoi inserire nel secondo array? ");
        scanf("%d", &n2);
    } while(n2 < 0 || n2 > nmax);

    printf("Inserisci i numeri del primo array:\n");
    for(i = 0; i < n1; i++)
        scanf("%d", &v1[i]);

    printf("Inserisci i numeri del secondo array:\n");
    for(i = 0; i < n2; i++)
        scanf("%d", &v2[i]);

    counter3 = 0;

    // Copia v1 in v3
    for(i = 0; i < n1; i++) {
        v3[counter3] = v1[i];
        counter3++;
    }

    // Aggiunge da v2 solo i numeri non presenti in v3
    for(i2 = 0; i2 < n2; i2++) {
        flag = 0;
        for(i1 = 0; i1 < counter3 && flag == 0; i1++) {
            if(v2[i2] == v3[i1]) flag = 1;
        }
        if(flag == 0) {
            v3[counter3] = v2[i2];
            counter3++;
        }
    }

    printf("\nArray unione:\n");
    for(i = 0; i < counter3; i++) {
        printf("%d ", v3[i]);
    }
    printf("\n");

    return 0;
}

