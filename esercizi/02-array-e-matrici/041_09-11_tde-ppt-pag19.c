//  Created by Francesco Roscio Ricon on 09/11/25.

#define N 100
#include <stdio.h>
int numSommaDiff (int a[], int len);
int sommadopo(int a[], int posizione_elemento, int len);
int sommaprima(int a[], int posizione_elemento);
int main() {
    int len, a[N];
    printf("quanti elementi vuoi inserire?");
    scanf("%d", &len);
    int i;
    for(i=0;i<len; i++)
        {
            scanf("%d", &a[i]);
        }
    int flag;
    flag = numSommaDiff(a, len);
    printf("%d", flag);
    
}
int numSommaDiff (int a[], int len_a)
    {
    int i;
    for(i=0;i<len_a;i++)
        {
            if(a[i]==(sommaprima(a, i)-sommadopo(a, i, len_a)))
                return 1;
        }
    return 0;
}
int sommaprima(int a[], int posizione_elemento)
    {
    int i;
    int sommap=0;
    for(i=posizione_elemento-1; i>=0; i--)
        {
            sommap=sommap+a[i];
        }
    return sommap;
}
int sommadopo(int a[], int posizione_elemento, int len)
    {
    int i=0;
    int sommad=0;
    for(i=posizione_elemento+1; i<=len; i++)
        {
            sommad=sommad+a[i];
        }
    return sommad;
}
