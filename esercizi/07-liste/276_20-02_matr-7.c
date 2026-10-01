//
//  main.c
//  matr 7
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//
#include <stdio.h>
#define N 100
#include <stdlib.h>

void inizializza(char mat[N][N]);
void stampa(char mat[N][N]);

typedef struct EL{
    int grado;
    int coeff;
    struct EL   *next;
}Monomio;
typedef Monomio *Polinomio;

Polinomio inseriscincoda(Polinomio head, int grado, int coeff);
int calcola(Polinomio head, int x);
Polinomio inserimentoP();
int calcola(Polinomio head, int x);
void disegna(char mat[N][N], Polinomio head);

int main() {
    char canvas[N][N];

    inizializza(canvas);
    
    Polinomio p=inserimentoP();
    disegna(canvas, p);
    stampa(canvas);
}

void inizializza(char mat[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            mat[r][c] = ' ';   // spazio
        }
    }
}

void stampa(char mat[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            printf("%c", mat[r][c]);
        }
        printf("\n");
    }
}
Polinomio inseriscincoda(Polinomio head, int grado, int coeff)
    {
        if(head==NULL)
            {
                Polinomio new=(Polinomio)malloc(sizeof(*new));
                new->next=NULL;
                new->coeff=coeff;
                new->grado=grado;
                return new;
            }
    head->next=inseriscincoda(head->next, grado, coeff);
    return head;
    }
Polinomio inserimentoP()
    {
    int grado=0;
    printf("Inserire grado polinomio");
    scanf("%d", &grado);
    Polinomio new=NULL;
    for(int i=0; i<=grado; i++)
        {
            int coeff=0;
            printf("inserirere coeff monomio di grado %d",i);
            scanf("%d",&coeff);
            if(coeff!=0)
                {
                    new=inseriscincoda(new, i, coeff);
                }
        }
    return new;
    }
int calcola(Polinomio head, int x)
    {
        if(head==NULL)
            return 0;
        int somma=0;
        while(head!=NULL)
            {
                int pot=1;
                for(int i=0; i<head->grado; i++)
                    {
                        pot=pot*x;
                    }
                somma=somma+(head->coeff)*pot;
                head=head->next;
            }
    return somma;
    }
void disegna(char mat[N][N], Polinomio head)
    {
    for(int c=0; c<N; c++)
        {
            int val=calcola(head, c);
            if(val<N && val>=0)
                {
                    mat[N-1-val][c]='.';
                }
        }
    }
