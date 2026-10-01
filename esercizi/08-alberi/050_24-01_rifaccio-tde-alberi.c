//  Created by Francesco Roscio Ricon on 24/01/26.
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
int wrapper(Albero tree, int k);
void funzione(Albero tree, int livello, int k, int *max, int *flag);

int main() {
    Albero t1=costruisci1();
    Albero t2=costruisci2();
    Albero t3=costruisci3();




    printf("T1 livello 2: %d\n",wrapper(t1, 2));
    printf("T2 livello 2: %d\n",wrapper(t2, 2));
    printf("T3 livello 3: %d\n",wrapper(t3, 3));


    return 0;
}


int massimoNodoLivello(Albero T, int K){
    //FUNZIONE DA COMPLETARE
    return 0;
}
//FUNZIONI AUSILIARIE




Albero nN(int v){Albero n=(Albero)malloc(sizeof(Nodo));n->val=v;n->left=NULL;n->right=NULL;return n;}
Albero costruisci1(){Albero r=nN(2);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);r->right->right=nN(2);return r;}
Albero costruisci2(){Albero r=nN(5);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);return r;}
Albero costruisci3(){Albero r=nN(2);r->left=nN(5);r->left->left=nN(1);r->left->right=nN(2);return r;}


void funzione(Albero tree, int livello, int k, int *max, int *flag)
    {
        if(tree==NULL)
            return;
        if(livello==k)
            {
                if(*max<tree->val)
                    {
                        *flag=1;
                        *max=tree->val;
                    }
            }
    funzione(tree->left, livello+1, k, max,flag);
    funzione(tree->right, livello+1, k, max, flag);
        
    }
int wrapper(Albero tree, int k)
    {
    int max=-1;
    int livello=1;
    int flag=0;
    funzione(tree, livello, k, &max, &flag);
    if(flag==0)
    {
        printf("valore non trovato");
        max=0;
    }
    return max;
    }
