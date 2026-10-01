#include <stdio.h>
#include <stdlib.h>


typedef struct n {
        int val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;

typedef struct EL{
    int val;
    int livello;
    struct EL * next;
}Vagone;
typedef Vagone* Lista;

albero createVal(int val);
albero creaAlbero1();albero creaAlbero2();albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int f(albero t);
int depth(albero t);
int max(int a,int b);
void inizializza(albero t,int v[],int liv);
void verifica(albero t,int elem[],int v[],int liv);
Lista inserisci_in_coda(Lista head, int val, int livello);
Lista wrapper(albero tree);
Lista crea_lista(albero tree, int livello, Lista head);
void stampalista(Lista head);
albero creaAlbero4();
int f(albero tree);

int main(){
    int ris=0;
    albero T1,T2,T3, T4;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    T4=creaAlbero4();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);


  
    Lista head1=NULL;
    head1=wrapper(T1);
    stampalista(head1);
    printf("\n");
    
    Lista head2=NULL;
    head2=wrapper(T2);
    stampalista(head2);
    printf("\n");
    Lista head3=NULL;
    head3=wrapper(T3);
    stampalista(head3);
    printf("\n");
    Lista head4=NULL;
    head4=wrapper(T4);
    stampalista(head4);
    printf("\n");
   printf("T1: %d\n",f(T1));
   printf("T2: %d\n",f(T2));
   printf("T3: %d\n",f(T3));
    printf("T3: %d\n",f(T4));
   
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

albero creaAlbero4() {
    albero tmp = createVal(1);

    tmp->left = createVal(2);
    tmp->right = createVal(2);

    tmp->left->left = createVal(3);
    tmp->left->right = createVal(3);
    tmp->right->left = createVal(3);
    tmp->right->right = createVal(3);

    tmp->left->left->left = createVal(4);
    tmp->left->left->right = createVal(4);

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

Lista crea_lista(albero tree, int livello, Lista head)
    {
        if(tree==NULL)
            return head;
        head=inserisci_in_coda(head, tree->val, livello);
        head=crea_lista(tree->left, livello+1, head);
        head= crea_lista(tree->right, livello+1, head);
    return head;
        }
Lista inserisci_in_coda(Lista head, int val, int livello)
    {
    Lista new=(Lista)malloc(sizeof(Vagone));
    new->next=NULL;
    new->val=val;
    new->livello=livello;
    if(head==NULL)
        {
            return new;
        }
    Lista scorrilista=head;
    while(scorrilista->next!=NULL)
        {
            scorrilista=scorrilista->next;
        }
    scorrilista->next=new;
    return head;
    }
Lista wrapper(albero tree)
    {
    Lista head=NULL;
    head=crea_lista(tree, 0, head);
    return head;
    }
void stampalista(Lista head)
    {
    Lista temp=head;
    while(temp!=NULL)
        {
            printf("(%d, %d) -->", temp->val, temp->livello);
            temp=temp->next;
        }
    }

int f(albero tree)
    {
    Lista head=NULL;
    head=wrapper(tree);
    Lista scorrilista=head;
    while(scorrilista!=NULL)
        {
            Lista doppio_scorrilista=head;
            while(doppio_scorrilista!=NULL)
                {
                    if(doppio_scorrilista->livello==scorrilista->livello)
                        {
                            if(doppio_scorrilista->val!=scorrilista->val)
                                return 0;
                        }
                    doppio_scorrilista=doppio_scorrilista->next;
                }
            scorrilista=scorrilista->next;
        }
    return 1;
    }
