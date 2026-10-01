//  Created by Francesco Roscio Ricon on 07/03/26.

#include <stdio.h>
#include <stdlib.h>
void creaNumero(int **p);
int main() {
    int *x=NULL;
    creaNumero(&x);
    printf("%d", *x);
}
void creaNumero(int **p)
    {
    int *punt=malloc(sizeof(int));
    *punt=10;
    *p=punt;
    }
