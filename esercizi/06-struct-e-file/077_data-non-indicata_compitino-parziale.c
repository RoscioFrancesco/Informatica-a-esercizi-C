//
//  main.c
//  compitino_parziale
//
#include <stdio.h>
#include <string.h>


typedef struct {
    char piatto[100];
    int calorie;
} portata;


typedef struct {
    portata primo;
    portata secondo;
    portata frutta;
    portata dolce;
} pasto;


typedef struct {
    pasto menu[10];
    int numPasti;
} menu;

void stampaMenu (menu m);
void sommePasti(menu m, int calorie_pasto[], int *len_caloriepasto);
void eliminaPastiIpercalorici(menu *m, int caloriedisoglia, int *numeropastiipercalorici, int calorie_pasto[]);
int main(void) {
    menu m = {
        {{{"Risotto ai funghi",720},{"Salmone al forno",520},{"Pera",95},{"Panna cotta",360} },
         {{"Penne al pesto",700},{"Vitello tonnato",560},{"Banana",105},{"Cheesecake",430} },
         {{"Minestrone",250},{"Bresaola rucola",300},{"Arancia",70},{"Sorbetto",160} },
         {{"Maccheroni ala gricia",950},{"Costata di manzo",850},{"Mela",80},{"Tiramisu",420} },
         {{"Lasagne",820},{"Costata di manzo",850},{"Kiwi",60},{"Cannolo",440} },
         {{"Gnocchi burro e salvia",680},{"Orata alla piastra",410},{"Fragole",50},{"Gelato",220} }
        },6};
    int calorie_pasti[10];
    int i=0;
    int sogliacalorica;
    int numeropastiipercalorici=0;
    stampaMenu(m);
    int len_caloriepasto=0; // lunghezza dell'array
    sommePasti(m, calorie_pasti, &len_caloriepasto);
    for(i=0; i<len_caloriepasto; i++)
        {
            printf("%d\n", calorie_pasti[i]);
        }
    printf("Inserire soglia calorica");
    scanf("%d", &sogliacalorica);
    eliminaPastiIpercalorici(&m, sogliacalorica, &numeropastiipercalorici, calorie_pasti);
    stampaMenu(m);
    printf("%d", numeropastiipercalorici);
}

void stampaMenu (menu m)
    {
    int scorrimenu=0;
    int scorripasto=0;
    int numero_pasti=m.numPasti;
    for(scorrimenu=0; scorrimenu<numero_pasti; scorrimenu++)
        {
            printf("pasto numero:%d\n", scorrimenu+1);
            printf("Primo: %s, calorie: %d\n", m.menu[scorrimenu].primo.piatto, m.menu[scorrimenu].primo.calorie);
            printf("Secondo: %s, calorie: %d\n", m.menu[scorrimenu].secondo.piatto, m.menu[scorrimenu].secondo.calorie);
            printf("Frutta: %s, calorie: %d\n", m.menu[scorrimenu].frutta.piatto, m.menu[scorrimenu].frutta.calorie);
            printf("Dolce: %s, calorie: %d\n", m.menu[scorrimenu].dolce.piatto, m.menu[scorrimenu].dolce.calorie);
            printf("\n");
                
        }
}
void sommePasti(menu m, int calorie_pasto[], int *len_caloriepasto)
    {
    int scorrimenu=0;
    int scorriportate=0;
    for(scorrimenu=0; scorrimenu<m.numPasti; scorrimenu++)
        {
            calorie_pasto[scorrimenu]=m.menu[scorrimenu].primo.calorie+m.menu[scorrimenu].secondo.calorie+m.menu[scorrimenu].frutta.calorie+m.menu[scorrimenu].dolce.calorie;
            (*len_caloriepasto)++;
        }// a scorrimenu =0 corrispondono le calorie del pasto 0;
    
    }
void eliminaPastiIpercalorici(menu *m, int caloriedisoglia, int *numeropastiipercalorici, int calorie_pasto[])
    {
    int numero_pasti=m->numPasti;
    int scorri_menu=0;
    menu temp;
    int i;
    int contatore=0;
    for(scorri_menu=0; scorri_menu<numero_pasti; scorri_menu++)
        {
            if(calorie_pasto[scorri_menu]<caloriedisoglia)
                {
                    
                    strcpy(temp.menu[contatore].primo.piatto, m->menu[scorri_menu].primo.piatto);
                    strcpy(temp.menu[contatore].secondo.piatto, m->menu[scorri_menu].secondo.piatto);
                    strcpy (temp.menu[contatore].dolce.piatto, m->menu[scorri_menu].dolce.piatto);
                    strcpy (temp.menu[contatore].frutta.piatto, m->menu[scorri_menu].frutta.piatto);
                    temp.menu[contatore].primo.calorie=m->menu[scorri_menu].primo.calorie;
                    temp.menu[contatore].secondo.calorie=m->menu[scorri_menu].secondo.calorie;
                    temp.menu[contatore].frutta.calorie=m->menu[scorri_menu].frutta.calorie;
                    temp.menu[contatore].dolce.calorie=m->menu[scorri_menu].dolce.calorie;
                    contatore++;
                }
            if(calorie_pasto[scorri_menu]>caloriedisoglia)
                (*numeropastiipercalorici)++;
        }
        temp.numPasti=contatore;
    for(scorri_menu=0; scorri_menu<contatore; scorri_menu++)
        {
            m->menu[scorri_menu]=temp.menu[scorri_menu];
            
        }
    
    m->numPasti=temp.numPasti;
    }
