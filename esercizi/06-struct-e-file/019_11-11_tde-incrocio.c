//  Created by Francesco Roscio Ricon on 11/11/25.
typedef struct
{
    int v1_iniziale;
    int v2_iniziale;
    int v1_incrocio;
    int v2_incrocio;
}puntodiincrocio;
#include <stdio.h>
#include <string.h>
#define N 20
void trovaIncrocio(int v1[], int v2[], int len_vettori, puntodiincrocio *ris);
int main(){
    int v1[N] = {1122, 1123, 1177, 1083, 1050, 1010, 919, 993, 1076, 1205, 1325, 1393, 1399};
    int v2[N] =  {1322, 1318, 1316, 1166, 1096, 1112, 1070, 912, 1154, 1294, 1350, 1624, 1782};
    int n = 13; // dimensioni effettive;
    int i;
    puntodiincrocio ris;
    printf("\n v1 = [");
    for(i = 0; i < n; i++)
        printf("%d, ", v1[i]);


    printf("]\n v2 = [");
    for(i = 0; i < n; i++)
        printf("%d, ", v2[i]);
    printf("]\n");
    trovaIncrocio(v1, v2, n, &ris);
    printf("Incrocio quando V1 prima vale %d e poi %d, mentre V2 prima vale %d e poi %d", ris.v1_iniziale, ris.v1_incrocio, ris.v2_iniziale, ris.v2_incrocio);
}
void trovaIncrocio(int v1[], int v2[], int len_vettori, puntodiincrocio *ris)
    {
    int flag=0;
    int i;
    for(i=0; i<len_vettori && flag==0; i++)
        {
            if((v1[i]-v2[i])*(v1[0]-v2[0])<0)
                {
                    flag=1;
                    ris->v1_iniziale=v1[i-1];
                    ris->v2_iniziale=v2[i-1];
                    ris->v1_incrocio=v1[i];
                    ris->v2_incrocio=v2[i];
                }
        }
    
    }
