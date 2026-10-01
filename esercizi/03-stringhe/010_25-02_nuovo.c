//
//  main.c
//  nuovo
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_STR_LEN 1000
char f(char parola[]);
char *elimina(char parola[], char lettera, int *len);

int main() {
    char S[MAX_STR_LEN] = "cane,gatto,albero,fiore,acqua,sole,amico,giardino,pietra,vento";
    printf("%s\n",S);
    printf("%c", f(S));
    int len=0;
    char *punt=NULL;
    punt=elimina(S, 'a', &len);
    printf("\n%s", punt);
    
    return 0;
}
char f(char parola[])
    {
    int isto[26]={0};
    for(int i=0; i<strlen(parola); i++)
        {
            isto[parola[i]-'a']++;
        }
    int max=0;
    int j=0;
    for(int i=0; i<26; i++)
        {
            if(isto[i]>max)
                {
                    max=isto[i];
                    j=i;
                }
        }
    return 'a'+j;
    }
char *elimina(char parola[], char lettera, int *len)
    {
    int segna=0;
    char *new=malloc(sizeof(char)*(strlen(parola)+1));
    for(int i=0; i<strlen(parola)-1; i++)
        {
            if(parola[i]==',' && parola[i+1]==lettera)
                {
                    int j=1;
                    while (parola[i+j]!='0') {
                        if(parola[i+j]==',')
                            break;
                        new[segna]=parola[i+j];
                        segna++;
                        j++;
                    }
                    new[segna]=',';
                    segna++;
                }
        }
    *len=segna;
    new[segna]='\0';
    return new;
    }
