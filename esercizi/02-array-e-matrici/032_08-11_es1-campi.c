//  Created by Francesco Roscio Ricon on 08/11/25.

#include <stdio.h>
typedef int VT[10];
int invertivettore (VT a, int len, VT b);
int main() {
    VT a,b;
    int i, prod;
    for(i=0; i<10; i++)
        {
            scanf("%d", &a[i]);
        }
    prod = invertivettore(a, 10, b);
    for(i=0; i<10; i++)
    {
        printf("%d", b[i]);
    }
    printf("%d", prod);
}
int invertivettore (VT a, int len, VT b)
{
    int i=0, prod=1;
    for(i=0;i<len; i++)
    {
        b[i]=a[len-i-1];
        prod=prod*a[i];
    }
    return prod;
}
