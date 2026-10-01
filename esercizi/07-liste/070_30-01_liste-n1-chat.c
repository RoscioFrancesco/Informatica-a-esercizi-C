//
//  main.c
//  liste n1 chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/* =======================
   STRUTTURA LISTA
   ======================= */
typedef struct Node {
    char *word;          // stringa dinamica
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY ALLOCAZIONE
   ======================= */

static char* my_strdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *d = (char*)malloc(n + 1);
    if (!d) {
        perror("malloc");
        exit(1);
    }
    memcpy(d, s, n + 1);
    return d;
}

static Node* newNode(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->word = my_strdup(w);  // stringa allocata dinamicamente
    n->next = next;
    return n;
}
Lista removeIfPropertyP(Lista l);
/* =======================
   STAMPA / FREE (RICORSIVI)
   ======================= */

void printList(Lista l) {
    if (l == NULL) {
        printf("NULL\n");
        return;
    }
    printf("\"%s\" -> ", l->word);
    printList(l->next);
}

void freeList(Lista l) {
    if (l == NULL) return;
    freeList(l->next);
    free(l->word);
    free(l);
}

/* =======================
   PROPRIETA' P (TUTTO RICORSIVO)
   ======================= */

static bool isVowelChar(char c) {
    c = (char)tolower((unsigned char)c);
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');
}

static int lenRec(const char *s) {
    if (s == NULL || *s == '\0') return 0;
    return 1 + lenRec(s + 1);
}

/*
  Ritorna true se esiste almeno una coppia di vocali UGUALI consecutive,
  es: "coooperare" -> 'o' e 'o' consecutive (vale true)
*/
static bool hasTwoEqualConsecutiveVowelsRec(const char *s) {
    if (s == NULL) return false;
    if (s[0] == '\0' || s[1] == '\0') return false;

    char a = (char)tolower((unsigned char)s[0]);
    char b = (char)tolower((unsigned char)s[1]);

    if (isVowelChar(a) && isVowelChar(b) && a == b) return true;
    return hasTwoEqualConsecutiveVowelsRec(s + 1);
}

static bool propertyP(const char *w) {
    int L = lenRec(w);
    bool evenLen = (L % 2 == 0);
    bool twoEqVowels = hasTwoEqualConsecutiveVowelsRec(w);

    /* XOR logico: vero se esattamente uno dei due è vero */
    return (evenLen && !twoEqVowels) || (!evenLen && twoEqVowels);
}

/* =======================
   RIMOZIONE RICORSIVA
   ======================= */
/*
  Elimina in-place tutti i nodi che soddisfano P.
  - head: puntatore alla testa (può cambiare)
  - ritorna: numero di nodi rimossi
  Vincoli: niente cicli, niente strutture ausiliarie, solo ricorsione.
*/

/* =======================
   MAIN + ESEMPI (lista costruita a mano)
   ======================= */
int main(void) {
    /*
      Esempi scelti per coprire i casi:
      - "casa"  (len=4 pari, no vocali uguali consecutive) => XOR true  => ELIMINA
      - "coooperare" (ha "oo" consecutive, len pari)      => XOR false => TIENI
      - "te"    (len=2 pari, no doppie vocali)            => XOR true  => ELIMINA
      - "booo"  (len=4 pari, ha "oo" consecutive)         => XOR false => TIENI
      - "idee"  (len=4 pari, ha "ee" consecutive)         => XOR false => TIENI
      - "radio" (len=5 dispari, no doppie vocali)         => XOR false => TIENI
      - "aab"   (len=3 dispari, ha "aa" consecutive)      => XOR true  => ELIMINA
    */

    Lista L =
        newNode("casa",
        newNode("coooperare",
        newNode("te",
        newNode("booo",
        newNode("idee",
        newNode("radio",
        newNode("aab", NULL)))))));

    printf("Lista iniziale:\n");
    printList(L);

    L=removeIfPropertyP(L);
    printf("\nLista finale:\n");
    printList(L);

    freeList(L);
}
int Prop(char parola[])
{   int pari=0;
        if(strlen(parola)%2==0)
            pari=1;
    int count_vocali=0;
    int i=0;
    int vocali=0;
    while(parola[i]!='\0')
        {
            if(parola[i]=='a' || parola[i]=='e' || parola[i]=='i' || parola[i]=='o' || parola[i]=='u')
                {
                    if(parola[i+1]==parola[i])
                        return 1;
                    return 0;
                }
            i++;
        }
    if(count_vocali>=2)
        vocali=1;
    if(vocali&&pari)
        return 0;
    if(vocali|| pari)
        return 1;
    return 0;
    }
Lista removeIfPropertyP(Lista l)
    {
        if(l==NULL)
            return NULL;
        if(Prop(l->word))
            {
                Lista temp=l->next;
                free(l->word);;
                free(l);
                return temp;
            }
        l->next=removeIfPropertyP(l->next);
        return l;
    }
