//  Created by Francesco Roscio Ricon on 07/03/26.

#include <stdio.h>
#include <stdlib.h>
void f(int vett[], int dim, int **pp, int *newdim);
int main() {
    int *vett=malloc(sizeof(int)*2);
    vett[0]=1;
    vett[1]=2;
    int *new=NULL;
    int newdim=0;
    f(vett, 2, &new,&newdim);
    for(int i=0; i<newdim; i++)
        {
            printf("%d-->", new[i]);
        }
}
void f(int vett[], int dim, int **pp, int *newdim)
    {
    int *new=malloc(sizeof(int)*2*dim);
    for(int i=0; i<dim; i++)
        {
            new[i]=vett[i];
        }
    *newdim=2*dim;
    *pp=new;
    }
