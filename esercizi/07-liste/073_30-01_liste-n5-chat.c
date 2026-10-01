//  Created by Francesco Roscio Ricon on 30/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
   STRUTTURA LISTA PAROLE
   ======================= */
typedef struct Node {
    char *word;          // stringa allocata dinamicamente
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY (per test)
   - build/print/free possono usare cicli
   ======================= */

static char* my_strdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *d = (char*)malloc(n + 1);
    if (!d) { perror("malloc"); exit(1); }
    memcpy(d, s, n + 1);
    return d;
}

static Node* newNode(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = my_strdup(w);
    n->next = next;
    return n;
}

static Lista buildListFromArray(const char *arr[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i)
        l = newNode(arr[i], l);
    return l;
}

static void printList(Lista l) {
    printf("[");
    for (Node *p = l; p != NULL; p = p->next) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
    }
    printf("]\n");
}

static void freeList(Lista l) {
    while (l != NULL) {
        Node *tmp = l;
        l = l->next;
        free(tmp->word);
        free(tmp);
    }
}
int trovaFinish(Lista cur, int cont, Lista *finish);
int aperta(char parola[]);
int chiusa(char parola[]);
Lista Eliminadastart(Lista start, char parola[]);
Lista EliminafinoFinish(Lista head, char parola[]);
Lista f(Lista head, int found, int contatore, Lista start, Lista finish);
/* =======================
   ESERCIZIO E5 (TODO)
   ======================= */
/*
  TODO:
  - Un blocco inizia quando incontri una parola contenente '('.
  - Tieni un contatore: +1 per '(' e -1 per ')', sommando su tutte le parole del blocco.
  - Il blocco finisce quando il contatore torna a 0 (bilanciamento chiuso).
  - Elimina interamente ogni blocco bilanciato trovato.
  - Se un blocco non si chiude entro fine lista, NON eliminare nulla di quel blocco.
  - Solo ricorsione, passando lo stato (contatore) tra le chiamate.
  - Libera nodi eliminati (nodo + stringa).
*/
Lista eliminaBlocchiBilanciatiParentesi(Lista l);

/* =======================
   FUNZIONE DI TEST (build + stampa prima/dopo)
   ======================= */
static void testCase(const char *title, const char *arr[], int n) {
    printf("=== %s ===\n", title);

    Lista L = buildListFromArray(arr, n);

    printf("Prima : ");
    printList(L);

    L=f(L, 0, 0, NULL, NULL);

    printf("Dopo  : ");
    printList(L);

    freeList(L);
    printf("\n");
}
int aperta(char parola[]);
int chiusa(char parola[]);
Lista Eliminadastart(Lista start, char parola[]);
Lista EliminafinoFinish(Lista head, char parola[]);
Lista f(Lista head, int found, int contatore, Lista start, Lista finish);
/* =======================
   MAIN: CASI DI TEST MIRATI
   ======================= */
