//  Created by Francesco Roscio Ricon on 08/11/25.

#include <stdio.h>
#define N 100
typedef struct{
    int numero_maglia;
    char nome[N];
}Giocatore;
typedef struct {
    int matricola;
    char nome[N];
    char citta[N];
    Giocatore elenco_giocatori[11];
}Squadra;
typedef struct
{
    Squadra elenco_squadre[6];
}Torneo;
void portieri (Torneo *t, int num_sq);
int main ()
{
    Torneo t;
    portieri(&t, 6);
    // affinchè babbia un senso devo popolare torne, squadra,
}
void portieri (Torneo *t, int num_sq)
{
    int i,j;
    for(i=0; i<num_sq; i++)
        {
            for(j=0; j<11; j++)
            {
                t->elenco_squadre[i].elenco_giocatori[j].numero_maglia==1;
                printf("%s",t->elenco_squadre[i].elenco_giocatori[j].nome);
            }
        }
}
