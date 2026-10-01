//
//  main.c
//  ESAME ES 1
//
//  Created by Francesco Roscio Ricon on 19/02/26.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct PrezzoStruct {
    float euro;
    int anno;
    int mese;
    int valido;
    struct PrezzoStruct *next;
} Prezzo;
typedef Prezzo * ListaPrezzi;
typedef struct videogioco {
    char nome[50];
    ListaPrezzi prezzi;
    struct videogioco *next;
} Videogioco;
typedef Videogioco * ListaVideogiochi;
typedef struct EL {
    char nome[50];
    float prezzomedio;
    struct EL *next;
}Vagone;
typedef Vagone *Lista_medie;
void stampaCatalogoConPrezzi(ListaVideogiochi);
ListaVideogiochi creaCatalogoDiEsempio();
ListaVideogiochi inserisciTestaGioco(ListaVideogiochi, char[], ListaPrezzi);
ListaPrezzi inserisciTestaPrezzo(ListaPrezzi, float, int, int, int);

float media(ListaPrezzi head);
Lista_medie inserisciincodamedia(Lista_medie head, char nome[], float pz_medio);
void stampamedie(Lista_medie head);
Lista_medie prezzoMedioPerVideogioco(ListaVideogiochi head);
float prezzoMedioVideogiochi(ListaVideogiochi head, int mese, int anno);
float trovaprezzo(ListaPrezzi head, int mese, int anno, int *out);

int main(){
    ListaVideogiochi c = creaCatalogoDiEsempio();
    int anno = 2025;
    int mese = 6;
    stampaCatalogoConPrezzi(c);
    Lista_medie new=prezzoMedioPerVideogioco(c);
    stampamedie(new);
    float medio=prezzoMedioVideogiochi(c, mese, anno);
    printf("\nprezzo medio nel mese %d, anno %d: %.2f euro\n", mese, anno, medio);
}
float media(ListaPrezzi head)
    {
        if(head==NULL)
            return 0;
    ListaPrezzi s=head;
    float somma=0;
    float count=0;
    while(s!=NULL)
            {
            if(s->valido==1)
                {
                    somma=somma+s->euro;
                    count++;
                }
            s=s->next;
            }
    if(count==0)
        return 0;
return (somma)/count;
}
Lista_medie inserisciincodamedia(Lista_medie head, char nome[], float pz_medio)
    {
    if(head==NULL)
        {
            Lista_medie new=(Lista_medie)malloc(sizeof(Vagone));
            strcpy(new->nome,nome);
            new->prezzomedio=pz_medio;
            new->next=NULL;
            return new;
        }
    head->next=inserisciincodamedia(head->next, nome, pz_medio);
    return head;
}
Lista_medie prezzoMedioPerVideogioco(ListaVideogiochi head)
{
    if(head==NULL)
        return NULL;
ListaVideogiochi sc=head;
Lista_medie new=NULL;
while(sc!=NULL)
    {
        float avg=media(sc->prezzi);
        new=inserisciincodamedia(new, sc->nome, avg);
        sc=sc->next;
    }
return new;
}
void stampamedie(Lista_medie head)
    {
        if(head==NULL)
            return;
    Lista_medie s=head;
    while(s!=NULL)
        {
            printf("%s - prezzo medio: %.2f\n", s->nome, s->prezzomedio);
            s=s->next;
        }
    }
float trovaprezzo(ListaPrezzi head, int mese, int anno, int *out) // out è una flag per segnalare che il prezzo non è stato trovatonello storico dei prezzi
    {
        if(head==NULL)
            {
                *out=1;
                return 0;
            }
    ListaPrezzi s=head;
    while(s!=NULL)
        {
            if(s->anno==anno && s->mese==mese && s->valido==1)
                {
                    *out=0;
                    return s->euro;
                }
            s=s->next;
        }
    (*out)=1;
    return 0;
    }
float prezzoMedioVideogiochi(ListaVideogiochi head, int mese, int anno)
    {
        if(head==NULL)
            return 0;
        float somma=0;
        float count=0;
        ListaVideogiochi scorri=head;
        while(scorri!=NULL)
            {
                float prezzo=0;
                int out_flag=0;
                prezzo=trovaprezzo(scorri->prezzi, mese, anno, &out_flag);
                if(out_flag==0) //trovato
                    {
                        somma=somma+prezzo;
                        count++;
                    }
                scorri=scorri->next;
            }
        if(count==0)
            return 0;
    return somma/count;
}


