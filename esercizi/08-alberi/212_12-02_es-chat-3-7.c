//
//  main.c
//  es chat 3 -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ====== TIPI (dal testo) ====== */
typedef struct node {
    char c;
    struct node *left, *right;
} *tree;

typedef struct nd {
    char *w;
    struct nd *next;
} *Lista;


int matchProibito(tree T, char *s, Lista proibite);

/* ====== UTILS ALBERO ====== */
static tree newNode(char c, tree L, tree R) {
    tree t = (tree)malloc(sizeof(*t));
    if (t == NULL) { perror("malloc"); exit(1); }
    t->c = c;
    t->left = L;
    t->right = R;
    return t;
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void printPreorder(tree t) {
    if (t == NULL) { printf("NULL "); return; }
    printf("%c ", t->c);
    printPreorder(t->left);
    printPreorder(t->right);
}

/* ====== UTILS LISTA PROIBITE ====== */
static Lista consWord(const char *w, Lista next) {
    Lista n = (Lista)malloc(sizeof(*n));
    if (n == NULL) { perror("malloc"); exit(1); }
    n->w = (char*)malloc(strlen(w) + 1);
    if (n->w == NULL) { perror("malloc"); exit(1); }
    strcpy(n->w, w);
    n->next = next;
    return n;
}

static void freeLista(Lista L) {
    while (L != NULL) {
        Lista succ = L->next;
        free(L->w);
        free(L);
        L = succ;
    }
}

static void printLista(Lista L) {
    printf("[");
    while (L != NULL) {
        printf("%s", L->w);
        if (L->next != NULL) printf(", ");
        L = L->next;
    }
    printf("]");
}

/* ====== ESEMPIO ALBERO PER TEST ======
        a
       / \
      b   e
     / \   \
    c   d   f
   /         \
  g           i

(Le vocali ti fanno scendere senza consumare caratteri)
*/
static tree buildExampleTree(void) {
    tree g = newNode('g', NULL, NULL);
    tree c = newNode('c', g, NULL);

    tree d = newNode('d', NULL, NULL);
    tree b = newNode('b', c, d);

    tree i = newNode('i', NULL, NULL);
    tree f = newNode('f', NULL, i);
    tree e = newNode('e', NULL, f);

    tree a = newNode('a', b, e);
    return a;
}

/* ====== MAIN ====== */
int verificaproibite(char parola[], Lista head);
int wrapper(tree t, char s[], Lista proibite);
int main(void) {
    tree T = buildExampleTree();

    /* lista di parole proibite (stringhe di 3 consonanti) */
    Lista proibite = NULL;
    proibite = consWord("bcd", proibite);
    proibite = consWord("cdf", proibite);
    proibite = consWord("gdf", proibite);

    char s1[] = "bdf";
    char s2[] = "cdg";
    char s3[] = "bbb";

    printf("Albero (preorder con NULL): ");
    printPreorder(T);
    printf("\n");

    printf("Proibite: ");
    printLista(proibite);
    printf("\n\n");

    printf("Test s=\"%s\" -> matchProibito = %d\n", s1, matchProibito(T, s1, proibite));
    printf("Test s=\"%s\" -> matchProibito = %d\n", s2, matchProibito(T, s2, proibite));
    printf("Test s=\"%s\" -> matchProibito = %d\n", s3, matchProibito(T, s3, proibite));

    freeLista(proibite);
    freeTree(T);
    return 0;
}
int èvocale(char lettera)
    {
        if(lettera=='a' || lettera=='e' || lettera=='i' || lettera=='o' || lettera=='u')
            return 1;
    return 0;
    }
int f(tree albero, char s[], char parola[], int salticonsecutivi, Lista proibite, int scorri)
    {
        if(albero==NULL)
            return 0;
        if(!èvocale(albero->c))
        {
            if(albero->c!=s[scorri])
                return 0;
            scorri++;
        }
    char parola2[4];
    parola2[0]=parola[0];
    parola2[1]=parola[1];
    parola2[2]=parola[2];
    parola2[3]=parola[3];
        if(s[scorri]=='\0' && albero->left==NULL && albero->right==NULL)
            return 1;
        parola2[2]=parola2[1];
        parola2[1]=parola2[0];
        parola2[0]=albero->c;
        parola2[3]='\0';
        if(verificaproibite(parola2, proibite))
            return 0;
        if(f(albero->left, s, parola, 0, proibite, scorri))
            return 1;
        if(f(albero->right, s, parola, 0, proibite, scorri))
            return 1;
        if(salticonsecutivi!=1)
            {
                if(albero->left!=NULL)
                    {
                        int newsalticonsecutivi=1;
                        return f(albero->left->left, s, parola, newsalticonsecutivi, proibite, scorri)|| f(albero->left->right, s, parola, newsalticonsecutivi, proibite, scorri);
                    }
                if(albero->right!=NULL)
                    {
                        int newsalticonsecutivi=1;
                        return f(albero->right->left, s, parola, newsalticonsecutivi, proibite, scorri)|| f(albero->right->right, s, parola, newsalticonsecutivi, proibite, scorri);
                    }
            }
    return 0;
    }

int verificaproibite(char parola[], Lista head)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(strcmp(parola, head->w)==0)
            return 1;
        head=head->next;
        }
    return 0;
    }
int matchProibito(tree T, char *s, Lista proibite)
    {
    if(T==NULL)
        return 0;
    if(wrapper(T, s, proibite))
        return 1;
    return matchProibito(T->left, s, proibite)|| matchProibito(T->right, s, proibite);
    }
int wrapper(tree t, char s[], Lista proibite)
    {
    char buf[4] = {'_', '_','_', '\0'};
    return f(t, s, buf, 0, proibite, 0);
    }
