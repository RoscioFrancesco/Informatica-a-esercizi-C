//  Created by Francesco Roscio Ricon on 15/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct c { char c;
                   struct c * next; } Cifra;
typedef Cifra * NumTelefono;
typedef struct con { char nome[1000];
                     char indirizzo[1000];
                     NumTelefono numero;
                     struct con * next; } Contatto;
typedef Contatto * Rubrica;

NumTelefono InsInTestaCifra( NumTelefono lista, char elem );
NumTelefono InsInFondoCifra( NumTelefono lista,char elem );
Rubrica costruisciRubrica();
NumTelefono costruisciNumero(char * telefono);
Rubrica InsInFondoContatto( Rubrica lista, char * nome, char * indirizzo, char * telefono );
void stampanumero(NumTelefono head);
void stamparubrica(Rubrica head);
Rubrica f(Rubrica head);

int main(){
    Rubrica rub;
    rub=costruisciRubrica();
    stamparubrica(rub);
    printf("\n\n");
    rub=f(rub);
    stamparubrica(rub);
}

Rubrica costruisciRubrica(){
    Rubrica lis=NULL;
    int i=0;
    char nomi[5][20]={"Alessandro","Marco","Giacomo","Giovanni","Matteo"};
    char indirizzi[5][20]={"via Milano 1,Mi","via Milano 1,Mi","via Milano 1,Mi","via Milano 1,Mi","via Milano 1,Mi"};
    char telefoni[5][20]={"333333333","+3956789","003956565656","03456678","4444444"};
    for(i=0;i<5;i++)
        lis=InsInFondoContatto(lis,nomi[i],indirizzi[i],telefoni[i]);
    return lis;
}

NumTelefono InsInTestaCifra ( NumTelefono lista, char elem ) {
    NumTelefono punt;
    punt = (NumTelefono) malloc(sizeof(Cifra));
    punt->c = elem;    punt->next = lista;
    return  punt;
}

NumTelefono InsInFondoCifra( NumTelefono lista,char elem ) {
    NumTelefono punt;
    if( lista==NULL ) {
        punt = (NumTelefono)malloc( sizeof(Cifra) );
        punt->next = NULL; punt->c = elem;
        return  punt;
    } else {   lista->next = InsInFondoCifra( lista->next, elem );
               return lista;   }
}

NumTelefono costruisciNumero(char * telefono){
    int i;
    NumTelefono lis=NULL;
    for(i=0;telefono[i]!='\0';i++)
        lis=InsInFondoCifra(lis,telefono[i]);
    return lis;
}

Rubrica InsInFondoContatto( Rubrica lista, char * nome, char * indirizzo, char * telefono ) {
    Rubrica punt;
    if( lista==NULL ) {
        punt = (Rubrica)malloc( sizeof(Contatto) );
        punt->next = NULL;
        strcpy(punt->nome, nome);
        strcpy(punt->indirizzo, indirizzo);
        punt->numero=costruisciNumero(telefono);
        return  punt;
    } else {   lista->next = InsInFondoContatto( lista->next, nome, indirizzo, telefono );
               return lista;   }
}
//
//
//OUTPUT ATTESO:
//Alessandro: via Milano 1,Mi Num.333333333
//Marco: via Milano 1,Mi Num.+3956789
//Giacomo: via Milano 1,Mi Num.003956565656
//Giovanni: via Milano 1,Mi Num.03456678
//Matteo: via Milano 1,Mi Num.4444444
//
//Alessandro: via Milano 1,Mi Num.+39333333333
//Marco: via Milano 1,Mi Num.+3956789
//Giacomo: via Milano 1,Mi Num.+3956565656
//Giovanni: via Milano 1,Mi Num.+3903456678
//Matteo: via Milano 1,Mi Num.+394444444


//- Se il numero inizia con il carattere '+' resta inalterato
//- Se inizia con due zeri, li sostituisce con un '+'
//- Se inizia con un solo zero o con una cifra diversa da zero ('1','2', ... '9') vi aggiunge i caratteri ‘+’, ‘3’ e ‘9’ all'inizio

NumTelefono modificanumero(NumTelefono head)
    {
        if(head==NULL)
            return head;
        if(head->c=='+')
            return head;
        if(head->c=='0' && head->next->c=='0')
            {
                head->next->c='+';
                NumTelefono temp=head->next;
                free(head);
                head=temp;
                return temp;
            }
        else
            {
                NumTelefono primo=(NumTelefono)malloc(sizeof(Cifra));
                primo->c='+';
                NumTelefono secondo=(NumTelefono)malloc(sizeof(Cifra));
                primo->next=secondo;
                secondo->c='3';
                NumTelefono terzo=(NumTelefono)malloc(sizeof(Cifra));
                secondo->next=terzo;
                terzo->c='9';
                terzo->next=head;
                return primo;
            }
    }
Rubrica f(Rubrica head)
    {
        if(head==NULL)
            return head;
    Rubrica scorri=head;
    while (scorri!=NULL) {
        scorri->numero=modificanumero(scorri->numero);
        scorri=scorri->next;
    }
    return head;
    }
void stamparubrica(Rubrica head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("%s", head->nome);
                printf("  %s", head->indirizzo);
                printf("  numero:  ");
                stampanumero(head->numero);
                printf("\n\n");
                head=head->next;
            }
    }
void stampanumero(NumTelefono head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("%c", head->c);
                head=head->next;
            }
    }
