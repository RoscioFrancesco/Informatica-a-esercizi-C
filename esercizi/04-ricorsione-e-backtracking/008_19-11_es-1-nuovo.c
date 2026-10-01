//
//  main.c
//  es 1 nuovo
//
//  Created by Francesco Roscio Ricon on 19/11/25.
//


#include <stdio.h>
#define N 100
void stampaalcontrario (int array[], int scorriarray);
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
    stampaalcontrario(array, num-1);
    
}
void stampaalcontrario (int array[], int scorriarray)
    {
    if(scorriarray==-1)
        ;
    else
    {
        
        printf("%d", array[scorriarray]);
        scorriarray--;
        stampaalcontrario(array, scorriarray);
    }
    }
