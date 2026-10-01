//
//  main.c
//  tde 2 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int giorno, mese, anno;
} data;

typedef struct {
    int ora, minuto, secondo;
} ora;

typedef struct {
    char codiceFiscale[100], cognome[100], nome[100], numeroTelefono[100];
    char cittaDiResidenza[100];
    data DataNascita;
} cliente;

typedef struct {
    cliente cli;
    data d;
    ora o;
    int durata; // in secondi
} telefonata;

typedef struct {
    telefonata telefonate[1000];
    int numTelefonate; // quante caselle sono valide
} listaTelefonate;


typedef struct EL{
    cliente cli;
    int numerotelefonate;
    int sommadurata;
    struct EL *next;
}Vagone;

typedef Vagone *Lista;

Lista inseriscincoda(Lista head, cliente cli, int durata);;
void stampaCliente(cliente c) {
    printf("%s %s (CF=%s, Tel=%s, Citta=%s, Nascita=%02d/%02d/%04d)",
           c.nome, c.cognome, c.codiceFiscale, c.numeroTelefono,
           c.cittaDiResidenza,
           c.DataNascita.giorno, c.DataNascita.mese, c.DataNascita.anno);
}

void stampaTelefonata(const telefonata *t) {
    stampaCliente(t->cli);
    printf(" | Data %02d/%02d/%04d %02d:%02d:%02d | durata=%d s\n",
           t->d.giorno, t->d.mese, t->d.anno,
           t->o.ora, t->o.minuto, t->o.secondo,
           t->durata);
}

/* helper: crea cliente velocemente */
cliente mkCliente(const char *cf, const char *cogn, const char *nome,
                  const char *tel, const char *citta,
                  int gg, int mm, int aa) {
    cliente c;
    strcpy(c.codiceFiscale, cf);
    strcpy(c.cognome, cogn);
    strcpy(c.nome, nome);
    strcpy(c.numeroTelefono, tel);
    strcpy(c.cittaDiResidenza, citta);
    c.DataNascita.giorno = gg;
    c.DataNascita.mese = mm;
    c.DataNascita.anno = aa;
    return c;
}

/* helper: aggiunge una telefonata a T */
void addTel(listaTelefonate *T, cliente c, int gg, int mm, int aa,
            int hh, int min, int ss, int durata) {
    int i = T->numTelefonate;
    T->telefonate[i].cli = c;
    T->telefonate[i].d.giorno = gg;
    T->telefonate[i].d.mese = mm;
    T->telefonate[i].d.anno = aa;
    T->telefonate[i].o.ora = hh;
    T->telefonate[i].o.minuto = min;
    T->telefonate[i].o.secondo = ss;
    T->telefonate[i].durata = durata;
    T->numTelefonate++;
}
Lista trova(Lista head, cliente cli);
int trovamax(listaTelefonate head);

