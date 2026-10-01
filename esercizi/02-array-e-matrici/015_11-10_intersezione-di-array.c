//  Created by Francesco Roscio Ricon on 11/10/25.
#include <stdio.h>
#include <string.h>

int main() {
    int array1[100], array2[100], c1, c2, n1, n2, i, intersezione[200], counter_intersezione;
    do{
        printf("Quanti numeri vuoi inserire nel primo array?");
        scanf("%d", &n1);
    } while(n1<0 || n1>100);
    do{
        printf("Quanti numeri vuoi inserire nel secondo array?");
        scanf("%d", &n2);
    } while(n2<0 || n2>100);
    printf("Inserire le cifre del primo array");
    for(i=0; i<n1; i++)
    scanf("%d", &array1[i]);
    printf("Inserire le cifre del secondo array");
    for(i=0; i<n1; i++)
    scanf("%d", &array2[i]);
    counter_intersezione = 0;
    for(c1=0; c1<n1; c1++)
    {
        for(c2=0; c2 < n2; c2++)
        {
            if(array1[c1]==array2[c2])
            {
                intersezione[counter_intersezione] = array1[c1];
                counter_intersezione++;
            }
        }
    }
    for(i=0; i<counter_intersezione; i++)
        printf("%d", intersezione[i]);
    printf("\n");
}
