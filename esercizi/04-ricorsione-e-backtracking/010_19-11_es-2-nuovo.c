//
//  main.c
//  es 2 nuovo
//
//  Created by Francesco Roscio Ricon on 19/11/25.
//

//[8, 3, 4, 1, 1, 3, 6]
//
//il programma stamperà
//
//[8, 4, 6]
//
//ATTENZIONE! Non basta stampare l'output, alla fine deve esistere un array contenente tutti e soli i valori pari dell'array di input.

#include <stdio.h>
#define N 100
void crea_pari (int *array, int len_array, int *len_pari, int pari[]);
int main() {
    int num;
    printf("Quanti elementi vuoi inserire?");
    scanf("%d", &num);
    int array[N];
    int array_pari[N];
    int len_pari=0;
    int i=0;
    for(i=0; i<num; i++)
        {
            printf("Inserire l'elemento %d", i+1);
            scanf("%d", &array[i]);
        }
    crea_pari(array, num, &len_pari, array_pari);
    for(i=0; i<len_pari; i++)
        {
            printf("%d", array_pari[i]);
        }
    
}
void crea_pari (int *array, int len_array, int *len_pari, int pari[])
    {
    if(len_array==0)
    {;}
    else
        {
            if((*array)%2==0)
                {
                    pari[*len_pari]=*array;
                    (*len_pari)++;
                }
            crea_pari(array+1, len_array-1, len_pari, pari);
        }
    }
