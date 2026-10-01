//
//  main.c
//  ricorsione 1
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURA LISTA
   ========================= */

typedef struct Node {
    char *word;            // stringa dinamica
    struct Node *next;
} Node;

typedef Node* Lista;

/* =========================
   PROTOTIPI (DA SVOLGERE)
   ========================= */


int palindromaPerLunghezza(Lista head);

/* =========================
   UTILITY (QUI I CICLI SONO OK)
   ========================= */

static char *dupstr(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static Lista push_back(Lista l, const char *s) {
    if (l == NULL) {
        Lista n = malloc(sizeof(Node));
        n->word = dupstr(s);
        n->next = NULL;
        return n;
    }
    l->next = push_back(l->next, s);
    return l;
}

static void printLista(Lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("\"%s\" ", l->word);
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    if (l == NULL) return;
    freeLista(l->next);
    free(l->word);
    free(l);
}

/* =========================
   MAIN DI TEST
   ========================= */

int main(void) {

    Lista l1 = NULL;
    l1 = push_back(l1, "ciao");        // 4
    l1 = push_back(l1, "ab");          // 2
    l1 = push_back(l1, "xy");          // 2
    l1 = push_back(l1, "test");        // 4

    Lista l2 = NULL;
    l2 = push_back(l2, "uno");         // 3
    l2 = push_back(l2, "due");         // 3
    l2 = push_back(l2, "tre");         // 3

    printf("Lista 1: ");
    printLista(l1);
    printf("Palindroma per lunghezza? %d\n\n",
           palindromaPerLunghezza(l1));

    printf("Lista 2: ");
    printLista(l2);
    printf("Palindroma per lunghezza? %d\n",
           palindromaPerLunghezza(l2));

    freeLista(l1);
    freeLista(l2);

    return 0;
}
int f(Lista head, Lista *scorri)
    {
        if(head==NULL)
            return 1;
        int ok=f(head->next, scorri);
        if(ok==0)
            return 0;
        if(strlen(head->word)!=strlen((*scorri)->word))
                return 0;
        (*scorri)=(*scorri)->next;
    return 1;
    }

int palindromaPerLunghezza(Lista head)
    {
    Lista scorri=head;
    return f(head, &scorri);
    }
//int aux(Lista curr, Lista *front)
//{
//    /* 1. CASO BASE */
//    if (curr == NULL)
//        return VALORE_BASE;
//
//    /* 2. DISCESA */
//    int ok = aux(curr->next, front);
//    if (!ok)
//        return FALLIMENTO;
//
//    /* 3. LOGICA IN RISALITA */
//    // confronto / decisione / eliminazione / accumulo
//
//    /* 4. AVANZA FRONT */
//    *front = (*front)->next;
//
//    /* 5. RITORNO */
//    return SUCCESSO;
//}
