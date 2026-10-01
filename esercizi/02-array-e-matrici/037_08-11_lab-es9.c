//  Created by Francesco Roscio Ricon on 08/11/25.

#include <stdio.h>
#define N 100
void funzione (int array[], int len, int *posiz_max, int *max);
int main() {
    int array[N], len, i, posiz_max, max;
    printf("Quanti elementi vuoi inserire?");
    scanf("%d", &len);
    for(i=0;i<len;i++)
        {
            scanf("%d", &array[i]);
        }
    funzione(array, len, &posiz_max, &max);
    printf("Il massimo è: %d", max);
    printf("La posizione del massimo è: %d", posiz_max+1);
}
void funzione (int array[], int len, int *posiz_max, int *max)
{
    int i;
    int last_max=array[0], last_pos_max=0;
    for(i=0;i<len;i++)
    {
        if(array[i]>last_max)
        {
            last_max=array[i];
            last_pos_max=i;
        }
    }
    *max=last_max;
    *posiz_max=last_pos_max;
}
