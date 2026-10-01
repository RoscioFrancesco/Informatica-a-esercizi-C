//  Created by Francesco Roscio Ricon on 26/10/25.

#include <stdio.h>
int operazione_di_potenza(int *, int *); // qs è il prototipo

int main() {
    
    int base, esp, finale;
    do{
        printf("Inserire la base");
        scanf("%d", &base);
        printf("Inserire l'esponente");
        scanf("%d", &esp);
        printf("\n");
    } while(base==0 && esp==0);
    finale = operazione_di_potenza(&esp, &base);
    printf("%d", finale);
    printf("\n");
    return 0;
}

int operazione_di_potenza(int *e, int *b)
    {
    int ris=1;
    int i;
    for(i=0; i<*e; i++)
        {
            ris = ris * *b;
        }
    return ris;
    }


