//
//  main.c
//  albero conteggio nodi
//
//  Created by Francesco Roscio Ricon on 29/11/25.
//

#include <stdio.h>
#include <stdlib.h>
typedef int Tipo;
typedef struct El
{
    Tipo dato;
    struct El *left;
    struct El *right;
}Nodo;
typedef Nodo *Tree;
Tree nuovoNodo(Tipo valore);
Tree creaAlberoEsempio();
int contanodi (Tree albero);
int contafoglie (Tree albero);
int contarami(Tree albero);
int calcolaprofondità(Tree albero);
Tree cercaelemento(int x, Tree albero, int *trovato);
Tree nuovoNodo(Tipo valore) {
    Tree t = (Tree)malloc(sizeof(Nodo));
    if (!t) {
        printf("Errore allocazione memoria\n");
        exit(1);
    }
    t->dato = valore;
    t->left = NULL;
    t->right = NULL;
    return t;
}
void stampa (Tree T);
Tree creaAlberoEsempio() {
    Tree root = nuovoNodo(50);

    root->left = nuovoNodo(30);
    root->right = nuovoNodo(70);

    root->left->left = nuovoNodo(20);
    root->left->right = nuovoNodo(40);

    root->right->left = nuovoNodo(60);
    root->right->right = nuovoNodo(80);

    root->left->left->left = nuovoNodo(10);
    root->left->left->right = nuovoNodo(25);

    root->left->right->left = nuovoNodo(35);
    root->left->right->right = nuovoNodo(45);

    root->right->left->left = nuovoNodo(55);
    root->right->left->right = nuovoNodo(65);

    root->right->right->left = nuovoNodo(75);
    root->right->right->right = nuovoNodo(90);

    return root;
}
int main() {
    int num;
    Tree root = creaAlberoEsempio();
    num=contanodi(root);
    printf("%d\n", num);
    int foglie;
    foglie=contafoglie(root);
    printf("foglie:%d\n", foglie);
    int rami;
    rami=contarami(root);
    printf("rami:%d\n", rami);
    int profondità;
    profondità=calcolaprofondità(root);
    printf("profondità:%d", profondità);
    Tree posizione;
    int x;
    printf("Che elemento vuoi cercare");
    scanf("%d", &x);
    int trovato=0;
    posizione=cercaelemento(x, root, &trovato);
    printf("%d\n", trovato);
    printf("%p\n", posizione);
    printf("%p\n", root);
    stampa(root);
}
int contanodi (Tree albero)
    {
        if(albero==NULL)
            return  0;
    return 1+contanodi(albero->left)+contanodi(albero->right);
    }
int contafoglie (Tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    return contafoglie(albero->left)+contafoglie(albero->right);
    }
int contarami(Tree albero)
    {
    int num;
    num=contanodi(albero)-contafoglie(albero);
    return num;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int calcolaprofondità(Tree albero)
    {
        if(albero==NULL)
        {
            return 0;
        }
    return max(calcolaprofondità(albero->left), calcolaprofondità(albero->right))+1;
    }
Tree cercaelemento(int x, Tree albero, int *trovato)
    {
    Tree temp;
        if(albero==NULL)
            return 0;
        if(albero->dato==x)
        {
            *trovato=1;
            return albero;
        }
        temp=cercaelemento(x, albero->left, trovato);
    if(*trovato!=1)
        cercaelemento(x, albero->right, trovato);
    return temp;
    }
void print (Tree t){
if (t==NULL)
return;
else
{printf("(");
print(t->left);
printf(" %d ",t->dato);
print(t->right);
printf(") ");
}
}
void stampa (Tree T)
{
    print(T);
    printf("\n");
}
