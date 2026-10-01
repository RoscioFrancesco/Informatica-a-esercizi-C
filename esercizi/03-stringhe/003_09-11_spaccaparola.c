//
//  main.c
//  spaccaparola
//
//  Created by Francesco Roscio Ricon on 09/11/25.
//  #include<stdio.h>
#include <stdio.h>
#include<string.h>
#define N 20





void spaccaParola(char parola[], char vocali[], char altro[], int len_parola, int *len_vocali, int *len_altro);


int main()
{
char parola[N] = "bella Info A!";
char vocali[N], altro[N];
    int len_parola;
    len_parola=strlen(parola);
    int len_vocali, len_altro;
    spaccaParola(parola, vocali, altro, len_parola, &len_vocali, &len_altro);
    printf("%s\n", parola);
    printf("%s\n", vocali);
    printf("%s", altro);





return 0;
}
void spaccaParola(char parola[], char vocali[], char altro[], int len_parola, int *len_vocali, int *len_altro)
{
    int i;
    int counter_vocali=0;
    int counter_altro=0;
    for(i=0;i<len_parola;i++)
        {
            if(parola[i]=='a' || parola[i]=='e' || parola[i]=='i' || parola[i]=='o'|| parola[i]=='u' || parola[i]=='A' || parola[i]=='E' || parola[i]=='I' || parola[i]=='O'|| parola[i]=='U' )
                {
                    vocali[counter_vocali]=parola[i];
                    counter_vocali++;
                }
            if(!(parola[i]=='a' || parola[i]=='e' || parola[i]=='i' || parola[i]=='o'|| parola[i]=='u' || parola[i]=='A' || parola[i]=='E' || parola[i]=='I' || parola[i]=='O'|| parola[i]=='U'))
                {
                    altro[counter_altro]=parola[i];
                    counter_altro++;
                }
        }
    altro[counter_altro]='\0';
    vocali[counter_vocali]='\0';
    *len_vocali=counter_vocali;
    *len_altro=counter_altro;
}