int main(void) {
    /* Caso 0: lista vuota */
    {
        const char **arr = NULL;
        testCase("Caso 0: lista vuota", arr, 0);
    }

    /* Caso 1: nessuna parentesi -> nessun blocco */
    {
        const char *arr[] = {"a", "b", "c"};
        testCase("Caso 1: nessuna parentesi", arr, 3);
    }

    /* Caso 2: blocco bilanciato semplice (apre e chiude su più parole) */
    {
        const char *arr[] = {"x", "in(izio", "uno", "due)", "y"};
        testCase("Caso 2: blocco bilanciato su piu parole", arr, 5);
    }

    /* Caso 3: blocco bilanciato in una sola parola */
    {
        const char *arr[] = {"keep", "a(b)c", "tail"};
        testCase("Caso 3: blocco bilanciato in una parola", arr, 3);
    }

    /* Caso 4: blocco non chiuso -> non eliminare nulla del blocco */
    {
        const char *arr[] = {"x", "start(", "mid", "end", "tail"};
        testCase("Caso 4: blocco non chiuso (non si elimina)", arr, 5);
    }

    /* Caso 5: più blocchi bilanciati disgiunti */
    {
        const char *arr[] = {"a", "b(", "c)", "keep", "d(", "e", "f)", "z"};
        testCase("Caso 5: due blocchi bilanciati disgiunti", arr, 8);
    }

    /* Caso 6: parentesi annidate su parole diverse (contatore sale e scende) */
    {
        const char *arr[] = {"x", "A(", "B(", "C)", "D)", "y"};
        testCase("Caso 6: annidamento su piu parole", arr, 6);
    }

    /* Caso 7: una ')' prima di qualsiasi '(' (non apre blocco da sola) */
    {
        const char *arr[] = {"x)", "keep", "a(", "b)", "tail"};
        testCase("Caso 7: chiusura senza apertura, poi blocco normale", arr, 5);
    }

    /* Caso 8: blocco che si chiude e poi un altro che non si chiude */
    {
        const char *arr[] = {"p(", "q)", "ok", "r(", "s", "t"};
        testCase("Caso 8: primo blocco chiuso, secondo non chiuso", arr, 6);
    }

    return 0;
}
/*
  TODO:
  - Un blocco inizia quando incontri una parola contenente '('.
  - Tieni un contatore: +1 per '(' e -1 per ')', sommando su tutte le parole del blocco.
  - Il blocco finisce quando il contatore torna a 0 (bilanciamento chiuso).
  - Elimina interamente ogni blocco bilanciato trovato.
  - Se un blocco non si chiude entro fine lista, NON eliminare nulla di quel blocco.
  - Solo ricorsione, passando lo stato (contatore) tra le chiamate.
  - Libera nodi eliminati (nodo + stringa).
*/

Lista f(Lista head, int found, int contatore, Lista start, Lista finish)
    {
        if(head==NULL)
            return head;
    if(aperta(head->word))
    {
        if(found==0)
        {
            found=1;
            contatore++;
            start=head;

            // ✅ CORREZIONE: qui trovi finish subito, invece di aspettare di arrivarci col frame "finish"
            if (trovaFinish(start, 0, &finish)) {
                Eliminadastart(start, finish->word);
                finish->next = f(finish->next, 0, 0, NULL, NULL);
                return head; // ✅ ritorna la testa corretta del segmento (head==start)
            } else {
                return head;
            }
        }
        else
        {
            contatore++;
        }
    }
    head->next=f(head->next, found, contatore, start, finish);
    return head;
    }
int aperta(char parola[])
    {
    int i=0;
    while(parola[i]!='\0')
        {
            if(parola[i]=='(')
                return 1;
            i++;
        }
    return 0;
    }
int chiusa(char parola[])
{
int i=0;
while(parola[i]!='\0')
    {
        if(parola[i]==')')
            return 1;
        i++;
    }
return 0;
}
Lista EliminafinoFinish(Lista head, char parola[])
    {
        if(head==NULL)
            return head;
        int compare=strcmp(head->word, parola);
        if(compare==0)
            return head;
        if(compare!=0)
            {
                Lista temp=head->next;
                free(head->word);
                free(head);
                return EliminafinoFinish(temp, parola);
            }
        head->next=EliminafinoFinish(head->next, parola);
        return head;
    }
Lista Eliminadastart(Lista start, char parola[])
    {
        if(start==NULL)
            return start;
        start->next=EliminafinoFinish(start->next, parola);
    return start;
    }
int trovaFinish(Lista cur, int cont, Lista *finish) {
    if (cur == NULL) return 0;

    if (aperta(cur->word)) cont++;
    if (chiusa(cur->word)) cont--;

    if (cont == 0) {
        *finish = cur;
        return 1;
    }
    return trovaFinish(cur->next, cont, finish);
}
//Regola mentale da esame (scrivila sul cervello)
//
//❓ Sto eliminando il nodo corrente (head)?
//
//👉 Sì → ritorna il risultato della ricorsione sul next
//
//👉 No → ritorna head
//
//Nel tuo caso:
//
//non elimini head
//
//elimini solo nodi dopo (start->next ... finish->prev)
//
//➡️ quindi return head;
