//
//  main.c
//  es tde 6 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct EL{
    char nome[100];
    char cognome[100];
    char sesso;
    int eta;
    struct EL *next;
}Persona;

typedef Persona *Lista;

typedef struct{
    Persona istr1;
    Persona istr2;
    Lista studenti;
    int num_studenti;
}Classe;
void f(Classe c, float *media_maschi, float *media_tutti);

/* ===== FUNZIONI DI SUPPORTO PER IL MAIN ===== */
Persona* newPersona(const char *nome, const char *cognome, char sesso, int eta) {
    Persona *p = (Persona*)malloc(sizeof(Persona));
    if(!p) { printf("Errore malloc\n"); exit(1); }
    strcpy(p->nome, nome);
    strcpy(p->cognome, cognome);
    p->sesso = sesso;
    p->eta = eta;
    p->next = NULL;
    return p;
}

Lista pushBack(Lista head, Persona *node) {
    if(head == NULL) return node;
    Persona *cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = node;
    return head;
}

void stampaListaStudenti(Lista head) {
    while(head != NULL) {
        printf(" - %s %s (%c, %d)\n", head->nome, head->cognome, head->sesso, head->eta);
        head = head->next;
    }
}

void freeLista(Lista head) {
    while(head != NULL) {
        Persona *tmp = head->next;
        free(head);
        head = tmp;
    }
}

void mediaClasse(Classe c, float *media_maschi, float *media_tutti);
int main() {
    Classe c;

    /* --- ISTRUTTORI (sono DUE struct Persona, non puntatori) --- */
    strcpy(c.istr1.nome, "Marco");
    strcpy(c.istr1.cognome, "Rossi");
    c.istr1.sesso = 'M';
    c.istr1.eta = 35;
    c.istr1.next = NULL;   // inutile ma pulito

    strcpy(c.istr2.nome, "Laura");
    strcpy(c.istr2.cognome, "Bianchi");
    c.istr2.sesso = 'F';
    c.istr2.eta = 32;
    c.istr2.next = NULL;

    /* --- STUDENTI: LISTA CONCATENATA --- */
    c.studenti = NULL;
    c.num_studenti = 0;

    c.studenti = pushBack(c.studenti, newPersona("Luca",   "Verdi",   'M', 20)); c.num_studenti++;
    c.studenti = pushBack(c.studenti, newPersona("Giulia", "Neri",    'F', 19)); c.num_studenti++;
    c.studenti = pushBack(c.studenti, newPersona("Paolo",  "Fontana", 'M', 27)); c.num_studenti++;
    c.studenti = pushBack(c.studenti, newPersona("Sara",   "Gallo",   'F', 23)); c.num_studenti++;
    c.studenti = pushBack(c.studenti, newPersona("Andrea", "Riva",    'M', 31)); c.num_studenti++;
    c.studenti = pushBack(c.studenti, newPersona("Elena",  "Costa",   'F', 25)); c.num_studenti++;

    /* --- STAMPA DI CONTROLLO --- */
    printf("Istruttore 1: %s %s (%c, %d)\n", c.istr1.nome, c.istr1.cognome, c.istr1.sesso, c.istr1.eta);
    printf("Istruttore 2: %s %s (%c, %d)\n", c.istr2.nome, c.istr2.cognome, c.istr2.sesso, c.istr2.eta);

    printf("\nStudenti (%d):\n", c.num_studenti);
    stampaListaStudenti(c.studenti);

    float mm, mt;
    mediaClasse(c, &mm, &mt);
    printf("\nMedia maschi: %.2f\n", mm);
    printf("Media totale: %.2f\n", mt);

    /* --- FREE --- */
    freeLista(c.studenti);
    c.studenti = NULL;

    return 0;
}
void mediaClasse(Classe c, float *media_maschi, float *media_tutti)
    {
    float somma_tutti=0;
    float somma_maschi=0;
    int count_tutti=0;
    int count_maschi=0;
    Lista punt=c.studenti;
    while(punt!=NULL)
        {
            somma_tutti=somma_tutti+punt->eta;
            count_tutti++;
            if(punt->sesso=='M')
                {
                    somma_maschi=somma_maschi+punt->eta;
                    count_maschi++;
                }
            punt=punt->next;
        }
    *media_tutti=somma_tutti/count_tutti;
    *media_maschi=somma_maschi/count_maschi;
    }
