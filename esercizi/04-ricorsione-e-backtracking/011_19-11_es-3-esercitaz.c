//
//  main.c
//  es 3 esercitaz
//
//  Created by Francesco Roscio Ricon on 19/11/25.
//  codice binario con ricorsione

#include <stdio.h>
int converti(int num);
int main() {
    int num;
    printf("Inserire numero");
    scanf("%d", &num);
    int ris;
    ris=converti(num);
    printf("%d", ris);
    
}
int converti(int num)
    {
        if(num/2==0)
            return num%2;
        else{
            
            return num%2+10*converti(num/2);
        }
    }
