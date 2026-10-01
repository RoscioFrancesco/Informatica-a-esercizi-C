//  Created by Francesco Roscio Ricon on 25/01/26.

#include <stdio.h>
#include <stdlib.h>


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
int controllaAlberi(Albero ta, Albero tb);
int cercacammino(Albero tree, char parola[], int livello);
int cercaCammino(Albero tree, char parola[]);
void creaparola(Albero tree, char parola[], int livello);
int funz(Albero TA, Albero TB, char parola[], int livello);
int controllaAlberi(Albero T1, Albero T2);

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
}
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
int cercacammino(Albero tree, char parola[], int livello)
    {
        if(tree==NULL)
            return 0;
        if(tree->c!=parola[livello])
            return 0;
        if (parola[livello + 1] == '\0')
            return (tree->left == NULL && tree->right == NULL);

        if(tree->left==NULL && tree->right==NULL)
            {
                if(parola[livello]==tree->c)
                    return 1;
                return 0;
            }
    return cercacammino(tree->left, parola, livello+1) || cercacammino(tree->right, parola, livello+1);
    }
int cercaCammino(Albero tree, char parola[])
    {
    return cercacammino(tree, parola, 0);
    }

//void creaparola(Albero tree, char parola[], int livello) questo funziona ma non è utile
//    {
//        if(tree==NULL)
//            {
//                return;
//            }
//        parola[livello]=tree->c;
//        if(tree->left==NULL && tree->right==NULL)
//        {
//            parola[livello+1]='\0';
//            return;
//        }
//    creaparola(tree->left, parola, livello+1);
//    creaparola(tree->right, parola, livello+1);
//    }

int funz(Albero TA, Albero TB, char parola[], int livello)
    {
        if(TA==NULL)
            return 1;
        parola[livello]=TA->c;
        if(TA->left==NULL && TA->right==NULL)
            {
                parola[livello+1]='\0';
                return cercaCammino(TB, parola);
            }
    return funz(TA->left, TB, parola, livello+1) && funz(TA->right, TB, parola, livello+1);
    
    }
int controllaAlberi(Albero T1, Albero T2)
    {
    char parola[11];
    return funz(T1, T2,parola, 0);
    }
