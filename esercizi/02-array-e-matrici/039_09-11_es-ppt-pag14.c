//  Created by Francesco Roscio Ricon on 09/11/25.

#include<stdio.h>
#define N 5
void riordina (int u[], int v[], int len_u, int len_v);
int main()
{
int u[N] = {4,1,3,7,0}, v[N] = {1,6,8,4};
    int len_u=5, len_v=4;
    int i=0;
    for(i=0; i<len_u;i++)
        {
            printf("%d", u[i]);
        }
    printf("\n");
    for(i=0; i<len_u;i++)
        {
            printf("%d", v[i]);
        }
    riordina(u, v, len_u, len_v);
    for(i=0; i<len_u; i++)
        {
            printf("%d", u[i]);
        }

// TODO stampa u dopo invocazione
return 0;
}
void riordina (int u[], int v[], int len_u, int len_v)
{
    int scorri_u=0, scorri_v=0, flag=1, i;
    int intermedio[N], contatore=0, len_inter, scorri_inter;
    for(scorri_u=0; scorri_u<len_u; scorri_u++)
        {
            for(scorri_v=0; scorri_v<len_v && flag==1; scorri_v++)
                {
                    if(u[scorri_u]==v[scorri_v])
                        {
                            flag=0;
                        }
                }
            if(flag==1)// qundi carattere mai incontrato
                {
                    intermedio[contatore]=u[scorri_u];
                    contatore++;
                }
            flag=1;
        }
    len_inter=contatore;
    flag=1;
    for(scorri_u=0; scorri_u<len_u; scorri_u++)
        {
            for(scorri_inter=0; scorri_inter<len_inter && flag==1; scorri_inter++)
                {
                    if(u[scorri_u]==intermedio[scorri_inter])
                        {
                            flag=0;
                        }
                }
            if(flag==1)
                {
                    intermedio[contatore]=u[scorri_u];
                    contatore++;
                }
            flag=1;
        }
    for(i = 0; i < len_u; i++)
        u[i] = intermedio[i];
    
}
