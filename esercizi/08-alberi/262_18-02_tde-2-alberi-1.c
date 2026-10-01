//
//  main.c
//  tde 2 alberi -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct El {
    int val;
    struct El *left, *right;
} Nodo;
typedef Nodo * Tree;


Tree nN(int v);
int altezza(Tree t);
void sp(int n);
void sL(Tree t,int l,int c);
void stampaAlbero(Tree t);
Tree costruisci1();
Tree costruisci2();
Tree costruisci3();
Tree costruisci4();
Tree costruisci5();
int verificanodo(Tree t, int s1, int s2);
void count(Tree t, int s1, int s2, int *c);
int conta(Tree t,int s1,int s2);

int main(){
    Tree t1=costruisci1(),t2=costruisci2(),t3=costruisci3(),t4=costruisci4(),t5=costruisci5();
    stampaAlbero(t1);printf("\n");
    stampaAlbero(t2);printf("\n");
    stampaAlbero(t3);printf("\n");
    stampaAlbero(t4);printf("\n");
    stampaAlbero(t5);printf("\n");


    printf("t1: %d\n",conta(t1,20,25));
    printf("t2: %d\n",conta(t2,2,6));
    printf("t3: %d\n",conta(t3,10,20));
    printf("t4: %d\n",conta(t4,10,15));
    printf("t5: %d\n",conta(t5,10,15));


    return 0;
}



Tree nN(int v){Tree n=(Tree)malloc(sizeof(Nodo));n->val=v;n->left=NULL;n->right=NULL;return n;}
int altezza(Tree t){int l,r;if(t==NULL)return 0;else{l=altezza(t->left);r=altezza(t->right);if(l>r)return(l+1);else return(r+1);}}
void sp(int n){int i;for(i=0;i<n;i++){printf(" ");}}
/*void sL(Tree t,int l,int c,int s){
    if(t==NULL){if(l>=c)sp(s);return;}
    if(l==c){sp(s/4-4);printf("   %d   ",t->val);sp(s/4-4);}else if(l>c){sL(t->left,l,c+1,s/2);sL(t->right,l,c+1,s/2);}
}*/
void st(Tree t){if(t==NULL)printf(" ");else printf("%d",t->val);}
void sL(Tree t,int l,int c){
    if(l==c && l==0){sp(40);st(t);sp(40);}
    if(l==c && l==1){sp(20);st(t);sp(20);}
    if(l==c && l==2){sp(10);st(t);sp(10);}
    if(l==c && l==3){sp(5);st(t);sp(5);}
    if(l==c && l==4){sp(2);st(t);sp(3);}
    if(t==NULL)return;
    sL(t->left,l,c+1);sL(t->right,l,c+1);
}
void stampaAlbero(Tree t){int i,h=altezza(t);for(i=1;i<=h;i++){sL(t,i,1);printf("\n");}}
Tree costruisci1(){Tree r=nN(8);r->left=nN(5);r->right=nN(8);r->left->left=nN(10);r->left->right=nN(9);r->right->left=nN(30);r->right->right=nN(2);return r;}
Tree costruisci2(){Tree r=nN(4);r->left=nN(5);r->right=nN(7);r->left->left=nN(1);r->left->right=nN(6);r->right->left=nN(30);r->right->right = nN(5);return r;}
Tree costruisci3(){Tree r=nN(3);r->left=nN(5);r->right=nN(4);r->left->left=nN(4);r->right->left=nN(3);r->right->right=nN(20);return r;}
Tree costruisci4(){Tree r=nN(1);r->left=nN(6);r->right=nN(6);r->left->left=nN(3);r->left->right=nN(8);r->right->left=nN(3);r->right->right=nN(2);r->right->right->right=nN(5);r->right->right->left=nN(10);return r;}
Tree costruisci5(){Tree r=nN(2);r->left=nN(5);r->right=nN(8);r->left->left=nN(6);r->left->right=nN(9);r->right->left=nN(3);r->right->right=nN(2);return r;}


int verificanodo(Tree t, int s1, int s2)
    {
        if(t==NULL)
            return 0;
        if(!(t->left!=NULL && t->right!=NULL))
            return 0;
        int somma=0;
        somma=t->val+t->left->val+t->right->val;
        if(somma>=s1 && somma<=s2)
            return 1;
        return 0;
    }
int conta(Tree t,int s1,int s2)
{
    int num=0;
    count(t, s1, s2, &num);
    return num;
}

void count(Tree t, int s1, int s2, int *c)
    {
        if(t==NULL)
            return;
        if(verificanodo(t, s1, s2))
            (*c)++;
    count(t->left, s1, s2, c);
    count(t->right, s1, s2, c);
    }
