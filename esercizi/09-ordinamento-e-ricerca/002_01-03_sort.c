//
//  main.c
//  sort
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//

#include <stdio.h>
void bubblesort(int vett[], int len);
int main() {
    int vett[5]={3,4,1,3,2};
    bubblesort(vett, 5);
    printf("\n");
    for(int i=0; i<5; i++)
        {
            printf("%d ", vett[i]);
        }
}
void bubblesort(int vett[], int len)
    {
    int i,j, n_swap;
    for(i=0; i<len-1; i++)
        {
            n_swap=0;
            for(j=0; j<len-1-i; j++)
                {
                    if(vett[j]>vett[j+1])
                        {
                            int temp=vett[j];
                            vett[j]=vett[j+1];
                            vett[j+1]=temp;
                            n_swap++;
                        }
                    printf("\n");
                    for(int i=0; i<5; i++)
                        {
                            printf("%d ", vett[i]);
                        }
                }
            printf("\n uscito ciclo");
            if(n_swap==0)
                break;
        }
    }
