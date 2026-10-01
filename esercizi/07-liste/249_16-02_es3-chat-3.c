//
//  main.c
//  es3 chat -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int val;
    struct Nodo* next;
} Nodo;

typedef Nodo* lista;

lista eliminaBlocchiPari(lista L);

lista newNode(int x) {
    lista n = (lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

lista pushBack(lista L, int x) {
    lista n = newNode(x);
    if (!L) return n;
    lista cur = L;
    while (cur->next)
        cur = cur->next;
    cur->next = n;
    return L;
}

lista buildFromArray(const int a[], int n) {
    lista L = NULL;
    for (int i = 0; i < n; i++)
        L = pushBack(L, a[i]);
    return L;
}

void printLista(lista L) {
    if (!L) {
        printf("(vuota)\n");
        return;
    }
    while (L) {
        printf("%d", L->val);
        if (L->next)
            printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

void freeLista(lista L) {
    while (L) {
        lista tmp = L;
        L = L->next;
        free(tmp);
    }
}


void f(lista *head);;
lista eliminaBlocchiPari(lista L) {
    f(&L);
    return L;
}

void runTest(const char* nome, const int a[], int n, const char* expected) {
    printf("=== %s ===\n", nome);

    lista L = buildFromArray(a, n);

    printf("Input:   ");
    printLista(L);

    L = eliminaBlocchiPari(L);

    printf("Output:  ");
    printLista(L);

    printf("Atteso:  %s\n\n", expected);

    freeLista(L);
}

int main() {

    /* TEST 1 (esempio testo) */
    int t1[] = {4, 6, 3, 8, 10, 12, 5, 2};
    runTest("Test 1 (esempio)", t1, 8, "3 -> 5 -> 2");

    /* TEST 2 (blocco in testa) */
    int t2[] = {2, 4, 6, 7, 9};
    runTest("Test 2 (blocco in testa)", t2, 5, "7 -> 9");

    /* TEST 3 (blocco in coda) */
    int t3[] = {1, 3, 5, 8, 10};
    runTest("Test 3 (blocco in coda)", t3, 5, "1 -> 3 -> 5");

    /* TEST 4 (lista tutta pari) */
    int t4[] = {2, 4, 6, 8};
    runTest("Test 4 (tutta pari)", t4, 4, "(vuota)");

    /* TEST 5 (pari singolo che resta) */
    int t5[] = {1, 2, 3, 4, 6, 5, 8, 7};
    runTest("Test 5 (singoli + blocco interno)", t5, 8,
            "1 -> 2 -> 3 -> 5 -> 8 -> 7");

    return 0;
}
int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        while(head!=NULL)
            {
                if(head->val%2==1)
                   break;
                count++;
                head=head->next;
            }
        return count;
    }
lista eliminaK(lista head, int k)
    {
        if(head==NULL)
            return head;
        for(int i=0; i<k; i++)
            {
                lista temp=head->next;
                free(head);
                head=temp;
            }
    return head;
    }
void f(lista *head)
    {
        if(head==NULL || *head==NULL)
            return;
        lista *pp=head;
        while(*pp!=NULL)
            {
                int num=blocco(*pp);
                if(num>=2)
                    {
                        *pp=eliminaK(*pp, num);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }

