//  Created by Francesco Roscio Ricon on 08/11/25.
int sommaDivisori(int num);
int controllaSePerfetto(int num, int somma);

#include <stdio.h>

int main() {
    int num, somma, flag;
    do{
        scanf("%d", &num);
    }while(num<0);
    somma=sommaDivisori(num);
    flag=controllaSePerfetto(num, somma);
    if(flag==0) printf("perfetto");
    if(flag==1) printf("abbondante");
    if(flag==-1) printf("difettivo");
}
int sommaDivisori(int num)
    {
    int i, somma=0;
    for(i=1; i<num/2; i++)
        {
            if(num % i==0)
                somma=somma+i;
        }
    return somma;
    }
int controllaSePerfetto(int num, int somma)
    {
    if(num==somma) return 0;
    if(num>somma) return 1;
    return -1;
    }
