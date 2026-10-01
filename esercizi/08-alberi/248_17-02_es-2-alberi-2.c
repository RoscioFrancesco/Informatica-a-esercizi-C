//
//  main.c
//  es 2 alberi  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE
   ========================= */

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} Node;

typedef Node* Tree;


int contaSpecchioLocali(Tree T);

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

Tree newNode(int v) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->val = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(Tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* Stampa inorder dei valori */
void printInorderValues(Tree T) {
    if (T == NULL) return;
    printInorderValues(T->left);
    printf("%d ", T->val);
    printInorderValues(T->right);
}

/* Stampa inorder come E/O (pari/dispari) */
void printInorderEO(Tree T) {
    if (T == NULL) return;
    printInorderEO(T->left);
    printf("%c ", (T->val % 2 == 0) ? 'E' : 'O');
    printInorderEO(T->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int palindroma(char parola[], int len);
int riempi(char parola[], Tree t, int num_nodi, int *count, int *segna);
int contanodi(Tree t);
void f(Tree t, int *count);

int main(void) {

    /* -------- TEST 1: nodo singolo --------
           5
       Sottoalbero(5): "O" => palindroma
       Atteso: 1
    */
    Tree T1 = newNode(5);

    printf("=== TEST 1 ===\n");
    printf("Inorder valori: ");
    printInorderValues(T1);
    printf("\nInorder E/O:    ");
    printInorderEO(T1);
    printf("\n");
    printf("contaSpecchioLocali(T1) = %d\n", contaSpecchioLocali(T1));
    printf("ATTESO = 1\n\n");



    /* -------- TEST 2: albero a 3 nodi --------
            2
           / \
          1   3

       Sottoalbero(1): "O"   pal
       Sottoalbero(3): "O"   pal
       Sottoalbero(2): "O E O" => "OEO" pal
       Atteso: 3
    */
    Tree T2 = newNode(2);
    T2->left = newNode(1);
    T2->right = newNode(3);

    printf("=== TEST 2 ===\n");
    printf("Inorder valori: ");
    printInorderValues(T2);
    printf("\nInorder E/O:    ");
    printInorderEO(T2);
    printf("\n");
    printf("contaSpecchioLocali(T2) = %d\n", contaSpecchioLocali(T2));
    printf("ATTESO = 3\n\n");



    /* -------- TEST 3: albero più grande --------
                 4
               /   \
              2     6
             / \   / \
            1   3 5   8

       Nodi palindromi attesi:
       - tutte le foglie: 1(O),3(O),5(O),8(E) => 4
       - nodo 2: inorder "O E O" => pal => +1
       - nodo 6: inorder "O E E" => NO
       - nodo 4: inorder "O E O E O E E" => NO
       Atteso: 5
    */
    Tree T3 = newNode(4);
    T3->left = newNode(2);
    T3->right = newNode(6);

    T3->left->left = newNode(1);
    T3->left->right = newNode(3);

    T3->right->left = newNode(5);
    T3->right->right = newNode(8);

    printf("=== TEST 3 ===\n");
    printf("Inorder valori: ");
    printInorderValues(T3);
    printf("\nInorder E/O:    ");
    printInorderEO(T3);
    printf("\n");
    printf("contaSpecchioLocali(T3) = %d\n", contaSpecchioLocali(T3));
    printf("ATTESO = 5\n\n");



    /* cleanup */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);

    return 0;
    

}


int palindroma(char parola[], int len) // len è il numero di caratteri
    {
    int i=0;
    int j=len-1;
    while(i<j)
        {
            if(parola[i]!=parola[j])
                return 0;
            i++;
            j--;
        }
    return 1;
    }

int riempi(char parola[], Tree t, int num_nodi, int *count, int *segna)
    {
        if(t==NULL)
            return 0;
        int sx= riempi(parola, t->left, num_nodi, count, segna);
        if(t->val%2==0)
            {
                parola[*segna]='E';
            }
        if(t->val%2==1)
            {
                parola[*segna]='O';
            }
        (*segna)++;
        (*count)++;
        if(*count==num_nodi)
            {
                int ris=palindroma(parola, *count);
                return ris;
            }
        int dx=riempi(parola, t->right, num_nodi, count, segna);
    return sx||dx;
    }
void f(Tree t, int *count)
    {
        if(t==NULL)
            return;
    int  num=contanodi(t);
    char *parola=malloc(sizeof(char)*num);
    int c=0;
    int segna=0;
    if(riempi(parola, t, num, &c, &segna))
        (*count)++;
    free(parola);
    f(t->left, count);
    f(t->right, count);
    }
int contanodi(Tree t)
    {
        if(t==NULL)
            return 0;
    return 1+contanodi(t->left)+contanodi(t->right);
    }
int contaSpecchioLocali(Tree T)
    {
    int count=0;
    f(T, &count);
    return count;
    }
