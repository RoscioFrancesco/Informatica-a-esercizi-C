//  Created by Francesco Roscio Ricon on 14/10/25.



#include <stdio.h>

int main() {
    int scelta, a, b;
    printf("Inserisci  un numero tra 1, 2, 0");
    scanf(" %d", &scelta);
    switch (scelta) {
        case 1:
            printf("Inserire il primo numero");
            scanf("%d", &a);
            printf("Inserire il secondo numero");
            scanf("%d", &b);
            printf("%d+%d=%d",a,b, a+b);
            break;
        case 2:
            printf("Inserire il primo numero");
            scanf("%d", &a);
            printf("Inserire il secondo numero");
            scanf("%d", &b);
            printf("%d*%d=%d",a, b, a*b);
            break;
        case 0:
            printf("Grazie ed arrivederci");
            break;
        default: printf("Errore");
        
    }
    return 0;

}
