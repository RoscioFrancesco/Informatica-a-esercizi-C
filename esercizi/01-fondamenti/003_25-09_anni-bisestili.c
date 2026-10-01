//
//  main.c
//  anni bisestili
//
//  Created by Francesco Roscio Ricon on 25/09/25.
//

#include <stdio.h>
int main ()
{
    int n;
    printf("Inserire l'anno:");
    scanf("%d", &n);
    if (n % 400 == 0)
        printf("L'anno %d è bisestile", n);
    else
        if(n % 4==0)
             if(n % 100==0)
                 printf("L'anno %d non è bisestile",n);
             else
                 printf("L'anno %d è bisestile", n);
    
        else printf ("L'anno %d non è bisestile",n);
    return 0;
                 
        
    
}
