//
//  main.c
//  es palindrome -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
    struct node *left, *right;
} node;

typedef node* tree;

typedef struct EL{
    char parola[100];
    struct EL *next;
}Vagone;
typedef Vagone *Lista;

tree newNode(char ch) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { printf("Errore malloc\n"); exit(1); }
    n->c = ch;
    n->left = n->right = NULL;
    return n;
}

void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

void printPreorder(tree T) {
    if (!T) return;
    printf("%c ", T->c);
    printPreorder(T->left);
    printPreorder(T->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int trovata(Lista head, char parola[]);
int palindroma(char parola[], int len);
Lista inserisciincoda(Lista head, char parola[]);
void f(tree t, int len, char parola[], Lista *l);
int depth(tree t);
Lista funzione_tot(tree t);
void stampa_lista(Lista head);
int main(void) {
    tree T = newNode('a');
    T->left = newNode('b');
    T->right = newNode('c');
    T->left->left = newNode('a');
    T->left->right = newNode('b');
    T->left->right->left = newNode('b');
    T->right->right = newNode('c');
    T->right->right->left = newNode('c');

    printf("Preorder albero: ");
    printPreorder(T);
    printf("\n\n");
    
    Lista new=funzione_tot(T);
    stampa_lista(new);
}
int palindroma(char parola[], int len)
    {
    int i=0;
    int j=len-1;
    while(i<j)
        {
            if(parola[i]!=parola[j])
                return 0;
            i++;
            j--;
        }
    return 1;
    }
void f(tree t, int len, char parola[], Lista *l) // questa riepie le palindrome da un nodo fisso
    {
        if(t==NULL)
            return;
        parola[len]=t->c;
        len++;
        if(palindroma(parola, len))
            {
                parola[len]='\0';
                if(trovata(*l, parola)==0)
                {
                    *l=inserisciincoda(*l, parola);
                }
            }
    f(t->left, len, parola, l);
    f(t->right, len, parola, l);
    }

Lista inserisciincoda(Lista head, char parola[])
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                strcpy(new->parola, parola);
                return new;
            }
    head->next=inserisciincoda(head->next, parola);
    return head;
    }
void wrapper_f(tree t, Lista *head) // fa una lista di palindrome per ogni nodo
    {
        if(t==NULL)
            return;
    int prof=depth(t);
    char *parola=malloc(sizeof(char)*(prof+1));
    f(t, 0, parola, head);
        free(parola);
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree t)
    {
    if(t==NULL)return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return 1+max(sx, dx);
    }
void scorri_albero(tree t, Lista *l)
    {
        if(t==NULL)
            return;
        wrapper_f(t, l);
    scorri_albero(t->left, l);
    scorri_albero(t->right, l);
    }
Lista funzione_tot(tree t)
    {
    Lista l=NULL;
    scorri_albero(t, &l);
    return l;
    }
void stampa_lista(Lista head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("%s-->", head->parola);
                head=head->next;
            }
    }
int trovata(Lista head, char parola[])
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(strcmp(head->parola, parola)==0)
                    return 1;
                head=head->next;
            }
    return 0;
    }
