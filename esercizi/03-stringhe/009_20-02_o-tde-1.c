//  Created by Francesco Roscio Ricon on 20/02/26.
#include <string.h>
#include <stdio.h>
void f(char parola[]);
int main()
    {
    char parola[50];
    strcpy(parola, "supercalifragilistichespiralidoso");
    f(parola);
    printf("%s", parola);
    }

void f(char parola[])
    {
    char appoggio[50];
    int j=0;
    for(int i=0; i<strlen(parola); i++)
        {
            if(parola[i]!='c')
                {
                    appoggio[j]=parola[i];
                    j++;
                }
        }
    appoggio[j]='\0';
    strcpy(parola, appoggio);
    }
