//
//  main.c
//  es 4
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

#include<stdio.h>
#include<string.h>
#define N 3
#define M 100


/*
Esempio di esecuzione con le variabili fornite
     frutta (1.5)     salumi (15.0)     salumi (22.2)
    vestiti (25.3)      pesce (10.2) casalinghi (7.2)
      pesce (14.2)     frutta (2.0)      pesce (17.2)
errori da sistemare: 2
la matrice viene sistemata:
     frutta (1.5)     salumi (15.0)      pesce (10.2)
    vestiti (25.3)      pesce (10.2) casalinghi (7.2)
      pesce (14.2)     frutta (2.0)     frutta (1.5)
 la bancarella di pesce piu economica costa: pesce (10.2)
 la bancarella piu economica costa: frutta (1.5)
*/


typedef char Stringa[M];
typedef struct {
    Stringa tipo;
    float costoKg; } Bancarella;
typedef char Stringa[M];
typedef struct {
    Bancarella mercato[N][N];
    int dimensioniReali; } MercatoRionale;




MercatoRionale inizializza();
void stampa(MercatoRionale m);

int controllaDisposizione(MercatoRionale m);
MercatoRionale f(MercatoRionale m);
int main()
{
    MercatoRionale m;


    Bancarella pesce, noPesce;
    int res, n=3;
    float costo;


    m=inizializza();
    stampa(m);


    printf("%d", controllaDisposizione(m));

    m=f(m);

    stampa(m);


    return 0;
}




MercatoRionale inizializza()
{
    MercatoRionale m;
    m.dimensioniReali=3;
    strcpy(m.mercato[0][0].tipo, "frutta"); m.mercato[0][0].costoKg = 1.5;
    strcpy(m.mercato[0][1].tipo, "salumi"); m.mercato[0][1].costoKg = 15.0;
    strcpy(m.mercato[0][2].tipo, "salumi"); m.mercato[0][2].costoKg = 22.2;
    strcpy(m.mercato[1][0].tipo, "vestiti"); m.mercato[1][0].costoKg = 25.3;
    strcpy(m.mercato[1][1].tipo, "pesce"); m.mercato[1][1].costoKg = 10.2;
    strcpy(m.mercato[1][2].tipo, "casalinghi"); m.mercato[1][2].costoKg = 7.2;
    strcpy(m.mercato[2][0].tipo, "pesce"); m.mercato[2][0].costoKg = 14.2;
    strcpy(m.mercato[2][1].tipo, "frutta"); m.mercato[2][1].costoKg = 2.0;
    strcpy(m.mercato[2][2].tipo, "pesce"); m.mercato[2][2].costoKg = 17.2;
    return m;
}


void stampa(MercatoRionale m)
{
    int i,j;
    printf("\n");
    for(i = 0; i<m.dimensioniReali; i++)
    {
        for(j = 0; j<m.dimensioniReali; j++)
            printf(" %10s (%2.1f)", m.mercato[i][j].tipo, m.mercato[i][j].costoKg);
        printf("\n");
    }
}

int controllaDisposizione(MercatoRionale m)
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(c==N-r-1)
                        {
                            if(strcmp(m.mercato[r][c].tipo, "pesce")!=0)
                                count++;
                        }
                    else
                        {
                            if(strcmp(m.mercato[r][c].tipo, "pesce")==0)
                                count++;
                        }
                }
        }
    return count;
    }
MercatoRionale f(MercatoRionale m)
    {
    int r_pesce=0;
    int c_pesce=0;
    float pesce_basso=0;
    int hasprec=0;
    int r_basso=0;
    int c_basso=0;
    float basso=m.mercato[0][0].costoKg;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(hasprec==0)
                        {
                            pesce_basso=m.mercato[r][c].costoKg;
                        }
                    if(strcmp(m.mercato[r][c].tipo, "pesce")==0)
                        {
                            if(m.mercato[r][c].costoKg<pesce_basso)
                                pesce_basso=m.mercato[r][c].costoKg;
                            r_pesce=r;
                            c_pesce=c;
                        }
                    if(basso>m.mercato[r][c].costoKg)
                        {
                            basso=m.mercato[r][c].costoKg;
                            r_basso=r;
                            c_basso=c;
                        }
                }
        }
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(c==N-r-1)
                        {
                            if(strcmp(m.mercato[r][c].tipo, "pesce")!=0)
                                {
                                    m.mercato[r][c]=m.mercato[r_pesce][c_pesce];
                                }
                        }
                    else
                        {
                            if(strcmp(m.mercato[r][c].tipo, "pesce")==0)
                                {
                                    m.mercato[r][c]=m.mercato[r_basso][c_basso];
                                }
                        }
                }
        }
    return m;
    }
