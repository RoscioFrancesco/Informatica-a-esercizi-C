//
//  main.c
//  ***3 3mz
//
//  Created by Francesco Roscio Ricon on 03/03/26.
//

//Hai due strutture così:
//E tre livelli di puntatori:
//Nodo *n1;
//Nodo **p1;
//Nodo ***pp1;
//Scrivi:
//void scambiaStrutture(Nodo ***a, Nodo ***b);

#include <stdio.h>
typedef struct {
    int valore;
} Nodo;
// scambiare i valori interni alle strutture
void scambia(Nodo ***a, Nodo ***b);
int main()
    {
    Nodo a;
    a.valore=1;
    Nodo b;
    b.valore=2;
    Nodo *n1=&a;
    Nodo *n2=&b;
    Nodo **p1=&n1;
    Nodo **p2=&n2;
    Nodo ***pp1=&p1;
    Nodo ***pp2=&p2;
    printf("a.valore=%d", a.valore);
    printf("\nb.valore=%d\n\n", b.valore);
    printf("(***pp1).valore: %d", (***pp1).valore);
    printf("\n(***pp2).valore: %d", (***pp2).valore);
    printf("\n chiamata \n");
    scambia(pp1, pp2);
    printf("a.valore=%d", a.valore);
    printf("\nb.valore=%d\n\n", b.valore);
    printf("(***pp1).valore: %d", (***pp1).valore);
    printf("\n(***pp2).valore: %d", (***pp2).valore);
    }
void scambia(Nodo ***a, Nodo ***b)
    {
    Nodo temp;
    temp=***a;
    ***a=***b;
    ***b=temp;
    }
