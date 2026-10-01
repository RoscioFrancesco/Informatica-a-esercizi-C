//  Created by Francesco Roscio Ricon on 09/10/25.



#include <stdio.h>


int main() {
    int i, numero, j, v1[100], v2[100];
    printf("Quanti valori si può inserire?");
    scanf("%d", &numero);
    j = 0;
    for(i=0; i < 2*numero+1; i++)
    {
        if(i<numero)scanf("%d", &v1[i]);
        if(i>numero)
        {   j++;
            printf("%d", v1[i-2*j]);
        }
    }
}
