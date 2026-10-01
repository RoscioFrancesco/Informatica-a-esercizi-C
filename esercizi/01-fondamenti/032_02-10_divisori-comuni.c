//  Created by Francesco Roscio Ricon on 02/10/25.


#include <stdio.h>

int main() {
    int v1, v2, max, min, i;
    printf("Inserisci il primo valore\n");
    scanf("%d", &v1);
    printf("Inserisci il secondo valore\n");
    scanf("%d", &v2);
    if (v1 > v2)
    { max = v1;
        min = v2;
    }
    else
    { max = v2;
        min = v1;
    }
    i = 1;
    printf("I divisori comuni sono: \n");
    do {
        if (v2 % i == 0 && v1 % i == 0)
            printf("%d, ", i);
        i++;
    } while (i < min);
}
