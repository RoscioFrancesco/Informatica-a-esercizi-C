
//  Created by Francesco Roscio Ricon on 18/11/25.

#include <stdio.h>
#define N 100
void stampaalcontrario (int array[], int *scorriarray, int len);
int main() {
    int num;
    printf("Quanti elementi vuoi inserire?");
    scanf("%d", &num);
    int array[N];
    int i;
    for(i=0; i<num; i++)
        {
            printf("Inserire l'elemento %d", i+1);
            scanf("%d", &array[i]);
        }
    stampaalcontrario(array, &array[num-1], num);
    
}
void stampaalcontrario (int array[], int *scorriarray, int len)
    {
    if(len==0)
        ;
    else
    {
        
        printf("%d", *scorriarray);
        stampaalcontrario(array, scorriarray-1, len-1);
    }
    }
