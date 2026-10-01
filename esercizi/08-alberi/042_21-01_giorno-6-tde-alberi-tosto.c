//
//  main.c
//  giorno -6 tde alberi tosto
//
//  Created by Francesco Roscio Ricon on 21/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
int assegnapunteggio(int padre, int figlio);
albero funzione(albero input, albero risultato, albero root);

int main(){
    int ris=0;
    albero input,risultato;
    input = creaAlbero1(); risultato = creaAlbero2();
    printf("\nalberi in input: "); stampa(input);
    printf("\nalbero risultato con solo 0: "); stampa(risultato);



   risultato=funzione(input,risultato, risultato);


   printf("\nalbero risultato dopo esecuzione della funzione\n");stampa(risultato);
   
   return 0;
}


//
// TODO: SVILUPPARE QUI DENTRO QUANTO RICHIESTO
//
void f(albero input,albero risultato){
    //SVILUPPARE QUI QUANTO RICHIESTO
    //FUNZIONI AUSILIARIE CON PARAMETRI AGGIUNTIVI SONO MOLTO CONSIGLIATE
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

albero funzione(albero input, albero risultato, albero root)
    {
    if(input==NULL)
        return root;
    if (input->left == NULL && input->right == NULL)
            return root;
    
    if(input==root)
    {
        risultato->val=0;
        risultato->left->val=assegnapunteggio(input->val, input->left->val);
        risultato->right->val=assegnapunteggio(input->val, input->right->val);
        return root;
        
    }
    risultato->left->val=assegnapunteggio(input->val, input->left->val);
    risultato->right->val=assegnapunteggio(input->val, input->right->val);
    root=funzione(input->left, risultato->left, root);
    root=funzione(input->right, risultato->right, root);
    return root;
    }

int assegnapunteggio(int padre, int figlio)
    {
        int num=abs(padre-figlio);
        if(num<=3)
            return 1;
        if(num>3 && num<=5)
            {
                return 2;
            }
        if(num>5 && num<=8)
            return 3;
    
    
            return 4;
    }
