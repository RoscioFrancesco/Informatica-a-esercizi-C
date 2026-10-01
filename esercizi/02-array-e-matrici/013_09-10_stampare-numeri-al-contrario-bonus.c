//  Created by Francesco Roscio Ricon on 09/10/25.



#include <stdio.h>


int main() {
    int i, numero, j, v[100];
    printf("Quanti valori si può inserire?");
    scanf("%d", &numero);
    for(i=numero; i>0; i--)
    {
        scanf("%d", &v[i]);
    }
    v[0]='\0';
    for(j=1; j<=numero; j++)
    {
        printf("%d", v[j]);
    }
    printf("\n");

}
