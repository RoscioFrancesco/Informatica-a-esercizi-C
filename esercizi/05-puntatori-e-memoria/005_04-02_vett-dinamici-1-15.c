//
//  main.c
//  vett dinamici 1 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>


int* filtra(int *v, int n, int *new_n);   /* TODO */

/* =========================================================
   UTILITY (QUI I CICLI SONO OK PER TEST)
   ========================================================= */
static int* allocAndFillFromArray(const int *a, int n) {
    int *v = (int*)malloc(sizeof(int) * n);
    if (!v) { perror("malloc"); exit(1); }
    for (int i = 0; i < n; i++) v[i] = a[i];
    return v;
}

static void printVector(const char *label, const int *v, int n) {
    printf("%s (n=%d) = [", label, n);
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i != n - 1) printf(", ");
    }
    printf("]\n");
}

/* (opzionale) calcola media in double, utile per debug nel main */
static double media(const int *v, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += v[i];
    return (n > 0) ? (double)sum / (double)n : 0.0;
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int main(void) {
    /* Test 1: caso "misto" */
    const int a1[] = { 10, 2, 3, 23, 101 };
    int n1 = (int)(sizeof(a1) / sizeof(a1[0]));
    int *v1 = allocAndFillFromArray(a1, n1);

    int new_n1 = 0;
    int *out1 = filtra(v1, n1, &new_n1);   

    printf("=== TEST 1 ===\n");
    printVector("Input", v1, n1);
    printf("Media(input) = %.2f\n", media(v1, n1));
    printVector("Output (solo > media)", out1, new_n1);
    printf("\n");

    free(v1);
    free(out1);

    /* Test 2: tutti uguali -> output vuoto */
    const int a2[] = { 5, 5, 5, 5 };
    int n2 = (int)(sizeof(a2) / sizeof(a2[0]));
    int *v2 = allocAndFillFromArray(a2, n2);

    int new_n2 = 0;
    int *out2 = filtra(v2, n2, &new_n2);

    printf("=== TEST 2 ===\n");
    printVector("Input", v2, n2);
    printf("Media(input) = %.2f\n", media(v2, n2));
    printVector("Output (solo > media)", out2, new_n2);
    printf("\n");

    free(v2);
    free(out2);

    /* Test 3: numeri negativi e positivi */
    const int a3[] = { -3, 0, 7, -1, 5 };
    int n3 = (int)(sizeof(a3) / sizeof(a3[0]));
    int *v3 = allocAndFillFromArray(a3, n3);

    int new_n3 = 0;
    int *out3 = filtra(v3, n3, &new_n3);

    printf("=== TEST 3 ===\n");
    printVector("Input", v3, n3);
    printf("Media(input) = %.2f\n", media(v3, n3));
    printVector("Output (solo > media)", out3, new_n3);
    printf("\n");

    free(v3);
    free(out3);

    /* Nota: se vuoi testare anche n=0, devi decidere come gestirlo nella consegna. */
    return 0;
}

int* filtra(int v[], int n, int *new_n)
    {
        float m=media(v, n);
    int count=0;
    for(int i=0; i<n; i++)
        {
            if(v[i]>m)
                count++;
        }
        *new_n=count;
        int *new=malloc(sizeof(int)*(count));
    int segna=0;
    for(int i=0; i<n; i++)
        {
            if(v[i]>m)
                {
                    new[segna]=v[i];
                    segna++;
                }
        }
    return new;
    }
