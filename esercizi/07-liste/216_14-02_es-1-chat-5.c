//
//  main.c
//  es 1 chat -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char parola[64];
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* ===== compatibili DI TEST (per avere output deterministici) =====
   Compatibili(a,b) = ultima lettera di a == prima lettera di b
   (case-insensitive NON gestito: qui confronto diretto)
*/
int compatibili(const char *a, const char *b) {
    size_t la = strlen(a), lb = strlen(b);
    if (la == 0 || lb == 0) return 0;
    return a[la - 1] == b[0];
}


int correggiBersaglioNoEstremi(Lista *L);


/* ===== helper per test ===== */
static Nodo* newNode(const char *s) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    strcpy(n->parola, s);
    n->next = NULL;
    return n;
}

static Lista buildList(const char *v[], int n) {
    if (n <= 0) return NULL;
    Nodo *head = newNode(v[0]);
    Nodo *tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = newNode(v[i]);
        tail = tail->next;
    }
    return head;
}

static void printList(const char *label, Lista l) {
    printf("%s", label);
    if (!l) { printf("NULL\n"); return; }
    while (l) {
        printf("%s", l->parola);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista l) {
    while (l) {
        Nodo *tmp = l->next;
        free(l);
        l = tmp;
    }
}
int f(Lista *l);
int main(void) {
    /* T1: già valida => return 1, lista invariata */
    const char *t1[] = {"ANA", "ARPA", "ALOE"};
    Lista L1 = buildList(t1, 3);
    printList("T1 prima : ", L1);
    int r1 = correggiBersaglioNoEstremi(&L1);
    printf("T1 return: %d\n", r1);
    printList("T1 dopo  : ", L1);
    printf("\n");

    /* T2: blocco interno eliminabile (POSTINO ancora; SALVIA,TAVOLO non compatibili; OCA compatibile) */
    const char *t2[] = {"POSTINO", "SALVIA", "TAVOLO", "OCA"};
    Lista L2 = buildList(t2, 4);
    printList("T2 prima : ", L2);
    int r2 = correggiBersaglioNoEstremi(&L2);
    printf("T2 return: %d\n", r2);
    printList("T2 dopo  : ", L2);
    printf("\n");

    /* T3: per sistemare servirebbe cancellare il primo nodo (vietato) => return -1, lista invariata */
    const char *t3[] = {"GATTO", "SALVIA", "TAVOLO", "PANE"};
    Lista L3 = buildList(t3, 4);
    printList("T3 prima : ", L3);
    int r3 = correggiBersaglioNoEstremi(&L3);
    printf("T3 return: %d\n", r3);
    printList("T3 dopo  : ", L3);
    printf("\n");

    /* T4: blocco arriva fino a fine lista => si eliminano tutti dopo l'ancora, resta solo il primo => return 0 */
    const char *t4[] = {"POSTINO", "SALVIA", "TAVOLO"};
    Lista L4 = buildList(t4, 3);
    printList("T4 prima : ", L4);
    int r4 = correggiBersaglioNoEstremi(&L4);
    printf("T4 return: %d\n", r4);
    printList("T4 dopo  : ", L4);
    printf("\n");

    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeList(L4);
    return 0;
}

int verificalista(Lista head)
{
        if(head==NULL || head->next==NULL)
            return 1;
        while(head!=NULL && head->next!=NULL)
            {
                if(compatibili(head->parola, head->next->parola)==0)
                    return 0;
                head=head->next;
            }
    return 1;
}
int correggiBersaglioNoEstremi(Lista *L)
    {
//    Lista temp=*L;
//    if(verificalista(temp))
//            return 1;
    printf("entrato");
    return f(L);
    }

//trova il primo nodo “ancora” che resta in lista e cancella il blocco massimo consecutivo di parole successive non compatibili con l’ancora, finché non trovi la prima parola compatibile (o fine lista).
int bloccoK(Lista head) // dovrebbe contare i nodi interni
    {
        if(head==NULL|| head->next==NULL)
            return 0;
        Lista scorri=head->next;
        int count=0;
        while(scorri!=NULL)
            {
                if(compatibili(head->parola, scorri->parola))
                    break;
                count++;
                scorri=scorri->next;
            }
        return count;
    }
Lista distruggiK(Lista head, int k)
    {
        if(head==NULL)
            return head;
    head=head->next;
    for(int i=0; head!=NULL && i<k; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
int f(Lista *l)
    {
        if(*l==NULL)
            return 0;
        Lista *pp=l;
    while (*pp!=NULL) {
        int len=0;
        len=bloccoK(*pp);
        if(len>0)
            {
                (*pp)->next=distruggiK((*pp), len);
            }
        else
            {
                pp=&(*pp)->next;
            }
    }
    return 1;
    }
