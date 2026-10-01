//
//  main.c
//  liste tde 7 liste -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//

//Si codifichi in C la seguente funzione:
//int inserisciCanzone(ListaArtisti Lis, char *artista, char *disc, int anno, char *canzone, int durata, int posizione)
//che

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Song {
    char *titolo;
    int durata, pos;
    struct Song *next;
} Canzone;
typedef Canzone* ListaCanzoni;

typedef struct Album {
    char *titolo;
    int n_canzoni, anno;
    ListaCanzoni canzoni;
    struct Album *next;
} Disco;
typedef Disco* ListaDischi;

typedef struct Singer {
    char *nome;
    int n_dischi;
    ListaDischi dischi;
    struct Singer *next;
} Artista;
typedef Artista* ListaArtisti;

/* =========================================================
   PROTOTIPI (ESERCIZIO)
   ========================================================= */
int discoPiuLungo(ListaArtisti artisti, int anno);  /* TODO */
int inserisciCanzone(ListaArtisti Lis, char *artista, char *disc, int anno,
                     char *canzone, int durata, int posizione);            /* TODO */

/* =========================================================
   UTILITY: strdup "portabile"
   ========================================================= */
static char* dupstr(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

/* =========================================================
   UTILITY: creazione nodi (per costruire casi di test nel main)
   ========================================================= */
static Artista* newArtista(const char *nome) {
    Artista *a = (Artista*)malloc(sizeof(Artista));
    if (!a) { perror("malloc"); exit(1); }
    a->nome = dupstr(nome);
    a->n_dischi = 0;
    a->dischi = NULL;
    a->next = NULL;
    return a;
}

static Disco* newDisco(const char *titolo, int anno) {
    Disco *d = (Disco*)malloc(sizeof(Disco));
    if (!d) { perror("malloc"); exit(1); }
    d->titolo = dupstr(titolo);
    d->anno = anno;
    d->n_canzoni = 0;
    d->canzoni = NULL;
    d->next = NULL;
    return d;
}

static Canzone* newCanzone(const char *titolo, int durata, int pos) {
    Canzone *c = (Canzone*)malloc(sizeof(Canzone));
    if (!c) { perror("malloc"); exit(1); }
    c->titolo = dupstr(titolo);
    c->durata = durata;
    c->pos = pos;
    c->next = NULL;
    return c;
}

/* =========================================================
   STAMPE (debug)
   ========================================================= */
static void stampaCanzoni(ListaCanzoni c) {
    while (c) {
        printf("      - (%d) \"%s\" durata=%d\n", c->pos, c->titolo, c->durata);
        c = c->next;
    }
}

static void stampaDischi(ListaDischi d) {
    while (d) {
        printf("    Disco: \"%s\" anno=%d  n_canzoni=%d\n", d->titolo, d->anno, d->n_canzoni);
        stampaCanzoni(d->canzoni);
        d = d->next;
    }
}

static void stampaArchivio(ListaArtisti a) {
    printf("=== ARCHIVIO ===\n");
    while (a) {
        printf("Artista: \"%s\"  n_dischi=%d\n", a->nome, a->n_dischi);
        stampaDischi(a->dischi);
        a = a->next;
    }
    printf("================\n");
}

/* =========================================================
   FREE (per non leakare)
   ========================================================= */
static void freeCanzoni(ListaCanzoni c) {
    while (c) {
        ListaCanzoni nxt = c->next;
        free(c->titolo);
        free(c);
        c = nxt;
    }
}

static void freeDischi(ListaDischi d) {
    while (d) {
        ListaDischi nxt = d->next;
        freeCanzoni(d->canzoni);
        free(d->titolo);
        free(d);
        d = nxt;
    }
}

static void freeArtisti(ListaArtisti a) {
    while (a) {
        ListaArtisti nxt = a->next;
        freeDischi(a->dischi);
        free(a->nome);
        free(a);
        a = nxt;
    }
}

/* =========================================================
   FUNZIONI DELL'ESERCIZIO (TODO - NON RISOLTE)
   ========================================================= */
int discoPiuLungo(ListaArtisti artisti, int anno)
{
    int max_len=0;
    int somma=0;
    if(artisti==NULL)
        return 0;
    ListaArtisti scorri_artisti=artisti;
    while (scorri_artisti!=NULL) {
        ListaDischi scorri_dischi=scorri_artisti->dischi;
        while(scorri_dischi!=NULL)
            {
                if(scorri_dischi->anno==anno)
                    {
                        ListaCanzoni scorri_canzoni=scorri_dischi->canzoni;
                        while (scorri_canzoni!=NULL) {
                            somma=somma+scorri_canzoni->durata;
                            scorri_canzoni=scorri_canzoni->next;
                        }
                        if(somma>max_len)
                            max_len=somma;
                        somma=0;
                    }
                scorri_dischi=scorri_dischi->next;
            }
        scorri_artisti=scorri_artisti->next;
    }
    return max_len;
}

int cerca_artista(ListaArtisti lis, char artista[], ListaArtisti *punt) // se lo trova mi ridà 1
    {
        if(lis==NULL)
            return 0;
    ListaArtisti scorri=lis;
    while (scorri!=NULL) {
        if(strcmp(scorri->nome, artista)==0)
        {
            *punt=scorri;
            return 1;
        }
        scorri=scorri->next;
        }
    return 0;
    }
int cercadisco(ListaDischi dischi, char disco[], ListaDischi *punt) // 0 se non lo trova, 1 se lo trova
    {
        if(dischi==NULL)
            return 0;
        ListaDischi scorri=dischi;
        while (scorri!=NULL) {
            if(strcmp(disco, scorri->titolo)==0)
            {
                *punt=scorri;
                return 1;
            }
            scorri=scorri->next;
        }
        return 0;
    }
//Infine, la funzione ha esito negativo qualora esista un album con medesimo titolo e anno diverso, canzone con medesimo titolo all’interno dell’album o un’altra canzone nella medesima posizione
int inserisciCanzone(ListaArtisti Lis, char *artista, char *disc, int anno, char *canzone, int durata, int posizione)
{
    ListaArtisti punt=NULL;
    int ris=cerca_artista(Lis, artista, &punt);
    if(ris==0)
        return -1;
    ListaDischi punt_aldisco=NULL;
    int ris_cercadisco=cercadisco(punt->dischi, disc, &punt_aldisco);
    if(ris_cercadisco==0) // in questo caso bisogna aggiungereil disco con dentro la canzone
        {
            
            ListaDischi nuovodisco=(ListaDischi)malloc(sizeof(*nuovodisco));
            (punt->n_dischi)++;
            punt->dischi=nuovodisco;
            nuovodisco->anno=anno;
            nuovodisco->n_canzoni=1;
            nuovodisco->next=punt->dischi;
            punt->dischi=nuovodisco;
            nuovodisco->titolo=malloc(sizeof(char)*(strlen(disc)+1));
            strcpy(nuovodisco->titolo, disc);
            nuovodisco->canzoni=(ListaCanzoni)malloc(sizeof(Canzone));
            nuovodisco->canzoni->titolo=malloc(sizeof(char)*(strlen(canzone)+1));
            strcpy(nuovodisco->canzoni->titolo,canzone);
            nuovodisco->canzoni->pos=0;
            nuovodisco->canzoni->durata=durata;
            nuovodisco->canzoni->next=NULL;
        }
    else // in questo caso bisogna aggiungere la canzone
        {
            if(punt_aldisco->anno!=anno)
                return -1;
            ListaCanzoni scorricanzoni=punt_aldisco->canzoni;
            int i=0;
            ListaCanzoni temp=scorricanzoni;
            for(;temp!=NULL; temp=temp->next)
            {
                if(i==posizione && strcmp(temp->titolo, canzone)!=0)
                    return -1;
                if(strcmp(temp->titolo, canzone)==0)
                    return -1;
                i++;
            }
            temp=scorricanzoni;
            while (temp!=NULL) {
                temp=temp->next;
            }
            ListaCanzoni new=(ListaCanzoni)malloc(sizeof(*new));
            new->durata=durata;
            new->pos=posizione;
            new->next=NULL;
            new->titolo=malloc(sizeof(char)*(strlen(canzone)+1));
            temp=new;
            (punt->dischi->n_canzoni)++;
        }
    return 0;
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int main(void) {
    /* Costruisco un archivio minimale:
       Artisti ordinati per nome (qui lo faccio “a mano” nel main).
    */
    ListaArtisti arch = newArtista("Adele");
    arch->next = newArtista("Coldplay");

    /* Aggiungo qualche disco/canzone “a mano” per avere dati su cui testare discoPiuLungo */
    arch->dischi = newDisco("25", 2015);
    arch->n_dischi = 1;
    arch->dischi->canzoni = newCanzone("Hello", 295, 1);
    arch->dischi->canzoni->next = newCanzone("Send My Love", 223, 2);
    arch->dischi->n_canzoni = 2;

    arch->next->dischi = newDisco("Ghost Stories", 2014);
    arch->next->n_dischi = 1;
    arch->next->dischi->canzoni = newCanzone("Always In My Head", 216, 1);
    arch->next->dischi->canzoni->next = newCanzone("Magic", 285, 2);
    arch->next->dischi->n_canzoni = 2;

    stampaArchivio(arch);

    /* ===== Test funzione 1 (TODO) ===== */
    int anno_test = 2015;
    int maxdur = discoPiuLungo(arch, anno_test);
    printf("\n[TEST] discoPiuLungo(anno=%d) -> %d\n", anno_test, maxdur);

    /* ===== Test funzione 2 (TODO) ===== */
    printf("\n[TEST] inserisciCanzone su artista esistente (dovrebbe tornare 0 quando implementata bene)\n");
    int esito = inserisciCanzone(arch, "Adele", "25", 2015, "I Miss You", 347, 3);
    printf("Esito inserisciCanzone = %d\n", esito);

    printf("\n[TEST] inserisciCanzone su artista NON esistente (dovrebbe tornare -1)\n");
    int esito2 = inserisciCanzone(arch, "Muse", "Absolution", 2003, "Hysteria", 228, 1);
    printf("Esito inserisciCanzone = %d\n", esito2);

    printf("\nArchivio DOPO i test (con funzioni TODO, probabilmente invariato):\n");
    stampaArchivio(arch);

    freeArtisti(arch);
    return 0;
}
