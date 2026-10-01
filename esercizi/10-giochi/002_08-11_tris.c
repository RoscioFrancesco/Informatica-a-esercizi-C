//  Created by Francesco Roscio Ricon on 08/11/25.

typedef struct {
    int turno;    // 1 se è il turno del giocatore 1, 2 se è il turno del giocatore 2
    int griglia[3][3];    // contiene tutti 0 all'inizializzazione, 1 e 2 per i giocatori 1 e 2
} Tris;
void mossa(Tris *a);
#include <stdio.h>
void inizializzazione (Tris *a);
void stampa(Tris *a);
int controlla_riga(Tris *a, int val);
int controlla_colonna(Tris *a, int val);
int controlla_d1(Tris *a, int val);
int controlla_d2(Tris *a, int val);
int giocatore(Tris *a);
int partitafinita(Tris *a, int *vittoria1, int *vittoria2);
int main() {
    int vittoria_1=0, vittoria_2=0;
    Tris a;
    a.turno=1;
    inizializzazione(&a);
    stampa(&a);
    do {
        printf("I giocatore %d scelga la mossa del turno %d", giocatore(&a), a.turno);
        mossa(&a);
        printf("\n");
        stampa(&a);
    } while (partitafinita(&a, &vittoria_1, &vittoria_2)==0);
    if(vittoria_1==1)
        printf("Ha vinto il giocatore 1");
    if(vittoria_2==1)
        printf("Ha vinto il giocatore 2");
    if(vittoria_1==0&&vittoria_2==0)
        printf("pareggio");
    
    
}
void inizializzazione (Tris *a)
    {
    int r=0, c=0;
    for(r=0;r<3;r++)
        {
            for(c=0; c<3; c++)
            {
                a->griglia[r][c]=0;
            }
        }
    }
void stampa(Tris *a)
    {
    int r=0, c=0;
    for(r=0;r<3;r++)
        {
            for(c=0; c<3; c++)
            {
                printf("%d ",a->griglia[r][c]);

            }
            printf("\n");
        }
    }
void mossa(Tris *a)
    {
    int riga;
    int colonna;
    do{
        printf("Inserire la riga\n");
        scanf("%d", &riga);
        printf("Inserire la colonna\n");
        scanf("%d", &colonna);
        if(riga>=0 && riga<3 && colonna>=0 && colonna<3)
        {if(a->turno%2==1)
            a->griglia[riga][colonna]=1;
            if(a->turno%2==0)
                a->griglia[riga][colonna]=2;
            a->turno++;
        }
        if(!(riga>=0 && riga<3 && colonna>=0 && colonna<3))
            printf("Mossa non valida\n");
    }while(!(riga>=0 && riga<=3 && colonna>=0 && colonna<=3));
    }
int partitafinita(Tris *a, int *vittoria1, int *vittoria2)
    {
    int flag=0;
    if(a->turno==9)
        flag=1;
    if(controlla_riga(a, 1) || controlla_colonna(a, 1) || controlla_d1(a, 1) || controlla_d2(a, 1))
    {
        flag=1;
        *vittoria1=1;
    }
    if(controlla_riga(a, 2) || controlla_colonna(a, 2) || controlla_d1(a, 2) || controlla_d2(a, 2))
    {
        flag=1;
        *vittoria2=1;
    }
    return flag; // flag =1 se la partita è finita
    }
int controlla_riga(Tris *a, int val)
{
    int r=0,c=0;
    int risultato=0;
    for(r=0; r<3;r++)
        {
                    if(a->griglia[r][c]==val && a->griglia[r][c+1]==val && a->griglia[r][c+2]==val)
                        risultato=1;
        }
    return risultato;
}
int controlla_colonna(Tris *a, int val)
{
    int r=0,c=0;
    int risultato=0;
    for(c=0; c<3;c++)
        {
                    if(a->griglia[c][r]==val && a->griglia[r+1][c]==val && a->griglia[r+2][c]==val)
                        risultato=1;
        }
    return risultato;
}
int controlla_d1(Tris *a, int val)
{
    int r=0,c=0;
    int risultato=0;
    if(a->griglia[c][r]==val && a->griglia[r+1][c+1]==val && a->griglia[r+2][c+2]==val)
                        risultato=1;
    return risultato;
}
int controlla_d2(Tris *a, int val)
{
    int r=0,c=2;
    int risultato=0;
    if(a->griglia[c][r]==val && a->griglia[r+1][c-1]==val && a->griglia[r+2][c-2]==val)
                        risultato=1;
    return risultato;
}
int giocatore(Tris *a)
    {
    int i;
    int giocatore;
    int turno=a->turno;
    if(turno%2==1)
        giocatore=1;
    if(turno%2==0)
        giocatore=2;
    return giocatore;
    }
