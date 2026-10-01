//  Created by Francesco Roscio Ricon on 08/11/25.

#include <stdio.h>
#define N 100
int funz_sqp_lunga (int len1, int len2);
void funz(int len3, int s3[],int *max, int *min, int *posmax, int *posmin);
int main() {
    int s1[N], i=0, s2[N], len1, len2, flag, max, min, pos_max, pos_min;
    printf("Inserire i numeri della prima sequenza");
    i=-1;
    do{
        i++;
        scanf("%d", &s1[i]);
    }while(s1[i]!=0 && i<N);
    len1=i;
    printf("Inserire i numeri della seconda sequenza");
    i=-1;
    do{
        i++;
        scanf("%d", &s2[i]);
    }while(s2[i]!=0 && i<N);
    len2=i;
    flag=funz_sqp_lunga(len1, len2);
    if(flag==1)
        {
            funz(len1, s1, &max, &min, &pos_max, &pos_min);
        }
    if(flag==2)
        {
            funz(len2, s2, &max, &min, &pos_max, &pos_min);
        }
    if(flag==0)
        printf("Non so cosa fare");
    printf("Il massimo è :%d\n", max);
    printf("Il minimo é: %d\n", min);
    printf("Posizione massimo:%d\n", pos_max);
    printf("Posizione minimo:%d\n", pos_min);
    
}
int funz_sqp_lunga (int len1, int len2)
    {
    if (len1>len2) return 1;
    if(len1<len2) return 2;
    return 0;
    }
void funz(int len3, int s3[],int *max, int *min, int *posmax, int *posmin)
    {
    int i=0;
    *max=s3[0];
    *min=s3[0];
    for(i=0; i<len3; i++)
        {
            if(s3[i]>*max)
            {
                *max=s3[i];
                *posmax=i;
            }
            if(s3[i]<*min)
                {
                    *min=s3[i];
                    *posmin=i;
                }
        }
    }

