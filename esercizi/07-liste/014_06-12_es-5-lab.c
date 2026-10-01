//  Created by Francesco Roscio Ricon on 06/12/25.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char nome[100];
    float prezzo;
    int flag;
}Piatto;
typedef struct EL{
    Piatto info;
    struct EL *next;
}Nodo;
typedef Nodo *Menu;
Menu inserisciincoda(Menu m, Nodo x);
Menu inserisciincodaricorsivo(Menu m, Nodo x);
void stampa(Menu m);
Menu soloVegan_ric(Menu m);
Menu menuEconomico(Menu m, float prezzo);
Menu menuEconomico_crea(Menu m, float prezzo, Menu new);
Menu menuEconomico_iter(Menu m, float prezzo);
int main() {
    Menu m=NULL;
    Nodo a, b, c;
    strcpy(a.info.nome, "Pasta al ragù");
    a.info.flag=0;
    a.info.prezzo=8.90;
    m=inserisciincodaricorsivo(m, a);
    
    strcpy(b.info.nome, "Insalata");
    b.info.flag=1;
    b.info.prezzo=6.55;
    m=inserisciincodaricorsivo(m, b);
    
    strcpy(c.info.nome, "Pesce");
    c.info.flag=1;
    c.info.prezzo=9;
    m=inserisciincodaricorsivo(m, c);
    float prezzo=9;
    stampa(m);
    Menu j=NULL;
    j=menuEconomico_iter(m, prezzo);
    printf("\n");
    stampa(j);
    
}
Menu inserisciincoda(Menu m, Nodo x)
    {
        Menu new;
        new=(Menu)malloc(sizeof(Nodo));
        new->info=x.info;
        new->next=NULL;
        if(m==NULL)
            return new;
        else
        {
            Menu scorri=m;
            while(scorri->next!=NULL)
                {
                    scorri=scorri->next;
                }
            scorri->next=new;
            new->next=NULL;
            return m;
        }
    }
Menu inserisciincodaricorsivo(Menu m, Nodo x)
    {
        if(m==NULL)
            {
                Menu new;
                new=(Menu)malloc(sizeof(Nodo));
                new->info=x.info;
                new->next=NULL;
                return new;
            }
        m->next=inserisciincodaricorsivo(m->next, x);
        return m;
    }
void stampa(Menu m)
    {
        if(m==NULL)
            printf("Vuoto");
        while(m!=NULL)
            {
                if(m->info.flag==1)
                    {
                        printf("%s (Vegano)-->", m->info.nome);
                    }
                else
                    {
                        printf("%s -->", m->info.nome);
                    }
                m=m->next;
            }
    printf("--|");
    }

Menu soloVegan_ric(Menu m)
{
    if (m == NULL)
        return NULL;

    if (m->info.flag == 0) {
        Menu temp = m->next;
        free(m);
        return soloVegan_ric(temp);
    }

    m->next = soloVegan_ric(m->next);
    return m;
}
Menu menuEconomico(Menu m, float prezzo) // questa elimina
    {
        if(m==NULL)
            return m;
        if(m->info.prezzo>prezzo)
            {
                Menu temp=m->next;
                free(m);
                return menuEconomico(temp, prezzo);
            }
        m->next=menuEconomico(m->next, prezzo);
        return m;
    }

Menu menuEconomico_iter(Menu m, float prezzo)
    {
       if(m==NULL)
           return NULL;
    Menu temp=m;
    Menu head_new=NULL;
        while(temp!=NULL)
            {
                if(temp->info.prezzo<prezzo)
                    {
                        head_new=inserisciincoda(head_new, *temp);
                    }
                temp=temp->next;
            }
        return head_new;
    }
