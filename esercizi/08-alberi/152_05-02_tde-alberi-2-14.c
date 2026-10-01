//  Created by Francesco Roscio Ricon on 05/02/26.

#include <stdio.h>
#include <stdlib.h>

#define N 100

/* =========================
   STRUTTURA ALBERO (come da testo)
   NOTA: nel testo dice "ternario" ma qui ci sono solo left/right.
   ========================= */
typedef struct ET {
    int dati[N];              /* vettore nel nodo */
    struct ET *left, *right;  /* figli */
} treeNode;

typedef treeNode* tree;

/* =========================
   PROTOTIPO (DA SVOLGERE)
   ========================= */
int funz(tree albero, int vett[]);
int f(tree T, int V[]);

/* crea un nodo con figli left/right NULL e inizializza dati a 0 */
static tree newNode(void) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    n->left = n->right = NULL;
    for (int i = 0; i < N; i++) n->dati[i] = 0;
    return n;
}

/* riempie i primi k valori del vettore del nodo, il resto resta 0 */
static void setPrefix(tree t, const int a[], int k) {
    if (!t) return;
    if (k > N) k = N;
    for (int i = 0; i < k; i++) t->dati[i] = a[i];
}

/* stampa i primi k valori di un vettore (solo per debug leggibile) */
static void printVecPrefix(const int a[], int k) {
    printf("[");
    for (int i = 0; i < k; i++) {
        printf("%d", a[i]);
        if (i < k - 1) printf(", ");
    }
    printf("]");
}

/* stampa l’albero (preorder) mostrando solo i primi k elementi del vettore dati */
static void printTreePre(tree t, int k, int depth) {
    if (!t) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("NULL\n");
        return;
    }

    for (int i = 0; i < depth; i++) printf("  ");
    printf("Nodo dati[0..%d] = ", k-1);
    printVecPrefix(t->dati, k);
    printf("\n");

    for (int i = 0; i < depth; i++) printf("  ");
    printf("L:\n");
    printTreePre(t->left, k, depth + 1);

    for (int i = 0; i < depth; i++) printf("  ");
    printf("R:\n");
    printTreePre(t->right, k, depth + 1);
}

/* libera l’albero */
static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}
void merge(int v[]);
int funz(tree albero, int vett[]);
void funzione(tree albero, int vett[], int *count);
int main(void) {
    /* =========================
       VETTORE DI RIFERIMENTO V
       =========================
       Per rendere l’esempio leggibile, usiamo solo i primi K valori (K<<N).
       Nel tuo f reale, la permutazione è del vettore di dimensione N.
    */
    int V[N];
    for (int i = 0; i < N; i++) V[i] = 0;

    /* scegliamo un prefisso significativo */
    const int K = 6;
    int prefV[K] = {10, 20, 30, 40, 50, 60};
    for (int i = 0; i < K; i++) V[i] = prefV[i];

    printf("V (prefisso usato nel test) = ");
    printVecPrefix(V, K);
    printf("\n\n");

    /* =========================
       COSTRUZIONE ALBERO DI TEST
       ========================= */
    tree T = newNode();

    /* root: permutazione del prefisso di V */
    int a0[K] = {40, 10, 60, 20, 50, 30};
    setPrefix(T, a0, K);

    /* figlio sinistro: NON permutazione (ripetizione) */
    T->left = newNode();
    int a1[K] = {10, 10, 30, 40, 50, 60};
    setPrefix(T->left, a1, K);

    /* figlio destro: permutazione del prefisso di V */
    T->right = newNode();
    int a2[K] = {60, 50, 40, 30, 20, 10};
    setPrefix(T->right, a2, K);

    /* aggiungo un livello sotto */
    T->right->left = newNode();
    int a3[K] = {10, 20, 30, 40, 50, 60}; /* identico a V -> permutazione */
    setPrefix(T->right->left, a3, K);

    T->right->right = newNode();
    int a4[K] = {10, 20, 30, 40, 50, 999}; /* non permutazione */
    setPrefix(T->right->right, a4, K);

    printf("ALBERO (preorder, mostro solo i primi %d elementi):\n", K);
    printTreePre(T, K, 0);

    
    printf("\nChiamo f(T, V)...\n");
    int ris = funz(T, V);
    printf("Risultato f(T,V) = %d\n", ris);

    /* cleanup */
    freeTree(T);
    return 0;
}



int verificapermutazione(int v_mio[], int vett_nodo[])
    {
    int copia[N];
    for(int i=0; i<N; i++)
        {
            copia[i]=vett_nodo[i];
        }
    merge(v_mio);
    merge(copia);
    for(int i=0; i<N; i++)
        {
            if(v_mio[i]!=copia[i])
                return 0;
        }
        return 1;
    }
void merge(int v[])
    {
    for(int i=0; i<N ; i++)
        {
            for(int j=i+1; j<N; j++)
                {
                    if(v[i] > v[j])
                        {
                            int tmp = v[j];
                            v[j] = v[i];
                            v[i] = tmp;
                        }
                }
        }
    }

void funzione(tree albero, int vett[], int *count)
    {
        if(albero==NULL)
            return;
        if(verificapermutazione(vett, albero->dati)==1)
            (*count)++;
    funzione(albero->left, vett, count);
    funzione(albero->right, vett, count);
    }
int funz(tree albero, int vett[])
    {
    int count=0;
    funzione(albero, vett, &count);
    return count;
    }
