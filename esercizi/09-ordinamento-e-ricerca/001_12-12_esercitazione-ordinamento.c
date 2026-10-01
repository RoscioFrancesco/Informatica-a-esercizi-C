//
//  main.c
//  esercitazione ordinamento
//
//  Created by Francesco Roscio Ricon on 12/12/25.
// in modo iterativo
//  faccio selection sort parto fa inizio array e verifico se il successivo è più grande oppure no, scorro tutto l'array.
// 1,3,9,7,5
// parto da 1 e verifico che è più picccolo di tutti gli altri elementi del dell'array
// uso 2 indici per scorreretutto array e uno per scorrere da elemento subito successivo (i mi scorre tutto e j è quello del loop interno )
// alla fine del primo loop l'elemento più piccolo è un prima posizione.
//  arrivato al 9 vedo che 9 è più grande di 7 , li scambio e ho 13597

// altro metodo: bubbl
#include <stdio.h>
#define N 10

// vogli ofare mergesort, bubble sort;
// l'arrya è passato per riferiemtno
void bubbleSort(int [], int);
void mergeSort(int v[], int start, int end);
void selectionSort(int [], int);
void stamp(int v[], int dim);
void copiaArray(int src[], int dest[], int dim);
void merge(int v[], int start, int end, int mid);

int main(){
    int v[N]={2,4,1,5,6,9,8,3,15,19};
    int t[N];
    stamp(v, 10);
    copiaArray(v, t, 10);
    mergeSort(t, 0, N-1);
    printf("\n");
    stamp(t, 10);
}
void selectionSort(int v[], int dim)
    {
    for(int i=0; i<dim; i++)
        {
            for(int j=i+1; j<dim; j++) // perchè gli elementi prima di i li ho già ordianti agli step precedenti
                {
                    if(v[i]>v[j]) // allora v[j] deve andare al posto di v[i] e vi in vj faccio un temp(3 biccheri)
                        {
                            int temp=v[j];
                            v[j]=v[i];
                            v[i]=temp;
                        }
                }
        }
    }
void stamp(int v[], int dim)
    {
    int i;
    for(i=0; i<dim; i++)
        {
            printf("%d,", v[i]);
        }
    }
void copiaArray(int src[], int dest[], int dim)
    {
    for(int i=0; i<dim; i++)
        {
            dest[i]=src[i];
        }
    }

// funzione bubble sort, non arrivo fino alla fine; e metto contatore che conta quando scambi, quando il contatore è 0 non ci sono scambi
void bubbleSort(int t[], int dim)
    {
    int i, j, n_swap;
    for(i=0; i<dim-1; i++)
        {
            n_swap=0;
            for(j=0; j<dim-i-1; j++) // j mi determina la finestra, definita va vj e v[j-1] e mi fermo a dim-i-j
                {
                    if(t[j]>t[j+1])
                    {
                        int tmp=t[j];
                        t[j]=t[j+1];
                        t[j+1]=tmp;
                        n_swap++;
                    }
                }
            if(n_swap==0)
                break;
        }

    }
// fuzione merge sort ricorsivo
void mergeSort(int v[], int start, int end) // faccio parte dividi et impera
    {
        int mid;
        if(start<end)
            {
                mid=(start+end)/2;
                mergeSort(v, start, mid);
                mergeSort(v, mid+1, end);
                merge(v,start, end, mid); // è funzione ausiliaria che la mi fa il merge;
            }
    }
void merge(int v[], int start, int end, int mid) // mi devo reare indici che partono da start e mid per scorrere e fare il merge
    {
        int i=start, j=mid+1, k=start, copy[N]; // copy è array di appoggio k è l'indice di copia nell'array di support
        while (i<=mid && j<=end) // copia finoc a che una non si esaurisce
            {
                if(v[i]>v[j])
                {
                    copy[k]=v[j];
                    j++;
                }
                else
                {
                    copy[k]=v[i];
                    i++;
                }
                k++;
                
            }
        // uscito da questo while una delle due metà ha finito gli elementi
        while(i<=mid)
            {
                copy[k]=v[i];
                k++;
                i++;
            }
        while(j<=end)
            {
                copy[k]=v[j];
                k++;
                j++;
            }
        for(i=start; i<=end; i++)
            {
                v[i]=copy[i];
            }
        
    }
