//  Created by Francesco Roscio Ricon on 14/10/25.

 //   Ad esempio, se i due array sono {1, 6, 1} e {-1, 4, 3}, verrà stampato 110 perché: 1>-1 (1), 6>4 (1), 1<3 (0).


#include <stdio.h>
#define Nmax 100
int main() {
    int l, i, v1[Nmax], v2[Nmax];
    do{
        printf("Quanti valori vuoi inserire");
        scanf("%d", &l);
    }while(l<0 || l>Nmax);
    printf("Inserisci i valori del primo array");
    for(i=0; i<l; i++)
    {
        scanf("%d", &v1[i]);
    }
    printf("Inserisci i valori del secondo array");
    for(i=0; i<l; i++)
    {
        scanf("%d", &v2[i]);
    }
    for(i=0; i<l; i++)
    {
        if(v1[i]>v2[i])
            printf("1");
        else printf("0");
    }
    
}
