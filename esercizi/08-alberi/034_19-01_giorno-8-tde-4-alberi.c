//  Created by Francesco Roscio Ricon on 19/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;


typedef Nodo *Albero;


Albero nN(char valore);
void stampaAlbero(Albero t);
void print(Albero t);
Albero costruisci1();
Albero costruisci2();
Albero costruisci3();
Albero costruisci4();

int cercaCammino(Albero t, char stringa[]);
void funzione(Albero t,char stringa[], int segnaposto, int *verità);
int controllaAlberi(Albero t_a, Albero t_b);
int controllaric(Albero t_a, Albero t_b, char stringa[], int pos);
int main() {


    Albero t1 = costruisci1();  // albero di riferimento
    Albero t2 = costruisci2();
    Albero t3 = costruisci3();
    Albero t4 = costruisci4();


    stampaAlbero(t1);
    stampaAlbero(t2);
    stampaAlbero(t3);
    stampaAlbero(t4);


    if(cercaCammino(t1,"ciano"))
        printf("ciano PRESENTE IN T1\n");
    else
        printf("ciano NON PRESENTE IN T1\n");


    if(cercaCammino(t3,"col"))
        printf("col PRESENTE IN T3\n");
    else
        printf("col NON PRESENTE IN T3\n");


    if(controllaAlberi(t1, t2))
        printf("t1 e t2 OK\n");
    else
        printf("t1 e t2 NON OK\n");


    if(controllaAlberi(t1, t3))
        printf("t1 e t3 OK\n");
    else
        printf("t1 e t3 NON OK\n");


    if(controllaAlberi(t1, t4))
        printf("t1 e t4 OK\n");
    else
        printf("t1 e t4 NON OK\n");


    return 0;
}




// Funzione per creare un nuovo nodo
Albero nN(char valore) {
    Albero nodo = (Albero) malloc(sizeof(Nodo));
    nodo->c = valore;nodo->left = NULL;nodo->right = NULL;
    return nodo;
}


// Funzione per stampare l'albero
void stampaAlbero(Albero t) {
    print(t);
    printf("\n");
}


void print(Albero t) {
    if (t == NULL)return;
    else {printf(" (");print(t->left);printf(" %c ", t->c);print(t->right);printf(") ");}
}


Albero costruisci1() {
    Albero radice = nN('c');
    radice->left = nN('i');
    radice->right = nN('o');
    radice->left->left = nN('a');
    radice->left->right = nN('n');
    radice->right->left = nN('l');
    radice->left->left->left = nN('o');
    radice->left->left->right = nN('n');
    radice->left->left->right->right = nN('o');
    return radice;
}


Albero costruisci2() {
    Albero radice = nN('c');
    radice->left = nN('o');
    radice->left->left = nN('l');
    radice->left->right = nN('t');
    radice->left->right->left = nN('t');
    radice->left->right->left->right = nN('o');
    radice->right = nN('i');
    radice->right->left = nN('n');
    radice->right->right = nN('a');
    radice->right->right->left = nN('o');
    radice->right->right->right = nN('n');
    radice->right->right->right->left = nN('o');
    return radice;
}


Albero costruisci3() {
    Albero radice = nN('c');
    radice->left = nN('o');
    radice->left->left = nN('l');
    radice->left->left->left = nN('l');
    radice->left->left->left->left = nN('o');
    radice->left->right = nN('t');
    radice->left->right->left = nN('t');
    radice->left->right->left->right = nN('o');
    radice->right = nN('i');
    radice->right->left = nN('n');
    radice->right->right = nN('a');
    radice->right->right->left = nN('o');
    radice->right->right->right = nN('n');
    radice->right->right->right->left = nN('o');
    return radice;
}


Albero costruisci4() {
    Albero radice = nN('c');
    radice->left = nN('o');
    radice->left->left = nN('l');
    radice->left->right = nN('t');
    radice->left->right->left = nN('t');
    radice->left->right->left->right = nN('o');
    radice->right = nN('i');
    radice->right->left = nN('m');
    radice->right->right = nN('a');
    radice->right->right->left = nN('o');
    radice->right->right->right = nN('n');
    radice->right->right->right->left = nN('o');
    return radice;
}


void funzione(Albero t,char stringa[], int segnaposto, int *verità)
{
    if(t==NULL)
        return;
    if(t->c==stringa[segnaposto])
        {
            if(t->left==NULL && t->right==NULL && stringa[segnaposto+1]=='\0')
            {
                *verità=1;
            }
            (segnaposto)=(segnaposto)+1;
            funzione(t->left, stringa, segnaposto, verità);
            funzione(t->right, stringa, segnaposto, verità);
        }
    
}
int cercaCammino(Albero t, char stringa[])
    {
    int verità=0;
    int segnaposto=0;
    funzione(t, stringa, segnaposto, &verità);
    if(verità==1)
        return 1;
    return 0;
    }


int controllaric(Albero t_a, Albero t_b, char stringa[], int pos)
    {
        if(t_a==NULL)
            return 1;
    stringa[pos]=t_a->c;
    stringa[pos+1]='\0';
    pos++;
    if(t_a->left==NULL && t_a->right==NULL)
        return cercaCammino(t_b, stringa);
    return controllaric(t_a->left, t_b, stringa, pos)&&controllaric(t_a->right, t_b, stringa, pos);
    }
int controllaAlberi(Albero t_a, Albero t_b)
    {
        char stringa[10];
    int ris=controllaric(t_a, t_b, stringa, 0);
    return ris;
    }
