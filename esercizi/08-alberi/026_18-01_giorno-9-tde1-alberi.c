//  Created by Francesco Roscio Ricon on 18/01/26.

//  Si consiglia molto fortemente l’uso di funzioni ausiliarie con parametri aggiuntivi che “trasportino” nelle chiamate informazioni utili.

#include <stdio.h>
#include <stdlib.h>


typedef struct n {
    int val;
    struct n *left;
    struct n *right;
} nodo;
typedef nodo *albero;

typedef struct EL
    {
    float media;
    struct EL *next;
}vagone;
typedef vagone *lista;

float trovamin(lista head);

albero createVal(int val);
albero creaAlbero1();
albero creaAlbero2();
albero creaAlbero3();


void print(albero t);
void stampa(albero T);
float costoMinimoMedio(albero T);
lista wrapper(albero t);
lista crealista(albero t, lista head);
void percorso(albero t, int somma, int count, lista *head);
float megawrapper(albero t);
float trovamin(lista head);

int main() {
    albero T1, T2, T3;
    T1 = creaAlbero1();
    T2 = creaAlbero2();
    T3 = creaAlbero3();


    printf("\nT1: ");
    stampa(T1);
    printf("\nT2: ");
    stampa(T2);
    printf("\nT3: ");
    stampa(T3);


    // visualizzazione risultati e invocazione funzione
    printf("Il percorso di T1 con media di valori minima ha media: %f\n", megawrapper(T1));
    printf("Il percorso di T2 con media di valori minima ha media: %f\n", megawrapper(T2));
    printf("Il percorso di T3 con media di valori minima ha media: %f\n", megawrapper(T3));


    return 0;
}


float costoMinimoMedio(albero T){
    //TODO: return da cancellare
    return 0;
}


albero creaAlbero1() {
    albero tmp = createVal(7);
    tmp->left = createVal(3);
    tmp->left->left = createVal(9);
    tmp->left->right = createVal(10);
    tmp->right = createVal(8);
    tmp->right->left = createVal(5);
    tmp->right->right = createVal(12);
    tmp->right->right->left = createVal(11);
    tmp->right->right->right = createVal(6);
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal(8);
    tmp->left = createVal(5);
    tmp->right = createVal(12);
    tmp->right->left = createVal(11);
    tmp->right->right = createVal(6);
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal(8);
    tmp->left = createVal(5);
    tmp->right = createVal(0);
    tmp->right->left = createVal(1);
    tmp->right->right = createVal(5);
    return tmp;
}


void print(albero t) {
    if (t == NULL)return;
    else {
        printf(" (");
        print(t->left);
        printf(" %d ", t->val);
        print(t->right);
        printf(") ");
    }
}


void stampa(albero T) {
    print(T);
    printf("\n");
}


albero createVal(int val) {
    albero tmp = (albero)malloc(sizeof(nodo));
    tmp->val = val;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

//void percorso(albero t, int* somma, int *count)
//    {
//    if(t==NULL)
//        return;
//    if(t->left==NULL && t->right==NULL)
//        return;
//    (*somma)=(*somma)+t->val;
//    (*count)=(*count)+1;
//    percorso(t->left, somma, count);
//    percorso(t->right, somma, count);
//}

void percorso(albero t, int somma, int count, lista *head)
{
    if (t == NULL) return;

    somma += t->val;
    count += 1;

    // se foglia: calcola media e inserisci in lista
    if (t->left == NULL && t->right == NULL) {
        float media = (float)somma / (float)count;

        lista new = (lista)malloc(sizeof(vagone));
        new->media = media;
        new->next = *head;
        *head = new;
        return;
    }

    // continua sui figli
    percorso(t->left,  somma, count, head);
    percorso(t->right, somma, count, head);
}


lista crealista(albero t, lista head)
    {
    int somma=0;
    int count=0;
    percorso(t, somma, count, &head);
    return head;
    }

lista wrapper(albero t)
    {
        lista elenco=NULL;
        if(t==NULL)
            return elenco;
        elenco=crealista(t, elenco);
    return elenco;
    }
float trovamin(lista head)
    {
        if(head==NULL)
            return 0;
        float min=head->media;
        while(head!=NULL)
            {
                if(head->media<min)
                    {
                        min=head->media;
                    }
                head=head->next;
            }
    return min;
    }
float megawrapper(albero t)
    {
    lista head=NULL;
    head=wrapper(t);
    float min=0;
    min=trovamin(head);
    return min;
    }
