//
//  main.c
//  tde 4 liste -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

/* =====================
   STRUTTURE DATI (da testo)
   ===================== */
typedef struct EL {
    char cognome[N], nome[N];
    struct EL *left, *right;
} node;

typedef node *tree;

/* Lista risultato */
typedef struct NL {
    char cognome[N], nome[N];
    struct NL *next;
} nodoLista;

typedef nodoLista *ListaPersone;


ListaPersone verificaEOOrdina(tree t);

/* =====================
   UTILITY PER TEST
   ===================== */
static tree nuovoNodo(const char *cognome, const char *nome) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    strncpy(n->cognome, cognome, N-1); n->cognome[N-1] = '\0';
    strncpy(n->nome, nome, N-1); n->nome[N-1] = '\0';
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaAlberoPreorder(tree t) {
    if (t == NULL) return;
    printf("%s %s\n", t->nome, t->cognome);
    stampaAlberoPreorder(t->left);
    stampaAlberoPreorder(t->right);
}

static void stampaLista(ListaPersone l) {
    while (l != NULL) {
        printf("%s %s -> ", l->nome, l->cognome);
        l = l->next;
    }
    printf("NULL\n");
}

static void liberaAlbero(tree t) {
    if (t == NULL) return;
    liberaAlbero(t->left);
    liberaAlbero(t->right);
    free(t);
}

static void liberaLista(ListaPersone l) {
    while (l != NULL) {
        ListaPersone tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =====================
   MAIN DI TEST
   ===================== */
int omonimi(tree albero, tree root);
int trovainalbero(tree nodomio, tree albero);
ListaPersone inserimentoordinato(ListaPersone head, char nome[], char cognome[]);
void riempilista(ListaPersone *head, tree albero);
int main() {
    /*
        Albero di esempio (senza omonimi)

               Rossi Mario
              /           \
        Bianchi Luca     Verdi Anna
            /
       Neri Paolo
    */
    tree t = nuovoNodo("Rossi", "Mario");
    t->left = nuovoNodo("Bianchi", "Luca");
    t->right = nuovoNodo("Verdi", "Anna");
    t->left->left = nuovoNodo("Neri", "Paolo");

    printf("=== Albero (preorder) ===\n");
    stampaAlberoPreorder(t);

    ListaPersone risultato = verificaEOOrdina(t);

    printf("\n=== Lista risultato ===\n");
    if (risultato == NULL)
        printf("NULL (albero contiene omonimi)\n");
    else
        stampaLista(risultato);

    liberaLista(risultato);
    liberaAlbero(t);

    /*
        Secondo albero (con omonimi)

             Rossi Mario
                \
              Rossi Mario   <-- omonimo
    */
    tree t2 = nuovoNodo("Rossi", "Mario");
    t2->right = nuovoNodo("Rossi", "Mario");

    printf("\n=== Albero 2 (preorder) ===\n");
    stampaAlberoPreorder(t2);

    risultato = verificaEOOrdina(t2);

    printf("\n=== Lista risultato ===\n");
    if (risultato == NULL)
        printf("NULL (albero contiene omonimi)\n");
    else
        stampaLista(risultato);

    liberaLista(risultato);
    liberaAlbero(t2);

    return 0;
}

int trovainalbero(tree nodomio, tree albero)
    {
        if(albero==NULL)
            return 0;
        if(strcmp(nodomio->nome, albero->nome)==0 && strcmp(nodomio->cognome, albero->cognome)==0 && nodomio!=albero)
            return 1;
    return trovainalbero(nodomio, albero->left) || trovainalbero(nodomio, albero->right);
    }
int omonimi(tree albero, tree root)
    {
        if(albero==NULL)
            return 0;
    int ris=trovainalbero(albero, root);
    return  ris|| omonimi(albero->left, root) || omonimi(albero->right, root);
    }
ListaPersone inserimentoordinato(ListaPersone head, char nome[], char cognome[])
    {
        if(head==NULL || strcmp(cognome,head->cognome)<0 || (strcmp(cognome,head->cognome)==0 && strcmp(nome,head->nome)))
            {
                ListaPersone new=(ListaPersone)malloc(sizeof(*new));
                new->next=head;
                strcpy(new->cognome, cognome);
                strcpy(new->nome, nome);
                return new;
            }
    head->next=inserimentoordinato(head->next, nome, cognome);
    return head;
    }

void riempilista(ListaPersone *head, tree albero)
    {
        if(albero==NULL)
            return;
        *head=inserimentoordinato(*head, albero->nome, albero->cognome);
    riempilista(head, albero->left);
    riempilista(head, albero->right);
    }
ListaPersone verificaEOOrdina(tree t)
    {
        if(omonimi(t, t)==1)
            return NULL;
        ListaPersone head=NULL;
        riempilista(&head, t);
        return head;
    }
