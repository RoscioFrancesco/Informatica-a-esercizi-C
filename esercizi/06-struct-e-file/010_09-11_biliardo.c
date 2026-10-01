//  Created by Francesco Roscio Ricon on 09/11/25.


#include <stdio.h>
#define R 20
#define C 10
#define N 100
typedef struct{
    int x_ora;
    int y_ora;
}posizione_palla;
void stampamatrice(int M[R][C], posizione_palla *p, posizione_palla p_neltempo[], int len_array);
int direzione_migliore (posizione_palla *p, int M[R][C], posizione_palla p_neltempo[], int *contatore);
int spostamento(posizione_palla *p, int M[R][C], int angolo, posizione_palla p_neltempo[]);
void inizializzamatrice(int M[R][C]);
void rimbalzol1 (int M[R][C], int *sp_r, int *sp_c);
int condizionerimbalzo(posizione_palla *p, int M[R][C], int *sp_r, int *sp_c);
int main(int argc, const char * argv[]) {
    int angolo_migliore;
    int len_array;
    posizione_palla p;
    posizione_palla p_neltempo[N];
    int M[R][C];
    printf("Inserire x palla");
    scanf("%d", &p.x_ora);
    printf("Inserire y palla");
    scanf("%d", &p.y_ora);
    inizializzamatrice(M);
    angolo_migliore=direzione_migliore(&p, M, p_neltempo, &len_array);
    stampamatrice(M, &p, p_neltempo, len_array);
}
void direzioni(int angolo, int *sp_r, int *sp_c)
{
    if(angolo == 45)   { *sp_r = -1; *sp_c = +1; }
    if(angolo == 135)  { *sp_r = -1; *sp_c = -1; }
    if(angolo == 225)  { *sp_r = +1; *sp_c = -1; }
    if(angolo == 315)  { *sp_r = +1; *sp_c = +1; }
}
void stampamatrice(int M[R][C], posizione_palla *p, posizione_palla p_neltempo[], int len_array)
    {
    int r, c, i, flag=0;
    for(r=0; r<R; r++)
        {
            for(c=0; c<C; c++)
                {
                    for(i=0; i<len_array;i++)
                    {
                        if(r==p_neltempo[i].x_ora&&c==p_neltempo[i].y_ora)
                            flag=1;
                        
                    }
                    if(flag==1)
                        printf("1");
                    else printf("0");
                }
            flag=0;
            printf("\n");
        }
    }
void inizializzamatrice(int M[R][C])
{
int r, c;
for(r=0; r<R; r++)
    {
        for(c=0; c<C; c++)
            {
                M[r][c]=0;
            }
    }
}
void rimbalzol1 (int M[R][C], int *sp_r, int *sp_c)
    {
        if (*sp_r<0 && sp_c>0)
            {
                *sp_r=-(*sp_r);
            }
        if (*sp_r>0 && sp_c<0)
            {
            *sp_c=-(*sp_c);
            }
    }
void rimbalzol2 (int M[R][C], int *sp_r, int *sp_c)
{
    if (*sp_r>0 && sp_c<0)
        {
            *sp_c=-(*sp_c);
        }
    if (*sp_r<0 && sp_c>0)
        {
        *sp_c=-(*sp_c);
        }
}
void rimbalzol3 (int M[R][C], int *sp_r, int *sp_c)
{
    if (*sp_r>0 && sp_c>0)
        {
            *sp_r=-(*sp_r);
        }
    if (*sp_r>0 && sp_c<0)
        {
        *sp_r=-(*sp_r);
        }
}
void rimbalzol4 (int M[R][C], int *sp_r, int *sp_c)
{
    if (*sp_r<0 && sp_c>0)
        {
            *sp_c=-(*sp_c);
        }
    if (*sp_r>0 && sp_c>0)
        {
        *sp_c=-(*sp_c);
        }
}
int condizionerimbalzo(posizione_palla *p, int M[R][C], int *sp_r, int *sp_c)
    {
    int contarimbalzi=0;
    if(p->x_ora==C-1)
        {
            rimbalzol4(M, sp_r, sp_c);
            contarimbalzi++;
        }
    if(p->x_ora==0)
        {
            rimbalzol1(M, sp_r, sp_c);
            contarimbalzi++;
        }
    if(p->y_ora==0)
        {
            rimbalzol1(M, sp_r, sp_c);
            contarimbalzi++;
        }
    if(p->y_ora==R-1)
        {
            rimbalzol3(M, sp_r, sp_c);
            contarimbalzi++;
        }
    return contarimbalzi;
    }
//int spostamento(posizione_palla *p, int M[R][C], int angolo, posizione_palla p_neltempo[])
//    {
//    int sp_r, sp_c;
//    direzioni(angolo,&sp_r, &sp_c);
//    int counter=0;
//    int contarimbalzi=0;
//    do{
//        int counter=0;
//        int spr_temp=sp_r;
//        int spc_temp=sp_c;
//        do{
//            direzioni(angolo, &spr_temp, &spc_temp);
//            counter++;
//            p_neltempo[counter].x_ora=spc_temp;
//            p_neltempo[counter].y_ora=spr_temp;
//        }while(p->x_ora==0 || p->y_ora==0 || p->x_ora==C || p->y_ora==R);
//        contarimbalzi=condizionerimbalzo(p, M, &sp_r, &sp_c);
//    }while(contarimbalzi<=4);
//    return counter;
//    }
int spostamento(posizione_palla *p, int M[R][C], int angolo, posizione_palla p_neltempo[])
{
    int sp_r, sp_c;
    direzioni(angolo, &sp_r, &sp_c);

    int rimbalzi = 0;
    int counter = 0;

    while(rimbalzi < 4)
    {
        /* Controllo rimbalzo sui bordi */
        if(p->x_ora + sp_r < 0 || p->x_ora + sp_r >= R)
        {
            sp_r = -sp_r;   // rimbalzo verticale
            rimbalzi++;
        }

        if(p->y_ora + sp_c < 0 || p->y_ora + sp_c >= C)
        {
            sp_c = -sp_c;   // rimbalzo orizzontale
            rimbalzi++;
        }

        /* Aggiorno posizione palla */
        p->x_ora += sp_r;
        p->y_ora += sp_c;

        /* Salvo la posizione nel percorso */
        p_neltempo[counter].x_ora = p->x_ora;
        p_neltempo[counter].y_ora = p->y_ora;

        counter++;
    }

    return counter;  // lunghezza del percorso
}
int direzione_migliore (posizione_palla *p, int M[R][C], posizione_palla p_neltempo[], int *contatore)
    {
    int angoli[4]={45, 135, 225, 315};
    int i=0;
    int max=-1;
    int angolo_migliore;
    for(i=0; i<4; i++)
        {
            if(spostamento(p, M, angoli[i], p_neltempo)>max)
                {
                    max=spostamento(p, M, angoli[i],0);
                    angolo_migliore=angoli[i];
                }
        }
    *contatore=max;
    return angolo_migliore;
    }

