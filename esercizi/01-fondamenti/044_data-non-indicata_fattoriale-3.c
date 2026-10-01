
#include <stdio.h>
int main() {
    int n, s, x, k, a, b, j, f, c, r;
    printf("Inserire l'esponente n a cui si vuole elvare a+b:");
    scanf("%d", &n);fflush(stdin);// questo è n fattoriale
    printf("Inserire il k esimo termine di cui si desidera il coefficiente, si consideri che a elevato alla n ha k=0:");
    scanf("%d", &k);fflush(stdin); // questo è il termine k
    if (k == 0 || n == k || n <= 0 || k <= 0 || n < k)
    printf("Errore, rivedi il valore di k");
    else
    x = n-1;
    s = n;
    while (x > 0) {
        s = s * x;
        x = x - 1;
    } // a qs punto ho calcolato n fattoriale come s
                             //calcolo k fattoriale
               b = k-1;
               a = k;
               while (b > 0) {
               a = a * b;
               b = b - 1;
                 } // ho calolato k fattoriale come a
    j = n-k;     // calcolo n-k fattoriale = f, sono consapevole che è il metodo più stupido
    c = j-1;
    f = j;
    while (c > 0) {
        f = f * c;
        c = c - 1;
    }
    
    r = s / (a * f);
    printf("\nIl risultato è %d\n", r);

}
