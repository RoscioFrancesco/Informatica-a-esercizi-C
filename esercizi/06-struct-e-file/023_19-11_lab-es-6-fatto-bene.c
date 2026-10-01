//  Created by Francesco Roscio Ricon on 19/11/25.




#include <math.h>
#include <stdio.h>
typedef struct {
    double Re, Im;
    } Complex;
Complex MaxComplessoModulo(Complex *array, int len);

void GetComplesso (Complex * n);
double Modulo(Complex  *n);
#define N 100
int main() {
    int num;
    Complex array[N];
    printf("Quanti numeri vuoi inserire?");
    scanf("%d", &num);
    int i=0;
    for(i=0; i<num; i++)
        {
            GetComplesso(&array[i]);
        }
    Complex massimo;
    i=0;
    int segna=0;
    double max=Modulo(&array[0]);
    massimo=MaxComplessoModulo(array,num);
    printf("%lf", massimo.Re);
    printf("%lf", massimo.Im);
    
}
void GetComplesso (Complex * n)
    {
    printf("Inserire parte reale del numero complesso");
    scanf("%lf", &n->Re);
    printf("Inserire parte immaginaria del numero complesso");
    scanf("%lf", &n->Im);
}
double Modulo(Complex  *n)
    {
        double mod;
        mod=sqrt((n->Re*n->Re)+(n->Im*n->Im));
        return mod;
    }
Complex MaxComplessoModulo(Complex *array, int len)
{
    Complex migliore;
    migliore.Im=0;
    migliore.Re=0;
    if (len == 0)
        return *array;
    else{
        
        migliore = MaxComplessoModulo(array + 1, len - 1);
        if (Modulo(array) > Modulo(&migliore))
            return *array;
        else
            return migliore;
        }
    
}
