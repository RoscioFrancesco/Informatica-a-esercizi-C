//
//  main.c

//  Created by Francesco Roscio Ricon on 14/12/25.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct s_nodo {
        int val;
        struct s_nodo *left;
        struct s_nodo *right;
} nodo;
typedef nodo *albero;

albero creaAlbero();
albero createVal(int val);
void print(albero t);
void printConLivello(albero t,int liv);
void sommaparidisp(albero t, int *sommapari, int *sommadispari, int livello);
void wrapper(albero t, int *sommapari, int *sommadispari);
void printGrafico(albero t, int spazio);
int check_tree(albero t);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int ris=0;
    ris=check_tree(alb);
    printf("\n%d", ris);
    printf("\n");
    printGrafico(alb, 0);
}




albero creaAlbero() {
    albero tmp = createVal(1);
    tmp->left = createVal(2);
    tmp->right = createVal(21);

    tmp->left->left = createVal(4);
    tmp->left->right = createVal(5);

    tmp->right->left = createVal(6);
    tmp->right->right = createVal(7);

    return tmp;
}


albero createVal(int val) {
       albero tmp = malloc(sizeof(nodo));
       tmp->val = val;
       tmp->left = NULL;
       tmp->right = NULL;
       return tmp;
}


void print(albero t){
       if(t==NULL)
           return;
       printf(" (");
       print(t->left);
       printf(" %d ",t->val);
       print(t->right);
       printf(") ");
}


void printConLivello(albero t,int liv){
       if(t==NULL)
           return;
       printf(" (");
       printConLivello(t->left,liv+1);
       printf("(v: %d, l: %d)",t->val,liv);
       printConLivello(t->right,liv+1);
       printf(") ");
}
// ridà intero somma nodi profondità pari=profdispari ritorna 1
int check_tree(albero t)
    {
        
        // qs funzione verifica che le somme siano uguali
    int sommapari=0;
    int sommadispari=0;
    wrapper(t, &sommapari, &sommadispari);
    if(sommapari==sommadispari)
        return 1;
    return 0;
    }
void sommaparidisp(albero t, int *sommapari, int *sommadispari, int livello)
    {
        if(t==NULL)
            return;
        if((livello)%2==0)
        {*sommapari=*sommapari+t->val;
        }
        else
        {
            (*sommadispari=*sommadispari+t->val);
        }
    sommaparidisp(t->left, sommapari, sommadispari, livello+1);
    sommaparidisp(t->right, sommapari, sommadispari, livello+1);
   }

void wrapper(albero t, int *sommapari, int *sommadispari)
    {
    int livello=0;
    sommaparidisp(t, sommapari, sommadispari, livello);
    }
void printGrafico(albero t, int spazio)
{
    if (t == NULL)
        return;

    spazio += 5;

    printGrafico(t->right, spazio);

    printf("\n");
    for (int i = 5; i < spazio; i++)
        printf(" ");
    printf("%d\n", t->val);

    printGrafico(t->left, spazio);
}
