//  Created by Francesco Roscio Ricon on 08/03/26.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef struct { int giorno, mese, anno; } Data;
typedef struct FN { char targa[8];
             int capienza, cilindrata, costoOrario;
                            struct FN * next; } Furgone;
typedef Furgone * Furgoni;
typedef struct PN { char targa[8];
             Data d;
                            int durata; // in ore
                            struct PN * next; } Prenotazione;
typedef Prenotazione * Prenotazioni;
int costo(Furgone x, Prenotazioni head);
Furgone f3(Prenotazioni P, Furgoni F, Furgoni giàmessi);
int main() {

}
Furgoni inseriscincod(Furgoni head, Furgone x)
    {
        if(head==NULL)
            {
                Furgoni new=(Furgoni)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincod(head->next, x);
    return head;
    }
Furgone f1(Prenotazioni P, Furgoni F)
    {
    int max=0;
    Furgone massimo=*F;
    while(F!=NULL)
        {
            if(costo(*F, P)>max)
                {
                    max=costo(*F,P);
                    massimo=*F;
                }
            F=F->next;
        }
    return massimo;
    }
int costo(Furgone x, Prenotazioni head)
    {
        if(head==NULL)
            return 0;
        float somma=0;
        while(head!=NULL)
            {
                if(strcmp(head->targa, x.targa)==0)
                    {
                        somma=somma+(head->durata*x.costoOrario);
                    }
                head=head->next;
            }
    return somma;
    }
int trova(Furgone x, Furgoni head)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(strcmp(x.targa, head->targa)==0)
                    return 1;
                head=head->next;
            }
    return 0;
    }
Furgoni f2(Prenotazioni P, Furgoni F)
    {
    Furgoni new=NULL;
    for(int i=0; i<10; i++)
        {
            Furgone temp=f3(P, F, new);
            new=inseriscincod(new, temp);

        }
        return new;
    }
Furgone f3(Prenotazioni P, Furgoni F, Furgoni giàmessi)
{
int max=0;
Furgone massimo=*F;
while(F!=NULL)
    {
        if(costo(*F, P)>max && trova(*F, giàmessi)==0)
            {
                max=costo(*F,P);
                massimo=*F;
            }
        F=F->next;
    }
return massimo;
}
