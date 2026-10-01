//
//  main.c
//  albero
//
//  Created by Francesco Roscio Ricon on 25/01/26.
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
int contaNodiLivello(Albero tree, int k);
void funzione(Albero tree, int livello, int k, int*contatore);

int main() {
    Albero t1=costruisci1();
    Albero t2=costruisci2();
    Albero t3=costruisci3();




    printf("T1: %d\n",contaNodiLivello(t1, 2));
    printf("T2: %d\n",contaNodiLivello(t2, 3));
    printf("T3: %d\n",contaNodiLivello(t3, 0));


    return 0;
}


//AGGIUNGERE QUI EVENTUALI FUNZIONI AUSILIARIE




Albero nN(int v){Albero n=(Albero)malloc(sizeof(Nodo));n->val=v;n->left=NULL;n->right=NULL;return n;}
Albero costruisci1(){Albero r=nN(2);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);r->right->right=nN(2);return r;}
Albero costruisci2(){Albero r=nN(5);r->left=nN(1);r->right=nN(5);r->left->left=nN(0);r->left->right=nN(2);return r;}
Albero costruisci3(){Albero r=nN(2);r->left=nN(5);r->left->left=nN(1);r->left->right=nN(2);return r;}

void funzione(Albero tree, int livello, int k, int*contatore)
    {
        if(tree==NULL)
            return;
        if(livello==k)
            (*contatore)++;
    funzione(tree->left, livello+1, k, contatore);
    funzione(tree->right, livello+1, k, contatore);
    }
int contaNodiLivello(Albero tree, int k)
    {
        if(tree==NULL)
            return 0;
    int contatore=0;
    funzione(tree, 0, k, &contatore);
    return contatore;
    }
