//  Created by Francesco Roscio Ricon on 07/11/25.

#include <string.h>
#include<stdio.h>
void lettereCentrali(char txt[], char res[], int len);
int main()
{
  char txt1[100] = "che buona la pasta aglio olio e peperoncino";
  char txt2[100] = "il C e' il mio linguaggio preferito!";
    char res1[100], res2[100];
    int len1, len2;
    len1=strlen(txt1);
    len2=strlen(txt2);
    lettereCentrali(txt1, res1, len1);
    lettereCentrali(txt1, res2, len2);
    printf("%s\n", txt1);
    printf("%s", res1);
}
void lettereCentrali(char txt[], char res[], int len)
    {
    int res_counter=0, k=0;
    int i=0;
    for(i=0; i<len;i++)
        {
            if(txt[i]==' ' || i==0)
                {
                    k=0;
                    do {
                        k++;
                    } while (txt[i+k] !=' ' && txt[i+k] !='\0');
                    res[res_counter]=txt[i+(k/2)];
                    res_counter++;
                }
            
        }
    res[res_counter+1]='\0';
    
    
    
    }
