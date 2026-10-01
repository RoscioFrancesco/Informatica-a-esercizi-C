//  Created by Francesco Roscio Ricon on 22/01/26.


#include <stdio.h>
#include <stdlib.h>

// Struttura dell'albero binario
typedef struct ET {
    int val;
    struct ET *left, *right;
} treeNode;

typedef treeNode *tree;

typedef struct EL {
    int grado;
    struct EL *next;
}Vagone;
typedef Vagone *Lista;



tree cn(int val);
void stampaAlbero(tree r, int spazio);
int checkTree(tree r);
tree costruisciAlbero1();
tree costruisciAlbero2();
tree costruisciAlbero3();
tree costruisciAlbero4();
Lista wrapper(tree albero);
Lista inserici_in_coda(Lista head, int valore);
Lista funzione(tree albero, Lista head, int somma);
void stampalista(Lista head);
int funzione_tot(tree albero);
int verificalista(Lista head);

int main() {
    tree t1=costruisciAlbero1();
    tree t2=costruisciAlbero2();
    tree t3=costruisciAlbero3();
    tree t4=costruisciAlbero4();

    printf("%d", funzione_tot(t1));
    printf("%d", funzione_tot(t2));
    printf("%d", funzione_tot(t3));
    printf("%d", funzione_tot(t4));
}



tree cn(int val){
    tree newNode=(tree)malloc(sizeof(treeNode));
    newNode->val=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

tree costruisciAlbero1(){
    tree r=cn(1);
    r->left=cn(5);
    r->right=cn(7);
    r->left->left=cn(21);
    r->left->right=cn(38);
    r->right->left=cn(12);
    r->right->right=cn(24);
    r->left->left->left=cn(100);
    r->left->left->right=cn(83);
    r->left->right->left=cn(67);
    r->right->right->left=cn(91);
    r->right->right->right=cn(75);
    return r;
}

tree costruisciAlbero2(){
    tree r=cn(8);
    r->left=cn(4);
    r->right=cn(2);
    r->left->left=cn(6);
    r->left->right=cn(11);
    r->right->left=cn(10);
    r->right->right=cn(14);
    r->left->left->left=cn(18);
    r->left->left->right=cn(30);
    r->left->right->left=cn(54);
    r->right->right->left=cn(72);
    r->right->right->right=cn(75);
    return r;
}

tree costruisciAlbero3(){
    tree r=cn(10);
    r->left=cn(5);
    r->right=cn(15);
    r->left->left=cn(1);
    r->left->right=cn(7);
    r->right->left=cn(12);
    r->right->right=cn(20);
    r->left->left->left=cn(0);
    r->left->left->right=cn(2);
    r->left->right->left=cn(6);
    r->right->right->left=cn(18);
    r->right->right->right=cn(5);
    return r;
}

tree costruisciAlbero4(){
    tree r=cn(9);
    r->left=cn(4);
    r->right=cn(14);
    r->left->left=cn(1);
    r->left->right=cn(6);
    r->right->left=cn(10);
    r->right->right=cn(18);
    r->left->left->left=cn(0);
    r->left->left->right=cn(2);
    r->left->right->left=cn(5);
    r->right->right->left=cn(17);
    r->right->right->right=cn(30);
    return r;
}

Lista funzione(tree albero, Lista head, int somma)
    {
        if(albero==NULL)
            return head;
        somma=somma+albero->val;
        if(albero->left==NULL && albero->right==NULL)
            {
                head=inserici_in_coda(head, somma);
            }
    head=funzione(albero->left, head, somma);
    head=funzione(albero->right, head, somma);
    return head;
    }

Lista inserici_in_coda(Lista head, int valore)
    {
    Lista new=(Lista)malloc(sizeof(Vagone));
    new->next=NULL;
    new->grado=valore;
    if(head==NULL)
        return new;
    Lista scorrilista=head;
    while (scorrilista->next!=NULL) {
        scorrilista=scorrilista->next;
    }
    scorrilista->next=new;
    return head;
    }

Lista wrapper(tree albero)
    {
    Lista head=NULL;
    head=funzione(albero, head, 0);
    return head;
    }

void stampalista(Lista head)
    {
    Lista scorrilista=head;
    while(scorrilista!=NULL)
        {
            printf("%d -->", scorrilista->grado);
            scorrilista=scorrilista->next;
        }
    }

int verificalista(Lista head)
    {
    if (head == NULL) return 0;
    Lista scorrilista=head;
    while(scorrilista->next!=NULL)
        {
            Lista scorrilista2=scorrilista->next;
            while(scorrilista2!=NULL)
                {
                    if(scorrilista->grado==scorrilista2->grado)
                        return 1;
                    scorrilista2=scorrilista2->next;
                }
            scorrilista=scorrilista->next;
        }
    return 0;
    }

int funzione_tot(tree albero)
    {
    Lista head=wrapper(albero);
    return verificalista(head);
}
