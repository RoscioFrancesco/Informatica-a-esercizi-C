//
//  main.c
//  tde 14 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//

#define N 1000
#include <stdlib.h>

typedef struct { int giorno, mese, anno; } Data;
typedef struct P { char come[N], cognomen[N];
                           Data dataNascita;
    struct P * next; } Persona;
typedef struct Li { char ISBN[N], titolo[N];
                            Persona * autore;
                            Data dataPubblicazione;
                Data dataUltimoPrestito;
                int prezzo;
                            struct Li * next; } Libro;
typedef Libro * Biblioteca;
Persona * inseriscincoda2(Persona *lista, Persona p);
Persona *copialista(Persona *head);
void distruggi(Persona *aut);
int èmin(Persona *p, Data data_pub)
    {
    
    while(p!=NULL)
    {
        if(-p->dataNascita.anno+data_pub.anno>18)
            return 0;
        p=p->next;
    }
    return 1;
    }
Biblioteca inseriscincoda(Biblioteca b, Libro x)
    {
        if(b==NULL)
            {
                Biblioteca new=(Biblioteca)malloc(sizeof(*new));
                *new=x;
                new->autore=copialista(x.autore);
                new->next=NULL;
                return new;
            }
    b->next=inseriscincoda(b->next, x);
    return b;
    }

Biblioteca f(Biblioteca bib)
    {
    Biblioteca new=NULL;
    while(bib!=NULL)
        {
            if(èmin(bib->autore, bib->dataPubblicazione))
                {
                    new=inseriscincoda(new, *bib);
                }
            bib=bib->next;
        }
    return new;
    }
int verifica(Data oggi, Biblioteca l)
    {
        if(oggi.anno-l->dataUltimoPrestito.anno>10)
            return 1;
    return 0;
    }

Biblioteca eliminaLibriInutilizzati(Biblioteca libri, Data oggi)
    {
    if(libri==NULL)
        return libri;
    if(verifica(oggi, libri))
        {
            Biblioteca succ=libri->next;
            distruggi(libri->autore);
            free(libri);
            libri=succ;
            return eliminaLibriInutilizzati(libri, oggi);
        }
    libri->next=eliminaLibriInutilizzati(libri->next, oggi);
    return libri;
    }
Persona *copialista(Persona *head)
    {
        if(head==NULL)
            return NULL;
    Persona *new=NULL;
        while(head!=NULL)
            {
                new=inseriscincoda2(new, *head);
                head=head->next;
            }
    return new;
    }
Persona * inseriscincoda2(Persona *lista, Persona p)
    {
        if(lista==NULL)
            {
                Persona *new=malloc(sizeof(*new));
                *new=p;
                new->next=NULL;
                return new;
            }
    lista->next=inseriscincoda2(lista, p);
    return lista;
    }
void distruggi(Persona *aut)
    {
        if(aut==NULL)
            return;
        Persona *temp=aut->next;
        free(aut);
        aut=temp;
        distruggi(aut);
    }
