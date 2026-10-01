//
//  main.c
//  giorno -6 tde 3 liste
//
//  Created by Francesco Roscio Ricon on 21/01/26.
//  Con l’avvento dell’unione bancaria europea arrivano correntisti dall’estero e urge uniformare la gestione dei contatti telefonici
//- Se il numero inizia con il carattere '+' resta inalterato
//- Se inizia con due zeri, li sostituisce con un '+'
//- Se inizia con un solo zero o con una cifra diversa da zero ('1','2', ... '9') vi aggiunge i caratteri ‘+’, ‘3’ e ‘9’ all'inizio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct c { char c;
                   struct c * next; } Cifra;
typedef Cifra * NumTelefono;
typedef struct con { char nome[1000];
                     char IBAN[1000];
                     NumTelefono numero;
                     struct con * next; } Correntista;
typedef Correntista * ListaConti;
NumTelefono InsInTestaCifra( NumTelefono lista, char elem );
NumTelefono InsInFondoCifra( NumTelefono lista,char elem );
ListaConti costruisciListaConti();
NumTelefono costruisciNumero(char * telefono);
ListaConti InsInFondoCorrentista( ListaConti lista, char * nome, char * IBAN, char * telefono );
void stampa(ListaConti start);
NumTelefono modifica_numero(NumTelefono numero);
ListaConti modifica_lista(ListaConti head);


int main(){
    ListaConti conti;
    conti=costruisciListaConti();
    stampa(conti);
    conti=modifica_lista(conti);
    printf("\n");
    stampa(conti);
}
ListaConti costruisciListaConti(){
    ListaConti lis=NULL;
    int i=0;
    char nomi[5][20]={"Alessandro","Marco","Giacomo","Giovanni","Matteo"};
    char IBAN[5][20]={"IT020000000000000","IT020000000000000","IT020000000000000","IT020000000000000","IT020000000000000"};
    char telefoni[5][20]={"333333333","+3956789","003956565656","03456678","4444444"};
    for(i=0;i<5;i++)
        lis=InsInFondoCorrentista(lis,nomi[i],IBAN[i],telefoni[i]);
    return lis; }

NumTelefono InsInTestaCifra ( NumTelefono lista, char elem ) {
    NumTelefono punt;
    punt = (NumTelefono) malloc(sizeof(Cifra));
    punt->c = elem;    punt->next = lista;
    return  punt;}

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
    return lis;}

ListaConti InsInFondoCorrentista( ListaConti lista, char * nome, char * IBAN, char * telefono ) {
    ListaConti punt;
    if( lista==NULL ) {
        punt = (ListaConti)malloc( sizeof(Correntista) );
        punt->next = NULL;
        strcpy(punt->nome, nome);
        strcpy(punt->IBAN, IBAN);
        punt->numero=costruisciNumero(telefono);
        return  punt;
    } else {   lista->next = InsInFondoCorrentista( lista->next, nome, IBAN, telefono );
               return lista;   }
}

void stampa(ListaConti start)
    {
        while(start!=NULL)
            {
                printf("%s IBAN:%s Numero: ", start->nome, start->IBAN);
                NumTelefono scorrinumero=start->numero;
                while(scorrinumero!=NULL)
                    {
                        printf("%c", scorrinumero->c);
                        scorrinumero=scorrinumero->next;
                    }
                printf("\n");
                start=start->next;
            }
    }
//- Se il numero inizia con il carattere '+' resta inalterato
//- Se inizia con due zeri, li sostituisce con un '+'
//- Se inizia con un solo zero o con una cifra diversa da zero ('1','2', ... '9') vi aggiunge i caratteri ‘+’, ‘3’ e ‘9’ all'inizio

NumTelefono modifica_numero(NumTelefono numero)
    {
        if(numero->c=='+')
            return numero;
        if(numero->c=='0' && numero->next->c=='0')
        {
            NumTelefono new_head;
            new_head=numero->next;
            new_head->c='+';
            free(numero);
            return new_head;
        }
    NumTelefono a = (NumTelefono)malloc( sizeof(Cifra) );
    a->c='+';
    NumTelefono b = (NumTelefono)malloc( sizeof(Cifra) );
    b->c='3';
    NumTelefono c = (NumTelefono)malloc( sizeof(Cifra) );
    c->c='9';
    a->next=b;
    b->next=c;
    c->next=numero;
    return a;
    }
ListaConti modifica_lista(ListaConti head)
    {
        if(head==NULL)
            return NULL;
    ListaConti scorri_conti=head;
        while(scorri_conti!=NULL)
        {
            scorri_conti->numero=modifica_numero(scorri_conti->numero);
            scorri_conti=scorri_conti->next;
        }
    return head;
    }
