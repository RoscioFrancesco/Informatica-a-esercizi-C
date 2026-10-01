//
//  main.c
//  tde liste da capo
//
//  Created by Francesco Roscio Ricon on 24/01/26.
// funzione eliminapicchi

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo{
int valore;
struct nodo* next;
} nodo;
typedef nodo* lista;

lista InsInFondo(lista lis, int elem);
void VisualizzaLista(lista lis);
lista costruisci();
int èunpicco(lista prec, lista scorrilista, lista succ);
void stampalista(lista head);
lista eliminapicchio(lista head);

int main(){
lista lis = costruisci();

    stampalista(lis);
    lis=eliminapicchio(lis);
    printf("\n");
    stampalista(lis);
}


lista InsInFondo(lista lis, int elem) {
lista punt;
if(lis == NULL){
    punt = malloc(sizeof(nodo));
    punt->next   = NULL;
    punt->valore = elem;
    return punt;
}
else {
    lis->next = InsInFondo(lis->next, elem);
    return lis;
}
}


void VisualizzaLista( lista lis ) {
if ( lis == NULL )
    printf(" ---| \n");
else {
    printf(" %d\n ---> ", lis->valore);
    VisualizzaLista( lis->next );
}
}

lista costruisci(){
// 1 -> 9 -> 4 -> 7 -> 7 -> 1 -> 11 -> 5 -> 7 -> 1 -> 5
lista lis = NULL;
lis = InsInFondo(lis, 1);
lis = InsInFondo(lis, 5);
lis = InsInFondo(lis, 16);
lis = InsInFondo(lis, 11);
lis = InsInFondo(lis, 12);
lis = InsInFondo(lis, 4);
lis = InsInFondo(lis, 5);
lis = InsInFondo(lis, 5);
lis = InsInFondo(lis, 3);
lis = InsInFondo(lis, 1);
lis = InsInFondo(lis, 5);

return lis;
}

lista eliminapicchio(lista head)
    {
    if(head==NULL)
        return head;
    lista prec=head;
    lista scorrilista=head->next;
    while(scorrilista->next!=NULL)
        {
            lista succ=scorrilista->next;
            if(èunpicco(prec, scorrilista, succ))
                {
                    prec->next=succ;
                    free(scorrilista);
                    scorrilista=succ;
                }
            else
                {
                    prec=scorrilista;
                    scorrilista=succ;
                }
        }
        return head;
    }
int èunpicco(lista prec, lista scorrilista, lista succ)
    {
        if(prec->valore<scorrilista->valore && scorrilista->valore>succ->valore)
            return 1;
    return 0;
    }
void stampalista(lista head)
    {
    lista scorrilista=head;
    while (scorrilista!=NULL) {
        printf("%d-->", scorrilista->valore);
        scorrilista=scorrilista->next;
    }
    }
