//  Created by Francesco Roscio Ricon on 03/03/26.
#include <stdio.h>
void scambia(int ***a, int ***b);
int main() {
    int x=10;
    int y=20;
    int *a;
    a=&x;
    int *b;
    b=&y;
    int **alfa;
    alfa=&a;
    int **beta;
    beta=&b;
    int ***primo;
    primo=&alfa;
    int ***secondo;
    secondo=&beta;
    scambia(primo, secondo);
    printf("\nx = %d", x);
    printf("\ny = %d", y);
}
void scambia(int ***a, int ***b)
    {
    int temp=***b;
    ***b=***a;
    ***a=temp;
    }
