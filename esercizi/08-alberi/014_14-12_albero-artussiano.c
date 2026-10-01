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


int main(){
  albero alb = creaAlbero();
  print(alb);
    
}




albero creaAlbero() {
    albero tmp = createVal(1);
    tmp->left = createVal(2);
    tmp->right = createVal(3);

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
//Un albero si dice artussiano se e solo se è composto da:
//
//nodi foglia
//nodi con un solo figlio
//nodi con due figli aventi lo stesso numero di discendenti

int contaNodi(albero root){
    if(root == NULL) return 0;
    return contaNodi(root->left) + contaNodi(root->right) + 1;
}

int alberoArtussiano(albero root){
    // Caso base: albero vuoto
    if(root == NULL) return 1;

    // Caso base: foglia
    if(root->left == NULL && root->right == NULL) return 1;
    
    // Analizzo il branch di destra
    if(root->left == NULL) return alberoArtussiano(root->right);
    
    // Oppure analizzo il branch di sinistra
    if(root->right == NULL) return alberoArtussiano(root->left);
    
    // Se ho entrambi i branch disponibili, devo verificare che:
    // Entrambi i branch hanno gli stessi nodi
    // Entrambi i sottoalberi sono artussiani
    if(contaNodi(root->left) == contaNodi(root->right) && alberoArtussiano(root->left) && alberoArtussiano(root->right)) return 1;
    
    return 0;
}
