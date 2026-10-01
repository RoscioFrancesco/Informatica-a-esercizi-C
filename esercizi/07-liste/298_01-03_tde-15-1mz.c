//
//  main.c
//  tde 15 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//

# include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Elem {   char * parola;
struct Elem * next; } Nodo;
typedef Nodo * Lista;

typedef struct Elem2 { Lista catena;
                       struct Elem2 * next; } NodoTesta;
typedef NodoTesta * ListaDiListe;

int palindroma(char parola[])
    {
    int i=0;
    int j=strlen(parola)-1;
    while(i<j)
        {
            if(parola[i]!=parola[j])
                return 0;
            i++;
            j--;
        }
    return 1;
    }
int ver(Lista head)
    {
    Lista scorri=head;
    int count=0;
    while(scorri!=NULL)
        {
            if(palindroma(scorri->parola))
                count++;
            scorri=scorri->next;
        }
    if(count>=2)
        return 1;
    return 0;
    }
ListaDiListe elimina(ListaDiListe head)
    {
    if(head==NULL)
        return head;
        if(ver(head->catena))
            {
                ListaDiListe temp=head->next;
                free(head);
                head=temp;
                return elimina(head);
            }
    head->next=elimina(head->next);
    return head;
    }
