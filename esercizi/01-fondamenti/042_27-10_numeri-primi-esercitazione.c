//  Created by Francesco Roscio Ricon on 27/10/25.

#include <stdio.h>
int leggiNumeroNaturale();
int sommaDivisori(int);
int numeroPerfetto(int, int *);
int main() {
    int num, flag, res; // res continua ad esistere, uso puntatore per farmi ridare il secondo risultato della funzione
    num = leggiNumeroNaturale();
    flag= numeroPerfetto(num, &res);
    if (flag)
    {
        printf("numero perfetto");
    }
    else
    {
            if (res>0) printf("Abbondante");
            if (res<0) printf("Difettivo");
    }
}
int leggiNumeroNaturale()
{
        int n;
        do
            {
                scanf("%d", &n);
            }while(n<0);
        return n;
    }
int sommaDivisori(int n)
{
int i; // lo uso per scorrere i numeri fino a n/2 o anche meglio fino alla radice di n
int somma=0;
for(i=1; i<=n; i++)
    {
        if(n%i==0)
            somma = somma + i;
    }
    return somma;
}
int numeroPerfetto(int numero, int *p_res)  // prende come variabile il nuemro e l'indirizzo a cui punta il puntatore ()punta a res.
    {
        int somma;
        somma = sommaDivisori(numero);
        *p_res = somma - numero - numero;//(per puntare la cella di memoria nel main, che non viene distrutta, mentre il puntatore viene distrutto, tuttavia ho già copiato in res) per capire se il numero è abbondante o difettivo (sto sottrandeo alla somma dei divisori propri il numero)
        return somma-numero == numero; // per capire se è perfetto è espressione boolana 0 o 1
    }

