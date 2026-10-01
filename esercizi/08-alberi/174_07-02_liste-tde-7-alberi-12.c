//
//  main.c
//  liste tde 7 alberi -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct ET {
    char *dato;
    struct ET *left;
    struct ET *right;
} treeNode;
typedef treeNode *tree;

typedef struct EL {
    char *dato;
    struct EL *next;
} listNode;
typedef listNode *list;

/* =========================
   PROTOTIPI (le funzioni le hai già sotto)
   ========================= */
int contains(tree t, char *word);
int wrapper(tree albero, list head);

/* =========================
   UTILITY: DUPLICA STRINGA (UNA SOLA VOLTA!)
   ========================= */
static char *dupstr(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

/* =========================
   UTILITY: CREA NODO ALBERO
   ========================= */
static tree newNode(const char *s) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = dupstr(s);
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   UTILITY: INSERIMENTO IN BST (ALFABETICO)
   ========================= */
static tree insertBST(tree t, const char *s) {
    if (t == NULL) return newNode(s);

    int cmp = strcmp(s, t->dato);
    if (cmp < 0) t->left = insertBST(t->left, s);
    else if (cmp > 0) t->right = insertBST(t->right, s);
    return t;
}

/* =========================
   UTILITY: STAMPA INORDER
   ========================= */
static void printInorder(tree t) {
    if (!t) return;
    printInorder(t->left);
    printf("%s ", t->dato);
    printInorder(t->right);
}

/* =========================
   UTILITY: FREE ALBERO
   ========================= */
static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t->dato);
    free(t);
}

/* =========================
   LISTA: inserimento ordinato (serve per creare L)
   ========================= */
static list inserisciOrdinato(list head, const char *parola) {
    if (head == NULL || strcmp(parola, head->dato) < 0) {
        list new = (list)malloc(sizeof(listNode));
        if (!new) { perror("malloc"); exit(1); }
        new->dato = dupstr(parola);
        new->next = head;
        return new;
    }
    head->next = inserisciOrdinato(head->next, parola);
    return head;
}

static void stampaLista(list l) {
    printf("[ ");
    while (l != NULL) {
        printf("%s ", l->dato);
        l = l->next;
    }
    printf("]\n");
}

static void freeList(list l) {
    while (l) {
        list tmp = l->next;
        free(l->dato);
        free(l);
        l = tmp;
    }
}

/* =========================
   MAIN DI TEST (SISTEMATO)
   ========================= */
int main(void) {
    tree t = NULL;

    /* Costruisco un albero BST alfabetico di parole (test) */
    const char *parole[] = { "cane", "gatto", "albero", "zebra", "mare", "casa", "sole" };
    int n = (int)(sizeof(parole) / sizeof(parole[0]));
    for (int i = 0; i < n; i++) {
        t = insertBST(t, parole[i]);
    }

    printf("Albero (inorder, alfabetico): ");
    printInorder(t);
    printf("\n\n");

    /* Test contains */
    const char *tests[] = { "gatto", "banana", "sole", "ALBERO", "cane" };
    int m = (int)(sizeof(tests) / sizeof(tests[0]));
    for (int i = 0; i < m; i++) {
        int ok = contains(t, (char*)tests[i]);
        printf("contains(t, \"%s\") = %d\n", tests[i], ok);
    }

    printf("\n");

    /* Costruisco lista ordinata */
    list L = NULL;
    L = inserisciOrdinato(L, "albero");
    L = inserisciOrdinato(L, "cane");
    L = inserisciOrdinato(L, "mare");
    L = inserisciOrdinato(L, "sole");
    L = inserisciOrdinato(L, "zaino");
    L = inserisciOrdinato(L, "gatto");

    printf("Lista (ordinata): ");
    stampaLista(L);

    /* Test wrapper */
    int ris = wrapper(t, L);
    printf("wrapper(t, L) = %d\n", ris);

    /* Free memoria */
    freeList(L);
    freeTree(t);

    return 0;
}

/* =========================================================
   DA QUI IN POI: LE TUE FUNZIONI (NON TOCCATE)
   ========================================================= */

int contains (tree t, char * word)
{
    if(t==NULL)
        return 0;
    if(strcmp(t->dato, word)==0)
    {
        return 1;
    }
    return contains(t->right, word)|| contains(t->left, word);
}

int èinlista(list head, char parola[])
{
    if(head==NULL)
        return 0;
    if(strcmp(head->dato, parola)==0)
        return 1;
    return èinlista(head->next, parola);
}

int profondita(tree albero);

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}

int profondita(tree albero)
{
    if(albero==NULL)
        return 0;
    int sx=profondita(albero->left);
    int dx=profondita(albero->right);
    return 1+max(sx, dx);
}

void f(tree albero, int v[], list head, int profondità)
{
    if(albero==NULL)
        return;
    if(èinlista(head, albero->dato))
    {
        (v[profondità])++;
    }
    f(albero->left, v, head, profondità+1);
    f(albero->right, v, head, profondità+1);
}

int wrapper(tree albero, list head)
{
    if(albero==NULL)
        return 1;
    int len=profondita(albero);
    int *vett=malloc(sizeof(int)*(len));
    for(int i=0; i<len; i++)
        vett[i]=0;
    f(albero, vett, head, 0);
    for(int j=0; j<len; j++)
        if(vett[j]==0)
            return 0;
    return 1;
}
