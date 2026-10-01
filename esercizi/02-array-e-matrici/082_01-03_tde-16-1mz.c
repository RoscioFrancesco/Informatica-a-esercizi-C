//  Created by Francesco Roscio Ricon on 01/03/26.

#include <stdio.h>
#include <stdlib.h>
void f(int vett[], int len);
int main()
    {
    int array[5]={4,6,2,3,9};
    f(array, 5);
    for(int i=0; i<5; i++)
        {
            printf("%d, ", array[i]);
        }
    }
void f(int vett[], int len)
    {
    if(len==1)
        return;
    int primo, secondo;
    primo=len-2;
    secondo=primo+1;
    while(secondo>0)
        {
            vett[secondo]=vett[secondo]+vett[primo];
            primo--;
            secondo--;
        }
    }
