//
//  main.c
//  tde 9 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//
#include <stdio.h>
#include <string.h>

#define N 1000
#define NS 20000
#define NC 2000
#define NE 400000

typedef struct { int giorno, mese, anno; } Data;

typedef struct {
    char matricola[7], nome[N], cognome[N];
    Data dataNascita;
    int valido;   /* 1 = occupato, 0 = vuoto */
} Studente;

typedef Studente Studenti[NS];

typedef struct {
    char codice[11], titolo[N];
    int numCrediti;
    int valido;   /* 1 = occupato, 0 = vuoto */
} Corso;

typedef Corso Corsi[NC];

typedef struct {
    char codiceCorso[11], matricolaStudente[N];
    int voto;
    Data data;
    int valido;   /* 1 = occupato, 0 = vuoto */
} Esame;

typedef Esame Esami[NE];


void f(Esami es, Corsi cor, Studenti stu, Studenti stuBravi);

/* ====== SUPPORTO STAMPA ====== */
void stampaStudente(const Studente *s) {
    printf("Matricola: %s | %s %s | Nascita: %02d/%02d/%04d\n",
           s->matricola, s->nome, s->cognome,
           s->dataNascita.giorno, s->dataNascita.mese, s->dataNascita.anno);
}

void stampaStuBravi(Studenti stuBravi) {
    printf("\n=== STUDENTI IN stuBravi (senza buchi) ===\n");
    int i = 0, count = 0;
    while (i < NS && stuBravi[i].valido == 1) {
        stampaStudente(&stuBravi[i]);
        count++;
        i++;
    }
    printf("Totale in stuBravi: %d\n", count);
}
float media(char matricola[], Esami lista);
int main(void) {
    /* ====== DICHIARAZIONI (array grandi: sono globalmente enormi, ma qui solo demo) ====== */
    static Studenti stu;
    static Corsi cor;
    static Esami es;
    static Studenti stuBravi;

    /* ====== INIZIALIZZA TUTTO A NON VALIDO ====== */
    for (int i = 0; i < NS; i++) {
        stu[i].valido = 0;
        stuBravi[i].valido = 0;
    }
    for (int i = 0; i < NC; i++) cor[i].valido = 0;
    for (int i = 0; i < NE; i++) es[i].valido = 0;

    /* ====== POPOLA QUALCHE STUDENTE ====== */
    stu[0].valido = 1;
    strcpy(stu[0].matricola, "123456");
    strcpy(stu[0].nome, "Mario");
    strcpy(stu[0].cognome, "Rossi");
    stu[0].dataNascita = (Data){10, 3, 2002};

    stu[1].valido = 1;
    strcpy(stu[1].matricola, "654321");
    strcpy(stu[1].nome, "Giulia");
    strcpy(stu[1].cognome, "Bianchi");
    stu[1].dataNascita = (Data){22, 11, 2001};

    stu[2].valido = 1;
    strcpy(stu[2].matricola, "111222");
    strcpy(stu[2].nome, "Luca");
    strcpy(stu[2].cognome, "Verdi");
    stu[2].dataNascita = (Data){5, 7, 2000};

    /* ====== POPOLA QUALCHE CORSO ====== */
    cor[0].valido = 1;
    strcpy(cor[0].codice, "INF001");
    strcpy(cor[0].titolo, "Informatica A");
    cor[0].numCrediti = 10;

    cor[1].valido = 1;
    strcpy(cor[1].codice, "MAT101");
    strcpy(cor[1].titolo, "Analisi 1");
    cor[1].numCrediti = 10;

    /* ====== POPOLA QUALCHE ESAME (collega matricola <-> corso) ====== */
    /* Esami di Mario (123456) */
    es[0].valido = 1;
    strcpy(es[0].codiceCorso, "INF001");
    strcpy(es[0].matricolaStudente, "123456");
    es[0].voto = 30;
    es[0].data = (Data){15, 2, 2024};

    es[1].valido = 1;
    strcpy(es[1].codiceCorso, "MAT101");
    strcpy(es[1].matricolaStudente, "123456");
    es[1].voto = 28;
    es[1].data = (Data){20, 6, 2024};

    /* Esami di Giulia (654321) */
    es[2].valido = 1;
    strcpy(es[2].codiceCorso, "INF001");
    strcpy(es[2].matricolaStudente, "654321");
    es[2].voto = 26;
    es[2].data = (Data){16, 2, 2024};

    es[3].valido = 1;
    strcpy(es[3].codiceCorso, "MAT101");
    strcpy(es[3].matricolaStudente, "654321");
    es[3].voto = 27;
    es[3].data = (Data){21, 6, 2024};

    /* Esami di Luca (111222) */
    es[4].valido = 1;
    strcpy(es[4].codiceCorso, "INF001");
    strcpy(es[4].matricolaStudente, "111222");
    es[4].voto = 30;
    es[4].data = (Data){18, 2, 2024};

    
    f(es, cor, stu, stuBravi);

    /* ====== STAMPA RISULTATO (stuBravi deve essere senza buchi) ====== */
    stampaStuBravi(stuBravi);

    return 0;
}
float media(char matricola[], Esami lista)
    {
    float somma=0;
    int count=0;
    for(int i=0; i<NE; i++)
        {
            if(lista[i].valido==1 && strcmp(lista[i].matricolaStudente,matricola)==0)
                {
                    somma=somma+lista[i].voto;
                    count++;
                }
        }
    return somma/count;
    }
void f(Esami es, Corsi cor, Studenti stu, Studenti stuBravi)
{
    int j=0;
    for(int i=0; i<NS; i++)
    {
        if(stu[i].valido==1)
        {
            float m=media(stu[i].matricola, es);
            if(m>=27)
            {
                stuBravi[j]=stu[i];
                j++;
            }
        }
        
    }
}
