//  Created by Francesco Roscio Ricon on 19/01/26.

#include <stdio.h>
#include <stdlib.h>


typedef struct E {
    int matricola;
    int codiceEsame;
    int voto;
    struct E *next;
} Esame;
typedef Esame *ListaEsami;


typedef struct S {
   int matricola;
   int numEsami;
   float media;
   struct S * next;
} Studente;
typedef Studente *ListaStudenti;


ListaEsami crea();

float calcolamedia(ListaEsami lista, int matricola, int*contatore);
ListaStudenti inserisciincoda(ListaStudenti head, float media, int num_esami, int matricola);
ListaStudenti funzione(ListaEsami lista);


int main() {
    ListaEsami listaEsami=crea();
    ListaStudenti listaStudenti=NULL;
    ListaEsami current=listaEsami;
    ListaStudenti cur;
    while (current != NULL) {
        printf("Matricola: %d, Codice Esame: %d, Voto: %d\n", current->matricola, current->codiceEsame, current->voto);
        current=current->next;
    }
    printf("\n");

    listaStudenti=funzione(listaEsami);
    cur=listaStudenti;
    while (cur->next != NULL) {
        printf("Matricola: %d, Numero Esami: %d, Media: %f\n", cur->matricola, cur->numEsami, cur->media);
        cur=cur->next;
    }


    return 0;
}


ListaEsami crea(){
    int i;ListaEsami esami=malloc(sizeof(Esame)*30);
    esami[0]=(Esame){1001,101,28,0};esami[1]=(Esame){1002,102,25,0};esami[2]=(Esame){1001,103,30,0};esami[3]=(Esame){1003,104,22,0};esami[4]=(Esame){1002,105,27,0};esami[5]=(Esame){1001,106,26,0};esami[6]=(Esame){1004,107,29,0};esami[7]=(Esame){1004,108,31,0};esami[8]=(Esame){1004,109,26,0};esami[9]=(Esame){1004,110,27,0};esami[10]=(Esame){1004,111,30,0};esami[11]=(Esame){1005,112,24,0};esami[12]=(Esame){1005,113,28,0};esami[13]=(Esame){1005,114,30,0};esami[14]=(Esame){1005,115,25,0};esami[15]=(Esame){1005,116,29,0};esami[16]=(Esame){1005,117,27,0};esami[17]=(Esame){1005,118,26,0};esami[18]=(Esame){1006,119,27,0};esami[19]=(Esame){1006,120,28,0};esami[20]=(Esame){1006,121,29,0};esami[21]=(Esame){1006,122,30,0};esami[22]=(Esame){1006,123,31,0};esami[23]=(Esame){1006,124,27,0};esami[24]=(Esame){1006,125,28,0};esami[25]=(Esame){1006,126,29,0};esami[26]=(Esame){1003,127,26,0};esami[27]=(Esame){1003,128,24,0};esami[28]=(Esame){1002,129,31,0};esami[29]=(Esame){1001,130,29,0};
    for(i=0;i<29;i++){esami[i].next=&esami[i+1];}esami[29].next=NULL;return esami;
}

ListaStudenti funzione(ListaEsami lista)
    {
        if(lista==NULL)
            return NULL;
        ListaEsami scorri_esami=lista;
    ListaStudenti head=NULL;
        while (scorri_esami!=NULL)
        {
            int contatore=0;
            float media=calcolamedia(lista, scorri_esami->matricola, &contatore);
            head=inserisciincoda(head, media, contatore, scorri_esami->matricola);
            contatore=0;
            scorri_esami=scorri_esami->next;
        }
        return head;
    }

float calcolamedia(ListaEsami lista, int matricola, int*contatore)
    {
    ListaEsami scorri_lista=lista;
    float somma=0;
    while(scorri_lista!=NULL)
        {
            if(matricola==scorri_lista->matricola)
            {
                (*contatore)++;
                somma=somma+scorri_lista->voto;
            }
            scorri_lista=scorri_lista->next;
        }
    return somma/(*contatore);
    }

ListaStudenti inserisciincoda(ListaStudenti head, float media, int num_esami, int matricola)
    {
        ListaStudenti new=malloc(sizeof(Studente));
        new->next=NULL;
        new->matricola=matricola;
        new->media=media;
        new->numEsami=num_esami;
    ListaStudenti scorristudenti=head;
        if(scorristudenti==NULL)
            {
                return new;
            }
        while(scorristudenti->next!=NULL)
            {
                if(scorristudenti->matricola==matricola)
                    return head;
                scorristudenti=scorristudenti->next;
            }
        scorristudenti->next=new;
        return head;
        
    }
