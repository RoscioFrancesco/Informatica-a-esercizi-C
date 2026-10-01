//  Created by Francesco Roscio Ricon on 11/10/25.

#include <stdio.h>

#include <string.h>
int main() {
    int v1[100], v2[100], counter2, i, numero, carattere, j, flag;
    do{
        printf("Quanti caratteri vuoi inserire?");
        scanf("%d", &numero);
    }while(numero<0 || numero > 100);
    counter2=0;
    j=0;
    flag =1;
    printf("Inserisci i caratteri");
    for(i=0; i<numero; i++)
    {
        scanf("%d", &v1[i]);
    if(i==0) {              // questo primo if seve ad inserie nel set il primo carattere dell'array originale
            v2[0] = v1[0];
            counter2++;
        }
        else {
            for(j=0, flag =0; j<i && flag==0; j++)          // in qs caso sto confrontando l'ultimo valore acqusito con tutti i precedenti, se è diverso viene                                                      messo in v2, altrimenti no;
            {
                if (v1[i] == v1[j])
                {
                    flag=1;
                    break;
                }
                
            }
            if (flag == 0){
                
                v2[counter2]= v1[i];
                counter2++;
            }
        
        }
        
    }
    

    for(i=0; i<counter2; i++)
        printf("%d", v2[i]);
}
