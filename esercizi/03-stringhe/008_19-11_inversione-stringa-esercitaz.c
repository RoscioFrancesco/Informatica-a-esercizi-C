//
//  main.c
//  inversione stringa esercitaz
//
//  Created by Francesco Roscio Ricon on 19/11/25.
//

#include <stdio.h>

int main() {
    
}
void f(char src[], char dest[], int pos)
    {
    if(src[0]!='\0')
        {
            dest[pos]=src[0];
            f(src+2,dest, pos-1);
        }
}
