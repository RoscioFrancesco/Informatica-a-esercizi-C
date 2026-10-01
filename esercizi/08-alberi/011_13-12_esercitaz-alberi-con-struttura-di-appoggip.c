//
//  main.c
//  esercitaz alberi con struttura di appoggip
//
//  Created by Francesco Roscio Ricon on 13/12/25.
//
// Nodo per la lista di conteggio


#include <stdio.h>
#include <stdlib.h>

typedef struct CountNode {
    int value;
    int count;
    struct CountNode *next;
} CountNode;

typedef CountNode *pCountNode;

typedef struct s_nodo {
        int val;
        struct s_nodo *left;
        struct s_nodo *right;
} nodo;
typedef nodo *albero;

pCountNode aggiungiincoda(int x, pCountNode head);
pCountNode riempilista(albero t, pCountNode head);
void stampalista(pCountNode lista);
albero creaAlbero();
albero createVal(int val);
pCountNode scorrilista(pCountNode lista);
int funzione_finale(pCountNode lista, int k, albero alb);

void print(albero t);
void printConLivello(albero t,int liv);
int scorrialbero(albero t, int k);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int val;
    int k=4;
    printf("\n");
    pCountNode head=NULL;
//    head=riempilista(alb, head);
    stampalista(head);
//    scorrilista(head);
//    printf("\n%d", val);
    val=funzione_finale(head, k, alb);
    printf("\n%d", val);
    
}




albero creaAlbero() {
       albero tmp = createVal(7);
       tmp->left = createVal(3);
       tmp->left->left = createVal(9);
       tmp->left->right = createVal(9);
       tmp->right = createVal(9);
       tmp->right->left = createVal(5);
       tmp->right->right = createVal(10);
       tmp->right->right->left = createVal(11);
       tmp->right->right->right = createVal(6);


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

pCountNode aggiungiincoda(int x, pCountNode head)
    {
    pCountNode new = (pCountNode)malloc(sizeof(CountNode));
    new->next=NULL;
    new->value=x;
    new->count=1;
        if(head==NULL)
            {
                return new;
            }
        pCountNode scorri=head;
        while(scorri->next!=NULL)
                scorri=scorri->next;
        scorri->next=new;
        return head;
    }
pCountNode riempilista(albero t, pCountNode head)
    {
        if(t==NULL)
            return head;
        head=aggiungiincoda(t->val, head);
        head=riempilista(t->left, head);
        head=riempilista(t->right, head);
        return head;
    }
void stampalista(pCountNode lista)
    {
        while(lista!=NULL)
        {
            printf("%d-->", lista->value);
            lista=lista->next;
        }
    }
pCountNode scorrilista(pCountNode lista)
    {
    pCountNode temp=lista;
    pCountNode ciclo=lista;
    if(lista==NULL)
        return NULL;
        while(temp->next!=NULL)
            {
                ciclo=temp->next;
                while(ciclo->next!=NULL)
                    {
                        if(ciclo->value==temp->value)
                            temp->count++;
                        ciclo=ciclo->next;
                    }
                temp=temp->next;
            }
        return lista;
    }
int funzione_finale(pCountNode lista, int k, albero alb)
    {
    lista=riempilista(alb, lista);
    lista=scorrilista(lista);
    while(lista!=NULL)
        {
            if(lista->count==k)
                return 1;
            lista=lista->next;
        }
    return 0;
    }
