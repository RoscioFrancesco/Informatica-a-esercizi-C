//
//  main.c
//  somma primi n numeri naturali
//
//  Created by Francesco Roscio Ricon on 27/09/25.
//

#include <stdio.h>

int main() {
    int n, s, ris;
    printf("Inserisci un numero N appartenente ai numeri natuali, il programma calcolarà la somma dei primi N numeri partendo da 1\n");
    scanf("%d", &n);
    s = 1;
    ris = 0;
    do {
        ris = ris + s;
        s = s + 1;
    } while (n >= s);
    printf("Il risultqato è %d\n", ris);
}
