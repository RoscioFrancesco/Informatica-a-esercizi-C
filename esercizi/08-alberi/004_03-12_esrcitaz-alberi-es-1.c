//
//  main.c
//  esrcitaz alberi es 1
//
//  Created by Francesco Roscio Ricon on 03/12/25.
//

//
//  main.c
//  albero conteggio nodi
//
//  Created by Francesco Roscio Ricon on 29/11/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int Tipo;
typedef struct El
{
    Tipo dato;
    struct El *left;
    struct El *right;
}Nodo;
typedef Nodo *Tree;
Tree nuovoNodo(Tipo valore);
Tree creaAlberoEsempio(void);
int contanodi (Tree albero);
int contafoglie (Tree albero);
int contarami(Tree albero);
int calcolaprofondità(Tree albero);
Tree cercaelemento(int x, Tree albero, int *trovato);
void stampaRami(Tree t, char *prefisso, int isRight);
void stampaAlbero(Tree t);
void cercamax_reale(Tree root, int *max);
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
Tree creaAlberoEsempio(void) {
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
    stampaAlbero(root);
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

//int contaNoFoglie(Tree t)
//{
//    if(t==NULL)
//        return 0;
//    if(t->left==NULL && t->right==NULL)
//        return 0;
//    return 1+contaNoFoglie(t->left)+contaNoFoglie(t->right);
//}
int sommanodi(Tree t)
    {
        if(t==NULL)
            return 0;
        
    return t->dato+ sommanodi(t->left)+sommanodi(t->right);
    }

void stampaRami(Tree t, char *prefisso, int isRight)
{
    if (t == NULL)
        return;

    // stampa ramo destro
    stampaRami(t->right, prefisso, 1);

    // stampa prefisso
    printf("%s", prefisso);

    // stampa il nodo con il connettore corretto
    if (isRight)
        printf("┌── ");
    else
        printf("└── ");

    printf("%d\n", t->dato);

    // prepara prefissi per i livelli successivi
    char nuovoPrefisso[200];
    strcpy(nuovoPrefisso, prefisso);

    if (isRight)
        strcat(nuovoPrefisso, "│   ");
    else
        strcat(nuovoPrefisso, "    ");

    // stampa ramo sinistro
    stampaRami(t->left, nuovoPrefisso, 0);
}

void stampaAlbero(Tree t)
{
    if (t == NULL)
    {
        printf("(albero vuoto)\n");
        return;
    }

    // il nodo radice non deve avere connettore, quindi lo stampiamo a parte
    printf("%d\n", t->dato);

    char prefisso[200] = "";
    stampaRami(t->right, prefisso, 1);
    stampaRami(t->left,  prefisso, 0);
}
// creare albero bts, ciè albero che ha a dx di elem tutti elme maggiori di elem, a sx tutti elementi minori di elem
Tree insert(Tree root, int value)
    {
        if(root==NULL)
            {
                Tree new_node=malloc(sizeof(Tree));
                new_node->dato=value;
                new_node->right=NULL;
                new_node->left=NULL;
                return new_node;
            }
        if(value<root->dato)
        {
            root->left=insert(root->left, value);
            return root;
        }
    if(value>root->dato)
        {
            root->right=insert(root->right, value);
            return root;
        }
    return root;
    }
int cercamax(Tree root)
    {
        if(root==NULL)
            return -1;
        if(root->right==NULL)
            return root->dato;
        return cercamax(root->right);
    }
void cercamax_reale(Tree root, int *max)
    {
        if(root==NULL)
            return;
        if(root->dato > *max)
            (*max)=root->dato;
        cercamax_reale(root->left, max);
        cercamax_reale(root->right, max);
    return;
    }


int wrapper(Tree root, int *errore)
    {
        if(root==NULL)
            {
                *errore=1;
                return -1;
            }
        int max_etero = root->dato;
        cercamax_reale(root, &max_etero);
        return max_etero;
    }
