//
//  main.c
//  tde 1 lista -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
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
int massimoNodoLivello(Albero T, int K);
void f(Albero t, int K, int livello, int *max);

int main() {
    Albero t1=costruisci1();
    Albero t2=costruisci2();
    Albero t3=costruisci3();




    printf("T1 livello 2: %d\n",massimoNodoLivello(t1, 2));
    printf("T2 livello 2: %d\n",massimoNodoLivello(t2, 2));
    printf("T3 livello 3: %d\n",massimoNodoLivello(t3, 3));


    return 0;
}


int massimoNodoLivello(Albero T, int K){
    int max=0;
    f(T, K, 1, &max);
    return max;
}
//FUNZIONI AUSILIARIE




Albero nN(int v){Albero n=(Albero)malloc(sizeof(Nodo));n->val=v;n->left=NULL;n->right=NULL;return n;}
Albero costruisci1(){Albero r=nN(2);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);r->right->right=nN(2);return r;}
Albero costruisci2(){Albero r=nN(5);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);return r;}
Albero costruisci3(){Albero r=nN(2);r->left=nN(5);r->left->left=nN(1);r->left->right=nN(2);return r;}



void f(Albero t, int K, int livello, int *max)
    {
        if(t==NULL)
            return;
        if(K==livello)
            {
                if(t->val>*max)
                    {
                        *max=t->val;
                    }
            }
    f(t->left, K, livello+1, max);
    f(t->right, K, livello+1, max);
    }

