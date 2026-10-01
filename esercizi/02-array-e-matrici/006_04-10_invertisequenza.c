//
//  main.c
//  invertisequenza
//
//  Created by Francesco Roscio Ricon on 04/10/25.
//
#include <stdio.h>
int main() {
int i;
int a[100];
i = 0;
while (i < 100) {
printf("fornisci un valore intero");
scanf("%d", &a[i]);
i++;
}
i--;
while (i >= 0) {
printf("%d\n", a[i]);
i--;
}
return 0;
}
