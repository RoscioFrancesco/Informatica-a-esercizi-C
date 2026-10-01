//
//  main.c
//  fibonacci.memo
//
//  Created by Francesco Roscio Ricon on 16/11/25.
//

#include <stdio.h>
#define N 100
int fib(int n,int memo[]);
int main() {
    int i=0;
    int memo[N], n;
    for(i=0; i<N; i++)
        {
            memo[i]=0;
            memo[0]=1;
            memo[1]=1;
        }
    printf("Inserire intero");
    scanf("%d", &n);
    fib(n, memo);
    for(i=0; i<n; i++)
    {
        printf(" %d ", memo[i]);
    }
}
int fib(int n,int memo[]) {
 if (memo[n] != 0)
 return memo[n];
 memo[n] = fib(n-1,memo) + fib(n-2,memo);
 return memo[n];
}
