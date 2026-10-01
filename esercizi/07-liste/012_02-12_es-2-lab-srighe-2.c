//  Created by Francesco Roscio Ricon on 02/12/25.



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct
    {
    char lettera;
    int x;
    int y;
}Punto_t;
typedef struct El
{
    Punto_t punto_del_poligono;
    struct El *next;
}poligono;
typedef poligono *puntatore_al_poligono;
puntatore_al_poligono acqusiscipunti(puntatore_al_poligono p);
float calcoladistanza(puntatore_al_poligono a, puntatore_al_poligono b);
int calcola_perimetro(puntatore_al_poligono p);
int main() {
    puntatore_al_poligono p=NULL;
    p=acqusiscipunti(p);
    float perimetro;
    perimetro=calcola_perimetro(p);
    printf("\n%f", perimetro);
}
puntatore_al_poligono acqusiscipunti(puntatore_al_poligono p)
    {
    int vertici;
    puntatore_al_poligono new, head=p;
    printf("Quanti vertici ha il poligono?");
    scanf("%d", &vertici);
    int i;
    for(i=0; i<vertici; i++)
        {
            new=(puntatore_al_poligono)malloc(sizeof(poligono));
            printf("Inserire la x del vertice %d", i+1);
            scanf("%d", &new->punto_del_poligono.x);
            printf("Inserire la y del vertice %d", i+1);
            scanf("%d", &new->punto_del_poligono.y);
            new->next=NULL;
            if(p==NULL)
            {
                p=new;
                head=p;
            }
            else
                {
                    p->next=new;
                    p=p->next;
                }
        }
        return head;
    }
// 2) calcoli il perimetro del poligono
int calcola_perimetro(puntatore_al_poligono p)
    {
    int somma=0;
    puntatore_al_poligono head=p;
    while(p->next!=NULL)
        {
            somma=somma+calcoladistanza(p, p->next);
            p=p->next;
        }
    somma=somma+calcoladistanza(p, head);
    return somma;
    }
float calcoladistanza(puntatore_al_poligono a, puntatore_al_poligono b)
    {
    float dist;
    dist=sqrtf((((a->punto_del_poligono.x-b->punto_del_poligono.x)*(a->punto_del_poligono.x-b->punto_del_poligono.x))+((a->punto_del_poligono.y-b->punto_del_poligono.y)*(a->punto_del_poligono.y-b->punto_del_poligono.y))));
    return dist;
    }
