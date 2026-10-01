//  Created by Francesco Roscio Ricon on 02/11/25.

#include <stdio.h>
#define N 100
int leggiInt();
void leggiArrayInt(int array[], int dimensioni);
void subpow(int len_array, int pezzo, int start, int vet[]);
void foo(int len_array, int vet[], int start);
void stampaArray(int len, int vet[]);
int main() {
    int i, array[N], dim, start, pezzo;
    printf("Inserire dimensioni array");
    scanf("%d", &dim);
    leggiArrayInt(array, dim);
    printf("Inserire punto di partenza");
    scanf("%d", &start);
    foo(dim, array, start);
    stampaArray(dim, array);
    
    
}
int leggiInt(int i)
    {
    int num;
    printf("Inserisci il numero %d:\n", i+1);
    scanf("%d", &num);
    return num;
    }
//void leggiIntN(int vet[])
//    {
//    vet[0]=1;
//    vet[1]=leggiInt();
//    }
void leggiArrayInt(int array[], int dimensioni)
    {
    int i;
    for(i=0; i<dimensioni; i++)
        {
            array[i]=leggiInt(i);
        }
    }
void subpow(int len_array, int pezzo, int start, int vet[])
    {
    int i;
    for(i=start; i<len_array && i<pezzo+start; i++)
        {
            vet[i] = (vet[i])*(vet[i]);
        }
    }
void foo(int len_array, int vet[], int start)
    {
    subpow(len_array, len_array-start ,start, vet);
    }
void stampaArray(int len, int vet[])
    {
    int i;
    for(i=0; i<len; i++)
        printf("%d  ", vet[i]);
    }