ListaVideogiochi creaCatalogoDiEsempio(){
    ListaVideogiochi catalogo = NULL;
    // allocazione videogiochi di esempio


    // GIOCO 6: Super Mario Odyssey
    ListaPrezzi prezzo6 = NULL;
    prezzo6 = inserisciTestaPrezzo(prezzo6, 59.99, 2025, 5, 1); // maggio 2025, valido
    prezzo6 = inserisciTestaPrezzo(prezzo6, 49.99, 2025, 6, 1); // giugno 2025, valido
    prezzo6 = inserisciTestaPrezzo(prezzo6, 39.99, 2025, 7, 0); // luglio 2025, non valido (out-of-stock)
    catalogo = inserisciTestaGioco(catalogo, "Super Mario Odyssey", prezzo6);
    
    // GIOCO 5: Call of Duty Modern Warfare 2
    ListaPrezzi prezzo5 = NULL;
    prezzo5 = inserisciTestaPrezzo(prezzo5, 69.99, 2025, 4, 1); // aprile 2025, valido
    prezzo5 = inserisciTestaPrezzo(prezzo5, 59.99, 2025, 5, 1); // maggio 2025, valido
    prezzo5 = inserisciTestaPrezzo(prezzo5, 49.99, 2025, 6, 1); // giugno 2025, valido
    prezzo5 = inserisciTestaPrezzo(prezzo5, 39.99, 2025, 7, 0); // luglio 2025, non valido (out-of-stock)
    catalogo = inserisciTestaGioco(catalogo, "Call of Duty Modern Warfare 2", prezzo5);
    
    // GIOCO 4: Battlefield 2042
    ListaPrezzi prezzo4 = NULL;
    prezzo4 = inserisciTestaPrezzo(prezzo4, 59.99, 2025, 3, 1); // marzo 2025, valido
    prezzo4 = inserisciTestaPrezzo(prezzo4, 49.99, 2025, 4, 0); // aprile 2025, non valido (out-of-stock)
    prezzo4 = inserisciTestaPrezzo(prezzo4, 39.99, 2025, 5, 1); // maggio 2025, valido
    prezzo4 = inserisciTestaPrezzo(prezzo4, 29.99, 2025, 6, 1); // giugno 2025, valido
    prezzo4 = inserisciTestaPrezzo(prezzo4, 19.99, 2025, 7, 1); // luglio 2025, valido
    catalogo = inserisciTestaGioco(catalogo, "Battlefield 2042", prezzo4);


    // GIOCO 3: Battlefield 6
    ListaPrezzi prezzo3 = NULL;
    prezzo3 = inserisciTestaPrezzo(prezzo3, 69.99, 2025, 7, 0); // luglio 2025, non valido
    catalogo = inserisciTestaGioco(catalogo, "Battlefield 6", prezzo3);


    // GIOCO 2 Xenoblade Chronicles 3
    ListaPrezzi prezzo2 = NULL;
    prezzo2 = inserisciTestaPrezzo(prezzo2, 59.99, 2025, 5, 1); // maggio 2025, valido
    prezzo2 = inserisciTestaPrezzo(prezzo2, 0, 2025, 6, 1); // giugno 2025, valido (offerta speciale bundle)
    prezzo2 = inserisciTestaPrezzo(prezzo2, 49.99, 2025, 7, 0); // luglio 2025, non valido (out-of-stock)
    catalogo = inserisciTestaGioco(catalogo, "Xenoblade Chronicles 3", prezzo2);


    // GIOCO 6: Cyberpunk 2077
    ListaPrezzi prezzo1 = NULL;
    prezzo1 = inserisciTestaPrezzo(prezzo1, 39.99, 2025, 4, 1); // aprile 2025, valido
    prezzo1 = inserisciTestaPrezzo(prezzo1, 29.99, 2025, 5, 0); // maggio 2025, non valido
    prezzo1 = inserisciTestaPrezzo(prezzo1, 19.99, 2025, 6, 0); // giugno 2025, non valido
    prezzo1 = inserisciTestaPrezzo(prezzo1, 9.99, 2025, 7, 0); // luglio 2025, non valido
    catalogo = inserisciTestaGioco(catalogo, "Cyberpunk 2077", prezzo1);
    
    return catalogo;
}


ListaVideogiochi inserisciTestaGioco(ListaVideogiochi head, char nomeVideogioco[], ListaPrezzi listaPrezzi){
    // Alloco il nuovo nodo
    ListaVideogiochi new = (ListaVideogiochi)malloc(sizeof(Videogioco));
    if(new == NULL){
        printf("Errore di allocazione\n");
        return head;
    }
    strcpy(new->nome, nomeVideogioco);
    new->prezzi = listaPrezzi;
    new->next = NULL;


    new->next = head;


    return new;
}


ListaPrezzi inserisciTestaPrezzo(ListaPrezzi head, float euro, int anno, int mese, int valid){
    // Alloco il nuovo nodo
    ListaPrezzi new = (ListaPrezzi)malloc(sizeof(Prezzo));
    if(new == NULL){
        printf("Errore di allocazione\n");
        return head;
    }
    new->euro = euro;
    new->anno = anno;
    new->mese = mese;
    new->valido = valid;
    new->next = NULL;


    new->next = head;


    return new;
}


void stampaCatalogoConPrezzi(ListaVideogiochi catalogo){
    ListaVideogiochi currGioco = catalogo;
    while(currGioco != NULL){
        printf("=============================\n");
        printf("Videogioco: %s\nPrezzi:\n", currGioco->nome);
        ListaPrezzi currPrezzo = currGioco->prezzi;
        while(currPrezzo != NULL){
            printf("%04d/%02d, %.2f, Valido: %d -->", currPrezzo->anno, currPrezzo->mese, currPrezzo->euro, currPrezzo->valido);
            currPrezzo = currPrezzo->next;
        }
        printf("NULL\n");
        currGioco = currGioco->next;
        printf("=============================\n      |\n      V\n");
    }
    printf("     NULL\n");
}
