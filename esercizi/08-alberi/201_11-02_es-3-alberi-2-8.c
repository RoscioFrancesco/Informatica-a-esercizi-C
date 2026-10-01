//
//  main.c
//  es 3 alberi 2 -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TN {
    char c;
    struct TN *left, *right;
} tn;
typedef tn* tree;

typedef struct LN {
    char c;
    struct LN *next;
} ln;
typedef ln* lista;

int matchStrambo(tree T, lista L);

/* =========================
   UTILITY: TREE
   ========================= */
static tree newNode(char c) {
    tree n = (tree)malloc(sizeof(tn));
    if (!n) { perror("malloc"); exit(1); }
    n->c = c;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void printTreePre(tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%c ", t->c);
    printTreePre(t->left);
    printTreePre(t->right);
}

/* =========================
   UTILITY: LISTA
   ========================= */
static lista pushBack(lista head, char c) {
    lista n = (lista)malloc(sizeof(ln));
    if (!n) { perror("malloc"); exit(1); }
    n->c = c;
    n->next = NULL;

    if (!head) return n;
    lista cur = head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return head;
}

static lista buildListFromString(const char *s) {
    lista head = NULL;
    for (int i = 0; s[i] != '\0'; i++) {
        head = pushBack(head, s[i]);
    }
    return head;
}

static void freeList(lista l) {
    while (l) {
        lista nxt = l->next;
        free(l);
        l = nxt;
    }
}

static void printList(lista l) {
    printf("[");
    while (l) {
        printf("%c", l->c);
        if (l->next) printf("->");
        l = l->next;
    }
    printf("]");
}

/* =========================
   MAIN DI TEST (con printf)
   ========================= */
int f(tree albero, lista head, int stato);
int èvocale(char lettera);
int main(void) {
    /* Costruiamo un albero di esempio:
               'b'
              /   \
            'a'   'c'
           /  \     \
         'd'  'e'   'o'
    */
    tree T = newNode('b');
    T->left = newNode('a');
    T->right = newNode('c');
    T->left->left = newNode('d');
    T->left->right = newNode('e');
    T->right->right = newNode('o');

    /* Lista di esempio (da “consumare” sulle vocali) */
    lista L1 = buildListFromString("xe");   /* due caratteri */
    lista L2 = buildListFromString("x");    /* uno */
    lista L3 = buildListFromString("");     /* vuota */

    printf("=== STRUTTURE INPUT ===\n");
    printf("Albero (preorder): ");
    printTreePre(T);
    printf("\n");

    printf("Lista L1 = "); printList(L1); printf("\n");
    printf("Lista L2 = "); printList(L2); printf("\n");
    printf("Lista L3 = "); printList(L3); printf("\n");

    printf("\n=== CHIAMATE matchStrambo(T, L) ===\n");
    printf("matchStrambo(T, L1) = %d\n", matchStrambo(T, L1));
    printf("matchStrambo(T, L2) = %d\n", matchStrambo(T, L2));
    printf("matchStrambo(T, L3) = %d\n", matchStrambo(T, L3));

    /* Pulizia memoria */
    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeTree(T);

    return 0;
}


int f(tree albero, lista head, int stato) // se consumo metto stato 1
    {
        if(albero==NULL && head==NULL)
            return 1;
        if(albero==NULL)
            return 0;
        if(èvocale(albero->c) && stato==1)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return (head==NULL);
        if(èvocale(albero->c) && stato==0)
            {
                head=head->next;
                stato=1;
            }
        if(!èvocale(albero->c))
            stato=0;
        int sx=0;
        int dx=0;
        if(albero->left!=NULL)
            sx=f(albero->left, head, stato);
        if(albero->right!=NULL)
            dx=f(albero->right, head, stato);
        return sx||dx;
    }
int matchStrambo(tree T, lista L)
    {
        if(T==NULL && L==NULL)
            return 1;
        if(T==NULL || L==NULL)
            return 0;
        return f(T, L, 0);
    }
int èvocale(char lettera)
    {
    if(lettera=='a' || lettera=='e' || lettera=='i' || lettera=='o' || lettera=='u')
        {
            return 1;
        }
    return 0;
    }
