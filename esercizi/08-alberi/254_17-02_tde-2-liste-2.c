//
//  main.c
//  tde 2 liste  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nd {
    char *word;
    struct Nd *next;
} Nodo;

typedef Nodo *Lista;

typedef struct Blc {
    Lista primo;
    Lista ultimo;
} Blocco;

typedef Blocco Vettore[26];

/* =========================
   (OPZIONALE) Albero per trasforma
   ========================= */
typedef struct Tn {
    char *word;
    struct Tn *left, *right;
} TNode;

typedef TNode *tree;
Lista f(char parola[], Lista L, Vettore V);
/* =========================
   PROTOTIPI ESERCIZIO
   ========================= */
Lista inserisci(char *p, Lista L, Vettore V);
tree trasforma(Lista L); /* firma indicativa */

/* =========================
   SUPPORTO PER I TEST
   ========================= */
static int idx(char c) { return (c - 'A'); }

static Nodo *newNode(const char *s) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->word = (char*)malloc(strlen(s) + 1);
    strcpy(n->word, s);
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista L, const char *s) {
    if (!L) return newNode(s);
    Nodo *cur = L;
    while (cur->next) cur = cur->next;
    cur->next = newNode(s);
    return L;
}

static void freeList(Lista L) {
    while (L) {
        Nodo *tmp = L;
        L = L->next;
        free(tmp->word);
        free(tmp);
    }
}

static void initV(Vettore V) {
    for (int i = 0; i < 26; i++) {
        V[i].primo = NULL;
        V[i].ultimo = NULL;
    }
}

/* Ricostruisce V da una lista già ordinata (per preparare i test) */
static void buildVfromList(Lista L, Vettore V) {
    initV(V);
    Nodo *cur = L;
    while (cur) {
        int i = idx(cur->word[0]);
        if (i < 0 || i > 25) { cur = cur->next; continue; }
        if (V[i].primo == NULL) V[i].primo = cur;
        V[i].ultimo = cur;
        cur = cur->next;
    }
}

static void printList(const char *title, Lista L) {
    printf("%s", title);
    if (!L) { printf("NULL\n"); return; }
    while (L) {
        printf("%s", L->word);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void printV(const char *title, Vettore V) {
    printf("%s\n", title);
    for (int i = 0; i < 26; i++) {
        char letter = (char)('A' + i);
        if (V[i].primo == NULL && V[i].ultimo == NULL) continue;

        printf("  %c: ", letter);
        printf("primo=");
        if (V[i].primo) printf("%s", V[i].primo->word);
        else printf("NULL");

        printf(", ultimo=");
        if (V[i].ultimo) printf("%s", V[i].ultimo->word);
        else printf("NULL");
        printf("\n");
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* Lista iniziale ORDINATA (maiuscole) */
    Lista L = NULL;
    L = pushBack(L, "ALFA");
    L = pushBack(L, "ALGORITMO");
    L = pushBack(L, "BETA");
    L = pushBack(L, "DELTA");
    L = pushBack(L, "OMEGA");

    Vettore V;
    buildVfromList(L, V);

    printf("===== STATO INIZIALE =====\n");
    printList("Lista: ", L);
    printV("Vettore V (solo lettere presenti):", V);
    printf("\n");

    /* TEST 1: inserimento in mezzo allo stesso segmento 'A' */
    printf("===== TEST 1: inserisci(\"ALBUM\") =====\n");
    printf("Output atteso: ALBUM entra tra ALFA e ALGORITMO; segmento A aggiornato\n");
    L = inserisci("ALBUM", L, V);
    printList("Lista dopo: ", L);
    printV("V dopo:", V);
    printf("\n");

    /* TEST 2: inserimento come nuova iniziale (segmento prima NULL) */
    printf("===== TEST 2: inserisci(\"GAMMA\") =====\n");
    printf("Output atteso: nasce segmento G con primo=ultimo=GAMMA\n");
    L = inserisci("GAMMA", L, V);
    printList("Lista dopo: ", L);
    printV("V dopo:", V);
    printf("\n");

    /* TEST 3: inserimento in testa assoluta */
    printf("===== TEST 3: inserisci(\"AARDVARK\") =====\n");
    printf("Output atteso: AARDVARK diventa la testa; A.primo cambia a AARDVARK\n");
    L = inserisci("AARDVARK", L, V);
    printList("Lista dopo: ", L);
    printV("V dopo:", V);
    printf("\n");

    /* TEST 4: inserimento in coda assoluta (iniziale Z) */
    printf("===== TEST 4: inserisci(\"ZETA\") =====\n");
    printf("Output atteso: ZETA va in fondo; nasce segmento Z con primo=ultimo=ZETA\n");
    L = inserisci("ZETA", L, V);
    printList("Lista dopo: ", L);
    printV("V dopo:", V);
    printf("\n");

    /* (Opzionale) test trasforma */
    printf("===== TEST 5 (OPZIONALE): trasforma(lista) =====\n");
    printf("Qui NON stampiamo output dell'albero (dipende dalla tua implementazione).\n");
    /* tree T = trasforma(L); */

    freeList(L);
    return 0;
}



Lista inserisci(char *p, Lista L, Vettore V) {
    L=f(p, L, V);
    return L;
}

//tree trasforma(Lista L) {
//    // TODO: tua soluzione
//}
//*/

//Si codifichi in C la funzione Lista inserisci(char * p, Lista L, Vettore V) che inserisce una nuova
//parola p in ordine alfabetico nella struttura dati aggiornando opportunamente il vettore
//ausiliario e restituendo la lista modificata
Lista inserimentoOrdinato(Lista l, char parola[])
    {
        if(l==NULL || strcmp(parola, l->word)<0)
            {
                Lista new=(Lista)malloc(sizeof(Nodo));
                new->next=l;
                new->word=malloc(sizeof(char)*(1+strlen(parola)));
                strcpy(new->word, parola);
                return new;
            }
    l->next=inserimentoOrdinato(l->next, parola);
    return l;
    }
Lista f(char parola[], Lista L, Vettore V) {
    L=inserimentoOrdinato(L, parola);
    int punt=parola[0]-'A';
    printf("\n\npunt:%d", punt);
    for(int i=0; i<26; i++)
        {
            if(i==punt)
                {
                    if(V[i].primo==NULL)
                        {
                            Lista temp=L;
                            while(temp!=NULL && temp->next!=NULL)
                                {
                                    if(strcmp(parola, temp->next->word)<0)
                                        break;
                                    temp=temp->next;
                                }
                            V[i].primo=temp;
                            V[i].ultimo=temp;
                        }
                    else
                    {
                        if(strcmp(parola, V[i].primo->word)<0)
                        {
                            Lista temp=L;
                            while(temp!=NULL && temp->next!=V[i].primo)
                            {
                                temp=temp->next;
                            }
                            V[i].primo=temp;
                        }
                    }
                }
        }
    return L;
}
