//  Created by Francesco Roscio Ricon on 08/11/25.


#include <stdio.h>
#define N 100
typedef struct
{
    int a;
    int b;
}coppia;

void funzioneformacoppie(int vet[], coppia *tuttelecoppie, int len, int *counter);
int dppqp(int a, int b);
int main() {
    int len, vet[N], i, ris[N];
    coppia tuttelecoppie[N];
    int counter=0;
    printf("Quanti numeri vuoi inserire?");
    scanf("%d", &len);
    for(i=0; i<len; i++)
        {
            scanf("%d", &vet[i]);
        }
    vet[i+1]=0;
    funzioneformacoppie(vet, tuttelecoppie, len, &counter);
    for(i=0;i<counter; i++)
        {
            if(dppqp(tuttelecoppie[i].a, tuttelecoppie[i].b)==1)
            printf("\n%d,%d\n", tuttelecoppie[i].a, tuttelecoppie[i].b);
        }
    
}
int dppqp (int a, int b) {
int x = 2, p = a*b;
if ( a%2 || b%2 || a==b ) // Se uno dei parametri è dispari o sono uguali: -> 0
return 0;
while ( x*x < p ) // Prova i quadrati di tutti i numeri pari iniziando
x += 2; // da 2 e fino a raggiungere o superare a*b
return x*x == p; // Se l’ultimo quadrato supera p: -> 0, altrimenti: -> 1
} // r
void funzioneformacoppie(int vet[], coppia *tuttelecoppie, int len, int *counter)
    {
    int i=0;
    for(i=0;i<len; i++)
        {
                        tuttelecoppie[*counter].a=vet[i];
                        tuttelecoppie[*counter].b=vet[i+1];
                        (*counter)++;
                    
                }
        }
    

