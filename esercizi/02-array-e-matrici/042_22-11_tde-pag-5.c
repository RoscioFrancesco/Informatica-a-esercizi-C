//  Created by Francesco Roscio Ricon on 22/11/25.

#include <stdio.h>
#define N 10
#define M 20
int funzione(int MAT[N][M], int num_r, int num_c);
int trovapicco(int pos_r, int pos_c, int num_r, int num_c, int MAT[N][M]);
int main() {
    int num_r=10, num_c=20;
    int ris;
    int MAT[10][20] = {
        {1, 2, 3, 1, 5, 7, 1, 2, 1, 3, 1, 0, 1, 5, 1, 2, 1, 2, 2, 1},
        {2, 1, 1, 2, 8, 2, 1, 1, 1, 1, 3, 1, 1, 1, 2, 3, 4, 1, 1, 1},
        {1, 0, 1, 9, 0, 1, 0, 1, 0, 4, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 5, 6, 0, 0, 0, 0, 1, 7, 0, 0, 1, 0, 0, 0, 0},
        {3, 1, 1, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
        {1, 2, 1, 0, 0, 0, 0, 9, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 5, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {2, 1, 0, 1, 0, 0, 0, 0, 0, 8, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 7, 0, 1, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9}
    };
    ris=funzione(MAT, N, M);
    printf("%d", ris);
}
int funzione(int MAT[N][M], int num_r, int num_c)
    {
    int scorri_r=0, scorri_c=0;
    int contatore=0;
    int vetR[8]={1, 1, 1, 0, 0, -1,-1, -1};
    int vetC[8]={1,0,-1, -1, 1, 1, 0, -1};
    int k=0;
    int flag=1;
    for(scorri_r=0; scorri_r<num_r; scorri_r++)
        {
            for(scorri_c=0; scorri_c<num_c; scorri_c++)
                {
                    for(k=0; k<8 && flag==1; k++)
                            {
                                if(scorri_r+vetR[k]<0 || scorri_c+vetC[k]<0 || scorri_r+vetR[k]>=num_r || scorri_c+vetC[k]>=num_c)
                                    continue;
                                    if(MAT[scorri_r][scorri_c]<=MAT[scorri_r+vetR[k]][scorri_c+vetC[k]]/2)
                                        flag=0;
                                
                            }
                    if(flag==1)
                        contatore++;
                    flag=1;
                }
        }
    return contatore;
    }
