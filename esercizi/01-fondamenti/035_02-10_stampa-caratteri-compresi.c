//  Created by Francesco Roscio Ricon on 02/10/25.


#include <stdio.h>
#include <math.h>

int main() {
    char c1, c2, max, min, continuare;
    do {
    do {
        printf("Inserisci il primo carattere\n");
        scanf(" %c", &c1);
        printf("Inserisci il secondo carattere\n");
        scanf(" %c", &c2);
        if (!((c1 >= 'a' && c1 <= 'z' && c2 >= 'a' && c2 <= 'z') || (c1 >= 'A' && c1 <= 'Z' && c2 >= 'A' && c2 <= 'Z'))) // voglio che siano entrambe maiuscole o entrambe minuscole non una maiuscola ed una minuscola
            printf("Errore\n\n");
    }while(!(c1 >= 'a' && c1 <= 'z' && c2 >= 'a' && c2 <= 'z') && !(c1 >= 'A' && c1 <= 'Z' && c2 >= 'A' && c2 <= 'Z'));
    
    if (c1 > c2);
    {
        max = c1;
        min = c2;
    }
    if (c2 > c1);
    {
        max = c2;
        min = c1;
    }
    do {
        printf("%c ", min);
        min = min + 1;
    } while (min <= max);
    printf("\n");
        do {
            printf("Vuoi continuare?s/n");
            scanf(" %c", &continuare);
        }while(!(continuare == 's' || continuare == 'n'));
    } while(continuare == 's');
    
}
