//  Created by Francesco Roscio Ricon on 28/02/26.


typedef struct {
    int giorno; /* tra 1 e 31 */
    int mese; /* tra 1 e 12 */
    int anno; /* tra 2003 e 2012 */
} data;

typedef struct {
    data giorno;
    float livelloPM10;
    float livelloBenzene;
    float livelloAnidrideSolforosa;
} rilievoGiornaliero;

typedef struct     {
    char quartiere[100]; /* nome del quartiere */
    rilievoGiornaliero rilievi[3653]; /* 3653 rilievi per 10 anni in ordine di data */
} rilieviQuartiere; /* dati monitorati nell’anno per un singolo quartiere */
int ver(rilievoGiornaliero R,  float maxPM10, float maxBZ, float maxAS);
typedef rilieviQuartiere rilieviGlobali[100]; /* dati monitorati nell’anno per 100 quartieri milanesi */
int ver(rilievoGiornaliero R,  float maxPM10, float maxBZ, float maxAS);
//int f(rilieviGlobali rg, float sogliaPM10, float sogliaBenzene, float sogliaAnidrideSolforosa);

int ver(rilievoGiornaliero R,  float maxPM10, float maxBZ, float maxAS)
    {
        int count=0;
        if(R.livelloAnidrideSolforosa>maxAS)
            count++;
        if(R.livelloBenzene>maxBZ)
            count++;
        if(R.livelloPM10>maxPM10)
            count++;
        if(count>=2)
            return 1;
        return 0;
    }
int max_rilievo(rilieviQuartiere rilievi, float maxPm, float maxBZ, float maxAS)
    {
        int max=0;
    for(int i=0; i<3653; i++)
        {
            if(ver(rilievi.rilievi[i],maxPm, maxBZ, maxAS))
                {
                    int j=0;
                    for(j=0; j+i<3653; j++)
                        {
                            if(ver(rilievi.rilievi[i+j],maxPm, maxBZ, maxAS)==0)
                                break;
                        }
                    if(j>max)
                        max=j;
                }
        }
        return max;
    }
int f(rilieviGlobali rg, float sogliaPM10, float sogliaBenzene, float sogliaAnidrideSolforosa)
    {
    int max=0;
    for(int i=0; i<100; i++)
        {
            int num=max_rilievo(rg[i], sogliaPM10, sogliaBenzene, sogliaAnidrideSolforosa);
            if(num>max)
                max=num;
        }
    return max;
    }
