//
//  main.c
//  esercitazione lista
//
//  Created by Francesco Roscio Ricon on 01/12/25.
//ho lista di stringhe e un prefisso fare funzione che copia le stringhe che iniziano con il prefisso in un0altra stringa

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
typedef char Stringa[N];
typedef  struct NodeStruct
{
    Stringa data;
    struct NodeStruct *next;
}Node;
typedef Node *pNode;
pNode funzione(pNode head1, pNode head2, Stringa prefix);
int controllaPrefisso(Stringa, Stringa);
pNode inserisciInCoda(pNode l, Stringa x);
int main() {
    // popolare lista
    pNode lista1=NULL, lista2=NULL;
    Stringa prefisso;
    lista2 = funzione(lista1, lista2, prefisso);
}
int controllaPrefisso(Stringa s, Stringa prefisso)
    {
    int len_prefix=strlen(prefisso);
    if(strlen(s)<len_prefix)
        return 0;
    int i=0;
    for(i=0; i<len_prefix; i++)
        {
            if(s[i]!=prefisso[i])
                return 0;
        }
    return 1;
    }
pNode funzione(pNode head1, pNode head2, Stringa prefix)
    {
        if(head1==NULL)
            {
                printf("Errore");
                return head2;
            }
    pNode curr=head1; //puntatore temporaneo per non perdere la testa della lista
    // scorro la lista fino a quando il cur non è null
    while (curr!=NULL)
        {
            if(controllaPrefisso(curr->data, prefix)) // se è verificata la inserisco in coda;
                head2=inserisciInCoda(head2, curr->data);
            curr=curr->next;
        }
    return head2;
    }


pNode inserisciInCoda(pNode l, Stringa x)
{
    pNode curr = l, pnew;
    pnew = (pNode)malloc(sizeof(Node));
    strcpy(pnew->data, x);
    pnew->next = NULL; // tanto sar‡ in coda

    // caso l Ë lista vuota
    if(l == NULL)
        return pnew;

    // sono certo che curr non sia NULL, quindi dereferenzio.
    // cerco ultimo nodo, quello che punta a NULL
    while(curr->next!= NULL)
    {
        curr = curr->next;
    }
    curr->next = pnew;
    // restituisco testa originale
    return l;

}
// funzione per eliminare n esimo nodo con funzione ricorsiva
pNode Elimina(pNode head, int pos)
    {
        if(pos<0)
            return head;
        if(head==NULL)
            return head;
        if(pos==0)
        {
            pNode temp=head;
            head=head->next;
            free(temp);
            return head;
        }
    head->next=Elimina(head->next, pos-1); // ritorno quello dopo
    return head; // quello che voglio passarmi in mano prima
    }
pNode Eliminapositer(pNode head, int index)
    {
        if(index<0)
            return head;
        if(head==NULL)
            return head;
        if(index==0)
        {
            pNode temp=head;
            head=head->next;
            free(temp);
            return head;
        }
        pNode cur=head, prec=NULL;
        int pos=0;
        while(pos<index && cur!=NULL)
            {
                prec=cur;
                cur=cur->next;
                pos++;
            }
        if(cur==NULL)// ho sforato la lista
            {
                printf("Indice troppo grande");
            }
        prec->next=cur->next;
        free(cur);
        return head;
    }
