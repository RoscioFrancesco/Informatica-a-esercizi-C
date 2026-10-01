//  Created by Francesco Roscio Ricon on 01/12/25.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Per funzioni su stringhe

// Macro
#define LEN 100

// Tipo Stringa
typedef char Stringa[LEN];

// Dati
typedef struct NodeStruct {
    Stringa data;
    struct NodeStruct *next;
} Node;
typedef Node *pNode;

// Prototipi
void stampaLista(pNode);
pNode inserisciCoda(pNode, Stringa);
pNode inserisciTesta(pNode, Stringa);
pNode inserisciPos(pNode, Stringa, int);
pNode inserisciOrdinatoNoRip(pNode, Stringa);
int listaLen(pNode);
int cercaElemento(pNode, Stringa);
void eliminaLista(pNode);
pNode eliminaPos(pNode, int);
pNode eliminaElementiValore(pNode, Stringa);
pNode funzione(int indice, pNode lista1, pNode lista2);
pNode funzione_ric(int indice, pNode lista1, pNode lista2);
// Main
int main() {
    pNode head = NULL; // Inizializzazione della lista
    pNode head2=NULL;
    Stringa s, mia;

    printf("Creazione lista con inserimento in testa:\n");
    strcpy(s, "Ciao");
    head = inserisciTesta(head, s);
    strcpy(s, "Mondo");
    head = inserisciTesta(head, s);
    strcpy(s, "Test");
    head = inserisciTesta(head, s);
    stampaLista(head);
    strcpy(mia, "a");
    head2 = inserisciTesta(head2, mia);
    strcpy(mia, "b");
    head2 = inserisciTesta(head2, mia);
    strcpy(mia, "c");
    head2 = inserisciTesta(head2, mia);
    stampaLista(head2);
    head2=funzione_ric(5, head, head2);
    stampaLista(head2);
}

// Funzioni
void stampaLista(pNode head) {
    if (head == NULL) {
        printf("Lista vuota!\n");
    } else {
        pNode curr = head;
        while (curr != NULL) {
            printf("%s -> ", curr->data);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

pNode inserisciCoda(pNode head, Stringa new_data) {
    pNode new_node = (pNode)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore di allocazione\n");
        return head;
    }
    strcpy(new_node->data, new_data);
    new_node->next = NULL;

    if (head == NULL) return new_node;

    pNode curr = head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = new_node;

    return head;
}

pNode inserisciTesta(pNode head, Stringa new_data) {
    pNode new_node = (pNode)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore di allocazione\n");
        return head;
    }
    strcpy(new_node->data, new_data);
    new_node->next = head;

    return new_node;
}

pNode inserisciPos(pNode head, Stringa new_data, int index) {
    if (index < 0) {
        printf("Indice %d non valido\n", index);
        return head;
    }

    if (index == 0) return inserisciTesta(head, new_data);

    pNode new_node = (pNode)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore di allocazione\n");
        return head;
    }
    strcpy(new_node->data, new_data);

    int pos = 0;
    pNode curr = head, prec = NULL;

    while (curr != NULL && pos < index) {
        prec = curr;
        curr = curr->next;
        pos++;
    }

    if (pos != index) {
        printf("Indice %d fuori dai limiti.\n", index);
        free(new_node);
        return head;
    }

    prec->next = new_node;
    new_node->next = curr;

    return head;
}

pNode inserisciOrdinatoNoRip(pNode head, Stringa new_data) {
    pNode curr = head, prec = NULL;

    while (curr != NULL && strcmp(new_data, curr->data) > 0) {
        prec = curr;
        curr = curr->next;
    }

    if (curr != NULL && strcmp(new_data, curr->data) == 0) {
        printf("Valore '%s' già presente, non inserito.\n", new_data);
        return head;
    }

    pNode new_node = (pNode)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore di allocazione\n");
        return head;
    }
    strcpy(new_node->data, new_data);
    new_node->next = curr;

    if (prec == NULL) {
        return new_node;
    } else {
        prec->next = new_node;
    }

    return head;
}

int listaLen(pNode head) {
    int len = 0;
    pNode curr = head;
    while (curr != NULL) {
        curr = curr->next;
        len++;
    }
    return len;
}

int cercaElemento(pNode head, Stringa value) {
    pNode curr = head;
    while (curr != NULL) {
        if (strcmp(curr->data, value) == 0) return 1;
        curr = curr->next;
    }
    return 0;
}

void eliminaLista(pNode head) {
    pNode curr;
    while (head != NULL) {
        curr = head;
        head = head->next;
        free(curr);
    }
}

pNode eliminaPos(pNode head, int index) {
    if (index < 0) {
        printf("Indice %d non valido\n", index);
        return head;
    }

    if (head == NULL) return head;

    if (index == 0) {
        pNode temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    pNode curr = head, prec = NULL;
    int pos = 0;

    while (curr != NULL && pos < index) {
        prec = curr;
        curr = curr->next;
        pos++;
    }

    if (curr == NULL) return head;

    prec->next = curr->next;
    free(curr);

    return head;
}

pNode eliminaElementiValore(pNode head, Stringa value) {
    pNode curr = head, prec = NULL, tmp;

    while (curr != NULL && strcmp(curr->data, value) == 0) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    head = curr;

    while (curr != NULL) {
        if (strcmp(curr->data, value) == 0) {
            tmp = curr;
            prec->next = curr->next;
            curr = curr->next;
            free(tmp);
        } else {
            prec = curr;
            curr = curr->next;
        }
    }

    return head;
}
pNode funzione(int indice, pNode lista1, pNode lista2) // iterativa
    {
    pNode temp1=lista1;
    pNode temp2=lista2;
    while(temp1!=NULL && temp2!=NULL && indice!=0)
    {
        temp2=temp2->next;
        temp1=temp1->next;
        indice--;
    }
    if(indice==0)
        {
            strcpy(temp2->data,temp1->data);
        }
    return lista2;
    
    }
// la faccio ricorsiva
pNode funzione_ric(int indice, pNode lista1, pNode lista2)
    {
        if(lista1==NULL|| lista2 == NULL)
            return lista2;
        if(indice==0)
            {
                strcpy(lista2->data,lista1->data);
            }
        lista2->next=funzione_ric(indice-1, lista1->next, lista2->next);
        return lista2;
    }
