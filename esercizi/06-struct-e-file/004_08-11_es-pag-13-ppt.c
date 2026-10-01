//  Created by Francesco Roscio Ricon on 08/11/25.

#define N 100
typedef struct {
    int v[N];
    int cont;
} arrayConCont;

#include <stdio.h>
void inputarray (arrayConCont *j);
int main() {
    int i;
    arrayConCont j;
    inputarray(&j);
    for(i=0; i<j.cont;i++)
        {
            printf("\n%d", j.v[i]);
        }
}
void inputarray (arrayConCont *j)
    {
    int i,n;
    printf("Quanti elementi vuoi inserire?");
    scanf("%d", &n);
    int num;
    for(i=0; i< n; i++)
        {
            printf("Inserire l'elemento %d", i+1);
            scanf("%d", &num);
            if(num%2==0)
            {
                j->v[j->cont]=num;
                j->cont++;
            }
        }
    }
