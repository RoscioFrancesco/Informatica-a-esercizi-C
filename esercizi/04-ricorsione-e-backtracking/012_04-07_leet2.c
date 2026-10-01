//
//  main.c
//  leet2
//
//  Created by Francesco Roscio Ricon on 04/07/26.
//

#include <stdio.h>

void f(int r, int c, int *count, int m, int n);
int uniquePaths(int m, int n) {
    int val=0;
    f(0,0, &val, m,n);
}


void f(int r, int c, int *count, int m, int n)
    {
        if(r==m && c==n)
            {
                (*count)++;
            }
        if(r<m)
            f(r+1, c, count, m, n);
        if(c<n)
            f(r, c+1, count, m,n);
    }
