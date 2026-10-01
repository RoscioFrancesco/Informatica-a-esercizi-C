//  Created by Francesco Roscio Ricon on 19/01/26.

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
void funzione(Albero t, int k, int*max, int livello);
int massimoNodoLivello(Albero t, int k);
int main() {
    Albero t1=costruisci1();
    Albero t2=costruisci2();
    Albero t3=costruisci3();




    printf("T1 livello 2: %d\n",massimoNodoLivello(t1, 2));
    printf("T2 livello 2: %d\n",massimoNodoLivello(t2, 2));
    printf("T3 livello 3: %d\n",massimoNodoLivello(t3, 3));


    return 0;
}




Albero nN(int v){Albero n=(Albero)malloc(sizeof(Nodo));n->val=v;n->left=NULL;n->right=NULL;return n;}
Albero costruisci1(){Albero r=nN(2);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);r->right->right=nN(2);return r;}
Albero costruisci2(){Albero r=nN(5);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);return r;}
Albero costruisci3(){Albero r=nN(2);r->left=nN(5);r->left->left=nN(1);r->left->right=nN(2);return r;}


void funzione(Albero t, int k, int*max, int livello)
    {
        if(t==NULL)
            return;
        if(livello==k)
            {
                if(*max<t->val)
                    *max=t->val;
            }
    funzione(t->left, k, max, livello+1);
    funzione(t->right, k, max, livello+1);
            
    }

int massimoNodoLivello(Albero t, int k)
    {
    int livello=1;
    int max=0;
    funzione(t, k, &max, livello);
    return max;
    }
