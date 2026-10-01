//  Created by Francesco Roscio Ricon on 16/01/26.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {int giorno, mese, anno;} Data;
typedef struct ELP {
    char nome[50];
    Data giorno_scadenza;
    struct ELP * next;
} NodoP;
typedef NodoP * ListaP;
typedef struct ELS {
    ListaP prodotti;
    struct ELS * next;
} NodoS;
typedef NodoS * ListaS;


ListaP aggiungiProdotto(ListaP prodotti, char nome[50], int giorno, int mese, int anno);
ListaS costruisci();
void stampaData(Data d);
void stampaProdotto(NodoP* prodotto);
void stampaProdotti(ListaP prodotti);
void stampaScaffale(NodoS* scaffale);
void stampaScaffali(ListaS scaffali);
void eliminaProdotto(ListaP scorriprodotti, ListaP scorriprodotti_prec);
void eliminaScaduti(ListaS lista_di_scaffali, Data G);



/// -------------------------------------------------------------------
/// MAIN ED ALTRE FUNZIONI
int main(){
    ListaS scaffali = costruisci();
    Data G = {5, 9, 2022};
    printf("Data di scadenza: "); stampaData(G); printf("\n\n");
    printf("Prima della rimozione dei prodotti scaduti:\n");
    stampaScaffali(scaffali);

    eliminaScaduti(scaffali, G);
    


    printf("Dopo la rimozione dei prodotti scaduti:\n");
    stampaScaffali(scaffali);
    return 0;
}


ListaP aggiungiProdotto(ListaP prodotti, char nome[50], int giorno, int mese, int anno){
    if(prodotti == NULL){
        prodotti = (ListaP) malloc(sizeof(NodoP));
        Data scad = {giorno, mese, anno}; strcpy(prodotti->nome, nome); prodotti->giorno_scadenza = scad; prodotti->next = NULL;
        return prodotti;
    } else { prodotti->next = aggiungiProdotto(prodotti->next, nome, giorno, mese, anno); return prodotti;}
}
ListaS costruisci(){
    ListaS scaffali = NULL;
    scaffali = (ListaS) malloc(sizeof(NodoS));scaffali->prodotti = NULL; scaffali->next = NULL;
    scaffali->prodotti = aggiungiProdotto(scaffali->prodotti, "Pasta", 14, 7, 2027);scaffali->prodotti = aggiungiProdotto(scaffali->prodotti, "Riso", 8, 11, 2020);scaffali->prodotti = aggiungiProdotto(scaffali->prodotti, "Farro", 9, 3, 2029);
    scaffali->next = (ListaS) malloc(sizeof(NodoS));scaffali->next->prodotti = NULL; scaffali->next->next = NULL;
    scaffali->next->prodotti = aggiungiProdotto(scaffali->next->prodotti, "Biscotti", 4, 6, 2020);scaffali->next->prodotti = aggiungiProdotto(scaffali->next->prodotti, "Cereali", 2, 7, 2025);scaffali->next->prodotti = aggiungiProdotto(scaffali->next->prodotti, "Toast", 1, 3, 2018);
    scaffali->next->next = (ListaS) malloc(sizeof(NodoS));scaffali->next->next->prodotti = NULL; scaffali->next->next->next = NULL;
    scaffali->next->next->prodotti = aggiungiProdotto(scaffali->next->next->prodotti, "More", 7, 9, 2016);scaffali->next->next->prodotti = aggiungiProdotto(scaffali->next->next->prodotti, "Lamponi", 25, 12, 2017);scaffali->next->next->prodotti = aggiungiProdotto(scaffali->next->next->prodotti, "Ribes", 18, 5, 2010);
    return scaffali;
}
void stampaData(Data d){ printf("%d/%d/%d", d.giorno, d.mese, d.anno); }
void stampaProdotto(NodoP* prodotto){printf(" ~ %s in scadenza il ", prodotto->nome);stampaData(prodotto->giorno_scadenza);}
void stampaProdotti(ListaP prodotti){
    if(prodotti == NULL){ printf(" * \n"); return; }
    stampaProdotto(prodotti); printf("\n"); stampaProdotti(prodotti->next);
}
void stampaScaffale(NodoS* scaffale){printf("+ - - -\n"); stampaProdotti(scaffale->prodotti);}
void stampaScaffali(ListaS scaffali){
    if(scaffali == NULL){ printf("+ _ _ _\n\n"); return; }
    stampaScaffale(scaffali);stampaScaffali(scaffali->next);
}
// 1 se d1 è una data antecedente alla data d2, 0 altrimenti.
int primaDi(Data d1, Data d2)
    {
        if(d1.anno<d2.anno)
            return 1;
        if(d1.anno>d2.anno)
            return 0;
        if(d1.mese<d2.mese)
            return 1;
        if(d1.mese>d2.mese)
            return 0;
        if(d1.giorno<d2.giorno)
            return 1;
        if(d1.giorno>d2.giorno)
            return 0;
    return 0;
    }

void eliminaScaduti(ListaS lista_di_scaffali, Data G)
{
    ListaS scorri_scaffali=lista_di_scaffali;
    while(scorri_scaffali!=NULL)
    {
        if (scorri_scaffali->prodotti == NULL) {
        scorri_scaffali = scorri_scaffali->next;
        continue;
        }
        
        while (scorri_scaffali->prodotti != NULL &&
                      primaDi(scorri_scaffali->prodotti->giorno_scadenza, G))
               {
                   ListaP temp = scorri_scaffali->prodotti;
                   scorri_scaffali->prodotti = scorri_scaffali->prodotti->next;
                   free(temp);
               }

               // se ho eliminato tutto lo scaffale
               if (scorri_scaffali->prodotti == NULL) {
                   scorri_scaffali = scorri_scaffali->next;
                   continue;
               }
        
        
        
        ListaP scorriprodotti=scorri_scaffali->prodotti->next;
        ListaP scorriprodotti_prec=NULL;
        while (scorriprodotti!=NULL)
        {

            if(primaDi(scorriprodotti->giorno_scadenza, G))
            {
                ListaP next = scorriprodotti->next;
                eliminaProdotto(scorriprodotti, scorriprodotti_prec);
                scorriprodotti = next;
            }
            else{
                
                scorriprodotti_prec=scorriprodotti;
                scorriprodotti=scorriprodotti->next;
            }
        }
        scorri_scaffali=scorri_scaffali->next;
    }
}
    
    
void eliminaProdotto(ListaP scorriprodotti, ListaP scorriprodotti_prec)
{
    if (scorriprodotti == NULL || scorriprodotti_prec == NULL)
        return;

    scorriprodotti_prec->next = scorriprodotti->next;
    free(scorriprodotti);
}
