//
//  main.c
//  tde 5 es 2 -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ================= STRUTTURE ================= */

typedef struct node_s {
    char v;
    struct node_s *left, *right;
} node_t;

typedef node_t* tree;

typedef struct Is{
    char v;
    struct Is *next;
}Vagone;
typedef Vagone * Lista;


int contaPercorsiPalindromi(tree T);

/* ================= FUNZIONI DI SUPPORTO ================= */

tree creaNodo(char c) {
    tree n = (tree)malloc(sizeof(node_t));
    n->v = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* stampa i percorsi root->leaf (debug) */
void stampaPercorsiRec(tree T, char path[], int depth) {
    if (T == NULL) return;

    path[depth] = T->v;

    if (T->left == NULL && T->right == NULL) {
        /* foglia: stampa la stringa del percorso */
        for (int i = 0; i <= depth; i++) printf("%c", path[i]);
        printf("\n");
        return;
    }

    stampaPercorsiRec(T->left, path, depth + 1);
    stampaPercorsiRec(T->right, path, depth + 1);
}

void stampaPercorsi(tree T) {
    char path[256];
    printf("Percorsi radice->foglia:\n");
    stampaPercorsiRec(T, path, 0);
}

/* =========================== MAIN =========================== */
Lista last(Lista head);
int main(void) {

    /* ===== TEST 1 =====
       Albero:
           a
          / \
         b   b
        /     \
       a       a

       Percorsi:
       a b a  -> "aba" palindromo
       a b a  -> "aba" palindromo
       Atteso: 2
    */
    tree T1 = creaNodo('a');
    T1->left = creaNodo('b');
    T1->right = creaNodo('b');
    T1->left->left = creaNodo('a');
    T1->right->right = creaNodo('a');

    printf("=== TEST 1 ===\n");
    stampaPercorsi(T1);
    printf("Numero percorsi palindromi: %d\n\n", contaPercorsiPalindromi(T1));


    /* ===== TEST 2 =====
       Albero:
           a
          / \
         b   c
        / \   \
       b   a   a

       Percorsi:
       a b b -> "abb" non palindromo
       a b a -> "aba" palindromo
       a c a -> "aca" palindromo
       Atteso: 2
    */
    tree T2 = creaNodo('a');
    T2->left = creaNodo('b');
    T2->right = creaNodo('c');
    T2->left->left = creaNodo('b');
    T2->left->right = creaNodo('a');
    T2->right->right = creaNodo('a');

    printf("=== TEST 2 ===\n");
    stampaPercorsi(T2);
    printf("Numero percorsi palindromi: %d\n\n", contaPercorsiPalindromi(T2));


    /* ===== TEST 3 =====
       Albero:
           x
          /
         y
        /
       z

       Percorso unico: "xyz" non palindromo
       Atteso: 0
    */
    tree T3 = creaNodo('x');
    T3->left = creaNodo('y');
    T3->left->left = creaNodo('z');

    printf("=== TEST 3 ===\n");
    stampaPercorsi(T3);
    printf("Numero percorsi palindromi: %d\n\n", contaPercorsiPalindromi(T3));


    /* ===== TEST 4 =====
       Albero con un solo nodo:
           q

       Percorso: "q" palindromo
       Atteso: 1
    */
    tree T4 = creaNodo('q');

    printf("=== TEST 4 ===\n");
    stampaPercorsi(T4);
    printf("Numero percorsi palindromi: %d\n\n", contaPercorsiPalindromi(T4));

    return 0;
}
void distruggilista(Lista head)
    {
    if(head==NULL)
        return;
    Lista temp=head->next;
    free(head);
    distruggilista(temp);
    }
Lista invertilista(Lista head)
    {
        if(head==NULL || head->next==NULL)
            {
                return head;
            }
    Lista temp=invertilista(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
    }
int compare(Lista l1, Lista l2)
    {
        while(l1!=NULL && l2!=NULL)
            {
                if(l1->v!=l2->v)
                    return 0;
                l1=l1->next;
                l2=l2->next;
            }
    return (l1==l2);
    }
Lista copia(Lista l1)
    {
        if(l1==NULL)
            {
                return NULL;
            }
    Lista new=(Lista)malloc(sizeof(*new));
    new->v=l1->v;
    new->next=copia(l1->next);
    return new;
    }
int palindroma(Lista l1)
    {
        if(l1==NULL || l1->next==NULL)
            return 1;
    Lista girata=copia(l1);
    girata=invertilista(girata);
    int ris=compare(girata, l1);
    distruggilista(girata);
    return ris;
    }
Lista inseriscincoda(Lista head, char x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->v=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
void f(tree albero, Lista head, int *count)
    {
        if(albero==NULL)
            return;
        head=inseriscincoda(head, albero->v);
        f(albero->left, head, count);
        f(albero->right, head, count);
        if(albero->left==NULL && albero->right==NULL && palindroma(head))
        {
            (*count)++;
            
        }
    if(head==NULL)
        return;
    else if (head->next==NULL)
        {
            free(head);
        }
    else
    {
        Lista ultimo=last(head);
        Lista scorri=head;
        while (scorri->next!=ultimo) {
            scorri=scorri->next;
        }
        scorri->next=NULL;
        if(ultimo!=NULL)
            free(ultimo);
    }
    
    }
Lista last(Lista head)
    {
        while(head!=NULL && head->next!=NULL)
            {
                head=head->next;
            }
    return head;
    }

int contaPercorsiPalindromi(tree T)
    {
    Lista head=NULL;
    int count=0;
    f(T, head, &count);
    return count;
    }
