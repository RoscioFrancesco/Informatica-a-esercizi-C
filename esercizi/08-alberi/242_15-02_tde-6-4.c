//
//  main.c
//  tde 6 -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct El {
  int val;
  struct El *left,*right;
} Nodo;
typedef Nodo *Albero;
Albero nN(int valore);
Albero costruisci1();
Albero costruisci2();
Albero costruisci3();
int wrapper(Albero t, int k);
int main() {
    Albero t1=costruisci1();
    Albero t2=costruisci2();
    Albero t3=costruisci3();




    printf("T1: %d\n",wrapper(t1, 2));
    printf("T2: %d\n",wrapper(t2, 3));
    printf("T3: %d\n",wrapper(t3, 0));


    return 0;
}

Albero nN(int v){Albero n=(Albero)malloc(sizeof(Nodo));n->val=v;n->left=NULL;n->right=NULL;return n;}
Albero costruisci1(){Albero r=nN(2);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);r->right->right=nN(2);return r;}
Albero costruisci2(){Albero r=nN(5);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);return r;}
Albero costruisci3(){Albero r=nN(2);r->left=nN(5);r->left->left=nN(1);r->left->right=nN(2);return r;}

void f(Albero t, int livello_target, int *count, int livello)
    {
        if(t==NULL)
            return;
        if(livello==livello_target)
            {
                (*count)++;
            }
    f(t->left, livello_target, count, livello+1);
    f(t->right, livello_target, count, livello+1);
    }
int wrapper(Albero t, int k)
    {
    int count=0;
    f(t, k, &count, 0);
    return count;
    }
