//  Created by Francesco Roscio Ricon on 18/11/25.




#include <math.h>
#include <stdio.h>
typedef struct {
    double Re, Im;
    } Complex;
Complex MaxComplessoModulo(Complex * array, int i, int len, int *segna, double max);

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
    double max=Modulo(array);
    massimo=MaxComplessoModulo(array,i,num, &segna, max);
    printf("%lf\n", array[segna].Re);
    printf("%lf", array[segna].Im);
    
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
Complex MaxComplessoModulo(Complex * array, int i, int len, int *segna, double max)
    {
        if(i==len)
            return array[*segna];
    if(Modulo(&array[i])>max)
        {
            max=Modulo(&array[i]);
            *segna=i;
        }
    return MaxComplessoModulo(array, i+1, len, segna, max);
        
    }
