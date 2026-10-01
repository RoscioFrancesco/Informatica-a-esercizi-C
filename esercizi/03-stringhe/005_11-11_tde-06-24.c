//
//  main.c
//  tde 06 24
//
//  Created by Francesco Roscio Ricon on 11/11/25.
//

#include <stdio.h>
#include <string.h>
#define N 100
void analizzaStringa(char input_string[], char solo_maiuscoli[], int len_stringainput, int *somma);
int main() {
    char input_string[] = "aBBcD1eF2g3HF";
    char solo_maiuscoli[N];
    int len_stringa=strlen(input_string);
    int somma=0;
    analizzaStringa(input_string, solo_maiuscoli, len_stringa, &somma);
    printf("%d", somma);
    printf("%s", solo_maiuscoli);
}
void analizzaStringa(char input_string[], char solo_maiuscoli[], int len_stringainput, int *somma)
    {
    int i=0, k=0;
    int scorrisolo_maiuscoli=0;
    int flag=0;
    for(i=0; i<len_stringainput; i++)
        {
            if(input_string[i]<='Z' && input_string[i]>='A')
                {
                    for(k=i; k<len_stringainput; k++)
                        {
                            if(input_string[i]==input_string[k])
                                {
                                    flag=1;
                                }
                        }
                    if(flag==0)
                    {
                        solo_maiuscoli[scorrisolo_maiuscoli]=input_string[i];
                        scorrisolo_maiuscoli++;
                    }
                    
                }
            flag=0;
        }
    solo_maiuscoli[scorrisolo_maiuscoli]='\0';
    for(i=0; i<len_stringainput; i++)
        {
            if(input_string[i]<='9' && input_string[i]>='0')
                {
                    *somma=*somma+ (input_string[i]-'0');
                }
        }
}
