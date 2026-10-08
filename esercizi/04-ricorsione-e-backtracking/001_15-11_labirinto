//
//  main.c
//  labirinto magri
//
//  Created by Francesco Roscio Ricon on 15/11/25.
//

#include <stdio.h>
#define N 10
#define DIM 10
typedef char labirinto_t[DIM][DIM];
void stampa_labirinto(labirinto_t) ;
int trova_uscita (labirinto_t, int, int);


void stampa_labirinto(labirinto_t l){
    printf("\n");
    for(int i =0; i <DIM; i++){
        for(int j =0; j<DIM; j++){
            printf("%c ", l[i][j]);
        }
        printf("\n");
    }
}
int trova_uscita (labirinto_t l, int rig, int col) {
    // coordinate fuori dal labirinto >> non procedere
    if (rig<0 || rig==DIM || col<0 || col==DIM)
        return 0;
    // se la casella è un muro o è già stata visitata >> non procedere
    if (l[rig][col] == 'M' || l[rig][col] == '.')
        return 0;
    // se la casella è l'uscita >> termina
    if (l[rig][col] == 'u')
        return 1;
    l[rig][col] = '.';    // marca casella corrente come visitata
    if (trova_uscita(l, rig+1, col))
        return 1;// esplora direzioni
    if (trova_uscita(l, rig-1, col))
        return 1;
    if (trova_uscita(l, rig, col+1))
        return 1;
    if (trova_uscita(l, rig, col-1))
        return 1;
    l[rig][col] = ' ';// cancella marcatura
    return 0;    // scarta percorso
}



int main () {
     labirinto_t l = {
            'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M',
            'p', ' ', 'M', ' ', ' ', ' ', 'M', ' ', ' ', 'M',
            'M', ' ', 'M', ' ', 'M', ' ', ' ', ' ', ' ', 'M',
            'M', ' ', 'M', ' ', 'M', 'M', 'M', ' ', 'M', 'M',
            'M', ' ', 'M', ' ', 'M', ' ', ' ', ' ', ' ', 'M',
            'M', ' ', ' ', ' ', 'M', ' ', 'M', 'M', 'M', 'M',
            'M', 'M', 'M', ' ', 'M', ' ', ' ', 'M', ' ', 'u',
            'M', ' ', ' ', ' ', 'M', ' ', ' ', 'M', ' ', 'M',
            'M', ' ', ' ', ' ', 'M', ' ', ' ', ' ', ' ', 'M',
            'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M'
            };
    stampa_labirinto(l);
    // individua partenza
    int px, py;
    for (int x = 0; x < DIM; x++) {
        for (int y = 0; y < DIM; y++) {
            if (l[x][y] == 'p') {
                px = x;
                py = y;
                //partenza trovata – termino ciclo
                x = DIM;
                y = DIM;
            }
        }
    }
    printf("Partenza trovata in %d-%d\n",px,py);
    // trova uscita
    if (trova_uscita(l, px, py)) {
        printf("Uscita trovata!");
    } else{
        printf("Nessuna uscita trovata\n\n");
    }
    stampa_labirinto(l);
    return 0;
}
