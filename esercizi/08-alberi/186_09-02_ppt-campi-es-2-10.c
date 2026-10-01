//
//  main.c
//  ppt campi es 2-10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come nel testo)
   ========================= */
typedef struct ET {
    char *dato;
    struct ET *left;
    struct ET *right;
} treeNode;

typedef treeNode * tree;

typedef struct EL {
    char *dato;
    struct EL *next;
} listNode;

typedef listNode * list;

/* =========================
   PROTOTIPI DA ESERCIZIO
   ========================= */
int contains(tree t, char *word);
int isContained(tree t, list l);

/* =========================
   STUB: NON RISOLVO
   ========================= */
int contains(tree t, char *word) {
    (void)t; (void)word;
    /* TODO */
    return 0;
}

int isContained(tree t, list l) {
    (void)t; (void)l;
    /* TODO */
    return 0;
}

/* =========================
   FUNZIONI DI SUPPORTO (TEST)
   ========================= */
static tree nuovoNodo(char *s) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = s;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static list nuovoElemento(char *s) {
    list n = (list)malloc(sizeof(listNode));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = s;
    n->next = NULL;
    return n;
}

/* inserimento in coda (lista ordinata già dal chiamante) */
static void appendList(list *l, char *s) {
    list n = nuovoElemento(s);
    if (*l == NULL) {
        *l = n;
        return;
    }
    list cur = *l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

static void stampaLista(list l) {
    printf("[ ");
    while (l != NULL) {
        printf("%s ", l->dato);
        l = l->next;
    }
    printf("]\n");
}

static void stampaAlberoPre(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%s ", t->dato);
    stampaAlberoPre(t->left);
    stampaAlberoPre(t->right);
}

/* =========================
   MAIN DI TEST + PRINTF
   ========================= */
int f(tree albero, list head);
int verificalivello(tree albero, int livelo_cur, int livellotarget, list head);
int depth(tree albero);

int main(void) {
    /* Costruzione albero di parole */
    tree t = nuovoNodo("mela");
    t->left = nuovoNodo("banana");
    t->right = nuovoNodo("pera");
    t->left->left = nuovoNodo("ananas");
    t->left->right = nuovoNodo("kiwi");
    t->right->right = nuovoNodo("uva");

    /* Costruzione lista ordinata alfabeticamente */
    list l = NULL;
    appendList(&l, "ananas");
    appendList(&l, "banana");
    appendList(&l, "kiwi");
    appendList(&l, "mela");

    printf("Albero (preorder): ");
    stampaAlberoPre(t);
    printf("\n");

    printf("Lista: ");
    stampaLista(l);

    
    printf("\ncontains(t, \"pera\") = %d\n", contains(t, "pera"));
    printf("isContained(t, l) = %d\n", f(t, l));

    return 0;
}
int trova(char parola[], list head)
    {
        if(head==NULL)
            return 0;
    list scorri=head;
    while (scorri!=NULL) {
        if(strcmp(scorri->dato, parola)==0)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=depth(albero->left);
    int dx=depth(albero->right);
    return 1+max(sx, dx);
    }
int verificalivello(tree albero, int livelo_cur, int livellotarget, list head)
    {
        if(albero==NULL)
            return 0;
        if(livelo_cur==livellotarget)
            {
                if(trova(albero->dato, head)==1)
                    return 1;
            }
    return verificalivello(albero->left, livelo_cur+1, livellotarget, head) || verificalivello(albero->right, livelo_cur+1, livellotarget, head);
    }
int f(tree albero, list head)
    {
        if(albero==NULL || head==NULL)
            return 0;
    int profondità=depth(albero);
    for(int i=0; i<profondità; i++)
        {
            if(verificalivello(albero, 0, i, head)==0)
                return 0;
        }
    return 1;
    }
