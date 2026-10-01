//
//  main.c
//  trovare lo zero
//
//  Created by Francesco Roscio Ricon on 16/11/25.
//
#include <math.h>
#include <stdio.h>
typedef struct {
    int grado;
    float coefficiente;
}monomio;
double calcola_valore (monomio polinomio[], float x_n, int grad_max);
double trova_zero(monomio polinomio[], float x_a, float x_b, int grad_max, double epsilon);
int main() {
    int i;
    int grado;
    double epsilon;
    float x_a, x_b;
    do{
        printf("L'utente inserisca il grado massimo del polinomio");
        scanf("%d", &grado);
    }while(grado>10);
    monomio polinomio[11];
    for(i=0; i<=grado; i++)
        {
            printf("Inserire il coefficiente di x^%d", i);
            polinomio[i].grado=i;
            scanf("%f", &polinomio[i].coefficiente);
        }
    do{
        printf("Inserire la x del primo punto");
        scanf("%f", &x_a);
        printf("Inserire la x del secono punto");
        scanf("%f", &x_b);
    }while(calcola_valore(polinomio, x_a, grado)*calcola_valore(polinomio, x_b, grado)>0);
    printf("Inserire approssimazione massima epsilon");
    scanf("%lf", &epsilon);
    double zero;
    zero=trova_zero(polinomio, x_a, x_b, grado, epsilon);
    printf("%lf", zero);
}
double calcola_valore (monomio polinomio[], float x_n, int grad_max)
    {
    double y_n=0;
    int i=0;
    double potenza=1;
    int scorri_potenza=0;
    for(i=0; i<=grad_max; i++)
        {
            for(scorri_potenza=0; scorri_potenza<=polinomio[i].grado; scorri_potenza++)
                {
                    potenza=potenza*x_n;
                }
            y_n=y_n+potenza*polinomio[i].coefficiente;
            potenza=1;
        }
    return y_n;
    }
double trova_zero(monomio polinomio[], float x_a, float x_b, int grad_max, double epsilon)
    {
    double zero;
    zero=(x_a+x_b)/2.0;
//    if(calcola_valore(polinomio, zero, grad_max)*calcola_valore(polinomio, x_a, grad_max)<0)
//    {
//        x_b=zero;
//    }
//    if(calcola_valore(polinomio, zero, grad_max)*calcola_valore(polinomio, x_b, grad_max)<0)
//    {
//        x_a=zero;
//    }
    double fm = calcola_valore(polinomio, zero, grad_max);
    double fa = calcola_valore(polinomio, x_a, grad_max);

    if(fa * fm < 0)
        x_b = zero;
    else
        x_a = zero;
    if(fabs(calcola_valore(polinomio, x_a, grad_max)-calcola_valore(polinomio, x_b, grad_max))<epsilon || calcola_valore(polinomio, zero, grad_max)==0)
            return zero;
    return(trova_zero(polinomio, x_a, x_b, grad_max, epsilon));
    }
