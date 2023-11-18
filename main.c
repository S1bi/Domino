#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int scelta = 0;

int selezioneTessera(int a)
{ // fa la selezione del giusto indice (basta dargli in input la variabile da cambiare)
    return a * 2 - 2;
}

void stampaSelezione(int *sel)
{
    printf("[%d|%d]", sel[0], sel[1]);
}

void genTessere(int *deck, int nTessere)
{
    for (int i = 0; i < nTessere * 2; i++)
    {
        srand(time(NULL) * i + time(NULL));
        int r = rand() % 6000;  // creazione numero random tra 1 e 6
        deck[i] = r / 1000 + 1; // inserimento numero per numero in array mano
    }
}

void stampaDeck(int *tessereDeck)
{ // lettura e formattazione dell'array
    printf("DECK: \n");
    for (int i = 0; i < scelta * 2; i = i + 2)
    {
        if (tessereDeck[i] != 0)
            printf("[%d|%d]", tessereDeck[i], tessereDeck[i + 1]); // stampa delle tessere una a una
    }
    printf("\n");
}

void stampaTerreno(int *terreno, int dim)
{
    printf("CAMPO: \n");
    for (int i = 0; i < dim * 2; i = i + 2)
    {
        if (terreno[i + 1] != 0)                           // così non stampa le caselle vuote
            printf("[%d|%d]", terreno[i], terreno[i + 1]); // stampa delle tessere una a una
    }
    printf("\n");
}

void ruotaTessera(int *tessereDeck, int pos, int *arraySel)
{
    selezioneTessera(pos);                   // seleziono il primo valore della tessera scelta (usare anche per scelta tessera da inserire)
    int temp = tessereDeck[pos];             // variabile d'appoggio
    tessereDeck[pos] = tessereDeck[pos + 1]; // tessera selezionata = val successivo
    tessereDeck[pos + 1] = temp;             // tessera successiva alla selezionata cambiata
    arraySel[0] = tessereDeck[pos];
    arraySel[1] = tessereDeck[pos + 1];
    stampaSelezione(arraySel);
}

int ultimaTessera(int *array, int dim)
{ // trova la posizione dell'ultima tessera dell'array
    for (size_t i = 0; i < dim; i++)
    {
        if (array[i] == 0)
        {
            return i - 1;
        }
    }
    return 0; // funzionante
}

void rimuoviUtilizzo(int pos, int *deck)
{
    deck[pos] = 0;
    deck[pos + 1] = 0;
}

void inserisciDestra(int *selezione, int *tabellone, int dim, int pos, int *deck)
{
    int ultimaTess = ultimaTessera(tabellone, dim);
    if (selezione[0] == tabellone[ultimaTess])
    {
        tabellone[ultimaTess + 1] = selezione[0];
        tabellone[ultimaTess + 2] = selezione[1];
        rimuoviUtilizzo(pos, deck);
    }
    else
    {
        printf("La tessera non corrisponde, provare a ruotarla o cambiare tessera \n");
    }
    stampaTerreno(tabellone, dim);
    stampaDeck(deck);
}

void inserisciSinistra(int *selezione, int *tabellone, int dim, int pos, int *deck)
{
    if (selezione[1] == tabellone[0])
    {
        for (size_t i = dim - 3; i != -1; i--)
        {
            tabellone[i + 2] = tabellone[i];
        }
        tabellone[0] = selezione[0];
        tabellone[1] = selezione[1];
        rimuoviUtilizzo(pos, deck);
    }
    else
    {
        printf("La tessera non corrisponde, provare a ruotarla o cambiare tessera \n");
    }
    stampaTerreno(tabellone, dim);
    stampaDeck(deck);
}

int main()
{
    int annulla = 0;            // operazione annulla ciclo
    int arraySelezione[2];      // array di gestione delle tessere da inserire
    do
    {
        printf("BENVENUTO NEL GIOCO DEL DOMINO! \n"
               "Seleziona la difficoltà: \n"
               "1. Facile (14 tessere);\n"
               "2. Normale (28 tessere);\n"
               "3. Difficile (36 tessere);\n"
               "4. Manuale (scegli il tuo numero di tessere). \n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 4);

    switch (scelta)
    {
    case 1:
        scelta = 14;
        break;
    case 2:
        scelta = 28;
        break;
    case 3:
        scelta = 36;
        break;
    default:
        printf("Seleziona il numero di tessere: ");
        scanf("%d", &scelta);
        break;
    }
    int tessereDeck[scelta * 2];
    int *deck = &tessereDeck; // puntatore array deck
    genTessere(deck, scelta);
    int tessereCampo[scelta * 2];
    for (int i = 0; i < scelta * 2; i++)
        tessereCampo[i] = 0;
    printf("IL GIOCO HA INIZIO \n Le tue tessere sono: \n");
    stampaDeck(deck);

    // INIIZIALIZZAZIONE CAMPO A SCOPO DI PROGETTAZIONE
    tessereCampo[0] = 1;
    tessereCampo[1] = 5;

    // stampo il terreno per far scegliere la mossa
    stampaTerreno(tessereCampo, scelta);

    int selezione = 0;
    do
    {
        printf("\nSelezionare la tessera su cui operare tra 1 e %d: \n", scelta);
        scanf("%d", &selezione);
    } while (selezione < 1 || selezione > scelta);
    int posTessera = selezioneTessera(selezione); // tessera selezionata dall'utente
    arraySelezione[0] = tessereDeck[posTessera];  // popolo la prima posizione
    arraySelezione[1] = tessereDeck[posTessera + 1];
    int *puntSel = arraySelezione;
    stampaSelezione(puntSel);
    // IMPLEMENTARE METODO DI CONTROLLO PER FINE PARTITA (CICLO PER SCELTA MOSSA)

    int mossa = 0;

    do
    {
        printf("\nScegliere la prossima mossa: \n"
               "1. Rotazione; \n"
               "2. Inserimento; \n"
               // POSSIBILE FUNZIONE AIUTO(?)
               "3. Annulla; \n");
        scanf("%d", &mossa);
    } while (mossa > 3 || mossa < 1); // controllo l'input utente
    switch (mossa)
    { // switch case di selezione della mossa
    case 1:
        ruotaTessera(deck, posTessera, puntSel);
        break;
    case 2:
        // CASO 0 DI ARRAY CAMPO VUOTO
        /* if (tessereCampo[0] == 0)
        {
            tessereCampo[0] = arraySelezione[0];
            tessereCampo[1] = arraySelezione[1];
            // STAMPA DEL TERRENO
            stampaTerreno(tessereCampo, scelta);
            // RIMOZIONE TESSERE DAL DECK
            rimuoviUtilizzo(puntSel);
            break;
        } */
        // INSERIMENTI POST PRIMO

        do
        {
            printf("Dove si vuole inserire la tessera? \n"
                   "1. Destra \n"
                   "2. Sinistra \n");
            scanf("%d", &mossa);
            if (mossa == 1)
            {
                inserisciDestra(puntSel, tessereCampo, scelta, posTessera, deck);
            }
            else
            {
                inserisciSinistra(puntSel, tessereCampo, scelta, posTessera, deck);
            }
        } while (mossa != 1 && mossa != 2);
        break;
    case 3:
        annulla = 1; // da implementare poi per i cicli
        printf("Operazione annullata, ritorno al tuo deck: \n");
        stampaDeck(deck);
        return 0;
    }
}