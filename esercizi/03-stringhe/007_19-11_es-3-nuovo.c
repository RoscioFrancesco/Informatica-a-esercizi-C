//  Created by Francesco Roscio Ricon on 19/11/25.

//"Oggi, dopo l'orale, ho preso 30 nell'esame di Informatica A"
//
//questa verrà trasformata in
//
//"ggidopoloralehopresonellesamedinformatica"

#include <stdio.h>
#include <string.h>
#define N 100
void creastringa(char *stringa, int *len_nuova, char nuova_stringa[]);
int main() {
    char stringa[N];
    char nuova_stringa[N];
    int len_nuova=0;
    int len_stringa;
    printf("Inserire stringa");
    fgets(stringa, N, stdin);
    len_stringa=strlen(stringa);
    creastringa(stringa, &len_nuova, nuova_stringa);
    nuova_stringa[len_nuova]='\0';
    printf("%s", nuova_stringa);
}
void creastringa(char *stringa, int *len_nuova, char nuova_stringa[])
    {
    
        if(*stringa=='\0')
        {;}
        else
        {
            if(*stringa<='z' && *stringa>='a')
                {
                    nuova_stringa[*len_nuova]=*stringa;
                    (*len_nuova)++;
                }
            creastringa(stringa+1, len_nuova, nuova_stringa);
            
        }
    }
