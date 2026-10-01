//  Created by Francesco Roscio Ricon on 18/11/25.




#include <stdio.h>
int intis_power(int n, int b);
int main() {
    int n,b;
    int ris;
    printf("Inserire n");
    scanf("%d", &n);
    printf("Inserire b");
    scanf("%d", &b);
    ris=intis_power(n, b);
    printf("%d", ris);
}
int intis_power(int n, int b)
    {
//    if(n%b==1)  return 1;
    if(n==1) return 1;
    if(n<0) return 0;
    if(b==0) return 0;
    if(b==1 && n==1) return 1;
    if(b==1) return 0;
        else
        {
            if(n%b==0)
            {
                return intis_power(n/b, b);
            }
            else return 0;
        }
//    versione di chat gpt
//    if (n == 1) return 1;
//
//        // casi speciali
//        if (n < 0) return 0;          // numeri negativi non sono potenze positive
//        if (b == 0) return 0;         // 0^k non definito per k>0
//        if (b == 1) return 0;         // solo 1 è potenza di 1, già gestito dal caso base
//
//        // se n non è divisibile per b, non è potenza
//        if (n % b != 0) return 0;
//
//        // ricorsione sul quoziente
//        return intis_power(n / b, b);
    }
