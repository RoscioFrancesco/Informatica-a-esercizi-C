//  Created by Francesco Roscio Ricon on 26/10/25.


#include <stdio.h>

int main() {
    int a, b, c;
    int *pa, *pb, *pc;
    pa= &a;
    pb= &b;
    pc= &c;
    printf("Inserire la prima variabile\n");
    scanf("%d", &a);
    printf("Inserire la seconda variabile\n");
    scanf("%d", &b);
    printf("valore di a prima dello scambio %d\n",*pa);
    printf("valore di b prima dello scambio %d\n",*pb);
    c= *pa;
    a= *pb;
    b= *pc;
    printf("valore di a dopo lo scambio %d\n",*pa);
    printf("valore di b dopo lo scambio %d\n",*pb);
    
    
}