int main(void) {
    /* ====== CLIENTI (3 persone) ====== */
    cliente A = mkCliente("RSSMRA90A01H501Z", "Rossi",  "Mario", "3331111111", "Roma",  1,  1, 1990);
    cliente B = mkCliente("VRDLGI92B15F205X", "Verdi",  "Luigi", "3332222222", "Milano",15,  2, 1992);
    cliente C = mkCliente("BNCLRA95C20D612Y", "Bianchi","Laura", "3333333333", "Torino",20,  3, 1995);

    /* =========================
       TEST 1: minor numero telefonate = cliente C (1 chiamata)
       somma durate C = 120
       ========================= */
    listaTelefonate T1;
    T1.numTelefonate = 0;

    addTel(&T1, A, 10, 2, 2026,  9, 10,  0,  60);
    addTel(&T1, A, 10, 2, 2026, 10,  0,  0, 200);
    addTel(&T1, B, 11, 2, 2026, 12, 30,  0,  30);
    addTel(&T1, B, 11, 2, 2026, 13,  0,  0,  90);
    addTel(&T1, C, 12, 2, 2026, 15, 45,  0, 120);

    printf("=========== TEST 1 ===========\n");
    for (int i = 0; i < T1.numTelefonate; i++) stampaTelefonata(&T1.telefonate[i]);
    printf("f(T1) = %d\n", trovamax(T1));
    printf("ATTESO = 120\n\n");

    /* =========================
       TEST 2: minor numero telefonate = cliente B (2 chiamate)
       somma durate B = 40 + 20 = 60
       ========================= */
    listaTelefonate T2;
    T2.numTelefonate = 0;

    addTel(&T2, A,  1, 3, 2026,  8,  0,  0,  10);
    addTel(&T2, A,  1, 3, 2026,  9,  0,  0,  10);
    addTel(&T2, A,  1, 3, 2026, 10,  0,  0,  10);
    addTel(&T2, A,  1, 3, 2026, 11,  0,  0,  10);
    addTel(&T2, C,  2, 3, 2026, 12,  0,  0,  70);
    addTel(&T2, C,  2, 3, 2026, 12, 30,  0,  80);
    addTel(&T2, C,  2, 3, 2026, 13,  0,  0,  90);
    addTel(&T2, B,  3, 3, 2026, 14,  0,  0,  40);
    addTel(&T2, B,  3, 3, 2026, 15,  0,  0,  20);

    printf("=========== TEST 2 ===========\n");
    for (int i = 0; i < T2.numTelefonate; i++) stampaTelefonata(&T2.telefonate[i]);
    printf("f(T2) = %d\n", trovamax(T2));
    printf("ATTESO = 60\n\n");

    /* =========================
       TEST 3: minor numero telefonate = cliente A (1 chiamata)
       somma durate A = 300
       ========================= */
    listaTelefonate T3;
    T3.numTelefonate = 0;

    addTel(&T3, B,  5, 4, 2026,  9,  0,  0,  30);
    addTel(&T3, B,  5, 4, 2026, 10,  0,  0,  30);
    addTel(&T3, B,  5, 4, 2026, 11,  0,  0,  30);
    addTel(&T3, C,  6, 4, 2026, 12,  0,  0,  50);
    addTel(&T3, C,  6, 4, 2026, 13,  0,  0,  50);
    addTel(&T3, A,  7, 4, 2026, 14,  0,  0, 300);

    printf("=========== TEST 3 ===========\n");
    for (int i = 0; i < T3.numTelefonate; i++) stampaTelefonata(&T3.telefonate[i]);
    printf("f(T3) = %d\n", trovamax(T3));
    printf("ATTESO = 300\n\n");

    return 0;
}
int trovamax(listaTelefonate head)
    {
    int count=1000;
    cliente min=head.telefonate[0].cli;
    Lista new=NULL;
    for(int i=0; i<head.numTelefonate; i++)
        {
            Lista punt=trova(new, head.telefonate[i].cli);
            if(punt==NULL)
                {
                    new=inseriscincoda(new, head.telefonate[i].cli, head.telefonate[i].durata);
                }
            else
                {
                    (punt->numerotelefonate)++;
                    punt->sommadurata=punt->sommadurata+head.telefonate[i].durata;
                }
        }
    int min2=new->numerotelefonate;
    int durata=0;
    Lista scorri=new;
    while(scorri!=NULL)
        {
            if(scorri->numerotelefonate<min2)
                {
                    min2=scorri->numerotelefonate;
                    durata=scorri->sommadurata;
                }
            scorri=scorri->next;
        }
    return durata;
    }
Lista inseriscincoda(Lista head, cliente cli, int durata)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->cli=cli;
                new->next=head;
                new->numerotelefonate=1;
                new->sommadurata=durata;
                return new;
            }
    head->next=inseriscincoda(head->next, cli, durata);
    return head;
    }
Lista trova(Lista head, cliente cli)
    {
    Lista scorri=head;
    while(scorri!=NULL)
        {
            if(strcmp(scorri->cli.codiceFiscale,cli.codiceFiscale)==0)
                return scorri;
            scorri=scorri->next;
        }
    return NULL;;
    }

