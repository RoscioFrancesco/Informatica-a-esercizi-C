//  Created by Francesco Roscio Ricon on 02/10/25.

#include <stdio.h>

int main() {
    int tab, n, prod, i;
    do {
        printf("Inserire la tabellina desiderata\n");
        scanf("%d", &tab);
        printf("Inserire lunghezza della tabellina richiesta\n");
        scanf("%d", &n);
        if (tab < 0 || n < 0)
            printf("Errore, inserire un numero positivo\n\n");
    } while (!(tab > 0 && n > 0));
    i = 1;
    do {
        prod = tab * i;
        printf ("%d   ", prod);
        i = i + 1;
         } while (i <= n);

}
