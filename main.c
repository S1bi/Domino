#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void selezioneTessera(int a){              //fa la selezione del giusto indice usando un puntatore (basta dargli in input la variabile da cambiare)
    int* ptrA = &a;
    *ptrA = a*2 -2;
}

void genTessere (int *deck, int nTessere) {
    for(int i = 0; i<nTessere*2; i++) {
        srand(time(NULL)*i+time(NULL));
        int r = rand() % 6000;          //creazione numero random tra 1 e 6
        deck[i] = r/1000 + 1;         //inserimento numero per numero in array mano
    }
}

void stampaDeck(int *tessereDeck) {                     //lettura e formattazione dell'array
    printf("DECK: \n");
    for(int i = 0; i < sizeof(*tessereDeck)/sizeof(int)*2; i = i+2) {
        printf("[%d|%d]", tessereDeck[i], tessereDeck[i+1]);                    //stampa delle tessere una a una
    }
}

void stampaTerreno(int *terreno, int dim) {
    printf("CAMPO: \n");
    for(int i = 0; i < dim*2; i = i+2) {
        if(terreno[i+1]!=0)                                                   //così non stampa le caselle vuote
            printf("[%d|%d]", terreno[i], terreno[i+1]);                    //stampa delle tessere una a una
    }
}

void ruotaTessera(int *tessereDeck, int scelta) {
    int tessera = 0;
    do {
        printf("Quale tessera si vuole modificare? Inserire un valore da 1 a %d \n", scelta);
        scanf("%d", &tessera);
    }while(tessera < 0 || tessera > scelta);
    selezioneTessera(tessera);          //seleziono il primo valore della tessera scelta (usare anche per scelta tessera da inserire)
    int temp = tessereDeck[tessera];                //variabile d'appoggio
    tessereDeck[tessera] = tessereDeck[tessera+1];          //tessera selezionata = val successivo
    tessereDeck[tessera+1] = temp;                      //tessera successiva alla selezionata cambiata
    stampaDeck(tessereDeck);
}

int main() {
    int scelta = 0;                 //selezione difficoltà e quantità tessere
    int arrayInserimento[2];        //array di gestione delle tessere da inserire
    do {
        printf("BENVENUTO NEL GIOCO DEL DOMINO! \n"
               "Seleziona la difficoltà: \n"
               "1. Facile (14 tessere);\n"
               "2. Normale (28 tessere);\n"
               "3. Difficile (36 tessere);\n"
               "4. Manuale (scegli il tuo numero di tessere). \n");
        scanf("%d", &scelta);
    }while(scelta < 1 || scelta > 4);

    switch (scelta) {
        case 1: scelta = 14;
            break;
        case 2: scelta = 28;
            break;
        case 3: scelta = 36;
            break;
        default:
            printf("Seleziona il numero di tessere: ");
            scanf("%d", &scelta);
            break;
    }
    int tessereDeck[scelta*2];
    int* deck = &tessereDeck;                   //puntatore array deck
    genTessere(deck, scelta);
    int tessereCampo[scelta*2];
    for(int i=0;i<scelta*2;i++)
        tessereCampo[i] = 0;
    printf("IL GIOCO HA INIZIO \n Le tue tessere sono: \n");
    stampaDeck(deck);

    //IMPLEMENTARE METODO DI CONTROLLO PER FINE PARTITA (CICLO PER SCELTA MOSSA)

    int mossa = 0;
    do {
        printf("\nScegliere la prossima mossa: \n"
               "1. Rotazione di una tessera; \n"
               "2. Inserimento di una tessera; \n"
               //POSSIBILE FUNZIONE AIUTO(?)
               "3. Arrenditi; \n");
        scanf("%d", &mossa);
    }while(mossa > 3 || mossa < 1);             //controllo l'input utente
    switch (mossa) {                        //switch case di selezione della mossa
        case 1:
            ruotaTessera(deck, scelta);
            break;
        case 2:
            do {
                int selezione = 0;          //tessera selezionata per il posizionamento
                do {
                    printf("Selezionare la tessera da inserire tra 1 e %d: \n", scelta);
                    scanf("%d", &selezione);
                }while(selezione < 1 || selezione > scelta);
                selezioneTessera(selezione);                   //da cambiare se l'altra va
                arrayInserimento[0] = tessereDeck[selezione];           //popolo la prima posizione
                arrayInserimento[1] = tessereDeck[selezione+1];         //popolo la seconda posizione
                //CASO 0 DI ARRAY CAMPO VUOTO
                if(tessereCampo[0] == 0) {
                    tessereCampo[0] = arrayInserimento[0];
                    tessereCampo[1] = arrayInserimento[1];
                    //STAMPA DEL TERRENO
                    stampaTerreno(tessereCampo, scelta);
                    //RIMOZIONE TESSERE DAL DECK
                    break;
                }
                //INSERIMENTI POST PRIMO
                printf("Dove si vuole inserire la tessera? \n"
                       "1. Destra \n"
                       "2. Sinistra \n");
                scanf("%d", &mossa);
                if(mossa == 1) {
                    //inserimento a dx
                }
                else {
                    //inserimento a sx
                }
            }while(mossa != 1 && mossa != 2);
            break;
        case 3:
            do {
                printf("Abbandonare la partita (1) o lasciar completare l'AI (2)? \n");
                scanf("%d", &mossa);
                if(mossa == 1) {
                    //calcolo del punteggio e fine
                }
                else {
                    //implementazione AI
                }
            }while(mossa != 1 && mossa != 2);
    }
    return 0;
}
