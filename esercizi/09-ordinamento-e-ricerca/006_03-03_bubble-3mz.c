//
//  main.c
//  bubble 3mz
//
//  Created by Francesco Roscio Ricon on 03/03/26.
//

#include <stdio.h>
void bubble(int vett[], int len);
int main() {
    int vett[5]={2,4,5,3,1};
    bubble(vett, 5);
    for(int i=0; i<5; i++)
        {
            printf("%d", vett[i]);
        }
}
void bubble(int vett[], int len)
    {
    int num_scambi=0;
    for(int i=0; i<len-1; i++)
        {
            num_scambi=0;
            for(int j=0; j<len-i-1; j++)
                {
                    if(vett[j]>vett[j+1])
                        {
                            int temp=vett[j];
                            vett[j]=vett[j+1];
                            vett[j+1]=temp;
                            num_scambi++;
                        }
                }
            if(num_scambi==0)
                break;
        }
    }
