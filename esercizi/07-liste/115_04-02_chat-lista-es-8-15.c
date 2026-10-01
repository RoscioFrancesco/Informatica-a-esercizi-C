//  Created by Francesco Roscio Ricon on 04/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   LISTA INTERNA: valori (tipo "degustazioni")
   ========================= */
typedef struct ValNode {
    int v;
    struct ValNode *next;
} ValNode;

typedef ValNode* ListaValori;

/* =========================
   LISTA ESTERNA: serie (tipo "birre")
   Ogni Serie contiene una lista interna di valori.
   ========================= */
typedef struct Serie {
    char *nome;           /* stringa dinamica, giusto per imitare i temi */
    ListaValori valori;   /* lista interna */
    struct Serie *next;   /* lista esterna */
} Serie;

typedef Serie* ListaSerie;

/* =========================
   UTILITY (qui i cicli sono OK per test)
   ========================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static ListaValori push_back_val(ListaValori l, int x) {
    ValNode *n = (ValNode*)malloc(sizeof(ValNode));
    if (!n) { perror("malloc"); exit(1); }
    n->v = x;
    n->next = NULL;

    if (l == NULL) return n;
    ValNode *cur = l;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return l;
}

static ListaValori fromArrayVal(const int a[], int n) {
    ListaValori l = NULL;
    for (int i = 0; i < n; i++) l = push_back_val(l, a[i]);
    return l;
}

static void printValori(ListaValori l) {
    printf("[");
    while (l) {
        printf("%d", l->v);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]");
}

static void freeValori(ListaValori l) {
    while (l) {
        ValNode *t = l->next;
        free(l);
        l = t;
    }
}

static ListaSerie push_back_serie(ListaSerie s, const char *nome, ListaValori valori) {
    Serie *n = (Serie*)malloc(sizeof(Serie));
    if (!n) { perror("malloc"); exit(1); }
    n->nome = dupstr(nome);
    n->valori = valori;
    n->next = NULL;

    if (s == NULL) return n;
    Serie *cur = s;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return s;
}

static void printSerie(ListaSerie s) {
    while (s) {
        printf("Serie \"%s\": ", s->nome);
        printValori(s->valori);
        printf("\n");
        s = s->next;
    }
}

static void freeSerie(ListaSerie s) {
    while (s) {
        Serie *t = s->next;
        free(s->nome);
        freeValori(s->valori);
        free(s);
        s = t;
    }
}




ListaValori listaPicchi(ListaValori in);


ListaSerie picchiPerOgniSerie(ListaSerie db);

/* =========================
   MAIN DI TEST
   ========================= */
/* utility comoda: crea lista valori da una lista di interi terminata da SENTINEL */
static ListaValori fromSentinel(const int *a, int SENTINEL) {
    ListaValori l = NULL;
    for (int i = 0; a[i] != SENTINEL; i++) {
        l = push_back_val(l, a[i]);
    }
    return l;
}
ListaValori f(ListaValori head);
ListaSerie inserisciserie(ListaSerie head, ListaSerie x);
ListaValori inserisciinfondo(ListaValori head, int x);

int main(void) {
    ListaSerie db = NULL;

    /* ============ SERIE 1: tanti picchi “puliti” ============ */
    int s1[] = { 1, 5, 16, 11, 12, 4, 5, 5, 3, 1, 5, -999 };
    db = push_back_serie(db, "MisureA_picchi_16_12", fromSentinel(s1, -999));

    /* ============ SERIE 2: molti uguali (nessun picco perché serve > strettamente) ============ */
    int s2[] = { 7, 7, 7, 7, 7, -999 };
    db = push_back_serie(db, "Piatta_tutti_uguali", fromSentinel(s2, -999));

    /* ============ SERIE 3: alternanza (picchi in posizioni multiple) ============ */
    int s3[] = { 1, 9, 1, 8, 2, 7, 3, 6, 4, 5, -999 };
    db = push_back_serie(db, "Alternanza_picchi_multipli", fromSentinel(s3, -999));

    /* ============ SERIE 4: include negativi e zero ============ */
    int s4[] = { -10, -3, -8, 0, -1, 2, 1, -5, -6, -2, -999 };
    db = push_back_serie(db, "Negativi_e_zero", fromSentinel(s4, -999));

    /* ============ SERIE 5: lista vuota (edge case) ============ */
    db = push_back_serie(db, "Vuota", NULL);

    /* ============ SERIE 6: un solo elemento (edge case: nessun picco) ============ */
    int s6[] = { 42, -999 };
    db = push_back_serie(db, "Singolo_elemento", fromSentinel(s6, -999));

    /* ============ SERIE 7: due elementi (edge case: nessun picco) ============ */
    int s7[] = { 3, 10, -999 };
    db = push_back_serie(db, "Due_elementi", fromSentinel(s7, -999));

    /* ============ SERIE 8: molti valori, picchi “sparsi” + run di uguali ============ */
    int s8[] = { 4, 6, 6, 2, 9, 1, 1, 8, 7, 7, 10, 3, 3, 2, 12, 0, -999 };
    db = push_back_serie(db, "Mista_run_uguali_e_picchi", fromSentinel(s8, -999));

    printf("=== DATABASE (prima) ===\n");
    printSerie(db);

    /* chiamata “stile tema”: nuova lista esterna con nuove liste interne (picchi) */
    ListaSerie out = picchiPerOgniSerie(db);

    printf("\n=== PICCHI (nuovo database) ===\n");
    printSerie(out);

    freeSerie(db);
    freeSerie(out);
    return 0;
}
ListaValori inserisciinfondo(ListaValori head, int x)
    {
        if(head==NULL)
            {
                ListaValori new=(ListaValori)malloc(sizeof(ValNode));
                new->next=NULL;
                new->v=x;
                return new;
            }
        head->next=inserisciinfondo(head->next, x);
        return head;
    }
ListaValori f(ListaValori head)
    {
        if(head==NULL)
            return head;
    ListaValori scorri=head;
    ListaValori prec=NULL;
    ListaValori new=NULL;
    while(scorri->next!=NULL)
        {
            ListaValori succ=scorri->next;
            if(prec!=NULL && prec->v<scorri->v && scorri->v>succ->v)
                {
                    new=inserisciinfondo(new, scorri->v);
                }
            prec=scorri;
            scorri=succ;
        }
    return new;

    }
ListaSerie inserisciserie(ListaSerie head, ListaSerie x)
    {
        if(head==NULL)
            {
                ListaSerie new=(ListaSerie)malloc(sizeof(Serie));
                new->nome = malloc(strlen(x->nome) + 1);
                strcpy(new->nome, x->nome);
                new->valori=NULL;
                new->valori=f(x->valori);
                new->next=NULL;
                return new;
            }
        head->next=inserisciserie(head->next, x);
        return head;
    }

ListaSerie picchiPerOgniSerie(ListaSerie head)
    {
        if(head==NULL)
            return head;
    ListaSerie new=NULL;
    ListaSerie scorri=head;
    while(scorri!=NULL)
        {
            new=inserisciserie(new, scorri);
            scorri=scorri->next;
        }
    return new;
    }
