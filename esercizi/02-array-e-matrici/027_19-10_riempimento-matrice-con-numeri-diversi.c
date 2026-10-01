//  Created by Francesco Roscio Ricon on 19/10/25.

#include <stdio.h>
#define N 3// N è il lato della matrice quadrata
int main() {
    int mat [N][N];
    int r=0, c=0, last, flag=0, rs=0, cs=0, i=0;
    for(r=0; r< N; r++)
        {
            for(c=0; c< N; c++){

                do{
                    printf("Inserire il valore [%d], [%d]", r ,c);
                    scanf("%d", &last);//poi modulo di ricerca
                    flag=0;
                    for(rs=0; rs<r && flag==0; rs++)
                    {
                        for(cs=0; cs<N && flag ==0; cs++) // controlla tutte le altre righe
                        {
                            if(last == mat[rs][cs])
                                flag = 1;
                        }
                    }
                    for(cs=0; cs<c && flag ==0; cs++)   // controlla la riga attuale
                    {
                        if(last == mat[r] [cs])
                            flag=1;
                    }
                    if(flag==0)
                        mat[r][c]=last;
                    if(flag==1)
                        printf("Errore, valore già inserito\n");
                }while(flag == 1);
            }
    }
    for(r=0;r<N; r++)
    {
        for(c=0; c<N; c++)
        {
            printf("%4d", mat[r][c]);
        }
        printf("\n");
    }
}
