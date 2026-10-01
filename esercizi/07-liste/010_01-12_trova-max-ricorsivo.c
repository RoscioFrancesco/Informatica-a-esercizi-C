//
//  main.c
//  trova max ricorsivo
//
//  Created by Francesco Roscio Ricon on 01/12/25.
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
pNode trovaMaxRicorsivo(pNode head);
pNode inserisciTesta(pNode, int);

int main() {
    // inizializzo la lista
    pNode head = NULL;
    head = inserisciTesta(head, 10);
    head = inserisciTesta(head, 5);
    head = inserisciTesta(head, 20);
    head = inserisciTesta(head, 15);
    // lista: 15 -> 20 -> 5 -> 10

    // stampo la lista
    printf("Lista creata:\n");
    stampaLista(head);
    printf("\n");

    // trovo il massimo
    pNode maxNode = trovaMaxRicorsivo(head);
    if (maxNode != NULL) {
        printf("Il valore massimo nella lista è: %d\n", maxNode->data);
    } else {
        printf("La lista è vuota.\n");
    }
    return 0;
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
pNode trovaMaxRicorsivo(pNode head)
    {
        if(head==NULL) //la lista è vuota
            return head;
        if(head->next==NULL) // la lista ha un elemento
            return head;
        trovaMaxRicorsivo(head->next);
        if(head->next->data>head->data)
            return head->next;
        else
        {
            return head;
        }
    }
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
