//
//  main.c
//  tde alberi -2 tosto
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct n {
        int val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;

typedef struct EL {
        int val;
    int livello;
    struct EL * next;
} elem;
typedef elem * Lista;


void stampalista(Lista head);
albero createVal(int val);
albero creaAlbero1();albero creaAlbero2();albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int f(albero t);
int depth(albero t);
int max(int a,int b);
void inizializza(albero t,int v[],int liv);
void verifica(albero t,int elem[],int v[],int liv);
Lista scorrialbero(albero T, int livello, Lista head);
Lista wrapper(albero T);
Lista inseriscincoda(Lista head, int val, int livello);

int main(){
    int ris=0;
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);
    
   printf("T1: %d\n",f(T1));
   printf("T2: %d\n",f(T2));
   printf("T3: %d\n",f(T3));
   
   return 0;
}



albero creaAlbero1() {
    albero tmp = createVal(7);
    tmp->left = createVal(3);tmp->left->left = createVal(9);tmp->left->right = createVal(9);
    tmp->right = createVal(8);tmp->right->left = createVal(9);tmp->right->right = createVal(9);
    tmp->right->right->left = createVal(11); tmp->right->right->right = createVal(6);
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal(7);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(1);tmp->left->right = createVal(5);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(11);tmp->left->left->left = createVal(6);
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal(7);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(4);tmp->left->right = createVal(5);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(2);tmp->left->left->left = createVal(6);
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
Lista inseriscincoda(Lista head, int val, int livello)
    {
    Lista new=(Lista)malloc(sizeof(elem));
    new->next=head;
    new->val=val;
    new->livello=livello;
    return new;
    }
Lista scorrialbero(albero T, int livello, Lista head)
    {
        if(T==NULL)
            return head;
    head=inseriscincoda(head, T->val, livello);
    head=scorrialbero(T->left, livello+1, head);
    head=scorrialbero(T->right, livello+1, head);
    return head;
    }
Lista wrapper(albero T)
    {
    Lista head=NULL;
    head=scorrialbero(T, 0, head);
    return head;
    }
int f(albero t)
    {
    Lista head=wrapper(t);
    Lista scorrilista=head;
    while (scorrilista!=NULL) {
        if (scorrilista->livello == 0) {
                    scorrilista = scorrilista->next;
                    continue;
                }
        Lista j=head;
        int flag=0;
        while(j!=NULL)
            {
                if(j->livello==scorrilista->livello)
                    {
                        if(j->val!=scorrilista->val)
                        {
                            flag=1;
                            break;
                        }
                    }
                j=j->next;
            }
        if(flag==0)
            return 1;
        scorrilista=scorrilista->next;
    }
    return 0;
}
