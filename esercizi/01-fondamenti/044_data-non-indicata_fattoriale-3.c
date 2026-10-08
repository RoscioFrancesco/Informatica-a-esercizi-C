/*
 * ESERCIZIO: Calcolo del coefficiente binomiale
 * 
 * Scrivere un programma in linguaggio C che calcoli il coefficiente del k-esimo 
 * termine dello sviluppo della potenza del binomio (a+b)^n.
 * 
 * Il programma deve:
 * 1. Richiedere l'inserimento dell'esponente n.
 * 2. Richiedere l'inserimento dell'indice k del termine desiderato.
 * 3. Effettuare un controllo di validità degli input (mostrando errore se 
 *    i valori non sono strettamente positivi, se n < k, o se k=0 o k=n).
 * 4. Calcolare sequenzialmente tramite cicli iterativi:
 *    - Il fattoriale di n (n!)
 *    - Il fattoriale di k (k!)
 *    - Il fattoriale di (n-k)!
 * 5. Calcolare e stampare il risultato finale con la formula:
 *    R = n! / (k! * (n-k)!)
 * 
 * Nota: non utilizzare funzioni esterne, ma svolgere i calcoli dei fattoriali
 * all'interno del main. Gestire la pulizia del buffer di input.
 */
#include <stdio.h>
int main() {
    int n, s, x, k, a, b, j, f, c, r;
    printf("Inserire l'esponente n a cui si vuole elvare a+b:");
    scanf("%d", &n);fflush(stdin);// questo è n fattoriale
    printf("Inserire il k esimo termine di cui si desidera il coefficiente, si consideri che a elevato alla n ha k=0:");
    scanf("%d", &k);fflush(stdin); // questo è il termine k
    if (k == 0 || n == k || n <= 0 || k <= 0 || n < k)
    printf("Errore, rivedi il valore di k");
    else
    x = n-1;
    s = n;
    while (x > 0) {
        s = s * x;
        x = x - 1;
    } // a qs punto ho calcolato n fattoriale come s
                             //calcolo k fattoriale
               b = k-1;
               a = k;
               while (b > 0) {
               a = a * b;
               b = b - 1;
                 } // ho calolato k fattoriale come a
    j = n-k;     // calcolo n-k fattoriale = f, sono consapevole che è il metodo più stupido
    c = j-1;
    f = j;
    while (c > 0) {
        f = f * c;
        c = c - 1;
    }
    
    r = s / (a * f);
    printf("\nIl risultato è %d\n", r);

}
