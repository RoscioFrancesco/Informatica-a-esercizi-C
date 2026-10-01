//
//  main.c
//  es tde 9 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//

#include <stdio.h>

#define N 6

typedef struct { int R, G, B; } colore;
typedef colore immagine[N][N];
int f(immagine T, int k);

int main() {
    immagine img = {
        /* riga 0 */ { {10,20,30}, {10,20,30}, {10,20,30}, { 0, 0, 0}, { 5, 5, 5}, { 9, 9, 9} },
        /* riga 1 */ { {10,20,30}, {10,20,30}, {10,20,30}, { 1, 2, 3}, { 5, 5, 5}, { 9, 9, 9} },
        /* riga 2 */ { {10,20,30}, {10,20,30}, {10,20,30}, { 4, 4, 4}, { 8, 8, 8}, { 9, 9, 9} },

        /* riga 3 */ { { 7, 1, 9}, { 2, 8, 2}, { 3, 3, 3}, { 4, 4, 4}, { 6, 7, 8}, { 1, 1, 1} },
        /* riga 4 */ { { 7, 1, 9}, { 0, 0, 1}, { 3, 3, 3}, { 2, 2, 2}, { 6, 7, 8}, { 1, 1, 1} },
        /* riga 5 */ { { 9, 9, 0}, { 0, 1, 0}, { 3, 3, 3}, { 2, 2, 2}, { 6, 7, 8}, { 1, 1, 1} }
    };

    /* stampa veloce di controllo (opzionale) */
    printf("Immagine inizializzata. Esempio pixel img[0][0] = (%d,%d,%d)\n",
           img[0][0].R, img[0][0].G, img[0][0].B);
    printf("%d", f(img, 4));
}
int compare(colore a, colore b)
    {
        if(a.B==b.B && a.G==b.G && a.R==b.R)
            return 1;
    return 0;
    }
int ver(immagine T, int k, int r, int c)
    {
    for(int scorri_r=0; scorri_r<k; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<k; scorri_c++)
                {
                    if(compare(T[r][c], T[r+scorri_r][c+scorri_c])==0)
                        return 0;
                }
        }
    return 1;
    }
int f(immagine T, int k)
    {
    for(int r=0; r<=N-k; r++)
        {
            for(int c=0; c<=N-k; c++)
                {
                    if(ver(T, k, r, c))
                        return 1;
                }
        }
    return 0;
    }
