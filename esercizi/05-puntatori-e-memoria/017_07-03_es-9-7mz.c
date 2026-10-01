//  Created by Francesco Roscio Ricon on 07/03/26.


#include <stdio.h>
#include <stdlib.h>
void leggiNumeri(int *dim, int **pp, int count, int i, int vett[]);
void stampa(int vett[], int dim);
void f(int *dim, int **pp);
int main() {
    int *pp;
    pp=NULL;
    int dim=2;
    f(&dim, &pp);
    stampa(pp, dim);
    }
void f(int *dim, int **pp)
    {
        int x=-1;
        printf("Inserire valore");
        scanf("%d", &x);
        int *vett=malloc(sizeof(int)*(*dim));
        *pp=vett;
        vett[0]=x;
        leggiNumeri(dim, pp, 0, 1, vett);
    }


void leggiNumeri(int *dim, int **pp, int count, int i, int vett[])
    {
    int x=10;
        while(x!=-1)
        {
            printf("Inserire valore");
            scanf("%d", &x);
            if(x==-1)
                break;
            if(i==*dim)
            {
                int prec=*dim;
                *dim=(*dim)*2;
                int *vett2=malloc(sizeof(int)*(*dim));
                for(int j=0; j<=prec;j++)
                {
                    vett2[j]=vett[j];
                }
                *pp=vett2;
                free(vett);
                vett=vett2;
            }

                vett[i]=x;
                i++;
        }
        
    }
void stampa(int vett[], int dim)
    {
        for(int i=0; i<dim; i++)
            {
                printf("%d-->", vett[i]);
            }
    }
