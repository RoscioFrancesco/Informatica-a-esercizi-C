//
//  main.c
//  tde feb 2023
//
//  Created by Francesco Roscio Ricon on 10/11/25.
// Riferimento: Informatica A (061202), TDE febbraio 2023, a.a. 2022/23: https://forms.office.com/e/NvC0Juckch

#include<string.h>
#define N 100
#include <stdio.h>

typedef char Stringa[N];

int controllaacronimo(Stringa acr, Stringa txt);
int main(){


    Stringa acr1="ATM", txt1 = "Azienda Trasporti Milanesi"; //SI
    Stringa acr2="AT", txt2 = "Azienda Trasporti Milanesi";  //NO
    Stringa acr3="ATM", txt3 = "Azienda Trasporti Lombardi"; //NO
    Stringa acr4="ATMK", txt4 = "Azienda Trasporti Milanesi";//NO
    Stringa acr5="ATM", txt5 = "Azienda Trasporti Milanesi Lombardi"; //NO


    // TODO: invocazione della funzione e stampa risultato

    int ris;
    ris=controllaacronimo(acr1, txt1);
    
    if(ris==1)
        printf("SI");
    if(ris==0)
        printf("NO");
}
int controllaacronimo(Stringa acr, Stringa txt)
    {
    int i, k=1;
    int flag=1;
    int lentxt;
    lentxt=strlen(txt);
    int lenacr;
    lenacr=strlen(acr);
    int contaspazi=0;
    for(i=0; i<lentxt; i++)
        {
            if(txt[i]==' ')
                contaspazi++;
        }
    if(contaspazi+1!=lenacr)
        return 0;
    for(i=0; i<lentxt && flag==1; i++)
        {
            if(acr[0]!=txt[0])
            {
                flag=0;
                return 0;
            }
            
            if(txt[i]==' ')
                {
                    if(acr[k]!=txt[i+1])
                    {
                        flag=0;
                    }
                    k++;
                }
        }
    if(flag==1) return 1;
    return 0;
    }

// TODO: funzione (� vietato stampare nella funzione)
