//
//  main.c
//  strighe ultimo esercizio
//
//  Created by Francesco Roscio Ricon on 02/12/25.
//

#include <stdio.h>
#include <stdlib.h>

// Dati
typedef struct NodeStruct {
    int data;
    struct NodeStruct *next;
} Node;
typedef Node *pNode;

// Prototipo
void stampaLista(pNode);
pNode inserisciTesta(pNode, int);
pNode eliminaDuplicatiRicorsivo(pNode);
pNode eliminaElementiUguali(pNode, int);

int main() {
    // inizializzo la lista
    pNode head = NULL;
    head = inserisciTesta(head, 20);
    head = inserisciTesta(head, 10);
    head = inserisciTesta(head, 10);
    head = inserisciTesta(head, 703);
    // lista: 703 -> 10 -> 10 -> 20

    printf("Lista creata:\n");
    stampaLista(head);
    printf("\n");

    // elimino i duplicati
    head = eliminaDuplicatiRicorsivo(head);
    printf("Lista dopo eliminazione dei duplicati:\n");
    stampaLista(head);
    return 0;
}

pNode eliminaElementiUguali(pNode head, int value) {
    // Caso base: lista vuota
    if (head == NULL) return NULL;

    // Caso: il nodo corrente contiene `value`
    if (head->data == value) {
        pNode tmp = head;          // Salvo il nodo corrente
        head = eliminaElementiUguali(head->next, value); // Elimino il resto dei nodi con `value`
        free(tmp);                 // Libero il nodo corrente
        return head;
    }

    // Caso: il nodo corrente non contiene `value
    head->next = eliminaElementiUguali(head->next, value);
    return head;
}

pNode eliminaDuplicatiRicorsivo(pNode head) {
    // Caso base: lista vuota o con un solo elemento
    if (head == NULL || head->next == NULL) return head;

    // Elimino ricorsivamente i duplicati del resto della lista
    head->next = eliminaDuplicatiRicorsivo(head->next);

    // Elimino ricorsivamente tutti i nodi uguali al dato di head
    head->next = eliminaElementiUguali(head->next, head->data);

    return head;
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
