//  Created by Francesco Roscio Ricon on 08/11/25.
#define N 100
typedef struct {
    int v[N];
    int cont;
}arrayConCont;
#include <stdio.h>
void funzione (arrayConCont *j, int array[], int len_array);
int main() {
    int array[N], len_array, i;
    printf("Quanti elementi vuoi inserire nell'array?");
    scanf("%d", &len_array);
    for(i=0; i<len_array; i++)
        {
            scanf("%d", &array[i]);
        }
    arrayConCont j;
    funzione(&j, array, len_array);
    for(i=0; i<j.cont; i++)
    {
        printf("%d\n", j.v[i]);
    }
}
void funzione (arrayConCont *j, int array[], int len_array)
{
    int i=0;
    j->cont=0;
    for(i=0; i<len_array; i++)
        {
            if(array[i]%2==0)
                {
                    j->v[j->cont]=array[i];
                    j->cont++;
                }
        }
}
