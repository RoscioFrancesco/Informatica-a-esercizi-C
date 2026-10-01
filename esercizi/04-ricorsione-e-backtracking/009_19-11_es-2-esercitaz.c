//
//  main.c
//  es 2 esercitaz
//
//  Created by Francesco Roscio Ricon on 19/11/25.
//

#include <stdio.h>
int potenze(int base, int esponente);
int main() {
    int base, esp;
    printf("Inserire base");
    scanf("%d", &base);
    printf("Inserire esponente");
    scanf("%d",&esp);
    int ris;
    ris=potenze(base, esp);
    printf("%d", ris);
}
int potenze(int base, int esponente)
    {
        if(esponente==0)
            return 1;
        return base*potenze(base, esponente--);
    }
