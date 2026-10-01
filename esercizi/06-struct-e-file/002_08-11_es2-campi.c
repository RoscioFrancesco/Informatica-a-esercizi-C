//  Created by Francesco Roscio Ricon on 08/11/25.

#include <stdio.h>
typedef int VT[10];
typedef struct{
    int a;
    int b;
}struttura;
void funzione(int a[], struttura *x1, int len_A);
int main()
{
    int i;
    VT A;
    for(i=0; i<10; i++)
    {
        scanf("%d", &A[i]);
    }
    struttura x1;
    x1.a=0;
    x1.b=0;
    funzione(A, &x1, 10);
    printf("%d\n", x1.a);
    printf("\n%d", x1.b);
}
void funzione(int a[], struttura *x1, int len_A) // sarebbe andato anche bene (VT a)
    {
    int i;
    for(i=0; i<len_A; i++)
        {
            if(i%2==0)
                x1->a=x1->a+a[i];
                else
                    x1->b=x1->b+a[i];
        }
    }
