//
//  main.c
//  setdi array acquisito
//
//  Created by Francesco Roscio Ricon on 13/10/25.
//

#include <stdio.h>

int main() {
    int n, v1[100], set[100], i, counterset=0, z=0, flag=1;
    i=0;
    do{
        printf("Quanti numeri vuoi inserire?");
        scanf("%d", &n);
    }while(n<0 || n>100);
    printf("Inserisci i numeri");
    for(i=0; i<n ; i++)
    {
        scanf("%d", &v1[i]);
    }
    for(i=0; i<n; i++)
    {
        
        for(z=i+1; z<n; z++)
            {
            if (v1[i]==v1[z])
                {
                    flag=0;
                    break;
                }
            }
        if(flag==1)
        {
            set[counterset]=v1[i];
            counterset++;
        }
        flag=1;
    }
    for(i=0; i<counterset; i++)
    {
        printf("%d", set[i]);
    }
    

}
