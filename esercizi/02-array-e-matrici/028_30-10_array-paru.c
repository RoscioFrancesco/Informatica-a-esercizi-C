//  Created by Francesco Roscio Ricon on 30/10/25.

#include <stdio.h>
#define N 100
int ritorna_pari (int vet[], int len_x, int vf_pari[]);
int main() {
    int vet_tot[N], l_tot, vet_pari[N], l_pari, i;
    printf("Quanti elementi vuoi inserire?");
    scanf("%d", &l_tot);
    for(i=0; i<l_tot; i++)
    {
        printf("Inserisci il carattere numero %d", i+1);
        scanf("%d", &vet_tot[i]);
    }
    l_pari = ritorna_pari(vet_tot, l_tot, vet_pari);
    for(i=0; i<l_pari; i++)
        {
            printf("%d  ", vet_pari[i]);
        }
    
}
int ritorna_pari (int vet[], int len_x, int vf_pari[])
    { // ora voglio fare la copia senz abuchi
    int i, len_pari=0;
    for(i=0; i<len_x; i++)
        {
            if(vet[i]%2 == 0)
                {
                    vf_pari[len_pari]=vet[i];
                    len_pari++;
                }
        }
        return len_pari;
    }
