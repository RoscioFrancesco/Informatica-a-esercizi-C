//
//  main.c
//  es 4 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//
//Una scuola è rappresentata da una lista di classi.
//Ogni classe contiene:
//una matrice int voti[25][6], dove ogni riga è uno studente e ogni colonna una prova
//una lista di assenti cronici
//Ogni nodo della lista degli assenti contiene:
//matricola studente
//numero totale di assenze
//Definisci le strutture.
//Scrivi la funzione:
//void eliminaClassiProblematiche(ListaClassi *L, int sogliaAssenze);
//che elimina tutte le classi in cui:
//almeno 8 studenti hanno media strettamente minore di 6 nella matrice dei voti
//nella lista degli assenti esistono almeno 4 studenti con assenze maggiori di sogliaAssenze
//La lista va modificata direttamente.
#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int matricola;
    int numero_assenze;
    struct EL* next;
}Studente;
typedef Studente *Lista;

typedef struct ES{
    int codiceclasse;
    int voti[25][6];
    Lista stud;
    struct ES *next;
}Classe;
typedef Classe *Lista_classi;
void distrggui(Lista head);
int main() {

}
int ver(Classe cl, int soglia)
    {
    int n=0;
    for(int r=0; r<25; r++)
        {
            float somma=0;
            float count=0;
            for(int c=0; c<6;c++)
                {
                    somma=somma+cl.voti[r][c];
                    count++;
                }
            if(somma/count<6)
                {
                    n++;
                }
        }
    Lista scorri=cl.stud;
    int c2=0;
    while(scorri!=NULL)
        {
            if(scorri->numero_assenze>soglia)
                c2++;
            scorri=scorri->next;
        }
    if(c2>=4 && n>=6)
        return 1;
    return 0;
    }
void eliminaClassiProblematiche(Lista_classi *L, int sogliaAssenze)
    {
    Lista_classi *pp=L;
    while(*pp!=NULL)
        {
            if(ver(**pp, sogliaAssenze))
                {
                    Lista_classi temp=*pp;
                    (*pp)=(*pp)->next;
                    distrggui(temp->stud);
                    free(temp);
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
void distrggui(Lista head)
    {
        if(head==NULL)
            return;
        Lista temp=head->next;
        free(head);
    distrggui(temp);
    }
