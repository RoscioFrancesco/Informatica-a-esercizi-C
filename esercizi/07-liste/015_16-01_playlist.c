//  Created by Francesco Roscio Ricon on 16/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struttura per rappresentare una canzone
typedef struct Canzone {
    char *titolo;            // Titolo della canzone (stringa dinamica)
    int durata;              // Durata in secondi
    struct Canzone *next;    // Puntatore alla prossima canzone
} Canzone;

// Struttura per rappresentare una playlist
typedef struct Playlist {
    char *nome;              // Nome della playlist (stringa dinamica)
    int lunghezza_totale;
    Canzone *canzoni;        // Lista di canzoni
    struct Playlist *next;   // Puntatore alla prossima playlist
} Playlist;


// Prototipi
Playlist* init();
Playlist* creaPlaylist(Playlist *head, const char *nome);
void aggiungiCanzone(Playlist *playlist, const char *titolo, int durata);
void stampaTuttePlaylist(Playlist *head);
void calcolalunghezza(Playlist* playlist);
void Eliminamin(Canzone* temp_prec_min, Canzone* temp_min);
void funzione(Playlist* laplaylist, int max);
void riduciDurate(Playlist* playlist, int max);

int main() {
    Playlist* playlists = init();
    int durataMassima = 600;
    calcolalunghezza(playlists);
    stampaTuttePlaylist(playlists);
    riduciDurate(playlists, durataMassima);
    stampaTuttePlaylist(playlists);
}

// Crea playlist
Playlist * init(){
    Playlist *playlists = NULL;

    // Creazione delle playlist
    playlists = creaPlaylist(playlists, "Rock");
    playlists = creaPlaylist(playlists, "Pop");

    // Aggiunta di canzoni alla playlist "Rock"
    aggiungiCanzone(playlists, "Bohemian Rhapsody", 355);
    aggiungiCanzone(playlists, "Stairway to Heaven", 480);

    // Aggiunta di canzoni alla playlist "Pop"
    aggiungiCanzone(playlists->next, "Thriller", 300);
    aggiungiCanzone(playlists->next, "Short Pop Song", 90);

    return playlists;
}

Playlist* creaPlaylist(Playlist *head, const char *nome) {
    // Allocazione di una nuova playlist
    Playlist *nuova = (Playlist *)malloc(sizeof(Playlist));
    if (nuova == NULL) {
        printf("Errore di allocazione memoria per la playlist");
        return NULL;
    }

    // Allocazione dinamica per il nome della playlist
    nuova->nome = (char *)malloc((strlen(nome) + 1) * sizeof(char));
    if (nuova->nome == NULL) {
        printf("Errore di allocazione memoria per il nome della playlist");
        free(nuova);
        return NULL;
    }

    // Copia del nome
    strcpy(nuova->nome, nome);

    // Inizializzazione della lista di canzoni
    nuova->canzoni = NULL;

    // Inserimento della nuova playlist in testa alla lista principale
    nuova->next = head;

    return nuova;
}

void aggiungiCanzone(Playlist *playlist, const char *titolo, int durata) {
    if (playlist == NULL) {
        printf("Errore: la playlist non esiste.\n");
        return;
    }

    // Allocazione di una nuova canzone
    Canzone *nuova = (Canzone *)malloc(sizeof(Canzone));
    if (nuova == NULL) {
        printf("Errore di allocazione memoria per la canzone");
        return;
    }

    // Allocazione dinamica per il titolo della canzone
    nuova->titolo = (char *)malloc((strlen(titolo) + 1) * sizeof(char));
    if (nuova->titolo == NULL) {
        printf("Errore di allocazione memoria per il titolo della canzone");
        free(nuova);
        return;
    }

    // Copia del titolo
    strcpy(nuova->titolo, titolo);

    // Assegnazione della durata
    nuova->durata = durata;

    // Inserimento della nuova canzone in testa alla lista delle canzoni della playlist
    nuova->next = playlist->canzoni;
    playlist->canzoni = nuova;
}

// Stampa
void stampaTuttePlaylist(Playlist *head) {
    Playlist *curr = head;

    while (curr != NULL) {
        printf("Playlist: %s\n", curr->nome);
        Canzone *canzone = curr->canzoni;

        while (canzone != NULL) {
            printf("  - %s (%d secondi)\n", canzone->titolo, canzone->durata);
            canzone = canzone->next;
        }
        printf("\n%d", curr->lunghezza_totale);

        curr = curr->next;
        printf("\n");
    }
}

void calcolalunghezza(Playlist* playlist)
    {
        while(playlist!=NULL)
            {
                    {
                        int durata=0;
                        Canzone* temp=playlist->canzoni;
                        while(temp!=NULL)
                        {
                            durata=durata+(temp->durata);
                            temp=temp->next;
                        }
                        playlist->lunghezza_totale=durata;
                    }
                playlist=playlist->next;
            }
    }

void riduciDurate(Playlist* playlist, int max)
    {
    Playlist* temp=playlist;
    while(temp!=NULL)
        {
            if(temp->lunghezza_totale>max)
                {
                    funzione(temp, max);
                }
            temp=temp->next;
        }
        return;
        
    }
void funzione(Playlist* laplaylist, int max)
    {
        do{
            Canzone*temp_prec=laplaylist->canzoni;
            int min=temp_prec->durata;
            Canzone*temp=temp_prec->next;
            Canzone*temp_min=laplaylist->canzoni;
            Canzone*temp_prec_min=NULL;
            while(temp!=NULL)
            {
                if(temp->durata<min)
                {
                    min=temp->durata;
                    temp_prec_min=temp_prec;
                    temp_min=temp;
                }
                
                temp_prec=temp;
                temp=temp->next;
            }
            laplaylist->lunghezza_totale=laplaylist->lunghezza_totale-temp_min->durata;
            if(temp_min==laplaylist->canzoni)
            {
                laplaylist->canzoni=temp_min->next;
                free(temp_min->titolo);
                free(temp_min);
            }
            else
            {
                Eliminamin(temp_prec_min, temp_min);
            }
        }while(laplaylist->lunghezza_totale>max);
    }

void Eliminamin(Canzone* temp_prec_min, Canzone* temp_min)
    {
    if(temp_min==NULL)
        {
            return;
        }
    temp_prec_min->next=temp_min->next;
    free(temp_min->titolo);
    free(temp_min);
    }

