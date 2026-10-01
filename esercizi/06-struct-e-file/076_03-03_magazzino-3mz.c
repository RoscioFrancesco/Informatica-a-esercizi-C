//
//  main.c
//  magazzino 3mz
//
//  Created by Francesco Roscio Ricon on 03/03/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int R;
    int C;
    int **qta;      // R x C quantità
    char ***cod;    // R x C stringhe (ogni cella è char*)
} Magazzino;

Magazzino creaMagazzino(int R, int C) {
    Magazzino m;
    int i, j;

    m.R = R;
    m.C = C;

    /* alloco qta */
    m.qta = (int**)malloc(R * sizeof(int*));
    if (!m.qta) { perror("malloc qta"); exit(1); }
    for (i = 0; i < R; i++) {
        m.qta[i] = (int*)malloc(C * sizeof(int));
        if (!m.qta[i]) { perror("malloc qta[i]"); exit(1); }
    }

    /* alloco cod */
    m.cod = (char***)malloc(R * sizeof(char**));
    if (!m.cod) { perror("malloc cod"); exit(1); }
    for (i = 0; i < R; i++) {
        m.cod[i] = (char**)malloc(C * sizeof(char*));
        if (!m.cod[i]) { perror("malloc cod[i]"); exit(1); }
    }

    /* inizializzo celle */
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            m.qta[i][j] = 0;
            m.cod[i][j] = NULL;
        }
    }

    return m;
}

/* ====== INSERISCI (per test) ====== */
void inserisciProdotto(Magazzino *m, int r, int c, const char *codice, int quantita) {
    if (r < 0 || r >= m->R || c < 0 || c >= m->C) return;

    if (m->cod[r][c] != NULL) {
        free(m->cod[r][c]);
        m->cod[r][c] = NULL;
    }

    m->cod[r][c] = (char*)malloc(strlen(codice) + 1);
    if (!m->cod[r][c]) { perror("malloc codice"); exit(1); }
    strcpy(m->cod[r][c], codice);

    m->qta[r][c] = quantita;
}

/* ====== STAMPA ====== */
void stampaMagazzino(const Magazzino *m) {
    int i, j;
    printf("\n--- MAGAZZINO (%dx%d) ---\n", m->R, m->C);
    for (i = 0; i < m->R; i++) {
        for (j = 0; j < m->C; j++) {
            if (m->cod[i][j] == NULL || m->cod[i][j][0] == '\0')
                printf("[   ---   ] ");
            else
                printf("[%8s:%2d] ", m->cod[i][j], m->qta[i][j]);
        }
        printf("\n");
    }
    printf("------------------------\n");
}

/* ====== LIBERA ====== */
void liberaMagazzino(Magazzino *m) {
    int i, j;

    if (!m) return;

    /* libera stringhe + righe */
    for (i = 0; i < m->R; i++) {
        for (j = 0; j < m->C; j++) {
            if (m->cod[i][j] != NULL) {
                free(m->cod[i][j]);
                m->cod[i][j] = NULL;
            }
        }
        free(m->cod[i]);
        m->cod[i] = NULL;

        free(m->qta[i]);
        m->qta[i] = NULL;
    }

    free(m->cod);
    m->cod = NULL;

    free(m->qta);
    m->qta = NULL;

    m->R = 0;
    m->C = 0;
}

/* ====== MAIN DI TEST ====== */
int main(void) {
    Magazzino m = creaMagazzino(3, 4);

    inserisciProdotto(&m, 0, 1, "A12", 5);
    inserisciProdotto(&m, 2, 3, "B7", 10);
    inserisciProdotto(&m, 1, 0, "X99", 3);

    stampaMagazzino(&m);

    liberaMagazzino(&m);
    return 0;
}
