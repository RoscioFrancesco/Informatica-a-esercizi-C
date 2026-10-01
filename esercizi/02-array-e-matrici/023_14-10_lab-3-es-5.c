//  Created by Francesco Roscio Ricon on 14/10/25.

//Ad esempio, se gli elementi inseriti fossero {10, 5, 3, 6, 1} (con media 5), la stringa stampata sarebbe "+=-+-".
//Infatti: 10>5 ('+'), 5=5 ('='), 3<5 ('-'), 6>5 ('+'), 1<5 ('-').

#include <stdio.h>
#include <string.h>
#define N 100
int main() {
    int v[N], i, n, media, somma=0;
    do{
        printf("Quanti elementi vuoi inserire?");
        scanf("%d", &n);
    }while(n<0 || n>N);
    for(i=0; i<n; i++)
        {
            scanf("%d", &v[i]);
        }
    for(i=0; i<n; i++)
    {
        somma= somma + v[i];
    }
    media=somma / n;
    for(i=0; i<n; i++)
    {
        if(v[i]==media) printf("=");
        if(v[i]<media) printf("-");
        if(v[i]>media) printf("+");
    }
    
}
