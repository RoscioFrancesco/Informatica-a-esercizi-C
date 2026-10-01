//
//  main.c
//  fibonacci
//
//  Created by Francesco Roscio Ricon on 16/11/25.
//

#include <stdio.h>
int fibo(int n);
int main() {
    int num;
    printf("Inserie il numero l'n-esimo numero di fibonacci desiderato");
    scanf("%d", &num);
    int ris;
    int i;
    for(i=0; i<num; i++)
    {
        ris=fibo(i);
        printf("%d ", ris);
    }
    
}
int fibo(int n)
    {
        if(n==0 || n==1)
            return 1;
        else
        {
            return (fibo(n-1)+fibo(n-2));
        }
    }
