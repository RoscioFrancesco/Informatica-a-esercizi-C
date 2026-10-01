//
//  main.c
//  esercitaz alberi
//
//  Created by Francesco Roscio Ricon on 12/12/25.
// somma nodi foglia del primo albero è uguale al valore di un odei nodi del secondo albero


#include <stdio.h>
#include <stdlib.h>


typedef struct n {
        int val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;

albero createVal(int val);
albero creaAlbero1();albero creaAlbero2();albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int sommaFoglie(albero root);
int cercaValore(albero root, int val);
int verificaSommaUgualeNodo(albero root1, albero root2);

int main(){
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);
    int ris;
    ris=verificaSommaUgualeNodo(T1, T2);
    printf("%d", ris);
    
}


//
// TODO: SVILUPPARE QUI DENTRO QUANTO RICHIESTO
//


albero creaAlbero1() {
    albero tmp = createVal(7);
    tmp->left = createVal(3);tmp->left->left = createVal(9);tmp->left->right = createVal(10);
    tmp->right = createVal(8);tmp->right->left = createVal(5);tmp->right->right = createVal(12);
    tmp->right->right->left = createVal(11); tmp->right->right->right = createVal(6);
    tmp->left->left->left = createVal(41);
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal(7);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(8);tmp->left->right = createVal(5);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(11);tmp->left->left->left = createVal(6);
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal(7);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(4);tmp->left->right = createVal(5);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(11);tmp->left->left->left = createVal(6);
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
int sommaFoglie(albero root)
    {
        if(root==NULL)
            return 0;
        if(root->left==NULL && root->right==NULL)
            {
                return root->val;
            }
    return sommaFoglie(root->left)+sommaFoglie(root->right);
    }
int cercaValore(albero root, int val)
    {
        if(root==NULL)
            return 0;
        if(root->val==val)
            return 1;
    return cercaValore(root->left, val) || cercaValore(root->right, val); // avrei potuto anche mettere + al posto di ||
    }

int verificaSommaUgualeNodo(albero root1, albero root2)
    {
    int sommafoglie1=sommaFoglie(root1);
    if(cercaValore(root2, sommafoglie1))
        return 1;
    int sommafoglie2=sommaFoglie(root2);
    if(cercaValore(root1, sommafoglie2))
        return 1;
    return 0;
    }

