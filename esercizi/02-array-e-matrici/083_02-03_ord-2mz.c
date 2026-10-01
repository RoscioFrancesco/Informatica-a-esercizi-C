//
//  main.c
//  ord 2mz
//
//  Created by Francesco Roscio Ricon on 02/03/26.
//

#include <stdio.h>
void bubble_sort(int vett[], int len);
void stampa(int vett[], int len);
int main() {
    int vett[5]={1,5,4,2,3};
    bubble_sort(vett, 5);
    stampa(vett, 5);
}

void bubble_sort(int vett[], int len)
    {
    int numero_inv=0;
    for(int i=0; i<len-1; i++)
        {
            numero_inv=0;
            for(int j=0; j<len-1-i; j++)
                {
                    if(vett[j]>vett[j+1])
                        {
                            int temp=vett[j+1];
                            vett[j+1]=vett[j];
                            vett[j]=temp;
                            numero_inv++;
                        }
                }
            if(numero_inv==0)
                break;
        }
    }
void stampa(int vett[], int len)
    {
    for(int i=0; i<len; i++)
        {
            printf("%d,",vett[i]);
        }
    }
