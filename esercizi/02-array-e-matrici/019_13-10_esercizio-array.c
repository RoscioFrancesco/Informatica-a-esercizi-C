//  Created by Francesco Roscio Ricon on 13/10/25.

#include <stdio.h>
#include <math.h>
#define nmax 100
int main() {
    int n, v[nmax], i, j;
    i=0;
    do{
        printf("Quanti numeri vuoi inserire?");
        scanf("%d", &n);
    } while(n<0 || n> nmax);
    for(i=0; i<n; i++)
    {
        scanf("%d", &v[i]);
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(v[j] == 2 * v[i])
            {
                printf(" %d - %d,", v[i], v[j]);
            }
        }
    }


}
