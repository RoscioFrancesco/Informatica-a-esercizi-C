//
//  main.c
//  liste 3  iterativo -16
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   STRUTTURE DATI
   ========================================================= */
typedef struct Node {
    char *word;          /* stringa dinamica */
    struct Node *next;
} Node;

typedef Node* Lista;

/* =========================================================
   UTILITY: strdup, creazione, stampa, free
   ========================================================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Node* newNodeDup(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = next;
    return n;
}

/* crea lista da array di stringhe (mantiene l'ordine) */
static Lista fromArray(const char *a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i)
        l = newNodeDup(a[i], l);
    return l;
}

static void printLista(Lista l) {
    printf("[");
    for (Node *p = l; p != NULL; p = p->next) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}


/* =========================================================
   MAIN DI TEST + PRINTF
   ========================================================= */

Lista f(Lista head, char parola[]);
void run(Lista head, char parola[], int segna, int *count, Lista *finish, int *flag);
void minrun(Lista head, char parola[], int *countmin, Lista *head_min, Lista *finish_min);
Lista distruggiblocco(Lista head, Lista finish_min);

int main(void)
{
    const char *PAT = "ZZQQ"; /* esempio: sottostringa da cercare nella concatenazione */

    const char *words[] = {
        "ZZ", "A", "B", "A", "QQ", "AB", "AX", "BA", "END"
    };
    int n = (int)(sizeof(words) / sizeof(words[0]));

    Lista l = fromArray(words, n);

    printf("PAT = \"%s\"\n", PAT);
    printf("Lista iniziale:\n");
    printLista(l);

    l = f(l, PAT);

    printf("\nLista dopo eliminaBloccoMinimoConPAT (atteso: modificata se esiste blocco valido):\n");
    printLista(l);

    freeLista(l);
    return 0;
}
// prima di tutto devo trovare start e finish del blocco minimo
void run(Lista head, char parola[], int segna, int *count, Lista *finish, int *flag)
    {
        if(head==NULL)
        {
            return;
        }
        if(*finish==NULL)
        {
            *flag=0;
            return;
        }
        int len_parola=strlen((*finish)->word);
        for(int i=0; i<len_parola; i++)
            {
                if((*finish)->word[i]==parola[segna])
                    {
                        (segna)++;
                        if(segna==strlen(parola))
                        {
                            (*finish)=(*finish)->next;
                            *flag=1;
                            return;
                        }
                            
                    }
            }
        (*count)++;
        (*finish)=(*finish)->next;
        run(head, parola, segna, count, finish, flag);
    }
void minrun(Lista head, char parola[], int *countmin, Lista *head_min, Lista *finish_min)
    {
        if(head==NULL)
        {
            
            return;
        }
        Lista finish=head;
        int segna=0;
        int count=0;
        int flag=0;
        run(head, parola, segna, &count, &finish, &flag);
        if(count<*countmin)
            {
                *countmin=count;
                *head_min=head;
                *finish_min=finish;
            }
    minrun(head->next, parola, countmin, head_min, finish_min);
    }
int wrapperminrun(Lista head, char parola[], Lista *head_min, Lista *finish_min)
    {
    if(head==NULL)
        return 0;
    Lista temp=head;
    int i=0;
    while (temp!=NULL) {
        i++;
        temp=temp->next;
        }
    int countmin=i;
    minrun(head, parola, &countmin, head_min, finish_min);
    return countmin;
    }
Lista f(Lista head, char parola[])
    {
        if(head==NULL || head->next==NULL)
            return head;
        Lista head_min=head;
        Lista finishmin=head->next;
        int lenmin=wrapperminrun(head, parola,&head_min , &finishmin);
        if(head==head_min)
            {
                head=distruggiblocco(head, finishmin);
                return head;
            }
    
        Lista scorri=head;
        while(scorri!=NULL && scorri->next!=head_min)
            {
                scorri=scorri->next;
            }
    
        Lista temp=scorri->next;
        scorri->next=finishmin;
        distruggiblocco(temp, finishmin);
    
    return head;
    }
Lista distruggiblocco(Lista head, Lista finish_min)
    {
    if(head==NULL)
        return head;
    if(head==finish_min)
        return finish_min;
    Lista temp=head->next;
    free(head->word);
    free(head);
    return distruggiblocco(temp, finish_min);
    }
