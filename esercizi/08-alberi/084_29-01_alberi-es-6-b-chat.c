//
//  main.c
//  alberi es 6 b chat
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;
typedef Node * Albero;
/* Lista di interi: rappresenta un cammino */
typedef struct IntList {
    int val;
    struct IntList* next;
} IntList;
typedef IntList* Cammino;
/* Lista di cammini (lista di liste) */
typedef struct PathList {
    IntList* path;           // un cammino
    struct PathList* next;   // prossimo cammino
} PathList;
typedef PathList *ListadiListe;
/* =======================
   UTILITY: creazione nodi
   ======================= */

Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

/* =======================
   LISTE: operazioni ricorsive
   (NO CICLI)
   ======================= */

/* aggiunge in testa: O(1) */
IntList* pushFront(IntList* xs, int v) {
    IntList* n = (IntList*)malloc(sizeof(IntList));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = xs;
    return n;
}

/* libera lista di interi */
void freeIntList(IntList* xs) {
    if (!xs) return;
    freeIntList(xs->next);
    free(xs);
}

/* copia lista di interi */
IntList* copyIntList(IntList* xs) {
    if (!xs) return NULL;
    IntList* n = (IntList*)malloc(sizeof(IntList));
    if (!n) { perror("malloc"); exit(1); }
    n->val = xs->val;
    n->next = copyIntList(xs->next);
    return n;
}

/* reverse ricorsivo (perché il cammino lo costruiamo in testa) */
IntList* reverseIntList(IntList* xs) {
    if (!xs || !xs->next) return xs;
    IntList* rest = reverseIntList(xs->next);
    xs->next->next = xs;
    xs->next = NULL;
    return rest;
}

/* concatena due PathList: ritorna la testa.
   (per comodità: aggiungo sempre in testa, poi unisco) */
PathList* concatPathList(PathList* a, PathList* b) {
    if (!a) return b;
    a->next = concatPathList(a->next, b);
    return a;
}

/* libera lista di cammini */
void freePathList(PathList* ps) {
    if (!ps) return;
    freePathList(ps->next);
    freeIntList(ps->path);
    free(ps);
}

/* =======================
   CHECK: strettamente crescente
   ======================= */

bool isStrictlyIncreasing(IntList* path) {
    // path è in ordine radice->foglia
    if (!path || !path->next) return true;
    return (path->val < path->next->val) && isStrictlyIncreasing(path->next);
}

/* =======================
   COSTRUZIONE LISTA CAMMINI (RICORSIVA)
   ======================= */

/* helper:
   - node: nodo corrente
   - currentRev: cammino corrente MA in ordine inverso (foglia->radice) perché pushFront
   ritorna: lista di cammini (PathList*)
*/
//PathList* increasingPathsRec(Node* node, IntList* currentRev) {
//    if (!node) return NULL;
//
//    // estendo il cammino (in testa)
//    IntList* extendedRev = pushFront(currentRev, node->val);
//
//    // se foglia: controllo e (se ok) aggiungo copia del cammino
//    if (!node->left && !node->right) {
//        IntList* path = copyIntList(extendedRev);   // copia del reverse
//        path = reverseIntList(path);                // metto in ordine radice->foglia
//
//        PathList* out = NULL;
//        if (isStrictlyIncreasing(path)) {
//            out = (PathList*)malloc(sizeof(PathList));
//            if (!out) { perror("malloc"); exit(1); }
//            out->path = path;
//            out->next = NULL;
//        } else {
//            freeIntList(path);
//        }
//
//        // devo liberare solo il nodo aggiunto (extendedRev), NON currentRev (che è condiviso)
//        free(extendedRev);
//        return out;
//    }
//
//    // ricorsione sui sottoalberi
//    PathList* leftPaths  = increasingPathsRec(node->left,  extendedRev);
//    PathList* rightPaths = increasingPathsRec(node->right, extendedRev);
//
//    // pulizia del nodo di cammino aggiunto
//    free(extendedRev);
//
//    // unisco i risultati
//    return concatPathList(leftPaths, rightPaths);
//}
//
//PathList* increasingPaths(Node* root) {
//    return increasingPathsRec(root, NULL);
//}

/* =======================
   STAMPA (NO CICLI)
   ======================= */

void printIntList(IntList* xs) {
    if (!xs) return;
    printf("%d", xs->val);
    if (xs->next) printf(" -> ");
    printIntList(xs->next);
}

