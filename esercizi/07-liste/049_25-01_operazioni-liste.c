//
//  main.c
//  operazioni liste
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//

// Librerie
#include <stdio.h>
#include <stdlib.h> // !!!

// Dati
typedef struct NodeStruct {
    int data;
    struct NodeStruct * next;
} Node;
typedef Node * pNode;

// Prototipi
void stampaLista(pNode);
pNode inserisciCoda(pNode, int);
pNode inserisciTesta(pNode, int);
pNode inserisciPos(pNode, int, int);
int listaLen(pNode);
float listaMedia(pNode, int*);
int cercaElemento(pNode, int);
void eliminaLista(pNode);
pNode funzione(pNode head, int k);

// Main
int main() {
    pNode head = NULL; // Inizializzazione della lista
    int err;

    printf("Creazione lista con inserimento in testa:\n");
    head = inserisciTesta(head, 10);
    head = inserisciTesta(head, 20);
    head = inserisciTesta(head, 30);
    stampaLista(head);

    printf("\nInserimento in coda:\n");
    head = inserisciCoda(head, 40);
    head = inserisciCoda(head, 50);
    stampaLista(head);
    head=funzione(head, 50);
    printf("\n");
    stampaLista(head);
    

    
}

// Funzioni
void stampaLista(pNode head){
    if(head == NULL){
        printf("Lista vuota!\n");
    }
    else{
        pNode curr = head;
        // Stampo fino al penultimo
        while(curr->next != NULL){
            printf("%d ->", curr->data);
            curr = curr->next;
        }
        // stampo l'ultimo
        printf("%d\n", curr->data);
    }
}

pNode inserisciCoda(pNode head, int new_data){
    // Alloco il nuovo nodo
    pNode new = (pNode)malloc(sizeof(Node));
    if(new == NULL){
        printf("Errore di allocazione\n");
        return head;
    }
    new->data = new_data;
    new->next = NULL;

    // Verifico che la lista sia allcocata, altrimenti il nuovo nodo è il primo
    if(head == NULL) return new;

    // Scorro la lista fino alla fine
    pNode curr = head;
    while(curr->next != NULL) curr = curr->next;
    
    // curr è l'ultimo elemento, quindi attacco new
    curr->next = new;

    return head;
}

pNode inserisciTesta(pNode head, int new_data){
    // Alloco il nuovo nodo
    pNode new = (pNode)malloc(sizeof(Node));
    if(new == NULL){
        printf("Errore di allocazione\n");
        return head;
    }
    new->data = new_data;
    new->next = NULL;

    new->next = head;

    return new;
}

pNode inserisciPos(pNode head, int new_data, int index) {
    // Controllo se l'indice è valido
    if (index < 0) {
        printf("Indice %d non valido\n", index);
        return head;
    }

    // Caso speciale: lista vuota
    if (head == NULL) {
        if (index == 0) {
            return inserisciTesta(head, new_data);
        } else {
            printf("Lista vuota, impossibile inserire in posizione %d.\n", index);
            return head;
        }
    }

    // Caso speciale: inserimento in testa
    if (index == 0) {
        return inserisciTesta(head, new_data);
    }

    // Alloco il nuovo nodo
    pNode new = (pNode)malloc(sizeof(Node));
    if (new == NULL) {
        printf("Errore di allocazione\n");
        return head;
    }
    new->data = new_data;
    new->next = NULL;

    int pos = 0;
    pNode curr = head, prec = NULL;

    while (curr != NULL && pos < index) {
        prec = curr;
        curr = curr->next;
        pos++;
    }

    // Verifica se l'indice è fuori dai limiti
    if (pos != index) {
        printf("Indice %d fuori dai limiti.\n", index);
        free(new);
        return head;
    }

    // Inserimento del nodo
    prec->next = new;
    new->next = curr;

    return head;
}

int listaLen(pNode head){
    int len = 0;
    pNode curr = head;

    while(curr != NULL){
        curr = curr->next;
        len ++;
    }

    return len;
}

int listaMax(pNode head, int* err){
    // lista vuota
    if(head == NULL){
        printf("Lista vuota\n");
        *err = 1;
        return 0;
    }

    // altrimenti
    *err = 0;
    int max = head->data;
    pNode curr = head;

    while(curr != NULL){
        if(max < curr->data) max = curr->data;
        curr = curr->next;
    }

    return max;
}

float listaMedia(pNode head, int* err){
    // lista vuota
    if(head == NULL){
        printf("Lista vuota\n");
        *err = 1;
        return 0;
    }

    // altrimenti
    *err = 0;
    float media = 0;
    int len = 0;
    pNode curr = head;

    while(curr != NULL){
        media += curr->data;
        curr = curr->next;
        len++;
    }

    return media/len;
}

int cercaElemento(pNode head, int value){
    pNode curr = head;
    
    while(curr != NULL){
        if(curr->data == value) return 1;
        curr = curr->next;
    }

    return 0;
}

void eliminaLista(pNode head){
    pNode curr = head;

    while(head != NULL){
        curr = head;
        head = head->next;

        free(curr);
    }
}

pNode funzione(pNode head, int k)
    {
        if(head==NULL)
            return head;
    pNode scorrilista=head;
    while(scorrilista!=NULL)
        {
            if(scorrilista->data==k)
                {
                    pNode new=(pNode)malloc(sizeof(Node));
                    new->data=k;
                    if(scorrilista==head)
                        {
                            new->next=head;
                            return new;
                        }
                    else
                    {
                        new->next=scorrilista->next;
                        scorrilista->next=new;
                        return head;
                    }
                }
            scorrilista=scorrilista->next;
        }
    return head;
    }
