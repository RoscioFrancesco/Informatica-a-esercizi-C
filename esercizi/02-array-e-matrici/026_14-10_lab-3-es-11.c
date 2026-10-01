//  Created by Francesco Roscio Ricon on 14/10/25.


#include <stdio.h>
#define Nmax 100
int main() {
    int scelta, n, i, tutto[Nmax], j=1, flag=0, num, mul2=0, mul3=0, mul5=0;
    do{
        printf("Quanti valori vuoi inserire nell'array?");
        scanf("%d", &n);
    }while(n<0 || n>Nmax);
    for(i=0; i<n; i++)
        {
            scanf("%d", &tutto[i]);
        }
    do{
        printf("Inserisci un valore tra 0,1,2,3");
        scanf("%d", &scelta);
    }while(!(scelta==1 || scelta==0 || scelta ==2 || scelta ==3));
    switch (scelta) {
        case 0:
            for(i=0; i<n; i++)
                {
                    printf("%d", tutto[i]);
                }
            break;
        case 1:
            for(i=0; i<n; i++)
                {
                    if(tutto[i]%2!=0)
                        tutto[i]= 2*tutto[i];
                    if(tutto[i]%2==0)
                        tutto[i]= tutto[i] / 2;
                    printf("%d", tutto[i]);
                }
            break;
        case 2:
            for(i=0; i<n; i++)
            {
                for(j=1, flag=0; flag==0; j++)
                    if((tutto[i]+j)%5 == 0)
                    {
                        num=tutto[i];
                        printf("%d ", num+j);
                        flag=1;
                    }
                
            }
        case 3:
            for(i=0; i<n; i++)
            {
                    if(tutto[i]%5==0) mul5++;
                    if(tutto[i]%2==0) mul2++;
                    if(tutto[i]%3==0) mul3++;
            }
            printf("%d multipli di 2, %d multipli di 3, %d multipli di 5", mul2, mul3, mul5);
            break;
    }
}
