//  Created by Francesco Roscio Ricon on 14/10/25.



#include <stdio.h>
#define N 100
#include <string.h>
int main() {
    int v[N], i, pari[N], dispari[N], l, c_pari=0, c_dispari=0;
    do{
        printf("Quanti caratteri vuoi inserire?");
        scanf("%d", &l);
    }while(l<0 || l>N);
    printf("Inserire i caratteri");
    for(i=0; i<l; i++)
    {
        scanf("%d", &v[i]);
    }
    for(i=0; i<l; i++)
    {
        if(v[i] %2 ==0)
        {
            pari[c_pari]=v[i];
            c_pari++;
        }
        if(v[i] %2 != 0){
            dispari[c_dispari]=v[i];
            c_dispari++;
        }
    }
    for(i=0; i<c_dispari; i++)
    {
        printf("%d", dispari[i]);
    }
    printf("\n");
    for(i=0; i<c_pari; i++)
    {
        printf("%d", pari[i]);
    }
    
    return 0;
}
