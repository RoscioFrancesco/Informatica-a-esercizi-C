//  Created by Francesco Roscio Ricon on 10/11/25.
#include <string.h>
#include <stdio.h>
#define N 100000
#include <limits.h>
typedef struct{
    char parola[50];
}array_di_stringhe;
int verificaTD (char s1[], char s2[]);
void funzione(int *numero_parole, int *paroleTD, char stringa[], int len_stringa, array_di_stringhe j[]);
int main() {
    char stringa[N];
    array_di_stringhe j[100000];
    fgets(stringa, N, stdin);
    int lunghezza;
    lunghezza=strlen(stringa);
    int numero_parole;
    int contatoreVD;
    funzione(&numero_parole, &contatoreVD, stringa, lunghezza, j);
    printf("%d", contatoreVD-1);
    printf("\n");
    printf("%d", numero_parole);
}
void funzione(int *numero_parole, int *paroleTD, char stringa[], int len_stringa, array_di_stringhe j[])
    {
    int i, k=0;
    int contaspazi=0;
    int scorri_parola=0;
    int scorri_j=0;
    for(i=0; i<len_stringa; i++)
        {
            if(stringa[i]==' ')
                contaspazi++;
        }
    *numero_parole=contaspazi;
    for(i=0; i<len_stringa; i++)
        {
            if(stringa[i-1]==' '|| i==0)
            {
                do {
                    j[scorri_j].parola[scorri_parola]=stringa[i+k];
                    k++;
                    scorri_parola++;
                }while(stringa[i+k]!='\0' && stringa[i+k]!=' ');
                j[scorri_j].parola[scorri_parola]='\0';
                k=0;
                scorri_j++;
                scorri_parola=0;
            }
        }
    k=0;
    int contatore=0;
    for(i=0; i<contaspazi; i++)
        {
            if(verificaTD(j[i].parola, j[i+1].parola))
                contatore++;
        }
    *paroleTD=contatore;
    }

int verificaTD (char s1[], char s2[])
    {
    int scorri_s1;
    int scorri_s2=0;
    int len1=strlen(s1);
    int len2=strlen(s2);
    for(scorri_s1=0; scorri_s1<len1; scorri_s1++)
        {
            for(scorri_s2=0; scorri_s2<len2; scorri_s2++)
                {
                    if(s1[scorri_s1]==s2[scorri_s2])
                        return 0;
                }
        }
        return 1;
    }
