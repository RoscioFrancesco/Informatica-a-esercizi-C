//  Created by Francesco Roscio Ricon on 08/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct v {
    char sequenza[100];
    int lunghezza;
    char nome[50];
    struct v *next;
} Nodo;

typedef Nodo * Lista;
Lista inseriscincodamia(Lista head, char sequenza[], int len, char nome[]);


void verifica(char programma[], int lunProg, Lista virusLis);
void aggiorna(Lista *virusLis, Lista virusScaricati); /* NOTA: uso Lista* per poter modificare la testa */

/* =========================
   UTILITY PER TEST
   ========================= */
static Lista nuovoVirus(const char *seq, int len, const char *nome) {
    Nodo *n = (Nodo *)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    memset(n, 0, sizeof(*n));
    strncpy(n->sequenza, seq, sizeof(n->sequenza) - 1);
    n->lunghezza = len;
    strncpy(n->nome, nome, sizeof(n->nome) - 1);
    n->next = NULL;
    return n;
}

static void pushTesta(Lista *head, Lista nodo) {
    nodo->next = *head;
    *head = nodo;
}

static void stampaDB(Lista head, const char *titolo) {
    printf("=== %s ===\n", titolo);
    if (!head) {
        printf("(vuoto)\n\n");
        return;
    }
    for (Lista p = head; p != NULL; p = p->next) {
        printf("Nome: %-12s | len=%d | seq=\"",
               p->nome, p->lunghezza);
        /* stampa solo i primi lunghezza char */
        for (int i = 0; i < p->lunghezza && p->sequenza[i] != '\0'; i++)
            putchar(p->sequenza[i]);
        printf("\"\n");
    }
    printf("\n");
}

static void freeLista(Lista head) {
    while (head) {
        Lista tmp = head->next;
        free(head);
        head = tmp;
    }
}

/* =========================
   FUNZIONI RICHIESTE (STUB)
   ========================= */
int trovato(Lista head, char sequenza[]);
int cercavirus(char programma[], char virus[], int lenp, int lenv);

/* =========================
   MAIN DI TEST
   ========================= */


int main(void) {
    /* Programma "scansionato" (esempio semplice con stringhe) */
    char programma[] = "AAAAxxVIRUS1xxBBBBxxVIRUS1xxCCCCyyVIRUS2yy";
    int lunProg = (int)strlen(programma);

    /* Database virus già noti */
    Lista db = NULL;
    pushTesta(&db, nuovoVirus("VIRUS2", 6, "Trojan.Z"));
    pushTesta(&db, nuovoVirus("VIRUS1", 6, "Worm.A"));

    /* Virus appena scaricati (aggiornamento) */
    Lista scaricati = NULL;
    pushTesta(&scaricati, nuovoVirus("VIRUS3", 6, "Spy.B"));   /* nuovo */
    pushTesta(&scaricati, nuovoVirus("VIRUS1", 6, "Worm.A"));  /* già presente */
    pushTesta(&scaricati, nuovoVirus("ABC", 3, "Test.C"));     /* nuovo (solo per test) */

    stampaDB(db, "DB corrente");
    stampaDB(scaricati, "Virus scaricati");

    printf("=== Scansione programma ===\n");
    printf("Programma: \"%s\"\n", programma);
    printf("Lunghezza: %d\n\n", lunProg);

    /* Test verifica */
    verifica(programma, lunProg, db);
    printf("\n");

    /* Test aggiorna */
    aggiorna(&db, scaricati);
    printf("\n");

    /* Dopo aggiornamento */
    stampaDB(db, "DB dopo aggiorna() (quando la implementi, dovrebbe includere i nuovi)");

    freeLista(db);
    freeLista(scaricati);
    return 0;
}
void verifica(char programma[], int lunProg, Lista virusLis)
    {
        if(virusLis==NULL)
            return;
    Lista scorri_lista=virusLis;
    Lista new_virusmiei=NULL;
    while (scorri_lista!=NULL) {
        if(cercavirus(programma, scorri_lista->sequenza, lunProg, scorri_lista->lunghezza))
            {
                if(trovato(new_virusmiei, scorri_lista->sequenza)==0)
                    {
                        new_virusmiei=inseriscincodamia(new_virusmiei, scorri_lista->sequenza, scorri_lista->lunghezza, scorri_lista->nome);
                    }
            }
        
        scorri_lista=scorri_lista->next;
        }
    Lista scorri_miei=new_virusmiei;
    if(scorri_miei==NULL)
        printf("Nessun virus trovato");
    else
        {
            while (scorri_miei!=NULL) {
                printf("virus trovati:%s\n", scorri_miei->nome);
                scorri_miei=scorri_miei->next;
            }
        }
    }
int cercavirus(char programma[], char virus[], int lenp, int lenv)
    {
    for(int i=0; i<lenp-lenv; i++)
        {
            if(programma[i]==virus[0])
                {
                    int flag=1;
                    for(int j=0; j<lenv; j++)
                        {
                            if(programma[i+j]!=virus[j]) // le sequenze non coincidono
                            {
                                flag=0;
                                break;
                            }
                        
                        }
                    if(flag==1)
                        return 1;
                }
        }
    return 0;
    }
Lista inseriscincodamia(Lista head, char sequenza[], int len, char nome[])
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                strcpy(new->sequenza,sequenza);
                new->next=head;
                new->lunghezza=len;
                strcpy(new->nome, nome);
                return new;
            }
    head->next=inseriscincodamia(head->next, sequenza, len, nome);
    return head;
    }
int trovato(Lista head, char sequenza[])
    {
        if(head==NULL)
            return 0;
    Lista scorri=head;
    while (scorri!=NULL) {
        if(strcmp(sequenza, scorri->sequenza)==0)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
void aggiorna(Lista *virusLis, Lista virusScaricati)
    {
        Lista scorri_nuovi=virusScaricati;
    while (scorri_nuovi!=NULL) {
        if(trovato(*virusLis, scorri_nuovi->sequenza)==0)
            {
                *virusLis=inseriscincodamia(*virusLis, scorri_nuovi->sequenza, scorri_nuovi->lunghezza, scorri_nuovi->nome);
            }
            scorri_nuovi=scorri_nuovi->next;
        }
    }
