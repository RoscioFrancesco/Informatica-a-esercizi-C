//  Created by Francesco Roscio Ricon on 08/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* =========================
   STRUTTURE
   ========================= */
typedef struct nd {
    char *word;          /* stringa dinamica */
    struct nd *next;
} parola;

typedef parola* Sequenza;


Sequenza shrink(Sequenza head); /* TODO */

/* =========================
   UTILITY PER TEST
   ========================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Sequenza newNode(const char *w) {
    Sequenza n = (Sequenza)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = NULL;
    return n;
}

/* Inserimento in coda (semplice per costruire i test) */
static Sequenza pushBack(Sequenza head, const char *w) {
    if (!head) return newNode(w);
    Sequenza cur = head;
    while (cur->next) cur = cur->next;
    cur->next = newNode(w);
    return head;
}

static void printSeq(const Sequenza s) {
    const Sequenza cur = s;
    (void)cur;
    Sequenza p = s;
    printf("[ ");
    while (p) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
        p = p->next;
    }
    printf(" ]\n");
}

static void freeSeq(Sequenza s) {
    while (s) {
        Sequenza tmp = s->next;
        free(s->word);
        free(s);
        s = tmp;
    }
}

/* =========================
   COSTRUZIONE SEQUENZE DI TEST
   ========================= */
static Sequenza build_test1(void) {
    /* regola -> lazio -> azione */
    Sequenza s = NULL;
    s = pushBack(s, "regola");
    s = pushBack(s, "lazio");
    s = pushBack(s, "azione");
    return s;
}

static Sequenza build_test2(void) {
    /* antro -> tropo -> polo -> logo -> laurea -> reato */
    Sequenza s = NULL;
    s = pushBack(s, "antro");
    s = pushBack(s, "tropo");
    s = pushBack(s, "polo");
    s = pushBack(s, "logo");
    s = pushBack(s, "laurea");
    s = pushBack(s, "reato");
    return s;
}

static Sequenza build_test3(void) {
    /* intimi -> timida -> datori -> torio */
    Sequenza s = NULL;
    s = pushBack(s, "intimi");
    s = pushBack(s, "timida");
    s = pushBack(s, "datori");
    s = pushBack(s, "torio");
    return s;
}

static Sequenza build_test4(void) {
    /* rostro -> zangola -> trogolo (non cambia) */
    Sequenza s = NULL;
    s = pushBack(s, "rostro");
    s = pushBack(s, "zangola");
    s = pushBack(s, "trogolo");
    return s;
}

/* =========================
   MAIN DI TEST
   ========================= */
char * accoppia(char parola1[], char parola2[], int num);
int overlappabili(char parola1[], char parola2[]);
int main(void) {
    
    Sequenza s1 = build_test1();
    Sequenza s2 = build_test2();
    Sequenza s3 = build_test3();
    Sequenza s4 = build_test4();
    Sequenza s5 = NULL;          /* lista vuota */
    Sequenza s6 = newNode("solo"); /* lista di un elemento */

    printf("=== TEST 1 ===\n");
    printf("Prima:  "); printSeq(s1);
    shrink(s1);
    printf("Dopo:   "); printSeq(s1);
    printf("\n");

    printf("=== TEST 2 ===\n");
    printf("Prima:  "); printSeq(s2);
    shrink(s2);
    printf("Dopo:   "); printSeq(s2);
    printf("\n");

    printf("=== TEST 3 ===\n");
    printf("Prima:  "); printSeq(s3);
    shrink(s3);
    printf("Dopo:   "); printSeq(s3);
    printf("\n");

    printf("=== TEST 4 ===\n");
    printf("Prima:  "); printSeq(s4);
    shrink(s4);
    printf("Dopo:   "); printSeq(s4);
    printf("\n");

    printf("=== TEST 5 (NULL) ===\n");
    printf("Prima:  "); printSeq(s5);
    shrink(s5);
    printf("Dopo:   "); printSeq(s5);
    printf("\n");

    printf("=== TEST 6 (SINGLE) ===\n");
    printf("Prima:  "); printSeq(s6);
    shrink(s6);
    printf("Dopo:   "); printSeq(s6);
    printf("\n");

    freeSeq(s1);
    freeSeq(s2);
    freeSeq(s3);
    freeSeq(s4);
    freeSeq(s5);
    freeSeq(s6);

    return 0;
}

//printf("%d", overlappabili("intimi", "timida"));
int overlappabili(char parola1[], char parola2[])
    {
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    if(len2==0)
        return -1;
    int count=0;
    for(int i=0; i<len1; i++)
        {
            if(parola1[i]==parola2[0])
                {
                    count=0;
                    for(int j=0; j<len1-i && j<len2; j++)
                        {
                            if(parola1[i+j]==parola2[j])
                                count++;
                            else
                                break;
                        }
                    if(i+count==len1 && count>=2)
                        return count;
                }
        }
    return -1;
    }
char * accoppia(char parola1[], char parola2[], int num)
    {
    char *new=malloc(sizeof(char)*(strlen(parola1)+strlen(parola2)-num+1));
    int len_new=strlen(parola1)+strlen(parola2)-num;
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    int j=0;
    int i=0;
    for(; i<len1; i++)
        {
            new[i]=parola1[i];
        }
    for(int j=num; j<len2; j++)
        {
            new[i]=parola2[j];
            i++;
        }
        new[len_new]='\0';
        return new;
    }
Sequenza shrink(Sequenza head)
    {
        if(head==NULL || head->next==NULL)
            return head;
    int count=0;
    count=overlappabili((head->word), (head->next->word));
        if(count!=-1)
            {
//                free(head->word);
                char *nuova=accoppia(head->word, head->next->word, overlappabili(head->word, head->next->word));
                free(head->word);
                head->word=nuova;
                Sequenza succ=head->next;
                Sequenza l=succ->next;
                head->next=l;
                succ->next=NULL;
                free(succ->word);
                free(succ);
                return shrink(head);
            }
    head->next=shrink(head->next);
    return head;
    }
