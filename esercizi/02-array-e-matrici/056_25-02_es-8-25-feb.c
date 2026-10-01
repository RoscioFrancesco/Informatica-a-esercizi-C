//
//  main.c
//  es 8 25 feb
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//

#include<stdio.h>
#define N 5

void f(int u[], int v[], int len_u, int len_v);
int main()
{
    int u[N] = {4,1,3,7,0}, v[N] = {1,6,8,4,9};
    f(u, v, N, N);
    for(int i=0; i<N; i++)
        {
            printf("%d,",u[i]);
        }
    
}

int trovato(int vett[], int len, int x)
    {
    for(int i=0; i<len; i++)
        {
            if(vett[i]==x)
                return 1;
        }
    return 0;
    }
void f(int u[], int v[], int len_u, int len_v)
    {
    int vett[N]={0};
    int segna=0;
    for(int i=0; i<len_u; i++)
        {
            if(!trovato(v, len_v, u[i]))
                {
                    vett[segna]=u[i];
                    segna++;
                }
        }
    for(int i=0; i<len_u; i++)
        {
            if(!trovato(vett, segna, u[i]))
                {
                    vett[segna]=u[i];
                    segna++;
                }
        }
    for(int i=0; i<len_u; i++)
        {
            u[i]=vett[i];
        }
    }
