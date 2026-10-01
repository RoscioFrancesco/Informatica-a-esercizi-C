//
//  main.c
//  tde 14 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//


void f(int array[4], int giusto[4], int ris[4])
    {
    int count1=0;
    int usato[4]={0,0,0,0};
    for(int i=0; i<4; i++)
        {
            if(array[i]==giusto[i])
            {
                count1++;
                usato[i]=1;
            }
        }
    int count2=0;
    for(int i=0; i<4; i++)
        {
            for(int j=0;j<4; j++)
                {
                    if(array[i]==giusto[j] && i!=j && usato[i]!=1)
                        count2++;
                }
        }
    int punta=0;
    for(int i=0; i<4; i++)
        {
            if(count1>0)
                {
                    ris[punta]=1;
                    count1--;
                    punta++;
                }
            if(count2>0)
                {
                    ris[punta]=2;
                    punta++;
                    count2--;
                }
        }
    for(int i=punta; i<4; i++)
        {
            ris[i]=0;
        }
    
    }
