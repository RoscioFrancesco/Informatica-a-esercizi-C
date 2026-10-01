//
//  main.c
//  unione di arrya
//
//  Created by Francesco Roscio Ricon on 12/10/25.
// per fare l'esercizio correttamente dovrei fare il set degli array in acqusizione

#include <stdio.h>
#include <stdbool.h>
#define nmax 100


int main() {
    int v1[nmax], v2[nmax], v3[nmax*2], i, n1, n2, counter3, i1, i2, flag, v4[nmax*2], j, i4, k, z;
    do{
        printf("Quanti numeri vuoi inserie nel primo array?");
        scanf("%d", &n1);
    } while(n1<0 || n1> nmax);
    counter3 =0;
    flag =0;
    do{
        printf("Quanti numeri vuoi inserie nel secondo array?");
        scanf("%d", &n2);
    } while(n2<0 || n2> nmax);
    printf("Inserisci i caratteri del primo array:\n");
    for(i=0; i<n1; i++)
    {
        scanf("%d", &v1[i]);
    }
    printf("Inserisci i caratteri del secondo array:\n");
    for(i=0; i<n2; i++)
    {
        scanf("%d", &v2[i]);
    }
    
    for(i=0; i<n1; i++)
    {
        v3[i] = v1[i];
        counter3++;
    }
    for(i2=0; i2<n2; i2++)
        {
            for(i1=0; i1<n1 && flag==0; i1++)
                {
                    if(v2[i2]==v1[i1])
                    {
                        flag=1;
                    }
                }
            if(flag==0)
            {
                v3[counter3] = v2[i2];
                counter3++;
            }
            flag = 0;
        }
    printf("\n");
    // a qs punto ci potrebbero essere ancora elementi ripetuti se abbiamo insirito elementi ripetuti in uno stesso array di partenza
    // quindi faccio il set di v3.
    flag =0;
    i4=0;
    k=0;
    for(i=0, flag =1; i<counter3; i++)
    {
        for(z=i+1, flag =1; z<counter3 && flag ==1; z++)
        {
            if (v3[i]==v3[z])
            {
                flag=0;
                break;
            }
        }
        
        if (flag == 1)
        {
            v4[i4]=v3[i];
            i4++;
        }
        
    }
    
    printf("\n");
    for(i=0; i<counter3; i++)
    {
        printf("%d ", v3[i]);
    }
    printf("\n");
    for(i=0; i<i4; i++)
    {
        printf("%d ", v4[i]);
    }
    
    
}
