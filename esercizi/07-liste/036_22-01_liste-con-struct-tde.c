//
//  main.c
//  liste con struct tde
//
//  Created by Francesco Roscio Ricon on 22/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ====== STRUTTURE (con correzione next in Sp) ====== */
typedef struct Date {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct Cli {
    int CodiceCliente;
    char cognome[100], nome[100];
    int puntiAccumulati;
} Cliente;

typedef struct CliN {
    Cliente C;
    struct CliN *next;
} ClienteNodo;

typedef ClienteNodo *ListaDiClienti;

typedef struct ES {
    char nomeProdotto[100];
    int prezzoUnitario;
    int quantitaAcquistata;
    struct ES *next;
} ElementoScontrino;

typedef ElementoScontrino *Scontrino;

typedef struct Sp {
    int CodiceCliente;
    Scontrino s;
    Data data;
    struct Sp *next;   /* <-- correzione */
} Spesa;

typedef Spesa *ListaDiSpese;



typedef struct EL {
    int CodiceCliente;
    char cognome[100], nome[100];
    int spesa;
    struct EL *next;
    int punti_accumulati;
} Cliente_mio;
typedef Cliente_mio *Lista_Clienti_miei;

/* ====== FUNZIONI DI COSTRUZIONE ====== */
ListaDiClienti inserisciClienteInTesta(ListaDiClienti l, int codice, const char *cognome, const char *nome, int punti) {
    ClienteNodo *n = malloc(sizeof(ClienteNodo));
    if (!n) exit(1);

    n->C.CodiceCliente = codice;
    strncpy(n->C.cognome, cognome, sizeof(n->C.cognome) - 1);
    n->C.cognome[sizeof(n->C.cognome) - 1] = '\0';
    strncpy(n->C.nome, nome, sizeof(n->C.nome) - 1);
    n->C.nome[sizeof(n->C.nome) - 1] = '\0';
    n->C.puntiAccumulati = punti;

    n->next = l;
    return n;
}

Scontrino aggiungiElementoScontrinoInTesta(Scontrino s, const char *prodotto, int prezzoUnit, int qta) {
    ElementoScontrino *e = malloc(sizeof(ElementoScontrino));
    if (!e) exit(1);

    strncpy(e->nomeProdotto, prodotto, sizeof(e->nomeProdotto) - 1);
    e->nomeProdotto[sizeof(e->nomeProdotto) - 1] = '\0';
    e->prezzoUnitario = prezzoUnit;
    e->quantitaAcquistata = qta;

    e->next = s;
    return e;
}

/* Inserimento in coda: comodo perché la lista spese deve essere cronologica */
ListaDiSpese inserisciSpesaInCoda(ListaDiSpese l, int codiceCliente, Data d, Scontrino s) {
    Spesa *n = malloc(sizeof(Spesa));
    if (!n) exit(1);

    n->CodiceCliente = codiceCliente;
    n->data = d;
    n->s = s;
    n->next = NULL;

    if (l == NULL) return n;

    Spesa *p = l;
    while (p->next != NULL) p = p->next;
    p->next = n;
    return l;
}

/* ====== FUNZIONI DI STAMPA ====== */
void stampaClienti(ListaDiClienti l) {
    printf("== Lista Clienti ==\n");
    while (l) {
        printf("Cod:%d  %s %s  Punti:%d\n",
               l->C.CodiceCliente, l->C.cognome, l->C.nome, l->C.puntiAccumulati);
        l = l->next;
    }
}

int totaleScontrino(Scontrino s) {
    int tot = 0;
    while (s) {
        tot += s->prezzoUnitario * s->quantitaAcquistata;
        s = s->next;
    }
    return tot;
}

void stampaScontrino(Scontrino s) {
    while (s) {
        printf("   - %s | %d x %d = %d\n",
               s->nomeProdotto, s->prezzoUnitario, s->quantitaAcquistata,
               s->prezzoUnitario * s->quantitaAcquistata);
        s = s->next;
    }
}

void stampaSpese(ListaDiSpese l) {
    printf("\n== Lista Spese (cronologica) ==\n");
    while (l) {
        printf("Cliente:%d  Data:%02d/%02d/%04d  Totale:%d\n",
               l->CodiceCliente, l->data.giorno, l->data.mese, l->data.anno,
               totaleScontrino(l->s));
        stampaScontrino(l->s);
        l = l->next;
    }
}

int trovato(int codicecliente, Lista_Clienti_miei head);
Lista_Clienti_miei inserisci_in_testa(Lista_Clienti_miei head, ListaDiClienti cliente, int sommaspese);
ListaDiClienti trovaclienti(int numerocliente, ListaDiClienti head);
Cliente trovamigliore(Lista_Clienti_miei head);
Cliente clienteMigliore(ListaDiSpese cronologia, ListaDiClienti elenco);

int main(void) {
    ListaDiClienti clienti = NULL;
    ListaDiSpese spese = NULL;

    /* --- Creo qualche cliente --- */
    clienti = inserisciClienteInTesta(clienti, 1003, "Verdi", "Luca", 0);
    clienti = inserisciClienteInTesta(clienti, 1002, "Bianchi", "Sara", 0);
    clienti = inserisciClienteInTesta(clienti, 1001, "Rossi", "Mario", 0);

    /* --- Creo spese cronologiche (inserimento in coda) --- */
    Data d1 = {10, 1, 2026};
    Scontrino s1 = NULL;
    s1 = aggiungiElementoScontrinoInTesta(s1, "Pasta", 2, 3);     // 6
    s1 = aggiungiElementoScontrinoInTesta(s1, "Sugo", 3, 1);      // 3
    spese = inserisciSpesaInCoda(spese, 1001, d1, s1);            // totale 9

    Data d2 = {12, 1, 2026};
    Scontrino s2 = NULL;
    s2 = aggiungiElementoScontrinoInTesta(s2, "Latte", 2, 2);     // 4
    s2 = aggiungiElementoScontrinoInTesta(s2, "Biscotti", 4, 1);  // 4
    spese = inserisciSpesaInCoda(spese, 1002, d2, s2);            // totale 8

    Data d3 = {15, 1, 2026};
    Scontrino s3 = NULL;
    s3 = aggiungiElementoScontrinoInTesta(s3, "Carne", 8, 1);     // 8
    s3 = aggiungiElementoScontrinoInTesta(s3, "Pane", 1, 2);      // 2
    spese = inserisciSpesaInCoda(spese, 1001, d3, s3);            // totale 10

    /* --- Stampo per verificare --- */
    stampaClienti(clienti);
    stampaSpese(spese);

    Cliente migliore=clienteMigliore(spese, clienti);
    printf("%d\n", migliore.CodiceCliente);
    printf("%s\n", migliore.nome);
    printf("%s\n", migliore.cognome);
    printf("%d\n", migliore.puntiAccumulati);
}


Cliente clienteMigliore(ListaDiSpese cronologia, ListaDiClienti elenco)
    {
    Lista_Clienti_miei head=NULL;
    ListaDiSpese scorrispese=cronologia;
    while (scorrispese!=NULL) {
        if(trovato(scorrispese->CodiceCliente, head))
            scorrispese=scorrispese->next;
        else {
            ListaDiSpese scorrispese2=scorrispese;
            int somma=0;
            while (scorrispese2!=NULL) {
                if(scorrispese2->CodiceCliente==scorrispese->CodiceCliente)
                    {
                        somma=somma+(scorrispese->s->prezzoUnitario)*(scorrispese->s->quantitaAcquistata);
                    }
                scorrispese2=scorrispese2->next;
            }
        
            head=inserisci_in_testa(head, trovaclienti(scorrispese->CodiceCliente, elenco), somma);
            scorrispese=scorrispese->next;
            }
        }
    return trovamigliore(head);
    }

Lista_Clienti_miei inserisci_in_testa(Lista_Clienti_miei head, ListaDiClienti cliente, int sommaspese)
    {
    Lista_Clienti_miei new=(Lista_Clienti_miei)malloc(sizeof(Cliente_mio));
    new->next=head;
    new->CodiceCliente=cliente->C.CodiceCliente;
    new->spesa=sommaspese;
    strcpy(new->cognome,cliente->C.cognome);
    strcpy(new->nome, cliente->C.nome);
    new->punti_accumulati=cliente->C.puntiAccumulati;
    return new;
    }
int trovato(int codicecliente, Lista_Clienti_miei head)
    {
    if(head==NULL)
        return 0;
    Lista_Clienti_miei scorrilista=head;
    while (scorrilista!=NULL) {
        if(scorrilista->CodiceCliente==codicecliente)
            return 1;
        scorrilista=scorrilista->next;
    }
    return 0;
    }
ListaDiClienti trovaclienti(int numerocliente, ListaDiClienti head)
    {
    ListaDiClienti scorri=head;
    while(scorri!=NULL)
        {
            if(scorri->C.CodiceCliente==numerocliente)
                return scorri;
            scorri=scorri->next;
        }
    return head;
    }

Cliente trovamigliore(Lista_Clienti_miei head)
    {
    int max=0;
    Cliente new;
    Lista_Clienti_miei scorrilista=head;
    while (scorrilista!=NULL) {
        if(scorrilista->spesa>max)
            {
                max=scorrilista->spesa;
            }
        scorrilista=scorrilista->next;
        }
    scorrilista=head;
    while (scorrilista!=NULL)
        {
            if(scorrilista->spesa==max)
                {
                    new.CodiceCliente=scorrilista->CodiceCliente;
                    strcpy(new.cognome,scorrilista->cognome);
                    strcpy(new.nome,scorrilista->nome);
                    new.puntiAccumulati=scorrilista->punti_accumulati;
                    return new;
                }
            scorrilista=scorrilista->next;
        }
    return new;
    }
