//
//  main.c
//  tde -2
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct allergene {
    char* nome;
    struct allergene* next;
} Allergene;
typedef struct pizza {
    char* nome;
    float prezzo;
    int vegetariana;
    struct allergene* allergeni;
    struct pizza* next;
} Pizza;
typedef Allergene* ListaAllergeni;
typedef Pizza* ListaPizze;
ListaAllergeni crea_allergeni(const char** nomi, int count);
ListaPizze crea_pizza(const char* nome, float prezzo, int vegetariana, const char** allergeni, int num_allergeni);
void stampa_menu(ListaPizze menu);
void freeallergeni(ListaAllergeni head);
ListaPizze rimuovi_allergene(ListaPizze head, char allergene[]);
int main() {
    const char* a1[] = {"glutine", "lattosio"};
    const char* a2[] = {"glutine"};
    const char* a3[] = {"glutine", "soia"};
    const char* a4[] = {"glutine", "lattosio"};
    const char* a5[] = {"glutine", "soia", "lattosio"};
    const char* a6[] = {"glutine", "sesamo"};
    ListaPizze menu = crea_pizza("Margherita", 6.5, 1, a1, 2);
    menu->next = crea_pizza("Diavola", 8.0, 0, a2, 1);
    menu->next->next = crea_pizza("Vegana", 7.0, 1, a3, 2);
    menu->next->next->next = crea_pizza("Quattro Formaggi", 7.5, 1, a4, 2);
    menu->next->next->next->next = crea_pizza("Capricciosa", 9.0, 0, a5, 3);
    menu->next->next->next->next->next = crea_pizza("Marinara", 5.5, 1, a6, 1);
    printf("=== MENU ===\n");
    stampa_menu(menu);
    menu=rimuovi_allergene(menu, "lattosio");
    printf("\n=== MENU DOPO RIMOZIONE 'lattosio' ===\n");
    stampa_menu(menu);
}
ListaAllergeni crea_allergeni(const char** nomi, int count) {
    ListaAllergeni testa = NULL;
    int i;
    for (i = count - 1; i >= 0; i--) {
        ListaAllergeni nuovo = malloc(sizeof(Allergene));
        nuovo->nome = strdup(nomi[i]);
        nuovo->next = testa;
        testa = nuovo;
    }
    return testa;
}
ListaPizze crea_pizza(const char* nome, float prezzo, int vegetariana, const char** allergeni, int num_allergeni) {
    Pizza* p = malloc(sizeof(Pizza));
    p->nome = strdup(nome);
    p->prezzo = prezzo;
    p->vegetariana = vegetariana;
    p->allergeni = crea_allergeni(allergeni, num_allergeni);
    p->next = NULL;
    return p;
}
void stampa_menu(ListaPizze menu) {
    while (menu) {
        printf("Pizza: %s (%.2f euro) [%s]\n", menu->nome, menu->prezzo,
               menu->vegetariana ? "Vegetariana" : "Non vegetariana");
        printf("  Allergeni: ");
        ListaAllergeni a = menu->allergeni;
        while (a) {
            printf("%s ", a->nome);
            a = a->next;
        }
        printf("\n");
        menu = menu->next;
    }
}
int trovaallergene(ListaAllergeni head, char allergene[])
    {
    ListaAllergeni scorri=head;
    while (scorri!=NULL) {
        if(strcmp(scorri->nome, allergene)==0)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
ListaPizze rimuovi_allergene(ListaPizze head, char allergene[])
    {
        if(head==NULL)
            return head;
    ListaPizze scorripizze=head;
    ListaPizze prec=NULL;
    while(scorripizze!=NULL)
        {
            ListaPizze succ=scorripizze->next;
            if(trovaallergene(scorripizze->allergeni, allergene))
                {
                    if(prec==NULL)
                        {
                            head=succ;
                            freeallergeni(scorripizze->allergeni);
                            free(scorripizze);
                            scorripizze=head;
                        }
                    else
                        {
                            prec->next=succ;
                            free(scorripizze);
                            scorripizze=succ;
                        }
                }
            else
                {
                    prec=scorripizze;
                    scorripizze=succ;
                }
        }
    return head;
    }
void freeallergeni(ListaAllergeni head)
    {
        while(head!=NULL)
            {
                ListaAllergeni temp=head;
                head=head->next;
                free(temp);
            }
}