void printPathList(PathList* ps) {
    if (!ps) return;
    printf("[ ");
    printIntList(ps->path);
    printf(" ]\n");
    printPathList(ps->next);
}

/* =======================
   FREE ALBERO (NO CICLI)
   ======================= */

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* =======================
   ESEMPI / MAIN
   ======================= */
ListadiListe concatenaLDL(ListadiListe a, ListadiListe b);
ListadiListe f(Albero tree, int prec, int hasprec, Cammino camcorr);
ListadiListe aggiungiLDL(ListadiListe head, Cammino cam);
Cammino copiacammino(Cammino cam);
ListadiListe increasingPaths(Albero tree);

int main(void) {
    /*
        ESEMPIO 1:

              5
             / \
            3   8
           / \   \
          2   4   9

        Cammini radice-foglia:
        5-3-2  (NO, decresce)
        5-3-4  (NO, 5->3 decresce)
        5-8-9  (SI: 5 < 8 < 9)
    */
    Node* t1 =
        newNode(5,
            newNode(3,
                newNode(2, NULL, NULL),
                newNode(4, NULL, NULL)
            ),
            newNode(8,
                NULL,
                newNode(9, NULL, NULL)
            )
        );

    printf("ESEMPIO 1 - cammini strettamente crescenti:\n");
    PathList* res1 = increasingPaths(t1);
    if (!res1) printf("(nessun cammino)\n");
    else printPathList(res1);

    freePathList(res1);
    freeTree(t1);

    /*
        ESEMPIO 2:

               1
             /   \
            2     3
           / \   / \
          4  1  4  10

        Cammini:
        1-2-4   (SI: 1<2<4)
        1-2-1   (NO)
        1-3-4   (SI: 1<3<4)
        1-3-10  (SI: 1<3<10)
    */
    Node* t2 =
        newNode(1,
            newNode(2,
                newNode(4, NULL, NULL),
                newNode(1, NULL, NULL)
            ),
            newNode(3,
                newNode(4, NULL, NULL),
                newNode(10, NULL, NULL)
            )
        );

    printf("\nESEMPIO 2 - cammini strettamente crescenti:\n");
    PathList* res2 = increasingPaths(t2);
    if (!res2) printf("(nessun cammino)\n");
    else printPathList(res2);

    freePathList(res2);
    freeTree(t2);

    return 0;
}
Cammino aggiungival(Cammino head, int x)
    {
        if(head==NULL)
        {
            Cammino new=(Cammino)malloc(sizeof(IntList));
            new->next=NULL;
            new->val=x;
            return new;
        }
    head->next=aggiungival(head->next, x);
    return head;
    }
Cammino copiacammino(Cammino cam)
    {
        if(cam==NULL)
            return cam;
    Cammino new=(Cammino)malloc(sizeof(*new));
    new->val=cam->val;
    new->next=copiacammino(cam->next);
    return new;
    }
ListadiListe aggiungiLDL(ListadiListe head, Cammino cam)
    {
        if(head==NULL)
            {
                ListadiListe new=(ListadiListe)malloc(sizeof(*new));
                new->next=NULL;
                new->path=copiacammino(cam);
                return new;
            }
    head->next=aggiungiLDL(head->next, cam);
    return head;
    }
ListadiListe f(Albero tree, int prec, int hasprec, Cammino camcorr)
    {
        if(tree==NULL)
            return NULL;
        if(hasprec &&(prec>=tree->val))
            return NULL;
    
        Cammino nuovo = copiacammino(camcorr);
        nuovo = aggiungival(nuovo, tree->val);
        if(tree->left==NULL && tree->right==NULL)
        {
            ListadiListe head=NULL;
            head=aggiungiLDL(head, nuovo);
            return head;
        }
    ListadiListe sx=f(tree->left, tree->val, 1, nuovo);
    ListadiListe dx=f(tree->right, tree->val, 1, nuovo);
    return concatenaLDL(sx, dx);
    }
ListadiListe concatenaLDL(ListadiListe a, ListadiListe b)
    {
        if(a==NULL)
            return b;
    a->next=concatenaLDL(a->next, b);
    return a;
    }
ListadiListe increasingPaths(Albero tree)
    {
    ListadiListe head=NULL;
    Cammino cam=NULL;
    head=f(tree, 0, 0, cam);
    return head;
    }
