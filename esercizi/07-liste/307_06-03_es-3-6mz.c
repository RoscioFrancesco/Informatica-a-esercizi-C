//
//  main.c
//  es 3 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//
//Esercizio 2 — Eliminare classi insufficienti
//Una scuola è rappresentata da una lista di classi.
//Ogni classe ha una matrice:
//int voti[25][6];
//dove ogni riga rappresenta uno studente e ogni colonna una prova scritta.
//Definisci la struttura Classe con:
//nomeClasse
//docenteCoordinatore
//matrice voti[25][6]
//puntatore al prossimo nodo
//Scrivi la funzione:
//void eliminaClassiDeboli(ListaClassi *L);
//che elimina tutte le classi in cui almeno 10 studenti hanno media strettamente minore di 6.
//La lista va modificata direttamente.



#include <stdio.h>
#include <stdlib.h>

typedef struct EL{
    char nomeClasse[100];
    char docente[100];
    int voti[25][6];
    struct EL *next;
}Classe;
typedef Classe *Lista;

int main() {

}

int ver(Lista head)
    {
    int count=0;
    for(int r=0; r<25; r++)
        {
            float somma=0;
            float n=0;
            for(int c=0; c<6; c++)
                {
                    somma=somma+head->voti[r][c];
                    n++;
                }
            if(somma/n<6)
                count++;
        }
    if(count>=10)
        return 1;
    return 0;
    }

void eliminaClassiDeboli(Lista *L)
    {
        if(*L==NULL)
            return;
        Lista *pp=L;
        while(*pp!=NULL)
            {
                if(ver(*pp))
                    {
                        Lista temp=*pp;
                        (*pp)=(*pp)->next;
                        free(temp);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
Lista elimina(Lista head)
    {
        if(head==NULL)
            return head;
        if(ver(head))
            {
                Lista temp=head->next;
                free(head);
                head=temp;
                return elimina(head);
            }
    head->next=elimina(head->next);
    return head;
    }
