//
//  main.c
//  tde 3 es 2 -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come testo)
   ========================= */
typedef struct nodoCompresso {
    char lettera;
    int quanti;
    struct nodoCompresso *next;
} NodoCompresso;

typedef NodoCompresso *ListaCompressa;

typedef struct ET {
    char parola[1000];
    struct ET *left, *right;
} treeNode;

typedef treeNode *Tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
ListaCompressa comprimiTantissimo(Tree T);   // TODO: NON implementare qui

/* =========================
   UTILITY PER TEST
   ========================= */
static Tree newNodeTree(const char *w) {
    Tree n = (Tree)malloc(sizeof(treeNode));
    if(!n) { perror("malloc"); exit(1); }
    strncpy(n->parola, w, sizeof(n->parola) - 1);
    n->parola[sizeof(n->parola) - 1] = '\0';
    n->left = n->right = NULL;
    return n;
}

static void freeTree(Tree T) {
    if(!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

static void printTreePre(Tree T) {
    if(!T) return;
    printf("%s ", T->parola);
    printTreePre(T->left);
    printTreePre(T->right);
}

static void printListaCompressa(ListaCompressa L) {
    printf("(");
    while(L) {
        printf("(%c, %d)", L->lettera, L->quanti);
        if(L->next) printf(", ");
        L = L->next;
    }
    printf(")\n");
}

static void freeListaCompressa(ListaCompressa L) {
    while(L) {
        NodoCompresso *tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN
   ========================= */
ListaCompressa inseriscincoda(ListaCompressa head, char lettera, int num);
void popolavett(Tree t, int vett[]);
int main(void) {
    /* Costruisco un albero che contiene: "albero", "mamma", "casa"
       (la forma dell'albero non è importante per l'output finale,
        perché devi contare tutte le lettere in tutto l'albero). */

    Tree T = newNodeTree("albero");
    T->left = newNodeTree("mamma");
    T->right = newNodeTree("casa");

    printf("Parole nell'albero (preorder): ");
    printTreePre(T);
    printf("\n");

    ListaCompressa R = comprimiTantissimo(T);

    printf("Lista compressa tantissimo ordinata: ");
    printListaCompressa(R);

    freeTree(T);
    freeListaCompressa(R);
    return 0;
}


ListaCompressa comprimiTantissimo(Tree T) {
    int *vett=malloc(sizeof(int)*26);
    for(int i=0; i<26; i++)
        {
            vett[i]=0;
        }
    popolavett(T, vett);
    ListaCompressa new=NULL;
    char lettera='a';
    for(int i=0; i<26; i++)
        {
            if(vett[i]>0)
            {
                new=inseriscincoda(new, lettera, vett[i]);
            }
            lettera++;
        }
    return new;
}
void f(int vett[], char parola[])
{
    int i=0;
    while (parola[i]!='\0') {
        vett[parola[i]-'a']++;
        i++;
    }
    return;
    }
void popolavett(Tree t, int vett[])
    {
        if(t==NULL)
            return;
        f(vett, t->parola);
    popolavett(t->left, vett);
    popolavett(t->right, vett);
    }
ListaCompressa inseriscincoda(ListaCompressa head, char lettera, int num)
    {
        if(head==NULL)
            {
                ListaCompressa new=(ListaCompressa)malloc(sizeof(*new));
                new->next=NULL;
                new->lettera=lettera;
                new->quanti=num;
                return new;
            }
        head->next=inseriscincoda(head->next, lettera, num);
        return head;
    }
