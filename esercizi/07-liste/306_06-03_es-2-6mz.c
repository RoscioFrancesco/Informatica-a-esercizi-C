//
//  main.c
//  es 2 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//Esercizio 3 — Casa editrice e autori coerenti


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct EL{
    char titolo[100];
    char cognome[100];
    int anno;
    float prezzo;
    char genere[100];
    struct EL *next;
}Libro;
typedef Libro * Lista_libri;

typedef struct ES{
    char nome[100];
    char cognoem[100];
    char naz[100];
    Lista_libri l;
    struct ES*next;
}Autore;
typedef Autore *Lista_Autori;

typedef struct EM{
    char nome[100];
    char cognoem[100];
    char naz[100];
    Lista_libri l;
    int num;
    struct EM*next;
}Autore2;
typedef Autore2 *Lista_Autori2;


Lista_libri inserisciLibro(Lista_libri head, Libro x);

int main() {

}
// prezzi in ordinew crescente
int coer(Autore a)
    {
    if(a.l==NULL)
        return 0;
    Lista_libri scorri=a.l;
    int count=0;
    char g[100];
    float pz=a.l->prezzo;
    strcpy(g, a.l->genere);
    while(scorri!=NULL && scorri->next!=NULL)
        {
            if(strcmp(scorri->genere, g)!=0)
                return 0;
            if(scorri->prezzo>=scorri->next->prezzo)
                return 0;
            count++;
            scorri=scorri->next;
        }
    if(count<3)
        return 0;
    return 1;
    }
Lista_libri copialista(Lista_libri head)
    {
        if(head==NULL)
            return NULL;
    Lista_libri new=NULL;
        while(head!=NULL)
            {
                new=inserisciLibro(new, *head);
                head=head->next;
            }
    return new;
    }
Lista_libri inserisciLibro(Lista_libri head, Libro x)
    {
        if(head==NULL)
            {
                Lista_libri new=(Lista_libri)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisciLibro(head->next, x);
    return head;
    }
Lista_Autori inserisciautore(Lista_Autori head, Autore x)
    {
        if(head==NULL)
            {
                Lista_Autori new=(Lista_Autori)malloc(sizeof(*new));
                *new=x;
                new->l=copialista(x.l);
                new->next=NULL;
                return new;
            }
    head->next=inserisciautore(head->next, x);
    return head;
    }
Lista_Autori autoriCoerenti(Lista_Autori A)
    {
        if(A==NULL)
            return NULL;
        Lista_Autori new=NULL;
        while(A!=NULL)
            {
                if(coer(*A))
                    {
                        new=inserisciautore(new, *A);
                    }
                A=A->next;
            }
    return new;
    }
int conta(Autore a)
    {
    Lista_libri p=a.l;
    int c=0;
    while(p!=NULL)
        {
            c++;
            p=p->next;
        }
    return c;
    }

