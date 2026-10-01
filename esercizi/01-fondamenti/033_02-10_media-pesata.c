//  Created by Francesco Roscio Ricon on 02/10/25.

#include <stdio.h>

int main()
{
    int i,  numero_voti;
    float voto, vpp, somma_pesi, peso, media, somma_vpp;
    printf("Quanti voti vuoi inserire?");
    scanf("%d", &numero_voti);
    do {
        printf("\nInserisci un nuovo voto\n");
        scanf("%f", &voto);
        printf("\nInserisci un nuovo peso\n");
        scanf("%f", &peso);
        vpp = voto * peso;
        somma_vpp = somma_vpp+ vpp;
        voto = 0;
        somma_pesi = somma_pesi + peso;
        numero_voti = numero_voti - 1;
    }   while(numero_voti >= 0);
    media = somma_vpp*1.0/ somma_pesi;
    printf("%f", media);

}
