//
//  main.c
//  copia di array senza lasciare buchi
//
//  Created by Francesco Roscio Ricon on 09/10/25.
//Chiedere all’utente di inserire un array di interi (di dimensione definita
//precedentemente) e quindi un numero intero t. Il programma quindi:
//• salva gli elementi inseriti in un vettore v1.
//• Copia tutti gli elementi di v1 che sono maggiori di n in un secondo vettore v2.
//• La copia deve avvenire nella parte iniziale di v2, senza lasciare buchi.


#include <stdio.h>

int main() {
    int v[100], n, i, soglia, v2[100], q, l;
    do{
        printf("Quanti numeri vuoi inserire?");
        scanf("%d", &n);
    } while(n<0 || n>100);
    printf("Inserire caratteri\n");
    for(i=0; i<n; i++)
    {
        scanf("%d", &v[i]);
    }
    printf("Inserisci il carattere di soglia\n");
    scanf("%d", &soglia);
    q=0;
    for(i=0; i<n; i++)
    {
        if(v[i]>soglia)
        {
            v2[q]=v[i];
            q++;
        }
    }
    l=q;
    for(q=0; q<l; q++)
        printf("%d\n", v2[q]);

}
