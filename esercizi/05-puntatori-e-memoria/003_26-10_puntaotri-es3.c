//  Created by Francesco Roscio Ricon on 26/10/25.


#include <stdio.h>

int main() {
    int i, v[5], *p, somma, min, max;
    p= &v[0];
    for(i=0; i<5; i++)
    {
        printf("Inserire il valore numero %d", i+1);
        scanf("%d", (p+i));
    }
    somma=0;
    p= &v[0];
    for(i=0; i<5; i++)
    {
        somma = *(p+i) + somma;
    }
    min = v[0];
    p= &v[0];
    for(i=0; i<5; i++)
    {
        if(*(p+i) < min)
        {
            min = *(p+i);
        }
    }
    
    max = v[0];
    p= &v[0];
    for(i=0; i<5; i++)
    {
        if(*(p+i) > max)
        {
            max = *(p+i);
        }
    }
    printf("La somma è: %d", somma);
    printf("Il massimo è: %d", max);
    printf("Il minimo è: %d", min);
    
    return 0;
}
