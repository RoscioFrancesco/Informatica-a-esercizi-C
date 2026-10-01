//
//  main.c
//  tde albero riempimento
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//
#include <stdio.h>
#include <stdlib.h>


typedef struct n {
        int val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;


albero createVal(int val);
albero creaAlbero1();albero creaAlbero2();
void print(albero t);
void stampa(albero T);
void f(albero input,albero risultato);
int depth(albero t);
int max(int a,int b);
void inizializza(albero t,int v[],int liv);
void verifica(albero t,int elem[],int v[],int liv);
void f(albero tree_input, albero tree_output);
int assegnapunteggio(int padre, int figlio);

int main(){
    int ris=0;
    albero input,risultato;
    input = creaAlbero1(); risultato = creaAlbero2();
    printf("\nalberi in input: "); stampa(input);
    printf("\nalbero risultato con solo 0: "); stampa(risultato);


   //LA FUNZIONE DA SVILUPPARE VIENE USATA QUI
   f(input,risultato);


   printf("\nalbero risultato dopo esecuzione della funzione\n");stampa(risultato);
   
   return 0;
}




albero creaAlbero1() {
    albero tmp = createVal(5);
    tmp->left = createVal(5);tmp->left->left = createVal(3);tmp->left->right = createVal(0);
    tmp->right = createVal(5);tmp->right->left = createVal(9);tmp->right->right = createVal(1);
    tmp->right->right->left = createVal(7); tmp->right->right->right = createVal(10);
    tmp->left->left->left = createVal(0); tmp->left->left->right = createVal(2);
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal(0);
    tmp->left = createVal(0);tmp->left->left = createVal(0);tmp->left->right = createVal(0);
    tmp->right = createVal(0);tmp->right->left = createVal(0);tmp->right->right = createVal(0);
    tmp->right->right->left = createVal(0); tmp->right->right->right = createVal(0);
    tmp->left->left->left = createVal(0); tmp->left->left->right = createVal(0);
    return tmp;
}


void print(albero t){
       if(t==NULL)return;
       else{printf(" (");print(t->left);printf(" %d ",t->val);print(t->right);printf(") ");}
}


void stampa(albero T){print(T);printf("\n");}


albero createVal(int val) {
    albero tmp = malloc(sizeof(nodo));
    tmp->val = val;    tmp->left = NULL;    tmp->right = NULL;
    return tmp;
}
//Il punteggio di un nodo non-radice dipende dalla differenza in valore assoluto Δ tra il valore del nodo ed il valore contenuto nel nodo genitore. Più nello specifico, il punteggio di un nodo è così definito:
//Se Δ<=3, il punteggio è 1;
//Se Δ è compreso nell’intervallo (3,5], il punteggio è 2 punto;
//Se Δ è compreso nell’intervallo (5,8], il punteggio è 3 punti;
//Se Δ>8, il punteggio è 4 punti.


int assegnapunteggio(int padre, int figlio)
    {
    int diff=abs(padre-figlio);
    if(diff<=3)
        return 1;
    if(diff>3 && diff<=5)
        return 2;
    if(diff>5 && diff<=8)
        return 3;
    
    return 4;
    }

void f(albero tree_input, albero tree_output)
{
    if(tree_input==NULL || tree_output==NULL)
        return;
    //    tree_output->left->val=assegnapunteggio(tree_input->val, tree_input->left->val);
    //    tree_output->right->val=assegnapunteggio(tree_input->val, tree_input->right->val);
    //    f(tree_input->right, tree_output->right);
    //    f(tree_input->left, tree_output->left);
    //    }
    
    if (tree_input->left != NULL && tree_output->left != NULL) {
        tree_output->left->val = assegnapunteggio(tree_input->val, tree_input->left->val);
        f(tree_input->left, tree_output->left);
    }
    
    if (tree_input->right != NULL && tree_output->right != NULL) {
        tree_output->right->val = assegnapunteggio(tree_input->val, tree_input->right->val);
        f(tree_input->right, tree_output->right);
    }
}
