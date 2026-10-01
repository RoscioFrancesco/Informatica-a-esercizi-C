//
//  main.c
//  confronto tra array
//
//  Created by Francesco Roscio Ricon on 09/10/25.
//

#include <stdio.h>

int main() {
    int v1[100], v2[100], n1, n2;
    int i=0;
    int flag;
    flag=1;
    printf("Quanti caratteri vuoi inserire nel primo array?\n");
    scanf("%d", &n1);
    printf("Quanti caratteri vuoi inserire nel secondo array?\n");
    scanf("%d", &n2);
    printf("Inserisci i caratteri del primo array\n");
    for(i=0; i<n1; i++)
    {
        scanf("%d", &v1[i]);
    }
    printf("Inserisci i caratteri del secondo array\n");
    for(i=0; i<n2; i++)
    {
        scanf("%d", &v2[i]);
    }
    if(n2==n1)
    {
        for(i=0; i< n2 && flag == 1; i++)
        {
            if(v1[i]!=v2[i])
            {
                flag = 0;
            }
        }
    }
    if(n2!=n1) flag=2;
    if(flag == 0) printf("gli array sono diversi, la diversità avviene al carattere %d", i);
    if(flag == 1) printf("gli array sono uguali");
    if(flag == 2) printf("gli array sono di diversa lunghezza");
    
}
