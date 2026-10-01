//
//  main.c
//  es 1 10mz
//
//  Created by Francesco Roscio Ricon on 10/03/26.
//

#include <stdio.h>
#include <stdlib.h>
int * creavett(int *len);
void vett2(int **punt, int *len);
void stampa(int array[], int len);
int main() {
    int len=5;
    int *punt=NULL;
    vett2(&punt, &len);
    stampa(punt,5);
}
//int * creavett(int *len)
//    {
//    int *vett=malloc(sizeof(int)*(*len));
//    for(int i=0; i<*len; i++)
//        {
//            vett[i]=i+1;
//        }
//    return vett;
//    }
void vett2(int **punt2, int *len)
    {
        int *vett=malloc(sizeof(int)*(*len));
    for(int i=0; i<*len; i++)
        {
            vett[i]=i;
        }
    *punt2=vett;
    }
void stampa(int array[], int len)
    {
    for(int i=0; i<len; i++)
        {
            printf("%d-->", array[i]);
        }
    }
