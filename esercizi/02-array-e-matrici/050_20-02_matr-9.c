//
//  main.c
//  matr 9
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#include <stdio.h>
int main()
    {
    int vett[10]={4,6,7,3,8,1,4,6,9,10};
    int max=0;
    int min=*vett;
    int *scorri=&vett[0];
    for(int i=0; i<10; i++)
        {
            if(*scorri>max)
                {
                    max=*scorri;
                }
            if(*scorri<min)
                {
                    min=*scorri;
                }
            scorri=scorri+1;
        }
    printf("max: %d, min: %d", max, min);
    }
